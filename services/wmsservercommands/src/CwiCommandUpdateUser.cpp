#include "CumUser.h"
#include "CwiCommandUpdateUser.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"


CwiCommandUpdateUser::CwiCommandUpdateUser(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandUpdateUser::~CwiCommandUpdateUser()
{

}

void CwiCommandUpdateUser::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

        if (pCumUserManager)
        {
            int iUserId = m_rpData->GetValue("Id").toInt();

            CumUser* pUser = pCumUserManager->FindUserById(iUserId);

            if (CHKPTR(pUser))
            {
                pUser->SetFirstName(m_rpData->GetValue("FirstName").toString());
                pUser->SetLastName(m_rpData->GetValue("LastName").toString());
                pUser->SetLogin(m_rpData->GetValue("Login").toString());
                pUser->SetPassword(m_rpData->GetValue("Password").toString());
                pUser->SetEmail(m_rpData->GetValue("Email").toString());
                pUser->SetAdministrator(m_rpData->GetValue("Admin").toBool());
                pUser->SetActive(m_rpData->GetValue("Active").toBool());
                pUser->SetEncrypted(m_rpData->GetValue("Encrypted").toBool());
                int iRes = pCumUserManager->UpdateUser(pUser);
                if(iRes >= 0)
                {
                    pResult->SetMessage("User updated");
                    pResult->SetMessageCode(1);
                    pResult->SetSeverity(eWmscomMessageServerityInfo);
                }
                else
                {
                    pResult->SetMessage("User Update failed");
                    pResult->SetMessageCode(-5000);
                    pResult->SetSeverity(eWmscomMessageServerityFatal);
                }
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

