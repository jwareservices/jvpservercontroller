//---------------------------------------------------------------------------

#pragma hdrstop


#include "TJvpUser.h"
#include "GInterfaces.h"
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TJvpUser::TJvpUser()
{

}

TJvpUser::~TJvpUser()
{

}


void TJvpUser::UserToJson( TJSONObject &AJObject )
{
	AJObject.AddPair("id", uID);
	AJObject.AddPair("areadeveloper_id", AId);
	AJObject.AddPair("username", UserName);
	AJObject.AddPair("password", Password);
	AJObject.AddPair("tenant_uuid", Sysutils::GUIDToString(TenantId));
	AJObject.AddPair("rsuser_uuid", Sysutils::GUIDToString(RsUserId));
	AJObject.AddPair("rs_group", RsGroupId);
	AJObject.AddPair("firstName", FirstName);
	AJObject.AddPair("middleName", MiddleName);
	AJObject.AddPair("lastName", LastName);
	AJObject.AddPair("userrole", Role);
	AJObject.AddPair("email", Email);
	AJObject.AddPair("notes", Notes);
	AJObject.AddPair("isActive", isActive);
}

void TJvpUser::JsontoUser(TJSONValue &AJsonValue)
{
	uID = AJsonValue.GetValue<int>("id");
	AId = AJsonValue.GetValue<int>("areadeveloper_id");
	UserName = AJsonValue.GetValue<String>("username");
	Password = AJsonValue.GetValue<String>("password");
	TenantId =
        Sysutils::StringToGUID(AJsonValue.GetValue<String>("tenant_uuid"));
	RsUserId =
        Sysutils::StringToGUID(AJsonValue.GetValue<String>("rsuser_uuid"));
	RsGroupId = AJsonValue.GetValue<String>("rs_group");
	FirstName = AJsonValue.GetValue<String>("fisrtName");
	MiddleName = AJsonValue.GetValue<String>("middleName");
	LastName = AJsonValue.GetValue<String>("lastName");
	Email = AJsonValue.GetValue<String>("email");
	Role = AJsonValue.GetValue<String>("userrole");
	Notes = AJsonValue.GetValue<String>("notes");
	isActive = AJsonValue.GetValue<bool>("isActive");
}

String TJvpUser::ToString()
{
    std::unique_ptr<TStringBuilder> str = std::make_unique<TStringBuilder>();

    try {
		str.get()->Append(uID);
		str.get()->Append(AId);
		str.get()->Append(UserName);
		str.get()->Append(FirstName);
		str.get()->Append(LastName);
		str.get()->Append(Email);
		str.get()->Append(Role);
		str.get()->Append(isActive);
    } catch (Exception &exec) {
        MainForm->Log("UER HELPER===>" + exec.Message);

	}
	return str.get()->ToString();
}

