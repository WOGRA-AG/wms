#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CwiCommandGetUserGroupByName.h"
#include "CwmsContext.h"
#include "CdmLogging.h"
#include "CwiSessionlessAccess.h"

CwiCommandGetUserGroupByName::CwiCommandGetUserGroupByName(CwmscomData* p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetUserGroupByName::~CwiCommandGetUserGroupByName()
{

}

void CwiCommandGetUserGroupByName::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QString qstrGroupName = m_rpData->GetValue("Name").toString();

    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            CumUserGroup* pUserGroup = pCumUserManager->FindUserGroupByName(qstrGroupName);
            if(pUserGroup)
            {
                pResult->AddValue("Group",pUserGroup->GetVariant());
                pResult->SetMessage("Group found!");
                pResult->SetMessageCode(1);
                pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
            else
            {
                pResult->SetMessage("No Group found on Server");
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
