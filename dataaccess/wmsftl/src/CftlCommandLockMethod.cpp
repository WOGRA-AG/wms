#include "CdmSessionManager.h"


#include "CftlCommandLockMethod.h"

CftlCommandLockMethod::CftlCommandLockMethod(long p_lMethodId, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lMethodId(p_lMethodId),
  m_bResult(true)
{
}

CftlCommandLockMethod::~CftlCommandLockMethod()
{

}

bool CftlCommandLockMethod::CheckValid()
{
    return (m_lMethodId > 0);
}

int CftlCommandLockMethod::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    long lSessionId = CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
    QSqlQuery cQuery(GetSqlDatabase());
    QString qstrSql;
    // first check if method is locked
    cQuery.prepare("select lmet.SessionId, wmsuser.login from WMS_CLASS_LOCKEDMETHOD lmet "
                      "inner join WMS_UM_SESSION ses  on ses.Sessionid = lmet.Sessionid "
                      "inner join WMS_UM_USER wmsuser on wmsuser.UserID = ses.UserId  "
                      "where lmet.SessionId <> ? and ses.State = 1 and lmet.MethodId = ?");
    cQuery.addBindValue((int)lSessionId);
    cQuery.addBindValue((int)m_lMethodId);

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
       cQuery.first();
       if(cQuery.isValid())
       {
          long lSessionId = cQuery.value(0).toInt();
          QString qstrLogin = cQuery.value(1).toString();
          ERR("The method is under examination by User " + qstrLogin + ". SessionId: "
              + QString::number(lSessionId));
       }
       else
       {
          // lock method
          cQuery.prepare("insert into WMS_CLASS_LOCKEDMETHOD (SessionId, MethodId) values(?, ?)");
          cQuery.addBindValue((int)lSessionId);
          cQuery.addBindValue((int)m_lMethodId);

          if (SUCCESSFULL(ExecuteQuery(cQuery)))
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

bool CftlCommandLockMethod::GetResult()
{
    return m_bResult;
}
