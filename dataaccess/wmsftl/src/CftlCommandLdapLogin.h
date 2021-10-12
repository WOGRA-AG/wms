#ifndef CDBCOMMANDLDAPLOGIN_H
#define CDBCOMMANDLDAPLOGIN_H
#ifndef WMS_NO_LDAP
#include "CftlAbstractCommand.h"

// Forwards
class CftlUserManager;
class CumUser;

class CftlCommandLdapLogin : public CftlAbstractCommand
{
private:
    CftlUserManager* m_rpUserManager;
    QString m_qstrApplication;
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrVersion;
    CumUser* m_pUser;

   qint64 GetNewSession();
public:
    CftlCommandLdapLogin(QString p_qstrApplication,
                        QString p_qstrVersion,
                        QString p_qstrLogin,
                        QString p_qstrPassword,
                        CftlDataAccess* p_pDataAccess,
                        CftlUserManager* p_pUserManager);
    ~CftlCommandLdapLogin();
    CumUser *GetUser();
protected:
    virtual bool CheckValid();
    virtual int Execute();
};
#endif // WMS_NO_LDAP
#endif // CDBCOMMANDLDAPLOGIN_H
