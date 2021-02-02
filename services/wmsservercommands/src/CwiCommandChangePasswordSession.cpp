#include "CwiCommandChangePasswordSession.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "IdmDataAccess.h"


CwiCommandChangePasswordSession::CwiCommandChangePasswordSession(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandChangePasswordSession::~CwiCommandChangePasswordSession()
{

}

void CwiCommandChangePasswordSession::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

        if (pCumUserManager)
        {
            int iSuccess = 1;

            QString qstrOldPassword = m_rpData->GetValue("PasswordOld").toString();
            QString qstrNewPassword = m_rpData->GetValue("PasswordNew").toString();
            QString qstrId = m_rpData->GetValue("UserId").toString();
            int UserId = qstrId.toInt();

            IdmDataAccess* pDataAccess = pCdmManager->GetDataAccess();
            CumUser* pCumUser = nullptr;

            if (CHKPTR(pDataAccess))
            {
                pCumUser = pDataAccess->FindUserById(UserId);
                if(pCumUser)
                {
                    QString qstrLogin = pCumUser->GetLogin();
                    pCumUser = pCdmManager->GetDataAccess()->FindUser(qstrLogin, qstrOldPassword, "");

                    if (pCumUser)
                    {
                        pCumUser->SetPassword(qstrNewPassword);
                        pCumUser->SetEncrypted(false);
                        iSuccess = pCumUserManager->UpdateUser(pCumUser);

                               pResult->SetMessage("Password changed");
                               pResult->SetMessageCode(iSuccess);
                               pResult->SetSeverity(eWmscomMessageServerityInfo);
                    }
                    else
                    {
                        pResult->SetMessage("Password wrong");
                        pResult->SetMessageCode(-5000);
                        pResult->SetSeverity(eWmscomMessageServerityFatal);
                    }
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
                pResult->SetMessage("Data Access not found");
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

