//---------------------------------------------------------------------------

#ifndef TJvpUserH
#define TJvpUserH
#include "TMainForm.h"

#include <memory>
#include <mutex>
#include <vector>
#include <map>
#include <any>

#include <System.JSON.hpp>
//---------------------------------------------------------------------------


class TJvpUser
{
  public:
    int uID;
    int AId;
    String UserName;
    String Password;
    TGUID TenantId;
    TGUID RsUserId;
    String RsGroupId;
    String FirstName;
    String MiddleName;
    String LastName;
    String Email;
    String Role;
    String Notes;
    bool isActive;

	TJvpUser();

    TJvpUser(const int uID, const int AId, const String UserName,
        const String APassword, const GUID TenantId, const GUID RsUserId,
        const String RsGroupId, const String FName, const String MName,
        const String LName, const String AEmail, const String Role,
        const String Notes, bool isActive) :
        uID(uID),
        AId(AId), UserName(UserName), Password(APassword), TenantId(TenantId),
        RsUserId(RsUserId), RsGroupId(RsGroupId), FirstName(FName),
        MiddleName(LName), LastName(LName), Email(AEmail), Role(Role),
        Notes(Notes), isActive(isActive) {};

	virtual ~TJvpUser();

    void UserToJson(TJSONObject &AJsonObject);
    void JsontoUser(TJSONValue &AJsonValue);
    String ToString();

    bool operator==(const TJvpUser &rhsUser)
    { // Equality on Id
        return uID == rhsUser.uID && UserName == rhsUser.UserName &&
               Password == rhsUser.Password;
    };

    bool operator<(const TJvpUser &rhsUser)
    { // Comparison sorting
        return LastName < rhsUser.LastName;
    };
};



#endif

