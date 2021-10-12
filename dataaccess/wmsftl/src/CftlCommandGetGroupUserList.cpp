// WMS Includes
#include "CumUser.h"

// Own Includes
#include "CftlCommandGetUserList.h"
#include "CftlCommandFindUser.h"
#include "CftlCommandGetGroupUserList.h"

CftlCommandGetGroupUserList::CftlCommandGetGroupUserList(qint64 p_lGroup, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lGroupId(p_lGroup)
{
}


CftlCommandGetGroupUserList::~CftlCommandGetGroupUserList()
{

}

QList<CumUser *> CftlCommandGetGroupUserList::GetResult()
{
    return m_qllUserList;
}

int CftlCommandGetGroupUserList::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;

    if(m_lGroupId <= 0)
    {
       lRet = ReadAllUsers();
    }
    else
    {
      lRet = ReadGroupUsers();
    }

    return lRet;
}

int CftlCommandGetGroupUserList::ReadAllUsers()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    CftlCommandGetUserList command(GetDataAccess());
    lRet = command.Run();
    m_qllUserList = command.GetResult();
    return lRet;
}

QString CftlCommandGetGroupUserList::CreateSelectPart()
{
    return "select user.UserId, FirstName, LastName, Login, Email, Pass, Admin, Active, Encrypted from WMS_UM_USER user ";
}

int CftlCommandGetGroupUserList::ReadGroupUsers()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare(CreateSelectPart() + "inner join WMS_UM_GROUPMEMBER member on user.userid = member.userid where member.GroupId = ?");
    cQSqlQuery.addBindValue(m_lGroupId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       cQSqlQuery.first();
       if(cQSqlQuery.isValid())
       {
          cQSqlQuery.first();

          do // loading each value
          {
             m_qllUserList.append(CreateUserObjectFromQuery(cQSqlQuery));
          }
          while(cQSqlQuery.next());

          lRet = EC(eDmOk);
       }
       else
       {
          lRet = EC(CdmLogging::eDmFalse);
          INFO("no users found on Db.");
       }
    }
    else
    {
       lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

CumUser* CftlCommandGetGroupUserList::CreateUserObjectFromQuery(QSqlQuery& p_rQuery)
{
    CumUser* pUser = new CumUser(p_rQuery.value(0).toInt(), nullptr);

    // the value at position 0 is the user id and not needed here
    // Value in col 1 is SurName
    // Value in col 2 is Name
    // Value in col 3 is Login
    // Value in col 4 is Email
    // Value in col 5 is Password

    pUser->SetFirstName(p_rQuery.value(1).toString());
    pUser->SetLastName(p_rQuery.value(2).toString());
    pUser->SetLogin(p_rQuery.value(3).toString());
    pUser->SetEmail(p_rQuery.value(4).toString());
    pUser->SetPassword(p_rQuery.value(5).toString());
    pUser->SetAdministrator(p_rQuery.value(6).toBool());
    pUser->SetActive(p_rQuery.value(7).toBool());
    pUser->SetEncrypted(p_rQuery.value(8).toBool());

    return pUser;
}

bool CftlCommandGetGroupUserList::CheckValid()
{
    return true;
}
