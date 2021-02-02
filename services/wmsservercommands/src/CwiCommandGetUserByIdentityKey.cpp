// WMS Manager Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"

// WMS Basetools Includes
#include "CwmsContext.h"

// Own Includes
#include "CwiSessionlessAccess.h"
#include "CwiCommandGetUserByIdentityKey.h"


CwiCommandGetUserByIdentityKey::CwiCommandGetUserByIdentityKey(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetUserByIdentityKey::~CwiCommandGetUserByIdentityKey()
{

}

void CwiCommandGetUserByIdentityKey::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QString qstrIdentityKey = m_rpData->GetValue("IdentityKey").toString();

    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            CumUser* pCumUser = pCumUserManager->FindUserByIdentityKey(qstrIdentityKey);
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

    CwmsContext::GetContext()->ServerLogout();
}

