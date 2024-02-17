//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH 

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.ConsoleUI.Wait.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.AppEvnts.hpp>
#include <System.IOUtils.hpp>
#include <System.DateUtils.hpp>
#include <Vcl.ExtActns.hpp>

#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.Menus.hpp>
#include "FireDAC.Phys.CDataGmail.hpp"
#include "FireDAC.Phys.CDataGmailDef.hpp"
#include <IPPeerClient.hpp>
#include <IPPeerServer.hpp>
#include <System.Tether.AppProfile.hpp>
#include <System.Tether.Manager.hpp>
#include <System.Tether.Manager.hpp>
#include <System.Tether.AppProfile.hpp>
#include "FireDAC.Phys.CDataGmail.hpp"
#include "FireDAC.Phys.CDataGmailDef.hpp"

#include "GInterfaces.h"
#include "TCustomerTaskForm.h"
#include "TPaymentHandler.h"
#include "TTaxRateHandler.h"
#include "TInvoiceHandler.h"
#include "TAdHocQuery.h"
#include "TInvoiceTaskForm.h"
#include "TPaymentTaskForm.h"

//#include "IEntityHandlerBase.h"
//#include <IPPeerClient.hpp>
//#include <IPPeerServer.hpp>




//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox2;
	TLabel *ServerRunLbl;
	TLabel *ServerRunTimeLbl;
	TLabel *Label5;
	TLabel *IterationsLbl;
	TLabel *Label4;
	TLabel *DBConnectionsLbl;
	TGroupBox *GroupBox1;
	TTimer *StatusTimer;
	TTimer *ServerTimer;
	TPanel *Panel2;
	TStatusBar *StatusBar;
	TButton *ClearLblBtn;
	TLabel *ExceptionCountLbl;
	TLabel *Label3;
	TPanel *Panel3;
	TShape *RunningIndicator;
	TCheckBox *FileLogChk;
	TPanel *Panel5;
	TLabel *ThreadStateLbl;
	TButton *ForceLogRotBtn;
	TButton *ShowCustThreadView;
	TButton *ShowInvThreadView;
	TPanel *BottomPnl;
	TFDGUIxWaitCursor *FDGUIxWaitCursor1;
	TFDManager *FDManager;
	TButton *GetCconnectionsBtn;
	TLabel *Label7;
	TLabel *ServerTimeLbl;
	TFDPhysPgDriverLink *FDPhysPgDriverLink;
	TTetheringManager *TetheringManager;
	TTetheringAppProfile *TetheringAppProfile;
	TMemo *Memo;
	TButton *AdHocQryBtn;
	TButton *SetLastRetrieveTime;
	TLabel *Label1;
	TLabel *CustInsertsLbl;
	TMainMenu *MainMenu1;
	TMenuItem *Exit1;
	TMenuItem *Exit;
	TGroupBox *GroupBox3;
	TButton *StartSchedulerBtn;
	TButton *StopTimerBtn;
	TLabel *InvInsertLbl;
	TLabel *Label9;
	TButton *ShowPymtThreadView;
	TButton *SetupTableBtn;
	TFDPhysCDataGmailDriverLink *FDPhysCDataGmailDriverLink1;
	TFDConnection *FDGmailConnection;
	TMemo *ColumnMemo;
	TGroupBox *GroupBox4;
	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall ServerTimerTimer(TObject *Sender);
	void __fastcall ClearLblBtnClick(TObject *Sender);
	void __fastcall StartSchedulerBtnClick(TObject *Sender);
	void __fastcall StopTimerBtnClick(TObject *Sender);
	void __fastcall ExtBtnClick(TObject *Sender);
	void __fastcall ForceLogRotBtnClick(TObject *Sender);
	void __fastcall ShowCustThreadViewClick(TObject *Sender);
	void __fastcall ShowInvThreadViewClick(TObject *Sender);
	void __fastcall GetConnectionsBtnClick(TObject *Sender);
	void __fastcall AdHocQryBtnClick(TObject *Sender);
	void __fastcall SetLastRetrieveTimeClick(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall ServerRunLblClick(TObject *Sender);
	void __fastcall ThreadStateLblClick(TObject *Sender);
	void __fastcall ShowPymtThreadViewClick(TObject *Sender);

private:	// User declarations

 	void __fastcall HandleGlobalException(TObject *Sender, Exception *E);
	void __fastcall StoreRetrievalSettings();
	void __fastcall AsyncFetchInvoices();
	void __fastcall AsyncFetchCustomers();
	void __fastcall AsyncFetchPayments();	
	void __fastcall AsyncFetchTaxes();	

	void __fastcall StateAliveIndicator();
	void __fastcall CleanupLogFile();	
	void __fastcall SetupLogFile();

	void __fastcall SetupPgConnectionProfile();
	void __fastcall SetupQuickbooksConnection(const String &ProfileConnName);
	void __fastcall SetQboProfileConnections();
	void __fastcall TerminalFailure(TObject* Sender, Exception* e);
	
	int 	FCompanyId{0};	
	int 	FExceptions{0};
	int 	FConnections{0};
	int 	FSystemChecks{0};
	int		FErrorLevel{0};
	int		FCustInsertions{0};
	int		FInvInsertions{0};
	bool	FServerStarted{false};
	bool	FErrorIndicator{false};

	std::unique_ptr<std::map<String, QboConnectionInfo>> QboConnectionProfiles;

	bool 	isMinimized {false};
	int 	originalHeight{0};
	int 	originalWidth{0};

	std::unique_ptr<TFileStream> FLogFile;
	
	TDateTime	FServerStartTime;
	TTime 		FCleanupTime;
	TTime 		FSystemCheckInterval;
	TDateTime 	FSchedulerStartTime;
	String 		FNow{""};
	String		FAppPath{""};

	void __fastcall WndProc(TMessage &Message);
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

//---------------------------------------------------------------------------
	void __fastcall Log(const String logStr);
	void __fastcall ExceptionThrown(const String exceptionStr);

	void __fastcall UpdateColumnContents(const String Contents, bool Clear);
	
	void __fastcall Execute();
	
	void __fastcall StopExecution();
	void __fastcall StartScheduler();
	void __fastcall ResizeGrid(TDBGrid* Grid);

	void __fastcall IncrementInsertCount(int Id);
	void __fastcall PgEventAlerterAlert(TFDCustomEventAlerter *ASender, const UnicodeString AEventName, const Variant &AArgument);

	void __fastcall ViewAllFields(TFDQuery *Query, TMemo* Memo);

	void __fastcall UpdateDataSetFieldAsString(TFDQuery *Destination, String field, int value);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
