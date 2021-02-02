#ifndef CDBCOMMANDLDAPLOGIN_H
#define CDBCOMMANDLDAPLOGIN_H
#ifndef WMS_NO_LDAP
#include "CdbAbstractCommand.h"

// Forwards
class CdbUserManager;
class CumUser;

class CdbCommandLdapLogin : public CdbAbstractCommand
{
private:
    CdbUserManager* m_rpUserManager;
    QString m_qstrApplication;
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrVersion;
    CumUser* m_pUser;

    long GetNewSession();
public:
    CdbCommandLdapLogin(QString p_qstrApplication,
                        QString p_qstrVersion,
                        QString p_qstrLogin,
                        QString p_qstrPassword,
                        CdbDataAccess* p_pDataAccess,
                        CdbUserManager* p_pUserManager);
    ~CdbCommandLdapLogin();
    CumUser *GetUser();
protected:
    virtual bool CheckValid();
    virtual int Execute();
};
#endif // WMS_NO_LDAP
#endif // CDBCOMMANDLDAPLOGIN_H
