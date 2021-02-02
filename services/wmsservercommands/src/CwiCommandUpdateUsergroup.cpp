#include "CwiCommandUpdateUsergroup.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"


CwiCommandUpdateUsergroup::CwiCommandUpdateUsergroup(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandUpdateUsergroup::~CwiCommandUpdateUsergroup()
{

}

void CwiCommandUpdateUsergroup::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

       if (pCumUserManager)
       {
           QString qstrName = m_rpData->GetValue("Name").toString();
           long lgroupId = m_rpData->GetValue("GroupId").toInt();
           int iRes = pCumUserManager->RenameUserGroup(lgroupId, qstrName);

           if(iRes >= 0)
           {
               pResult->SetMessage("Usergroup updated");
               pResult->SetMessageCode(1);
               pResult->SetSeverity(eWmscomMessageServerityInfo);
           }
           else
           {
               pResult->SetMessage("failed to Update group");
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

