//WMS Manager Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"

//Basetools Includes
#include "CwmsContext.h"

//own includes
#include "CwiSessionlessAccess.h"
#include "CwiCommandGetGroupUserList.h"

CwiCommandGetGroupUserList::CwiCommandGetGroupUserList(CwmscomData* p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetGroupUserList::~CwiCommandGetGroupUserList()
{

}

QList<CumUser*> CwiCommandGetGroupUserList::GetResult()
{
    return m_qlUserList;
}

QVariantList CwiCommandGetGroupUserList::GetResultToVariant(QList<CumUser*> ql_userList)
{
    QList<CumUser*>::iterator qlIt = ql_userList.begin();
    QList<CumUser*>::iterator qlItEnd = ql_userList.end();

    for(; qlIt != qlItEnd; ++qlIt)
    {
        CumUser *ptempUser = (*qlIt);
        m_qlUserListToVariant.append(ptempUser->GetVariant());
    }
    return m_qlUserListToVariant;
}

long CwiCommandGetGroupUserList::ReadAllUsers()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QList<CumUser*> qll_userList;
    lRet = pCumUserManager->GetUserListUnmanaged(qll_userList);

    QList<CumUser*>::iterator qllIt = qll_userList.begin();
    QList<CumUser*>::iterator qllItEnd = qll_userList.end();

    for(; qllIt != qllItEnd; ++qllIt)
    {
        CumUser *ptempUser = (*qllIt);
        m_qlUserList.append(ptempUser);
    }
    return lRet;
}

void CwiCommandGetGroupUserList::Execute()
{
    CwiSessionlessAccess access;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);
    int iGroupId = m_rpData->GetValue("Name").toInt();

    if(pCdmManager)
    {
        pCumUserManager = pCdmManager->GetUserManager();
        if(pCumUserManager)
        {
            long lRetAllUsers = ReadAllUsers();
            if(lRetAllUsers > 0)
            {
                //QList<CumUser*> qll_UserList = GetResult();
                QList<CumUser*> qll_UserList;
                pCumUserManager->GetListOfUsersInList(iGroupId, qll_UserList);
                QVariantList qvlUsersInGroup = GetResultToVariant(qll_UserList);
                if(!qvlUsersInGroup.isEmpty())
                {
                    pResult->AddValue("User", qvlUsersInGroup);
                    pResult->SetMessage("Users Found in Group!");
                    pResult->SetMessageCode(1);
                    pResult->SetSeverity(eWmscomMessageServerityInfo);
                }
                else
                {
                    pResult->SetMessage("No Users with membership to Group found.");
                    pResult->SetMessageCode(CdmLogging::eDmFalse);
                    pResult->SetSeverity(eWmscomMessageServerityError);
                }
            }
            else {
                pResult->SetMessage("No Users found");
                pResult->SetMessageCode(-5000);
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
