//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("TMainForm.cpp", MainForm);
USEFORM("Forms\TAdminTaskForm.cpp", AdminTaskForm);
USEFORM("Forms\TAdHocQuery.cpp", AdHocQuery);
USEFORM("Forms\SetupTablesFromQbo.cpp", SetupTablesForm);
USEFORM("Forms\TCustomerTaskForm.cpp", CustomerTaskForm);
USEFORM("Forms\TTimedErrorMessage.cpp", ExceptionForm);
USEFORM("Forms\TPaymentTaskForm.cpp", PaymentTaskForm);
USEFORM("Forms\TInvoiceTaskForm.cpp", InvoiceTaskForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "JvpAdminController";
		TStyleManager::TrySetStyle("Slate Classico");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TCustomerTaskForm), &CustomerTaskForm);
		Application->CreateForm(__classid(TInvoiceTaskForm), &InvoiceTaskForm);
		Application->CreateForm(__classid(TAdHocQuery), &AdHocQuery);
		Application->CreateForm(__classid(TPaymentTaskForm), &PaymentTaskForm);
		Application->CreateForm(__classid(TSetupTablesForm), &SetupTablesForm);
		Application->CreateForm(__classid(TAdminTaskForm), &AdminTaskForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
