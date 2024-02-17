#ifndef GInterfacesH
    #define GInterfacesH

    #pragma once

    #include <memory>
    #include <mutex>
    #include <vector>
    #include <map>
    #include <tuple>
    #include <any>
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <chrono>
    #include <thread>
    #include <future>
    #include <time.h>
    #include <stdlib.h>
    #include <time.h>

	#include <System.SysUtils.hpp>
	#include <Data.DBJson.hpp>
    #include <System.Hash.hpp>
    #include <System.JSON.hpp>
    #include <Data.DB.hpp>
    #include <System.SyncObjs.hpp>
	#include <FireDAC.Stan.Error.hpp>
    #include <FireDAC.Phys.PGWrapper.hpp>
    #include <FireDAC.Comp.Client.hpp>

    #include <xmldom.hpp>
    #include <XMLIntf.hpp>
    #include <msxmldom.hpp>

//----------------------------------------------------------------------------
//       6$ervices#1Guy@home
//******************************************
//
// Some Rad Classes from Embacadero
//
// TQuerySerializer
//
// TJSONToDataSetBridge
//
//************************************

    #ifndef _CON_REMOTE_
        #define _CON_REMOTE_
    #endif

    #ifndef __DEBUG_
        #define __DEBUG_
    #endif

//#undef _CON_REMOTE_  //Comment this out for local RAD Server

//#undef _D_DEBUG_

//----------------------------------------------------------------------------

// Use 'extern'  to allow FSyncEvent to be available in all units but allocate it elsewhere.
extern std::unique_ptr<TEvent> FSyncEvent;
extern std::unique_ptr<TCriticalSection> FSyncLock;

inline const unsigned SUPER_MODE = 0x01;
inline const unsigned USER_MODE = 0x02;
inline const unsigned ADMIN_MODE = 0x04;

inline const int CUSTOMER = 1;
inline const int INVOICE = 2;

inline const String PG_VENDOR_LIB = "C:\\PGSql\\PG64\\libpq.dll";
inline const String LOG_FILE_NAME = "jvpserver.log";

inline const String DEFAULT_PG_INVOICE_SELECT{"SELECT * FROM franchise_invoice" };
inline const String DEFAULT_QBO_INVOICE_SELECT{"SELECT * FROM Invoices" };

inline const String QBO_BASE_PATH { "C:\\Data\\Qbo" };

struct QboConnectionInfo
{
    String ClientId;
    String CachePath;
    QboConnectionInfo() = default; // Add default constructor
    QboConnectionInfo(const String &Id, const String &Path) :
        ClientId(Id), CachePath(Path)
    {
    }
};

// RTL
const TSysCharSet GNumbers = TSysCharSet() << '0' << '1' << '2' << '3' << '4'
                                           << '5' << '6' << '7' << '8' << '9';

//----------------------------------------------------------------------------------------------------------
inline bool seeded = false;
static String GetStringOfRandomLetters(int length)
{
    String result;

    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for (int i = 0; i < length; ++i) {
        char letter = 'A' + (rand() % 26); // Random capital letter
        result += String(letter);
    }

    return result;
}

// Function to generate a string of random digits
static String GetStringOfRandomDigits(int length)
{
    String result;

    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for (int i = 0; i < length; ++i) {
        char digit = '0' + (rand() % 10); // Random digit
        result += String(digit);
    }

    return result;
}

// Helper to convert TWaitResult into string.
static const String GetWaitResultMessage(TWaitResult waitResult)
{
    static const String waitResultMessages[] = { L"wrSignaled", L"wrTimeOut",
        L"wrAbandoned", L"wrError" };

    int index = static_cast<int>(waitResult);
    if (index >= 0 && index < 4) {
        return waitResultMessages[index];
    } else {
        return L"Unknown result occurred while waiting for the FSyncEvent!";
    }
}

//-----------------------------------------------------------------------------------

enum OperationType
{
    Customer,
    Invoice
};

struct Operation
{
    OperationType type;
    String AKey;
};

struct TData
{
    String customerId;
    String invoiceId;
};

typedef TData* TDataPtr;

//-----------------------------------------------------------------------------------
// Returns future
template<typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type> RunAsync(
    F &&f, Ts &&... params)
{
    return std::async(std::launch::async, // call to f(params...)
        std::forward<F>(f), std::forward<Ts>(params)...);
}

//---------------------------------------------------------------------------

static TJSONObject* JsonValueToObject(TJSONValue* value)
{
    TJSONObject* jsonObj = new TJSONObject;
    TBytes jsonBytes = TEncoding::UTF8->GetBytes(value->ToString());
    jsonObj->Parse(jsonBytes, 0);
    return jsonObj;
}
//-----------------------------------------------------------------------------------

template<typename RepType = int, typename Period = std::ratio<1> >
void MinPause(int minutes)
{
    std::chrono::duration<RepType, Period> duration(minutes);
    std::this_thread::sleep_for(
        std::chrono::duration_cast<std::chrono::duration<RepType, Period> >(
            duration));
}
//-----------------------------------------------------------------------------------

template<typename RepType = int, typename Period = std::ratio<1> >
void SecPause(int seconds)
{
    std::chrono::duration<RepType, Period> duration(seconds);
    std::this_thread::sleep_for(
        std::chrono::duration_cast<std::chrono::duration<RepType, Period> >(
            duration));
}
//-----------------------------------------------------------------------------------

template<typename T>
std::string ValueToString(const T &value)
{
	std::ostringstream oss;
    oss << value;
    return oss.str();
}
//-----------------------------------------------------------------------------------


struct SJwCustomerSync
{
    int Id;
    String Name;
    String SyncToken;
    bool Edited;
};

struct SQboCustomerSync
{
    int Id;
    String Name;
    String SyncToken;
    bool Active;
};
//-----------------------------------------------------------------------------------

class TInvoice
{
  public:
    String id;
    String cid;
    String qbid;
    String terms;
    String created;
    String duedate;
    String invoicenum;
    String lineItem;
    String amountdue;
    String balance;

    __fastcall TInvoice() {}
    ~TInvoice() {}

    bool operator==(const TInvoice &rhsEmp)
    {
        return id == rhsEmp.id;
    }

    bool operator<(const TInvoice &rhsEmp)
    {
        return (CompareStr(id, rhsEmp.id) < 0) ? true : false;
    }
};
//-----------------------------------------------------------------------------------

class TPayment
{
  public:
    int id;
    int cid;
    int uid;
    int qbid;
    int invoicenum;
    float tax;
    float total_amount;
    float amount_due;
    String pymtmethod;
    String created;

    __fastcall TPayment() {}
    ~TPayment() {}

    bool operator==(const TPayment &rhsEmp)
    {
        return invoicenum == rhsEmp.invoicenum;
    }

    bool operator<(const TPayment &rhsEmp)
    {
        return (id < rhsEmp.id) ? true : false;
    }
};
//-----------------------------------------------------------------------------------

class TCustomer
{
  public:
    int id; // integer NOT NULL,
    int uid; // integer,
    String
        customer_name; // character varying(150) COLLATE pg_catalog."default",
    String first_name; // character varying(64) COLLATE pg_catalog."default",
    String last_name; // character varying(64) COLLATE pg_catalog."default",
    String address; // character varying(150) COLLATE pg_catalog."default",
    String suite; // character varying(25) COLLATE pg_catalog."default",
    String city; // character varying(150) COLLATE pg_catalog."default",
    String st; // character varying(25) COLLATE pg_catalog."default",
    String zip; // character varying(32) COLLATE pg_catalog."default",
    String email; // character varying(150) COLLATE pg_catalog."default",
    String
        mobile_number; // character varying(128) COLLATE pg_catalog."default",
    String
        office_number; // character varying(128) COLLATE pg_catalog."default",
    float tax; // numeric(4,3),
    float account_balance; // numeric(8,2),
    String
        preferred_pymt_method; // character varying(150) COLLATE pg_catalog."default",
    String
        ap_first_name; // character varying(150) COLLATE pg_catalog."default",
    String ap_last_name; // character varying(150) COLLATE pg_catalog."default",
    String ap_email; // character varying(150) COLLATE pg_catalog."default",
    String
        ap_office_number; // character varying(150) COLLATE pg_catalog."default",
    int visits_per_week; // integer,
    float monthly_contract_amount; // numeric(8,2),
    float proated_amount; // numeric(8,2),
    String
        initial_cleaning_duties; // character varying(512) COLLATE pg_catalog."default",
    String
        description_of_duties; // character varying(512) COLLATE pg_catalog."default",
    String
        marketing_source; // character varying(150) COLLATE pg_catalog."default",
    bool one_off_cleaning; // boolean,
    String notes; // COLLATE pg_catalog."default",
    String attachements; // bytea,
    String
        service_start_date; // character varying(25) COLLATE pg_catalog."default",
    bool marketing_fee; // boolean,
    String modfied_date; // character varying(25) COLLATE pg_catalog."default",
    String days_of_week; // character varying(50) COLLATE pg_catalog."default",
    bool active; // boolean,
    String qbo_id; // integer,
    float cc_merchant_fee; // numeric(5,2),
    String
        tax_exempt_reason; // character varying(50) COLLATE pg_catalog."default",
    bool taxable; // boolean,
    String created_date; // character varying(50) COLLATE pg_catalog."default",
    int cid; // integer,
    int terms; // integer,
    String display_name;
    String tax_code_ref;
    String fax_number;
    String fully_qualified_name;
    String customer_type_ref;
    String title_name;
    String sync_token;
    TDateTime deleted_date;
    bool edited;

    __fastcall TCustomer() {}
    ~TCustomer() {}

    bool operator==(const TCustomer &rhsEmp)
    {
        return cid == rhsEmp.cid;
    }

    bool operator<(const TCustomer &rhsEmp)
    {
        return (cid < rhsEmp.cid) ? true : false;
    }
};
//-----------------------------------------------------------------------------------

// Data context to be moved around for communications
class IContext
{
  public:
    virtual std::any __fastcall Context() = 0;
    virtual void __fastcall SetContext(std::any Data) = 0;
    virtual void __fastcall Reset() = 0;
};
//-----------------------------------------------------------------------------------

class ICommand
{
  public:
    virtual void ProcessCommand(const String Data) = 0;
};
//-----------------------------------------------------------------------------------

template<typename Func>
auto TimeFunc(Func f)
{
    auto begin = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    return ms.count;
}
//-----------------------------------------------------------------------------------

#endif

// std::this_thread::sleep_for(std::chrono::seconds(30));
// std::this_thread::sleep_for(std::chrono::milliseconds(500));

// Usage example:
// Assume `query` is a pointer to an already executed TFDQuery
// Record record(query);
// auto value = record.getFieldValue("someFieldName");

//enum TDirectionOption : unsigned char { diIn, ldiOut };
//
//class TDirection {
//public:
//
//	static const uint8_t diIn = 1 << 0;
//	static const uint8_t diOut = 1 << 1;
//
//private:
//	std::set<uint8_t> direction;
//
//public:
//	TDirection& operator<<(uint8_t dir) {
//		direction.clear(); // Clear previous values as we are only handling one direction
//		direction.insert(dir);
//		return *this;
//	}
//
//	// Method to check the current direction (assuming only one will be set)
//	uint8_t getCurrentDirection() const {
//		if (!direction.empty()) {
//			return *direction.begin();
//        }
//		return 0;
//    }
//};
// Usage
//TDirection direction;
//direction << TDirection::dIN;

//static String GetNodeValue(const String &xmlString, const String &nodeName)
//{
//    _di_IXMLDocument doc = IXMLDocument::Create(nullptr);
//    doc->DOMVendor = GetDOMVendor("MSXML");
//    doc->Options = doc->Options << doNodeAutoIndent;
//    doc->LoadFromXML(xmlString);
//
//    // Navigate to the LineEx node
//    _di_IXMLNode lineExNode = doc->DocumentElement->ChildNodes->FindNode("Row")->ChildNodes->FindNode("LineEx");
//    if (lineExNode != nullptr)
//    {
//        for (int i = 0; i < lineExNode->ChildNodes->Count; i++)
//        {
//            _di_IXMLNode nameValueNode = lineExNode->ChildNodes->Get(i);
//            if (nameValueNode->ChildNodes->FindNode("Name")->Text == nodeName)
//            {
//                return nameValueNode->ChildNodes->FindNode("Value")->Text;
//            }
//        }
//    }
//
//    return ""; // Return an empty string if not found
//}

//TBytesStream a stream that stores its data in bytes.
//
//static void SerializeObjectToFile(TStream* AStream, String AKey, TObject* AObject)
//{
//	int32_t objectSize = sizeof(AObject); // this should always be a 32 bit int
//
////	for (std::map<AKey, AObject *>::iterator i = AObject.begin(); i != AObject.end(); ++i)
////	for(std::map<Key,Val>::iterator iter = myMap.begin(); iter != myMap.end(); ++iter)
//	for (auto i = AObject->begin(); i != AObject->end(); ++i)
//	{
//		int32_t sizeStr = i->first.length() + 1; // this should always be a 32 bit int
//
//		AStream.write(&sizeStr, sizeof(sizeStr)); // 4 byte length of string
//		AStream.write(i->first.c_str(), sizeStr); // null terminated string
//
//		AStream.write(&sizeAccount, sizeof(objectSize)); // 4 byte size of object
//		AStream.write(i->second, objectSize);    // object data itself
//	}
//}

//	TCriticalSection *FLock;
//
//	void __fastcall Execute() {
//			Sleep(1000 * FValue);
//			FLock->Acquire();
//			printf("%-3d", FValue);
//			FLock->Release();
//	}
//

//	int handle;
//			handle = FileCreate(BackupFileName);
//			FileClose(handle);

//
//	std::unique_ptr<TCriticalSection> FLock = std::make_unique<TCriticalSection>();
//	try
//		{
//			_di_ITask SystmeCheckThread = TTask::Create([this, &FLock]()
//			{
//				while(true)
//				{
//					Log("[SYSTEMCHECK]: " + IntToStr(FSystemChecks));
//					FLock->Acquire();
//						FSystemChecks++;
//						IterationsLbl->Caption=IntToStr(FSystemChecks);
//						DBConnectionsLbl->Caption = IntToStr(FDManager->ConnectionCount);
//					FLock->Release();
//					Sleep(1800000);
//				}
//			});
//			SystmeCheckThread->Start();
//		}
//		catch(const Exception &exception)
//		{
//			ExceptionThrown("[0x0A]:[SYSCHK]: " + exception.Message);
//		}

//		MessageDlg(
//			"An error has occured!\n\nUNIT: ( GPDM ) MODULE: ( DMC )\n\n " +
//			e.ToString(), TMsgDlgType::mtError,
//			TMsgDlgButtons() << TMsgDlgBtn::mbOK, 0);

//
//		if( "PG" == FConnectionDefName )
//		{
//			FDPhysPgDriverLink->VendorLib = "C:\\PGSQL\\LIB\\libpq.dll"; // 64 bit
//
//			BaseConnection[FCurrentConnections]->ConnectionString=PG_CONNECTION_STRING;
//			BaseConnection[FCurrentConnections]->Connected=true;
//			FConnectionEstablished = BaseConnection[FCurrentConnections]->Connected;
//			MainForm->Log("Postgres Connected" + BoolToStr(FConnectionEstablished));
//		}
//		else if( "QBO" == FConnectionDefName )
//		{
//			oParams->Clear();
//			oParams->Add("DriverId=CDataQuickBooksOnline");
//			oParams->Add("CompanyId=9130356198669556" );
//			oParams->Add("InitiateOAuth=GETANDREFRESH");
//			oParams->Add("OAuthSettingsLocation=c:\\Data\\JWOauth\\OAuthSettings.txt");
//			oParams->Add("UseSandbox=false");
//			oParams->Add("Location=%APPDATA%\\CData\\QuickBooksOnline Data Provider\\Schema");
//			oParams->Add("CacheLocation=%APPDATA%\\CData\\QuickBooksOnline Data Provider");
//			oParams->Add("IncludeCustomeFields=true");
//			oParams->Add("ReadOnly=false");
//			oParams->Add("RTK=524E464841415355465041413153554241474B4545393237000000000000000000000000000000003131313131313131000058455A53395232584B3239560000");
//			oParams->Add("AutoCache=false");
//
//			ConnectionMgr->AddConnectionDef("CDataQuickBooksOnlineConn",
//				"CDataQuickBooksOnline", oParams);
//			BaseConnection[FCurrentConnections]->ConnectionDefName = "CDataQuickBooksOnlineConn";
//			BaseConnection[FCurrentConnections]->Connected=true;;
//			FConnectionEstablished = true;
//			MainForm->Log("QBO Connected" + BoolToStr(FConnectionEstablished));
//		}
//
//

//   TStream* stream1 = TFileStream::Create(From.Text,
//        fmOpenRead | fmShareDenyWrite);
//    try {
//        TStream* stream2->TFileStream::Create
//            (To.Text fmOpenCreate | fmShareDenyRead);
//        try {
//            stream2->CopyFrom(stream1, stream1->Size);
//        }
//        __finally {
//            delete stream2;
//        }
//    }
//    __finally {
//        delete stream1;
//	}

//class TResourceLogger
//{
//	static TResourceLogger* LoggerInstance;
//
//	std::unique_ptr<TJSONObject>  EException;
//	std::unique_ptr<TEMSLoggingService> Logger;
//
// public:
//	TResourceLogger() {
//		EException = std::make_unique<TJSONObject>();
//		Logger = std::make_unique<TEMSLoggingService>();
//	}
//
//	~TResourceLogger(){};
//
//	TResourceLogger(TResourceLogger &instance) = delete;
//    void operator=(const TResourceLogger &instance) = delete;
//
//	void Log(String Id, String Name, String Value)
//	{
//		EException->AddPair(Name, Value);
//		Logger->Log(Id, EException.get());
//		EException->RemovePair(Id);
//	}
//
//	void Log(String Id, String Value)
//	{
//		EException->AddPair(Id, Value);
//		Logger->Log(Id, EException.get());
//		EException->RemovePair(Id);
//
//
//	}
//
// 	void Log(String Id, int Value)
//	{
//		EException->AddPair(Id, Value);
//		Logger->Log(Id, EException.get());
//		EException->RemovePair(Id);
//
//	}
//
// };


