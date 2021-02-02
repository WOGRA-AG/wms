#include "CwiCommandAddNewUsergroup.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"


CwiCommandAddNewUsergroup::CwiCommandAddNewUsergroup(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandAddNewUsergroup::~CwiCommandAddNewUsergroup()
{

}

void CwiCommandAddNewUsergroup::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

       if (pCumUserManager)
       {
          QString qstrName = m_rpData->GetValue("Name").toString();
          int groupId = pCumUserManager->CreateUserGroup(qstrName);
          if(groupId >= 0)
          {
              pResult->AddValue("GroupId", groupId);
              pResult->SetMessage("Usergroup created");
              pResult->SetMessageCode(1);
              pResult->SetSeverity(eWmscomMessageServerityInfo);
          }
          else
          {
              pResult->SetMessage("failed to create group");
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

