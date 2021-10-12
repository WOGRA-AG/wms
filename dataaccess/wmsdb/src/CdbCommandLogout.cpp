#include "CdbCommandLogout.h"

CdbCommandLogout::CdbCommandLogout(qint64 p_lSessionId,CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSessionId(p_lSessionId)
{
}

CdbCommandLogout::~CdbCommandLogout()
{

}

int CdbCommandLogout::Execute()
{
  qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   qstrQuery = QString("update WMS_UM_SESSION set State = %1, LogOutDate = %2 "
                       "where SessionId = %3")
                     .arg("false")
                     .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                     .arg(m_lSessionId);

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      lRet = EC(eDmOk);
   }
   else
   {
      lRet = EC(eDmInvalidUpdateStatement);
      ERR("Logout was not successfull!!");
   }


    return lRet;
}

bool CdbCommandLogout::CheckValid()
{
    return (m_lSessionId > 0);
}

bool CdbCommandLogout::NeedsActiveSession()
{
    return false;
}
