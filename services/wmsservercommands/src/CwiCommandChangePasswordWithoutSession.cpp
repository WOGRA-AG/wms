// WMS Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"

// Basetools Includes
#include "CwmsContext.h"

// Own Includes
#include "CwiCommandChangePasswordWithoutSession.h"



CwiCommandChangePasswordWithoutSession::CwiCommandChangePasswordWithoutSession(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandChangePasswordWithoutSession::~CwiCommandChangePasswordWithoutSession()
{

}

void CwiCommandChangePasswordWithoutSession::Execute()
{
    CwmsContext::GetContext()->ServerLogin();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (pCumUserManager)
      {
         int iSuccess = 1;

         QString qstrPassword = m_rpData->GetValue("Password").toString();
         QString qstrId = m_rpData->GetValue("UserId").toString();
         int UserId = qstrId.toInt();

               CumUser* pCumUser =  pCumUserManager->FindUserById(UserId);
               if(pCumUser)
               {
                    pCumUser->SetPassword(qstrPassword);
                    pCumUser->SetEncrypted(false);
                   iSuccess = pCumUserManager->UpdateUser(pCumUser);
                   pResult->SetMessage("Password changed");
                   pResult->SetMessageCode(iSuccess);
                   pResult->SetSeverity(eWmscomMessageServerityInfo);
               }
              else
               {
                    pResult->SetMessage("Password not changed");
                    pResult->SetMessageCode(-5000);
                    pResult->SetSeverity(eWmscomMessageServerityFatal);
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

    CwmsContext::GetContext()->ServerLogout();
}
