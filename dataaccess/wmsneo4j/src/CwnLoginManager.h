#ifndef CWNLOGINMANAGER_H
#define CWNLOGINMANAGER_H

// System and QT Includes
#include <qmap.h>


// own Includes
#include "CumUser.h"
#include "CwnDataAccess.h"


// forwards
class CwnDataAccess;
class CwnUserManager;

 /*
  * This class manages the login and logout of users on the system
  */
class CwnLoginManager
{
protected:
    CwnDataAccess* m_rpCwnDataAccess;
    CwnUserManager* m_rpCwnUserManager;
public:

    CwnLoginManager(CwnDataAccess* p_pCwnDataAccess, CwnUserManager* p_pCwnUserManager);
    virtual ~CwnLoginManager();
public:
    long Login(QString p_qstrApplication,
               QString p_qstrLogin,
               QString p_qstrPassword,
               CumUser*& p_rpCumUser,
               bool& p_bDemo,
               int& p_iModules,
               QString& p_qstrVersion);
public:
    virtual long Logout(  long p_lSessionId );
    virtual long FindSession(  long p_lSessionId, long p_lUserId );
    virtual long GetNewSession(QString p_qstrApplication, long p_lUserId);
    bool LicenceCheck(QString p_qstrApplication,
                      bool& p_bDemo,
                      int& p_iModules,
                      QString p_qstrVersion);

    long LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rUser);
    virtual CdmSession* FindSession(int p_iSessionId);
    virtual CdmSession* FindSession(QString p_qstrBaseAuth);
    void UpdateSession(int p_iSessionId);
    void UpdateSession(QString p_qstrBaseAuth);
    void SessionTimeoutCheck(int p_iTimeoutMin);
};

#endif //
