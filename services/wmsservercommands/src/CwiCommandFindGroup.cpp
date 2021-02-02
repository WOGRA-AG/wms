
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUserGroup.h"
#include "CwiSessionlessAccess.h"
#include "CwiCommandFindGroup.h"
#include "CwmsContext.h"

CwiCommandFindGroup::CwiCommandFindGroup(CwmscomData* p_pData)
    :m_rpData(p_pData)
{
}

CwiCommandFindGroup::~CwiCommandFindGroup()
{
}

void CwiCommandFindGroup::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QString qstrSearchString = m_rpData->GetValue("Name").toString();

    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            QLinkedList<CumUserGroup*> qlUserGroup = pCumUserManager->FindUserGroupsByNameUnmanaged(qstrSearchString);
            if (!qlUserGroup.isEmpty())
            {
                QVariantList qvlGroup;

                QLinkedList<CumUserGroup*>::iterator qlIt = qlUserGroup.begin();
                QLinkedList<CumUserGroup*>::iterator qlItEnd = qlUserGroup.end();

                for(; qlIt != qlItEnd; ++qlIt)
                {
                    CumUserGroup* pUserGroup = *qlIt;
                    qvlGroup.append(pUserGroup->GetVariant());
                    DELPTR(*qlIt);
                }

                if (qvlGroup.count() > 0)
                {
                    pResult->AddValue("Group",qvlGroup);
                    pResult->SetMessage("Groups found!");
                    pResult->SetMessageCode(1);
                    pResult->SetSeverity(eWmscomMessageServerityInfo);
                }
                else
                {
                    pResult->SetMessage("No Groups found on Server");
                    pResult->SetMessageCode(0);
                    pResult->SetSeverity(eWmscomMessageServerityError);
                }
            }
            else
            {
                pResult->SetMessage("User Manager not found");
                pResult->SetMessageCode(CdmLogging::eDmFalse);
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
}
