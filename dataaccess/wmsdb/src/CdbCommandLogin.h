#ifndef CDBCOMMANDLOGIN_H
#define CDBCOMMANDLOGIN_H

#include "CdbAbstractCommand.h"

// Forwards
class CdbUserManager;
class CumUser;

class CdbCommandLogin : public CdbAbstractCommand
{
    private:
        CdbUserManager* m_rpUserManager;
        QString m_qstrApplication;
        QString m_qstrLogin;
        QString m_qstrPassword;
        QString m_qstrVersion;
        bool m_bDemo;
        int m_iModules;
        long m_lNewSession;
        CumUser* m_pCumUser;

    public:
        CdbCommandLogin(QString p_qstrApplication,
                        QString p_qstrVersion,
                        QString p_qstrLogin,
                        QString p_qstrPassword,
                        CdbDataAccess* p_ppDataAccess,
                        CdbUserManager* p_pUserManager);

        virtual ~CdbCommandLogin();
        long GetSessionId();
        bool IsDemo();
        int GetModules();
        CumUser *GetUser();
protected:
        virtual int Execute();
        virtual bool CheckValid();
        virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDLOGIN_H
