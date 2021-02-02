#include "CwiCommandDeleteUsergroup.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"


CwiCommandDeleteUsergroup::CwiCommandDeleteUsergroup(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandDeleteUsergroup::~CwiCommandDeleteUsergroup()
{

}

void CwiCommandDeleteUsergroup::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

       if (pCumUserManager)
       {
           int iGroupId = m_rpData->GetValue("GroupId").toInt();
           pCumUserManager->DeleteUserGroup(iGroupId);

          pResult->SetMessage("Group deleted");
          pResult->SetMessageCode(1);
          pResult->SetSeverity(eWmscomMessageServerityInfo);
       }
       else
       {
          pResult->SetMessage("Invalid UserManager pointer!");
          pResult->SetMessageCode(-5000);
          pResult->SetSeverity(eWmscomMessageServerityFatal);
       }
    }
    else
    {
       pResult->SetMessage("Session not found!");
       pResult->SetMessageCode(-5000);
       pResult->SetSeverity(eWmscomMessageServerityFatal);
    }
}

