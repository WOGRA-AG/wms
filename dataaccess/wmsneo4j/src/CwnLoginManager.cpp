#include "CwnLoginManager.h"
#include "CwnCommandLogin.h"
#include "CwnCommandLogout.h"
#include "CwnCommandFindSession.h"
#include "CwnCommandGetNewSession.h"
#include "CwnCommandLdapLogin.h"
#include "CwnCommandCheckSessionTimeout.h"
#include "CwnCommandUpdateSession.h"



CwnLoginManager::CwnLoginManager(CwnDataAccess* p_pCwnDataAccess, CwnUserManager* p_pCwnUserManager) : m_rpCwnDataAccess(p_pCwnDataAccess), m_rpCwnUserManager(p_pCwnUserManager)
{

}

CwnLoginManager::~CwnLoginManager()
{
    //Nothing to do.
}

long CwnLoginManager::Login(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rpCumUser, bool& p_bDemo, int& p_iModules, QString& p_qstrVersion)
{
    CwnCommandLogin loginSessionCheck(p_qstrApplication,p_qstrVersion,p_qstrLogin,p_qstrPassword,m_rpCwnDataAccess,m_rpCwnUserManager);

    long Ret=loginSessionCheck.Run();

    if(Ret>0)
        p_rpCumUser = loginSessionCheck.GetUser();

    return loginSessionCheck.GetSessionId();
}

long CwnLoginManager::Logout(  long p_lSessionId )
{
    CwnCommandLogout logoutSession(p_lSessionId,m_rpCwnDataAccess);

    return logoutSession.Run();
}

long CwnLoginManager::FindSession(  long p_lSessionId, long p_lUserId )
{
    CwnCommandFindSession findSession(p_lSessionId,p_lUserId,m_rpCwnDataAccess);

    return findSession.Run();
}

long CwnLoginManager::GetNewSession(QString p_qstrApplication, long p_lUserId)
{
    CwnCommandGetNewSession getNewSession(p_qstrApplication,p_lUserId,m_rpCwnDataAccess);
    int Ret = getNewSession.Run();

    return (Ret>0)?getNewSession.GetResult():-1;
}

bool CwnLoginManager::LicenceCheck(QString p_qstrApplication, bool& p_bDemo, int& p_iModules, QString p_qstrVersion)
{
    Q_UNUSED(p_qstrApplication);
    Q_UNUSED(p_bDemo);
    Q_UNUSED(p_iModules);
    Q_UNUSED(p_qstrVersion);
    return true;
}

long CwnLoginManager::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rUser)
{
    #ifndef WMS_NO_LDAP
        CwnCommandLdapLogin command(p_qstrApplication, "", p_qstrLogin, p_qstrPassword, m_rpCwnDataAccess, m_rpCwnUserManager);
        long lRet = command.Run();

        if (lRet>0)
        {
            p_rUser = command.GetUser();
        }

        return lRet;
    #else
        return CdmError::eDmNotSupportedFeatureForThisDb;
    #endif
}

CdmSession *CwnLoginManager::FindSession(int p_iSessionId)
{
    CdmSession* pSesion = nullptr;
    CwnCommandFindSession command(p_iSessionId, m_rpCwnDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

CdmSession *CwnLoginManager::FindSession(QString p_qstrBaseAuth)
{
    CdmSession* pSesion = nullptr;
    CwnCommandFindSession command(p_qstrBaseAuth, m_rpCwnDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

void CwnLoginManager::UpdateSession(int p_iSessionId)
{
    CwnCommandUpdateSession command(p_iSessionId, m_rpCwnDataAccess);
    command.Run();
}

void CwnLoginManager::UpdateSession(QString p_qstrBaseAuth)
{
    CwnCommandUpdateSession command(p_qstrBaseAuth, m_rpCwnDataAccess);
    command.Run();
}

void CwnLoginManager::SessionTimeoutCheck(int p_iTimeoutMin)
{
    CwnCommandCheckSessionTimeout command(p_iTimeoutMin, m_rpCwnDataAccess);
    command.Run();
}
