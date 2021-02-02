#include "CwiCommandGetUserGroupById.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CwmsContext.h"
#include "CdmLogging.h"
#include "CumUserGroup.h"
#include "CwiSessionlessAccess.h"

CwiCommandGetUserGroupById::CwiCommandGetUserGroupById(CwmscomData *p_pData)
    : m_rpData(p_pData)
{

}

CwiCommandGetUserGroupById::~CwiCommandGetUserGroupById()
{

}

void CwiCommandGetUserGroupById::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    int iGroupId = m_rpData->GetValue("Name").toInt();

    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            CumUserGroup* pUserGroup = pCumUserManager->FindUserGroupById(iGroupId);
            if(pUserGroup)
            {
                pResult->AddValue("Group",pUserGroup->GetVariant());
                pResult->SetMessage("Groups found!");
                pResult->SetMessageCode(1);
                pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
            else
                        {
                            pResult->SetMessage("No Groups found on Server");
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
