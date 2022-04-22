// System and Qt Includes
#include <QSqlQuery>

#include "CdbCommandCheckObjectLocked.h"

CdbCommandCheckObjectLocked::CdbCommandCheckObjectLocked(qint64 p_lObjectId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lObjectId(p_lObjectId),
  m_lSessionId(p_lSessionId)
{
}

CdbCommandCheckObjectLocked::~CdbCommandCheckObjectLocked()
{

}

bool CdbCommandCheckObjectLocked::CheckValid()
{
    return (m_lObjectId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

int CdbCommandCheckObjectLocked::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // asking table if this object is inserted
    qstrQuery = QString("SELECT ses.SessionId FROM WMS_DM_LOCKEDOBJECT lo inner join WMS_UM_SESSION ses on lo.SessionId = ses.SessionId "
                        "where lo.objectid = %1 and ses.SessionId <> %2 and ses.State = 1")
                        .arg(m_lObjectId)
                        .arg(m_lSessionId);

    if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          qint64 lSessionId = cQSqlQuery.value(0).toInt();
          INFO("Object with ID" + QString::number(m_lObjectId) +
               " is locked by session " + QString::number(lSessionId));
          lRet = EC(eDmTrue);
        }
       else
       {
          lRet = EC(eDmFalse);
          INFO("Object is not locked.");
       }
    }

    return lRet;
}
