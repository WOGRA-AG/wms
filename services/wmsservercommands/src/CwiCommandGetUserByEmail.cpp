// WMS Manager Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"

// Basetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwiSessionlessAccess.h"
#include "CwiCommandGetUserByEmail.h"


CwiCommandGetUserByEmail::CwiCommandGetUserByEmail(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetUserByEmail::~CwiCommandGetUserByEmail()
{

}

void CwiCommandGetUserByEmail::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QString qstrUserEmail = m_rpData->GetValue("Email").toString();


    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            CumUser* pCumUser = pCumUserManager->FindUserByEmail(qstrUserEmail);
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
