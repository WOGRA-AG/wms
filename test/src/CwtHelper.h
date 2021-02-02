#ifndef CWTHELPER_H
#define CWTHELPER_H

#include <QString>


class CumUserManager;
class CdmDataProvider;
class CumUser;
class CdmClass;
class CdmClassManager;


#define ADMIN_USER_ID 1
#define LOGIN_ADMIN "admin"
#define PASSWORD_ADMIN "admin"

#define LOGIN_TEST "test"
#define PASSWORD_TEST "test"

#define LOGIN_UNKNOWN "unknown"
#define PASSWORD_UNKNOWN "unknown"

#define TEST_LANGUAGE "Englisch"
#define TEST_CLASS_NAME "Test"
#define TEST_MEMBER_KEYNAME "zeichen"


class CwtHelper
{
public:
    CwtHelper();
    static QString CreateUniqueName(QString p_qstrName);
    static void Logout();
    static void Login(QString p_qstrLogin, QString p_qstrPassword);
    static CumUserManager *GetUserManager();
    static void CreateScheme(QString p_qstrName);
    static void DeleteScheme(QString p_qstrName);
    static CumUser *CreateUser(QString p_qstrIdentitfier, CumUserManager *pUserManager);
    static CdmClass *CreateTestClass();
    static CdmDataProvider *GetDataProvider();
private:
    static CdmClassManager *GetClassManager();
};

#endif // CWTHELPER_H
