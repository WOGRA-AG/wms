// WMS Includes
#include "CumUser.h"

// Own Includes
#include "CdbCommandGetUserList.h"

CdbCommandGetUserList::CdbCommandGetUserList(CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess)
{
}

CdbCommandGetUserList::CdbCommandGetUserList(QString p_qstrSearchString, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_qstrSearchString(p_qstrSearchString),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CdbCommandGetUserList::~CdbCommandGetUserList()
{

}

int CdbCommandGetUserList::Execute()
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

QString CdbCommandGetUserList::GetSelectPartOfQuery()
{
    return QString("select UserId, FirstName, LastName, Email, Login, Pass, Admin, Active, Encrypted, SchemeIndependent from WMS_UM_USER wmsuser ");
}

int CdbCommandGetUserList::SetResult(QSqlQuery& p_rQuery)
{
    int lRet = 0;
    p_rQuery.first();
    if(p_rQuery.isValid())
    {
       do
       {
          CumUser* pCumUser = new CumUser(p_rQuery.value(0).toInt(), nullptr);
          // the value at position 0 is the user id and not needed here
          pCumUser->SetFirstName(p_rQuery.value(1).toString());
          pCumUser->SetLastName(p_rQuery.value(2).toString());
          pCumUser->SetEmail(p_rQuery.value(3).toString());
          pCumUser->SetLogin(p_rQuery.value(4).toString());
          pCumUser->SetPassword(p_rQuery.value(5).toString());
          pCumUser->SetAdministrator(p_rQuery.value(6).toBool());
          pCumUser->SetActive(p_rQuery.value(7).toBool());

          m_qllUsers.append(pCumUser);
       }
       while(p_rQuery.next());

       lRet = EC(eDmOk);
    }
    else
    {
       lRet = EC(CdmLogging::eDmFalse);
       INFO("No User found on Db!!!");
    }

    return lRet;
}

QString CdbCommandGetUserList::GenerateJoin()
{
    return "left join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsuser.UserId = wmsscheme.AccessorId where ((wmsscheme.SchmeUri is nullptr and wmsuser.SchemeIndependent = 1) or "
           "wmsscheme.SchmeUri = '" + m_qstrSchemeUri + "')";
}


int CdbCommandGetUserList::FindAllUsers()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = GetSelectPartOfQuery();

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin();
    }

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      lRet = SetResult(cQSqlQuery);
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

int CdbCommandGetUserList::FindUsersByUnknownString()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = GetSelectPartOfQuery();

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin() + " and ";
    }
    else
    {
        qstrQuery += "where ";
    }

    qstrQuery += QString("(LOWER(wmsuser.Email) like '%%1%' or LOWER(wmsuser.Login) like '%%1%' or LOWER(wmsuser.FirstName) like '%%1%' or LOWER(wmsuser.LastName) like '%%1%')")
                       .arg(CwmsUtilities::MaskStringForChanges(m_qstrSearchString.toLower()));

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      SetResult(cQSqlQuery);
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

   return iRet;
}

QList<CumUser*> CdbCommandGetUserList::GetResult()
{
    return m_qllUsers;
}

bool CdbCommandGetUserList::CheckValid()
{
    return true;
}


