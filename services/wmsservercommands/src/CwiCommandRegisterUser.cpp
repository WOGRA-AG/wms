// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserManager.h"

// Basetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwiCommandRegisterUser.h"

CwiCommandRegisterUser::CwiCommandRegisterUser(CwmscomData *p_pData)
: m_pUser(nullptr),
  m_rpData(p_pData)
{
    if (CHKPTR(m_rpData))
    {
       CwmsContext::GetContext()->ServerLogin();
    }
}

CwiCommandRegisterUser::~CwiCommandRegisterUser()
{
    if (CHKPTR(m_rpData))
    {
        CwmsContext::GetContext()->ServerLogout();
    }
}

void CwiCommandRegisterUser::Execute()
{
    if (CHKPTR(m_rpData))
    {
        CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
        if(pCdmManager)
        {
             CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
             if(pCumUserManager)
             {
                 QString qstrFirstName = m_rpData->GetValue("FirstName").toString();
                 QString qstrLastName = m_rpData->GetValue("LastName").toString();
                 QString qstrLoginName = m_rpData->GetValue("Login").toString();
                 QString qstrPassword = m_rpData->GetValue("Password").toString();
                 QString qstrEmail = m_rpData->GetValue("Email").toString();
                 QString qstrIdentityKey = m_rpData->GetValue("IdentityKey").toString();

                 int lReturn = pCumUserManager->RegisterUser(qstrLoginName, qstrPassword, qstrLastName, qstrFirstName, qstrEmail, qstrIdentityKey);

                 if(lReturn == CdmLogging::eDmInvalidInsertStatement) {
                     pResult->SetMessage("User already exists in Db");
                     pResult->SetMessageCode(-5000);
                     pResult->SetSeverity(eWmscomMessageServerityFatal);
                 }
                 else
                 {
                     pResult->AddValue("UserId" , lReturn);
                     pResult->SetMessage("User added successfully");
                     pResult->SetMessageCode(1);
                     pResult->SetSeverity(eWmscomMessageServerityInfo);

                     m_pUser = pCumUserManager->FindUserById(lReturn);
                 }
             }
             else
             {
                 pResult->SetMessage("User Manager not found");
                 pResult->SetMessageCode(-5000);
                 pResult->SetSeverity(eWmscomMessageServerityFatal);
             }
        }
        else
        {
             pResult->SetMessage("Session not found");
             pResult->SetMessageCode(-5000);
             pResult->SetSeverity(eWmscomMessageServerityFatal);
        }
    }
}

CumUser* CwiCommandRegisterUser::GetUser()
{
    return m_pUser;
}
