//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FireDAC.Phys.CDataGmail"
#pragma link "FireDAC.Phys.CDataGmailDef"
#pragma link "FireDAC.Phys.CDataGmail"
#pragma link "FireDAC.Phys.CDataGmailDef"
#pragma resource "*.dfm"

// Application->HandleMessage(); 
//std::unique_ptr<TSimpleEvent> FSyncEvent = std::make_unique<TSimpleEvent>(true);
//std::unique_ptr<TThreadProcessor> FThreadProcessor = std::make_unique<TThreadProcessor>(false);
//std::unique_ptr<TCriticalSection> FSyncLock = std::make_unique<TCriticalSection>();

std::unique_ptr<TEvent> FSyncEvent = std::make_unique<TEvent>(false);

TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	try
	{
		Application->OnException = HandleGlobalException;

		originalHeight = this->Height; 
		originalWidth = this->Width; 
		
		FDManager->Active=true;
		
		QboConnectionProfiles = std::make_unique<std::map<String, QboConnectionInfo>>();
		
		SetupPgConnectionProfile();
		
		Application->OnException = TerminalFailure;

		FNow = DateTimeToStr(Now());
		StatusTimer->Enabled=true;

		FAppPath = ExtractFilePath(Application->ExeName);
		SetupLogFile();

		FServerStartTime     = Now();
		FSchedulerStartTime  = GetTime();
		FCleanupTime 		 = FSchedulerStartTime;
		FSystemCheckInterval = FSchedulerStartTime;
		
		ServerTimeLbl->Caption 		= DateTimeToStr(FServerStartTime);
		DBConnectionsLbl->Caption 	= IntToStr(FConnections);

		FExceptions = 0;
		FSystemChecks=0;
		FCustInsertions=0;
		FInvInsertions=0;
		FSystemCheckInterval = 0;
		FServerStarted=false;
		FErrorIndicator = false;

		FSyncEvent->ResetEvent();

		String threaded = System::IsMultiThread ? "TRUE" : "FALSE";
		
		Log("Application Started");
		Log("System Is Threaded: " + threaded);
		Log("Processor Count: " + IntToStr(TThread::ProcessorCount));
		Log("Thread Count: " + IntToStr(CPUCount));


	} catch (const Exception &exception) {
		ShowMessage("In MainForm ctor: " + exception.Message );
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// BEGIN SYSTEM METHODS
//---------------------------------------------------------------------------
void __fastcall TMainForm::WndProc(TMessage &Message)
{
	if (Message.Msg == WM_NCLBUTTONDBLCLK)
	{
		if (isMinimized)
		{
			// Restore to original dimensions
			this->Height = originalHeight;
			this->Width = originalWidth;
			isMinimized = false;
		}
		else
		{
			// Minimize to the size of the title bar
			this->Height = GetSystemMetrics(SM_CYCAPTION);
			this->Width = originalWidth;
			isMinimized = true;
		}
		return;
	}
	TForm::WndProc(Message);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HandleGlobalException(TObject *Sender, Exception *E)
{
	Log("Application handled a global error: " + E->Message);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UpdateColumnContents(const String Contents, bool Clear)
{
	if(Clear)
		ColumnMemo->Clear();
		
	ColumnMemo->Lines->Add(Contents);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SetupPgConnectionProfile()
{
	try
	{
		std::unique_ptr<TStrings> oParams = std::make_unique<TStringList>();
		
		FDPhysPgDriverLink->VendorLib = PG_VENDOR_LIB; // 64 bit

#ifdef _CON_REMOTE_
		//  On remote AWS Windows Server
		oParams->Add("DriverID=PG"); 
		oParams->Add("Server=3.233.80.167");  
		oParams->Add("Port=5433"); 
		oParams->Add("Database=janview"); 
		oParams->Add("User_Name=postgres"); 
		oParams->Add("Password=md241"); 
		oParams->Add("CharacterSet=utf8"); 
		oParams->Add("Pooling=true;"); 
		oParams->Add("ExtendedMetadata=true");
#else                                                                                          
		// On localhost
		oParams->Add("Server=127.0.0.1");  
		oParams->Add("Port=5433"); 
		oParams->Add("Database=janview"); 
		oParams->Add("User_Name=postgres"); 
		oParams->Add("Password=md241"); 
		oParams->Add("CharacterSet=utf8"); 
		oParams->Add("Pooling=true;"); 
		oParams->Add("ExtendedMetadata=true");
#endif
		FDManager->AddConnectionDef("PG", "PG", oParams.get());

		oParams->Clear();
		FConnections = FDManager->ConnectionCount;

	}
	catch(const Exception &exception)
	{
		ExceptionThrown("[0x0A]:[SETUPFDMANAGER]: " + exception.Message);
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetQboProfileConnections()
{
	try
	{
		MainForm->Log("Creating Qbo Connection");

		std::unique_ptr<TFDConnection> PgProfileConnection{std::make_unique<TFDConnection>(nullptr)};
		PgProfileConnection->ConnectionDefName="PG";
		PgProfileConnection->Connected=true;
		std::unique_ptr<TFDQuery> qryPgProfileQuery{std::make_unique<TFDQuery>(nullptr)};

		qryPgProfileQuery->SQL->Text = "select * from admin_qbo_profile_controller";
		qryPgProfileQuery->Open();

		while(!qryPgProfileQuery->Eof)
		{
			String profileCompanyId = qryPgProfileQuery->FieldByName("profile_client_id")->AsString;
			String profilePath = qryPgProfileQuery->FieldByName("profile_cache_path")->AsString;
			String profileName = qryPgProfileQuery->FieldByName("profile_name")->AsString;

			QboConnectionInfo connInfo{profileCompanyId, profilePath};

			(*QboConnectionProfiles)[profileName] = connInfo;

			SetupQuickbooksConnection(profileName);

			qryPgProfileQuery->Next();
		}
	}
	catch(const Exception &exception)
	{
		ExceptionThrown("[0x0A]:[SETUPFDMANAGER]: " + exception.Message);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetupQuickbooksConnection(const String &ProfileConnName)
{
    try
    {
		auto oParams = std::make_unique<TStringList>();
		
		const auto& profile = (*QboConnectionProfiles)[ProfileConnName];
		
		String ProfileCachePath = profile.CachePath;
		
		const String OAuthSettingsPath = System::Sysutils::IncludeTrailingPathDelimiter(QBO_BASE_PATH + "\\" + ProfileCachePath) + "OAuthSettings.txt";
        const String LocationPath = System::Sysutils::IncludeTrailingPathDelimiter(QBO_BASE_PATH + "\\" + ProfileCachePath) + "QuickBooksOnline Data Provider\\Schema";
		const String CacheLocationPath = System::Sysutils::IncludeTrailingPathDelimiter(QBO_BASE_PATH + "\\" + ProfileCachePath) + "QuickBooksOnline Data Provider";
		
        oParams->Add("DriverId=CDataQuickBooksOnline");
        oParams->Add("CompanyId=" + profile.ClientId);
        oParams->Add("InitiateOAuth=GETANDREFRESH");
        oParams->Add("UseSandbox=false");
        oParams->Add("OAuthSettingsLocation=" + OAuthSettingsPath);
        oParams->Add("Location=" + LocationPath);
        oParams->Add("CacheLocation=" + CacheLocationPath);
		oParams->Add("IncludeCustomFields=true");
        oParams->Add("ReadOnly=false");
        oParams->Add("RTK=524E464A41415355465041413153554241474B454539323700000000000000000000000000000000374E46545550594100004E3553565535354E544D394B0000");
        oParams->Add("AutoCache=false");
		FDManager->AddConnectionDef(ProfileConnName, "CDataQuickBooksOnline", oParams.get());
		
        FConnections = FDManager->ConnectionCount;
    }
	catch(const Exception &exception)
    {
        ExceptionThrown("[0x0A]:[SETUPFDMANAGER]: " + exception.Message);
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::SetLastRetrieveTimeClick(TObject *Sender)
{
	CustomerTaskForm->SetLastRetrievalTime();
	InvoiceTaskForm->SetLastRetrievalTime();                                                             
}
//---------------------------------------------------------------------------

// Thread safe Logging
//---------------------------------------------------------------------------
void __fastcall TMainForm::Log(String logStr)
{
	TThread::Queue(NULL, [this, logStr]() -> void { 	
		String nowLog = " [" + FNow + "]: " + logStr;
		Memo->Lines->Append(nowLog);
		nowLog += sLineBreak;
		FLogFile->Write(nowLog.BytesOf() , nowLog.Length());
	});
}

// Thread safe Exception reporter
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExceptionThrown(const String exceptionStr)
{
	TThread::Queue(NULL, [this, exceptionStr]() -> void {
		FErrorIndicator=true;
		String nowLog = "[" + FNow + "]: " + exceptionStr + sLineBreak;
		ExceptionCountLbl->Caption = IntToStr( ++FExceptions );
		Memo->Lines->Append(nowLog);
		FErrorIndicator=true;
		FLogFile->Write(nowLog.BytesOf() , nowLog.Length());
	});
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StateAliveIndicator()
{
	if(!FServerStarted || FErrorIndicator)
	{
		RunningIndicator->Brush->Color == clRed ?  RunningIndicator->Brush->Color = clMaroon :  
			RunningIndicator->Brush->Color = clRed;
	}
	else {
		RunningIndicator->Brush->Color == clGreen ?  RunningIndicator->Brush->Color = clLime :  
			RunningIndicator->Brush->Color = clGreen;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearLblBtnClick(TObject *Sender)
{
	Memo->Clear();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetupLogFile()
{
	try
	{
		TDirectory::SetCurrentDirectory(FAppPath);
		
		if (!TDirectory::Exists("data")) {
			TDirectory::CreateDirectory("data");
		}

		TDirectory::SetCurrentDirectory("data");

		if(!FileExists(LOG_FILE_NAME))
		{
			int handle = FileCreate(LOG_FILE_NAME);
			FileClose(handle);
		}
	
		FLogFile = std::make_unique<TBufferedFileStream>(LOG_FILE_NAME, fmOpenReadWrite);
	}
	catch(const Exception &exception)
	{
		ExceptionThrown("[0x0A]:[SETUPLOGS]: " + exception.Message);
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CleanupLogFile()
{
	TStream* NewFileS;
	try
	{
		if(FLogFile)
		{
			FLogFile.reset();
			
			std::unique_ptr<TStringBuilder> NameBuilder = std::make_unique<TStringBuilder>();
			NameBuilder->Append(FormatDateTime("mmddyyyy", Now()))->Append("_")->Append(LOG_FILE_NAME);
			String BackupFileName = NameBuilder->ToString();


			NewFileS = TFile::Create(BackupFileName);
			delete NewFileS;
			
			TFile::Copy(LOG_FILE_NAME, BackupFileName, true);
			String newBak = ChangeFileExt(BackupFileName, L".BAK");
			RenameFile(BackupFileName, newBak);

            // After rotation create new log file
			FLogFile = std::make_unique<TBufferedFileStream>(LOG_FILE_NAME, fmOpenReadWrite);

			Memo->Clear();
		}

	}
	catch(const Exception &exception) 
	{
		ExceptionThrown("[0x0A]:[CLEANINGFILES]: " + exception.Message);
		if(NewFileS)
			delete NewFileS;
	}

}

void __fastcall TMainForm::GetConnectionsBtnClick(TObject *Sender)
{
	Log("Active Database Connections: " + IntToStr(FDManager->ConnectionCount) );
	DBConnectionsLbl->Caption = IntToStr(FDManager->ConnectionCount);
}
//---------------------------------------------------------------------------
// END SYSTEM METHODS
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  TIMER EVENTS
//---------------------------------------------------------------------------
void __fastcall TMainForm::StatusTimerTimer(TObject *Sender)
{
	FNow = Now();
	StatusBar->Panels->Items[0]->Text = DateTimeToStr(Now());
	TTime time = GetTime();
	// Log rotate every 12 hours
	if( MinutesBetween( time, FCleanupTime ) > 720 )    // Every 12 hours
	{
		FCleanupTime = time;
		CleanupLogFile();
		Log( "[FIRED_CLEANUP]:[LOG_FILE_BACKUP]"  );
	}

	// Check FDManager count
	if( MinutesBetween( time, FSystemCheckInterval ) > 240 )   // Every 4 hours
	{
		FSystemCheckInterval = time;
		IterationsLbl->Caption=IntToStr(FSystemChecks++);
		FConnections = FDManager->ConnectionCount;
		DBConnectionsLbl->Caption = IntToStr(FConnections);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ServerRunLblClick(TObject *Sender)
{
	if(FServerStarted)
	{
		DBConnectionsLbl->Caption = IntToStr(FConnections);
		ServerRunTimeLbl->Caption = FormatDateTime("hh:nn:ss", Now() - FServerStartTime);
	}
}

void __fastcall TMainForm::ThreadStateLblClick(TObject *Sender)
{
	FErrorIndicator=false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMainForm::ServerTimerTimer(TObject *Sender)
{
	StateAliveIndicator();	
	ExceptionCountLbl->Caption = IntToStr(FExceptions);
	if(Memo->Lines->Count > 1000)
		Memo->Clear();
}
//---------------------------------------------------------------------------
//  TIMER EVENTS END
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// SCHEDULER THREAD METHODS
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartSchedulerBtnClick(TObject *Sender)
{
	CustomerTaskForm->StartThread();
//	InvoiceTaskForm->StartThread();
	StopTimerBtn->Enabled=true;
	StartSchedulerBtn->Enabled=false;
	ServerTimer->Enabled=true;
	FServerStarted=true;
	RunningIndicator->Brush->Color = clGreen;
	FServerStartTime=GetTime();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StopTimerBtnClick(TObject *Sender)
{
	CustomerTaskForm->StopThread();
//	InvoiceTaskForm->StopThread();

	FErrorIndicator=false;
	ServerTimer->Enabled=false;
	StartSchedulerBtn->Enabled=true;
	StopTimerBtn->Enabled=false;
	RunningIndicator->Brush->Color = clRed;
}

void __fastcall TMainForm::IncrementInsertCount(int Id)
{
	switch (Id) {
		case CUSTOMER:
			CustInsertsLbl->Caption=IntToStr(++FCustInsertions);
			break;
		case INVOICE:
			InvInsertLbl->Caption=IntToStr(++FInvInsertions);
			break;
	default:
		break;
	}                                    
}
//---------------------------------------------------------------------------
// SCHEDULER THREAD METHODS END
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// GENERAL UI/APP METHODS
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitClick(TObject *Sender)
{
	  Beep();      
	  Beep();      
	  Application->Terminate();	
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExtBtnClick(TObject *Sender)
{
	  Beep();      
	  Beep();      
	  Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TerminalFailure(TObject* Sender, Exception* e)
{
	Application->ShowException(e);
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ResizeGrid(TDBGrid* Grid)
{
	for (int idx = 0; idx < Grid->Columns->Count - 1; idx++) {
		Grid->Fields[idx]->DisplayWidth = 7;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ForceLogRotBtnClick(TObject *Sender)
{
	CleanupLogFile();
	MainForm->Log("[FORCEDFILECLEANUP]");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowCustThreadViewClick(TObject *Sender)
{
	if(!CustomerTaskForm->Visible)
	{
		CustomerTaskForm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowInvThreadViewClick(TObject *Sender)
{
	if(!InvoiceTaskForm->Visible)
	{
		InvoiceTaskForm->Show();
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowPymtThreadViewClick(TObject *Sender)
{
	if(!PaymentTaskForm->Visible)
	{
		PaymentTaskForm->Show();
	}
	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AdHocQryBtnClick(TObject *Sender)
{
	AdHocQuery->Show();	
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewAllFields(TFDQuery *Query, TMemo* Memo)
{
	int i;
	try
	{
		Query->Open();
		while(Query->Eof)
		{
			for(int ndx=0; ndx < Query->Fields->Count - 1; ndx++)
			{
				Memo->Lines->Add(Query->Fields->Fields[ndx]->FieldName);
				Memo->Lines->Add(Query->Fields->Fields[ndx]->AsString);
				Memo->Lines->Add(IntToStr(Query->Fields->Fields[i]->DataSize));
			}
		}
		Query->Next();
	}
	__finally 
	{
		Query->Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::UpdateDataSetFieldAsString(TFDQuery *Destination, String field, int value)
{
//	if(FDefaultConnnected) 
//	{
		TFDQuery* DestinationPtr = Destination;
		int recs = DestinationPtr->RecordCount;
		try {
			DestinationPtr->Open();
			DestinationPtr->First();
			while (!DestinationPtr->Eof) {
				DestinationPtr->Edit();
				DestinationPtr->FieldByName(field)->AsString = IntToStr(value++);
				DestinationPtr->Post();
				DestinationPtr->Next();
			}
			DestinationPtr->Close();
		}
		catch (const Exception &e) {
			MainForm->ExceptionThrown("[0x0A]:[UPDATEDATSET]: " + e.Message);
			DestinationPtr->Close();
		}
//	}
}

