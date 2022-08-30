#include "CwnCommandLogin.h"
#include "CwnCommandLicenceCheck.h"
#include "CwnCommandGetNewSession.h"

CwnCommandLogin::CwnCommandLogin(QString p_qstrApplication,
                                 QString p_qstrVersion,
                                 QString p_qstrLogin,
                                 QString p_qstrPassword,
                                 CwnDataAccess* m_rpDataAccess,
                                 CwnUserManager* p_pUserManager):CwnCommandBase(m_rpDataAccess),
    m_rpUserManager(p_pUserManager),
    m_qstrApplication(p_qstrApplication),
    m_qstrLogin(p_qstrLogin),
    m_qstrPassword(p_qstrPassword),
    m_qstrVersion(p_qstrVersion),
    m_bDemo(false),
    m_iModules(0),
    m_lNewSession(0),
    m_pCumUser(nullptr)
{
}

CwnCommandLogin::~CwnCommandLogin()
{

}

int CwnCommandLogin::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    CwnCommandLicenceCheck commandLicenceCheck(m_qstrApplication, m_qstrVersion, GetDataAccess());
    bool bCheckResult = (commandLicenceCheck.Run() > 0);
    m_bDemo = commandLicenceCheck.IsDemo();
    m_iModules = commandLicenceCheck.GetModules();

    if(bCheckResult)
    {
        m_pCumUser = m_rpUserManager->FindUser(m_qstrLogin, m_qstrPassword);
        if(m_pCumUser)
        {
            CwnCommandGetNewSession commandNewSession(m_qstrApplication, m_pCumUser->GetId(), GetDataAccess());
            iRet = commandNewSession.Run();
            m_lNewSession = commandNewSession.GetResult();

        }
        else
        {
            iRet = EC(eDmUserNotFound);
        }
    }
    else
    {
        iRet = EC(eDmNoLicenceLeft);
    }

    return iRet;
}

bool CwnCommandLogin::CheckValid()
{

    return (CHKPTR(m_rpUserManager) &&
            !m_qstrApplication.isEmpty() &&
            !m_qstrLogin.isEmpty() &&
            !m_qstrPassword.isEmpty());
}

qint64 CwnCommandLogin::GetSessionId()
{
    return m_lNewSession;
}

bool CwnCommandLogin::IsDemo()
{
    return m_bDemo;
}

int CwnCommandLogin::GetModules()
{
    return m_iModules;
}

CumUser* CwnCommandLogin::GetUser()
{
    return m_pCumUser;
}
void CwnCommandLogin::interpretAnswer(QVariant &Ret)
{
    Q_UNUSED(Ret)
    //Nothing to do;
}
