
// WMS Includes
#include "CumUser.h"

// Own includes
#include "CftlUserManager.h"
#include "CftlCommandLicenceCheck.h"
#include "CftlCommandGetNewSession.h"
#include "CftlCommandLogin.h"


CftlCommandLogin::CftlCommandLogin(QString p_qstrApplication,
                                 QString p_qstrVersion,
                                 QString p_qstrLogin,
                                 QString p_qstrPassword,
                                 CftlDataAccess* p_ppDataAccess,
                                 CftlUserManager* p_pUserManager)
: CftlAbstractTransactionalCommand(p_ppDataAccess),
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

CftlCommandLogin::~CftlCommandLogin()
{
}

int CftlCommandLogin::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    CftlCommandLicenceCheck command(m_qstrApplication, m_qstrVersion, GetDataAccess());
    bool bCheckResult = (command.Run() > 0);
    m_bDemo = command.IsDemo();
    m_iModules = command.GetModules();

    if(bCheckResult)
    {
       m_pCumUser = m_rpUserManager->FindUser(m_qstrLogin, m_qstrPassword, "");

       if(m_pCumUser && m_pCumUser->IsActive())
       {
           CftlCommandGetNewSession commandNewSession(m_qstrApplication, m_pCumUser->GetId(), GetDataAccess());
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

bool CftlCommandLogin::CheckValid()
{

    return (CHKPTR(m_rpUserManager) &&
            !m_qstrLogin.isEmpty() &&
            !m_qstrPassword.isEmpty());
}

bool CftlCommandLogin::NeedsSessionCheck()
{
    return false;
}

long CftlCommandLogin::GetSessionId()
{
    return m_lNewSession;
}

bool CftlCommandLogin::IsDemo()
{
    return m_bDemo;
}

int CftlCommandLogin::GetModules()
{
    return m_iModules;
}

CumUser* CftlCommandLogin::GetUser()
{
    return m_pCumUser;
}
