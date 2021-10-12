
// WMS Includes
#include "CumUser.h"

// Own includes
#include "CdbUserManager.h"
#include "CdbCommandLicenceCheck.h"
#include "CdbCommandGetNewSession.h"
#include "CdbCommandLogin.h"


CdbCommandLogin::CdbCommandLogin(QString p_qstrApplication,
                                 QString p_qstrVersion,
                                 QString p_qstrLogin,
                                 QString p_qstrPassword,
                                 CdbDataAccess* p_ppDataAccess,
                                 CdbUserManager* p_pUserManager)
: CdbAbstractCommand(p_ppDataAccess),
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

CdbCommandLogin::~CdbCommandLogin()
{
}

int CdbCommandLogin::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    INFO("Checking licence");
    CdbCommandLicenceCheck command(m_qstrApplication, m_qstrVersion, GetDataAccess());
    bool bCheckResult = (command.Run() > 0);
    m_bDemo = command.IsDemo();
    m_iModules = command.GetModules();

    if(bCheckResult)
    {
        INFO("Licence successfully checked.");
        INFO("Looking for User in Usermanager. Login: " + m_qstrLogin);

        // No encryption needed here will be done by FindUser!
       m_pCumUser = m_rpUserManager->FindUser(m_qstrLogin, m_qstrPassword, "");

       if(m_pCumUser)
       {
           if (m_pCumUser->IsActive())
           {
               INFO("User found and successfully validated");
               INFO("Creating new session.");
               CdbCommandGetNewSession commandNewSession(m_qstrApplication, m_pCumUser->GetId(), m_pCumUser->GetBaseAuth(), GetDataAccess());
               iRet = commandNewSession.Run();
               m_lNewSession = commandNewSession.GetResult();
               INFO("New Session ID:" + QString::number(m_lNewSession));
           }
           else
           {
               ERR("User was found but is inactive.");
               iRet= EC(eDmUserNotFound);
           }
       }
       else
       {
           INFO("User not found. Wrong credentials.")
          iRet = EC(eDmUserNotFound);
       }
    }
    else
    {
        INFO("Licence Validation failed.")
       iRet = EC(eDmNoLicenceLeft);
    }


    return iRet;
}

bool CdbCommandLogin::CheckValid()
{

    return (CHKPTR(m_rpUserManager) &&
            !m_qstrApplication.isEmpty() &&
            !m_qstrLogin.isEmpty() &&
            !m_qstrPassword.isEmpty());
}

qint64 CdbCommandLogin::GetSessionId()
{
    return m_lNewSession;
}

bool CdbCommandLogin::IsDemo()
{
    return m_bDemo;
}

int CdbCommandLogin::GetModules()
{
    return m_iModules;
}

CumUser* CdbCommandLogin::GetUser()
{
    return m_pCumUser;
}

bool CdbCommandLogin::NeedsActiveSession()
{
    return false;
}
