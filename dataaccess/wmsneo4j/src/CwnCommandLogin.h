#ifndef CWNCOMMANDLOGIN_H
#define CWNCOMMANDLOGIN_H

#include <QString>

#include "CwnCommandBase.h"
#include "CwnUserManager.h"
#include "CumUser.h"
#include "CwnDataAccess.h"

class CwnCommandLogin : public CwnCommandBase
{
private:
    CwnDataAccess* m_rpDataAccess;
    CwnUserManager* m_rpUserManager;
    QString m_qstrApplication;
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrVersion;
    bool m_bDemo;
    int m_iModules;
    long m_lNewSession;
    CumUser* m_pCumUser;

public:
    CwnCommandLogin(QString p_qstrApplication,
                    QString p_qstrVersion,
                    QString p_qstrLogin,
                    QString p_qstrPassword,
                    CwnDataAccess* m_rpDataAccess,
                    CwnUserManager* p_pUserManager);

    virtual ~CwnCommandLogin();

    long GetSessionId();
    bool IsDemo();
    int GetModules();
    CumUser *GetUser();

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOGIN_H
