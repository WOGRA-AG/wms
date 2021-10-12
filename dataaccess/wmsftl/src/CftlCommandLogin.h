#ifndef CDBCOMMANDLOGIN_H
#define CDBCOMMANDLOGIN_H

#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlUserManager;
class CumUser;

class CftlCommandLogin : public CftlAbstractTransactionalCommand
{
    private:
        CftlUserManager* m_rpUserManager;
        QString m_qstrApplication;
        QString m_qstrLogin;
        QString m_qstrPassword;
        QString m_qstrVersion;
        bool m_bDemo;
        int m_iModules;
       qint64 m_lNewSession;
        CumUser* m_pCumUser;

    public:
        CftlCommandLogin(QString p_qstrApplication,
                        QString p_qstrVersion,
                        QString p_qstrLogin,
                        QString p_qstrPassword,
                        CftlDataAccess* p_ppDataAccess,
                        CftlUserManager* p_pUserManager);

        virtual ~CftlCommandLogin();
       qint64 GetSessionId();
        bool IsDemo();
        int GetModules();
        CumUser *GetUser();
protected:
        virtual int Execute();
        virtual bool CheckValid();
        virtual bool NeedsSessionCheck();

};

#endif // CDBCOMMANDLOGIN_H
