#include "CwiCommandAddUser.h"
#include "CdmDataProvider.h"
#include "CumUser.h"
#include "CumUserManager.h"


CwiCommandAddUser::CwiCommandAddUser(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandAddUser::~CwiCommandAddUser()
{

}

void CwiCommandAddUser::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QVariant qUser = m_rpData->GetValue("User");
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (pCumUserManager)
      {
         int iSuccess = -5000;
         CumUser* pUser = new CumUser(pCumUserManager);

         if (pUser->GetId() <= 0)
         {
             pUser->SetFirstName(m_rpData->GetValue("FirstName").toString());
             pUser->SetLastName(m_rpData->GetValue("LastName").toString());
             pUser->SetLogin(m_rpData->GetValue("Login").toString());
             pUser->SetPassword(m_rpData->GetValue("Password").toString());
             pUser->SetEmail(m_rpData->GetValue("Email").toString());
             pUser->SetAdministrator(m_rpData->GetValue("Admin").toBool());

             if (m_rpData->HasValue("Scheme"))
             {
                 pUser->AddSchemeUri(m_rpData->GetValue("Scheme").toString());
                 pUser->SetSchemeIndependent(false);
             }
             else
             {
                 pUser->SetSchemeIndependent(true);
             }

             int UserId = pCumUserManager->CreateUser(pUser);
            iSuccess = 1;
            if (UserId > 0)
            {
               pResult->AddValue("UserId", UserId);
               pResult->SetMessage("User created");
               pResult->SetMessageCode(iSuccess);
               pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
         }
         else
         {
            pResult->SetMessage("User Already Existent");
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
}

