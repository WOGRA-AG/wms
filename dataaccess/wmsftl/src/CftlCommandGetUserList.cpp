// WMS Includes
#include "CumUser.h"

// Own Includes
#include "CftlCommandGetUserList.h"

CftlCommandGetUserList::CftlCommandGetUserList(CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess)
{
}

CftlCommandGetUserList::CftlCommandGetUserList(QString p_qstrSearchString, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_qstrSearchString(p_qstrSearchString)
{
}

CftlCommandGetUserList::~CftlCommandGetUserList()
{

}

int CftlCommandGetUserList::Execute()
{
    if (m_qstrSearchString.isEmpty())
    {
        return FindAllUsers();
    }
    else
    {
        return FindUsersByUnknownString();
    }
}

int CftlCommandGetUserList::FindAllUsers()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select UserId, FirstName, LastName, Login, Email, Pass, Admin, Active from WMS_UM_USER");

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         do
         {
            CumUser* pCumUser = new CumUser(cQSqlQuery.value(0).toInt(), nullptr);
            // the value at position 0 is the user id and not needed here
            // Value in col 1 is SurName
            // Value in col 2 is Name
            // Value in col 3 is Login
            // Value in col 4 is Email
            // Value in col 5 is Password

            pCumUser->SetFirstName(cQSqlQuery.value(1).toString());
            pCumUser->SetLastName(cQSqlQuery.value(2).toString());
            pCumUser->SetLogin(cQSqlQuery.value(3).toString());
            pCumUser->SetEmail(cQSqlQuery.value(4).toString());
            pCumUser->SetPassword(cQSqlQuery.value(5).toString());
            pCumUser->SetAdministrator(cQSqlQuery.value(6).toBool());
            pCumUser->SetActive(cQSqlQuery.value(7).toBool());

            m_qllUsers.append(pCumUser);
         }
         while(cQSqlQuery.next());

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         INFO("No User found on Db!!!");
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

int CftlCommandGetUserList::FindUsersByUnknownString()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

   cQSqlQuery.prepare("select UserId, FirstName, LastName, Login, Email, Pass, Admin, Active, Encrypted from WMS_UM_USER where Email like ? or Login like ? or LastName like ?");
   cQSqlQuery.addBindValue("%" + m_qstrSearchString + "%");
   cQSqlQuery.addBindValue("%" + m_qstrSearchString + "%");
   cQSqlQuery.addBindValue("%" + m_qstrSearchString + "%");

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      while(cQSqlQuery.isValid())
      {
         CumUser* pCumUser = new CumUser(cQSqlQuery.value(0).toInt(), nullptr);

         // the value at position 0 is the user id and not needed here
         // Value in col 1 is SurName
         // Value in col 2 is Name
         // Value in col 3 is Login
         // Value in col 4 is Email
         // Value in col 5 is Password

         pCumUser->SetFirstName(cQSqlQuery.value(1).toString());
         pCumUser->SetLastName(cQSqlQuery.value(2).toString());
         pCumUser->SetLogin(cQSqlQuery.value(3).toString());
         pCumUser->SetEmail(cQSqlQuery.value(4).toString());
         pCumUser->SetPassword(cQSqlQuery.value(5).toString());
         pCumUser->SetAdministrator(cQSqlQuery.value(6).toBool());
         pCumUser->SetActive(cQSqlQuery.value(7).toBool());
         pCumUser->SetEncrypted(cQSqlQuery.value(8).toBool());

         m_qllUsers.append(pCumUser);
         iRet = EC(eDmOk);
         cQSqlQuery.next();
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

   return iRet;
}

QList<CumUser*> CftlCommandGetUserList::GetResult()
{
    return m_qllUsers;
}

bool CftlCommandGetUserList::CheckValid()
{
    return true;
}
