// CodeGear C++Builder
// Copyright (c) 1995, 2022 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'QboCustomer.pas' rev: 36.00 (Windows)

#ifndef QbocustomerHPP
#define QbocustomerHPP

#pragma delphiheader begin
#pragma option push
#if defined(__BORLANDC__) && !defined(__clang__)
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#endif
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <REST.Json.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Qbocustomer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPrimaryEmailAddr;
class DELPHICLASS TPrimaryPhone;
class DELPHICLASS TBillAddr;
class DELPHICLASS TMetaData;
class DELPHICLASS TCustomer_1;
class DELPHICLASS TCustomer;
class DELPHICLASS TCustomers;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPrimaryEmailAddr : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FAddress;
	
public:
	__property System::UnicodeString Address = {read=FAddress, write=FAddress};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPrimaryEmailAddr() { }
	
public:
	/* TObject.Create */ inline __fastcall TPrimaryEmailAddr() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TPrimaryPhone : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FFreeFormNumber;
	
public:
	__property System::UnicodeString FreeFormNumber = {read=FFreeFormNumber, write=FFreeFormNumber};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPrimaryPhone() { }
	
public:
	/* TObject.Create */ inline __fastcall TPrimaryPhone() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TBillAddr : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FCity;
	System::UnicodeString FLine1;
	int FPostalCode;
	double FLat;
	double FLong;
	System::UnicodeString FCountrySubDivisionCode;
	int FId;
	
public:
	__property System::UnicodeString City = {read=FCity, write=FCity};
	__property System::UnicodeString Line1 = {read=FLine1, write=FLine1};
	__property int PostalCode = {read=FPostalCode, write=FPostalCode, nodefault};
	__property double Lat = {read=FLat, write=FLat};
	__property double Long = {read=FLong, write=FLong};
	__property System::UnicodeString CountrySubDivisionCode = {read=FCountrySubDivisionCode, write=FCountrySubDivisionCode};
	__property int Id = {read=FId, write=FId, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TBillAddr() { }
	
public:
	/* TObject.Create */ inline __fastcall TBillAddr() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TMetaData : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::TDateTime FCreateTime;
	System::TDateTime FLastUpdatedTime;
	
public:
	__property System::TDateTime CreateTime = {read=FCreateTime, write=FCreateTime};
	__property System::TDateTime LastUpdatedTime = {read=FLastUpdatedTime, write=FLastUpdatedTime};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TMetaData() { }
	
public:
	/* TObject.Create */ inline __fastcall TMetaData() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TCustomer_1 : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TPrimaryEmailAddr* FPrimaryEmailAddr;
	int FSyncToken;
	System::UnicodeString Fdomain;
	System::UnicodeString FGivenName;
	System::UnicodeString FDisplayName;
	bool FBillWithParent;
	System::UnicodeString FFullyQualifiedName;
	System::UnicodeString FCompanyName;
	System::UnicodeString FFamilyName;
	bool Fsparse;
	TPrimaryPhone* FPrimaryPhone;
	bool FActive;
	bool FJob;
	double FBalanceWithJobs;
	TBillAddr* FBillAddr;
	System::UnicodeString FPreferredDeliveryMethod;
	bool FTaxable;
	System::UnicodeString FPrintOnCheckName;
	double FBalance;
	int FId;
	TMetaData* FMetaData;
	
public:
	__fastcall TCustomer_1();
	__fastcall virtual ~TCustomer_1();
	__property TPrimaryEmailAddr* PrimaryEmailAddr = {read=FPrimaryEmailAddr};
	__property int SyncToken = {read=FSyncToken, write=FSyncToken, nodefault};
	__property System::UnicodeString domain = {read=Fdomain, write=Fdomain};
	__property System::UnicodeString GivenName = {read=FGivenName, write=FGivenName};
	__property System::UnicodeString DisplayName = {read=FDisplayName, write=FDisplayName};
	__property bool BillWithParent = {read=FBillWithParent, write=FBillWithParent, nodefault};
	__property System::UnicodeString FullyQualifiedName = {read=FFullyQualifiedName, write=FFullyQualifiedName};
	__property System::UnicodeString CompanyName = {read=FCompanyName, write=FCompanyName};
	__property System::UnicodeString FamilyName = {read=FFamilyName, write=FFamilyName};
	__property bool sparse = {read=Fsparse, write=Fsparse, nodefault};
	__property TPrimaryPhone* PrimaryPhone = {read=FPrimaryPhone};
	__property bool Active = {read=FActive, write=FActive, nodefault};
	__property bool Job = {read=FJob, write=FJob, nodefault};
	__property double BalanceWithJobs = {read=FBalanceWithJobs, write=FBalanceWithJobs};
	__property TBillAddr* BillAddr = {read=FBillAddr};
	__property System::UnicodeString PreferredDeliveryMethod = {read=FPreferredDeliveryMethod, write=FPreferredDeliveryMethod};
	__property bool Taxable = {read=FTaxable, write=FTaxable, nodefault};
	__property System::UnicodeString PrintOnCheckName = {read=FPrintOnCheckName, write=FPrintOnCheckName};
	__property double Balance = {read=FBalance, write=FBalance};
	__property int Id = {read=FId, write=FId, nodefault};
	__property TMetaData* MetaData = {read=FMetaData};
};


class PASCALIMPLEMENTATION TCustomer : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TCustomer_1* FCustomer;
	System::TDateTime Ftime;
	
public:
	__fastcall TCustomer();
	__fastcall virtual ~TCustomer();
	__property TCustomer_1* Customer = {read=FCustomer};
	__property System::TDateTime time = {read=Ftime, write=Ftime};
};


class PASCALIMPLEMENTATION TCustomers : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::DynamicArray<TCustomer*> FDataset;
	
public:
	__fastcall virtual ~TCustomers();
	__property System::DynamicArray<TCustomer*> Dataset = {read=FDataset, write=FDataset};
public:
	/* TObject.Create */ inline __fastcall TCustomers() : System::Classes::TPersistent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Qbocustomer */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_QBOCUSTOMER)
using namespace Qbocustomer;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// QbocustomerHPP
