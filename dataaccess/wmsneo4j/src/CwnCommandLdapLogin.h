#ifndef CWNCOMMANDLDAPLOGIN_H
#define CWNCOMMANDLDAPLOGIN_H
#ifndef WMS_NO_LDAP

#include "CwnCommandBase.h"
#include "CwnDataAccess.h"

// Forwards
class CwnUserManager;
class CumUser;


class CwnCommandLdapLogin : public CwnCommandBase
{
private:
    CwnUserManager* m_rpUserManager;
    QString m_qstrApplication;
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrVersion;
    CumUser* m_pUser;

   qint64 GetNewSession();
public:
    CwnCommandLdapLogin(QString p_qstrApplication,
                        QString p_qstrVersion,
                        QString p_qstrLogin,
                        QString p_qstrPassword,
                        CwnDataAccess* p_pDataAccess,
                        CwnUserManager* p_pUserManager);
    ~CwnCommandLdapLogin();
    CumUser *GetUser();
protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual void interpretAnswer(QVariant& Ret);
};
#endif // WMS_NO_LDAP
#endif // CWNCOMMANDLDAPLOGIN_H

