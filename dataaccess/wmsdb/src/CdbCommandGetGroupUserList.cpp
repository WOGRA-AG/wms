// WMS Includes
#include "CumUser.h"

// Own Includes
#include "CdbCommandGetUserList.h"
#include "CdbCommandFindUser.h"
#include "CdbCommandGetGroupUserList.h"

CdbCommandGetGroupUserList::CdbCommandGetGroupUserList(long p_lGroup, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lGroupId(p_lGroup)
{
}


CdbCommandGetGroupUserList::~CdbCommandGetGroupUserList()
{

}

QList<CumUser *> CdbCommandGetGroupUserList::GetResult()
{
    return m_qllUserList;
}

int CdbCommandGetGroupUserList::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;

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

int CdbCommandGetGroupUserList::ReadAllUsers()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    INFO("Call read all users");
    CdbCommandGetUserList command(GetDataAccess());
    lRet = command.Run();
    INFO("All users read.")
    m_qllUserList = command.GetResult();
    INFO("User count: " + QString::number(m_qllUserList.count()));
    return lRet;
}

int CdbCommandGetGroupUserList::ReadGroupUsers()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    INFO("Loading all users in group " + QString::number(m_lGroupId));

   qstrQuery = QString("select UserId, FirstName, LastName, Login, Email, Pass, Admin, Active, Encrypted from WMS_UM_USER where UserId in (select UserId from WMS_UM_GROUPMEMBER where GroupId = %1)")
                       .arg(m_lGroupId);

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
       cQSqlQuery.first();

       if (cQSqlQuery.isValid())
       {
       do // loading each value
       {
         CumUser* pUser = new CumUser(cQSqlQuery.value(0).toInt(), nullptr);

         // the value at position 0 is the user id and not needed here
         // Value in col 1 is SurName
         // Value in col 2 is Name
         // Value in col 3 is Login
         // Value in col 4 is Email
         // Value in col 5 is Password

         pUser->SetFirstName(cQSqlQuery.value(1).toString());
         pUser->SetLastName(cQSqlQuery.value(2).toString());
         pUser->SetLogin(cQSqlQuery.value(3).toString());
         pUser->SetEmail(cQSqlQuery.value(4).toString());
         pUser->SetPassword(cQSqlQuery.value(5).toString());
         pUser->SetAdministrator(cQSqlQuery.value(6).toBool());
         pUser->SetActive(cQSqlQuery.value(7).toBool());
         pUser->SetEncrypted(cQSqlQuery.value(8).toBool());
         m_qllUserList.append(pUser);
       }
       while(cQSqlQuery.next());
        }
       else
       {
           lRet = EC(CdmLogging::eDmFalse);
           INFO("could not read users.");
       }
       INFO("User count: " + QString::number(m_qllUserList.count()));
   }
   else
   {
      lRet = EC(eDmInvalidSelectStatement);
   }

    return lRet;
}


bool CdbCommandGetGroupUserList::CheckValid()
{
    return true;
}
