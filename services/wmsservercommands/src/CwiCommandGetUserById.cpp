#include "CwiCommandGetUserById.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CwmsContext.h"
#include "CwiSessionlessAccess.h"

CwiCommandGetUserById::CwiCommandGetUserById(CwmscomData *p_pData)
    : m_rpData(p_pData)
{

}

CwiCommandGetUserById::~CwiCommandGetUserById()
{

}

void CwiCommandGetUserById::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    int iUserId = m_rpData->GetValue("UserId").toInt();

    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            CumUser* pCumUser = pCumUserManager->FindUserById(iUserId);
            if (pCumUser)
            {
               pResult->AddValue("User", pCumUser->GetVariant());
               pResult->SetMessage("User found!");
               pResult->SetMessageCode(1);
               pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
            else
            {
                pResult->SetMessage("User not found on Server");
                pResult->SetMessageCode(CdmLogging::eDmFalse);
                pResult->SetSeverity(eWmscomMessageServerityError);
            }
        }
        else
        {
            pResult->SetMessage("User Manager not found");
            pResult->SetMessageCode(-5000);
            pResult->SetSeverity(eWmscomMessageServerityError);
        }
    }
    else
    {
        pResult->SetMessage("Session not found");
        pResult->SetMessageCode(-5000);
        pResult->SetSeverity(eWmscomMessageServerityError);
    }
}
