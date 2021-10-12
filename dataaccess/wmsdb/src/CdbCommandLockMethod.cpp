#include "CdbCommandLockMethod.h"

CdbCommandLockMethod::CdbCommandLockMethod(qint64 p_lMethodId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lMethodId(p_lMethodId),
  m_bResult(true)
{
}

CdbCommandLockMethod::~CdbCommandLockMethod()
{

}

bool CdbCommandLockMethod::CheckValid()
{
    return (m_lSessionId > 0 && m_lMethodId > 0);
}

int CdbCommandLockMethod::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery;
    QString qstrSql;
    // first check if method is locked
    qstrSql = QString("select lmet.SessionId, wmsuser.login from WMS_CLASS_LOCKEDMETHOD lmet "
                      "inner join WMS_UM_SESSION ses  on ses.Sessionid = lmet.Sessionid "
                      "inner join WMS_UM_USER wmsuser on wmsuser.UserID = ses.UserId  "
                      "where lmet.SessionId <> %1 and ses.State = 1 and lmet.MethodId = %2")
    .arg(m_lSessionId)
    .arg(m_lMethodId);

    if (ExecuteQuery(qstrSql, cQuery) > 0)
    {
       cQuery.first();
       if(cQuery.isValid())
       {
         qint64 lSessionId = cQuery.value(0).toInt();
          QString qstrLogin = cQuery.value(1).toString();
          ERR("The method is under examination by User " + qstrLogin + ". SessionId: "
              + QString::number(lSessionId));
       }
       else
       {
          // lock method
          qstrSql = QString("insert into WMS_CLASS_LOCKEDMETHOD (SessionId, MethodId) values(%1, %2)")
             .arg(m_lSessionId)
             .arg(m_lMethodId);

          if (ExecuteQuery(qstrSql, cQuery) > 0)
          {
             INFO("Method locked. ID: " + QString::number(m_lMethodId));
             m_bResult = true;
          }
          else
          {
             ERR("Could not lock method.");
          }
       }
    }


    return iRet;
}

bool CdbCommandLockMethod::GetResult()
{
    return m_bResult;
}
