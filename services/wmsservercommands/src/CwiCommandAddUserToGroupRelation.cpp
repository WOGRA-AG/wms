#include "CwiCommandAddUserToGroupRelation.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"


CwiCommandAddUserToGroupRelation::CwiCommandAddUserToGroupRelation(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandAddUserToGroupRelation::~CwiCommandAddUserToGroupRelation()
{

}

void CwiCommandAddUserToGroupRelation::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

       if (pCumUserManager)
       {
           int iUserId = m_rpData->GetValue("UserId").toInt();
           int iGroupId = m_rpData->GetValue("GroupId").toInt();
          int iRes = pCumUserManager->AddUserToUserGroup(iUserId, iGroupId);
          if(iRes >= 0)
          {
              pResult->SetMessage("User to Group Relation created");
              pResult->SetMessageCode(1);
              pResult->SetSeverity(eWmscomMessageServerityInfo);
          }
          else
          {
              pResult->SetMessage("failed to add Relation");
              pResult->SetMessageCode(-5000);
              pResult->SetSeverity(eWmscomMessageServerityFatal);
          }
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

