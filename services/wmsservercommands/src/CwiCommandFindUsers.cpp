
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CwiCommandFindUsers.h"

CwiCommandFindUsers::CwiCommandFindUsers(CwmscomData* p_pData)
    :m_rpData(p_pData)
{
}

CwiCommandFindUsers::~CwiCommandFindUsers()
{
}

void CwiCommandFindUsers::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    QString qstrSearchString = m_rpData->GetValue("FindUsers").toString();

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if(pCdmManager)
    {
        CumUserManager* pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            QList<CumUser*> qlUsers = pCumUserManager->FindUsersUnmanaged(qstrSearchString);
            QVariantList qvlUsers;
            if (!qlUsers.isEmpty())
            {
                QList<CumUser*>::iterator qllIt = qlUsers.begin();
                QList<CumUser*>::iterator qllItEnd = qlUsers.end();

                for (; qllIt != qllItEnd; ++qllIt)
                {
                    CumUser* pUser = *qllIt;
                    qvlUsers.append(pUser->GetVariant());
                    DELPTR(pUser); // must be deleted because the result won't be stored in UserManager.
                }



               pResult->AddValue("User",qvlUsers);
               pResult->SetMessage("Users found!");
               pResult->SetMessageCode(1);
               pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
            else
            {
                pResult->AddValue("User",qvlUsers);
                pResult->SetMessage("No users found on Server");
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
