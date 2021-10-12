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
    qstrQuery = QString("select SessionId from WMS_DM_LOCKEDOBJECT where ObjectId = %1")
                        .arg(m_lObjectId);

    if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       cQSqlQuery.first();
       if(cQSqlQuery.isValid())
       {
         qint64 lSessionId = cQSqlQuery.value(0).toInt();
          INFO("Object with ID" + QString::number(m_lObjectId) +
               " is locked by session " + QString::number(m_lSessionId));

          if(lSessionId == m_lSessionId)
          {
             lRet = EC(eDmFalse);
             INFO("Object is locked by the same user, so it plays no role if this object is locked or not, he has all rigths.");
          }
          else
          {
             // Check if locking session is valid
             qstrQuery = QString ("select State from WMS_UM_SESSION where SessionId = %1").arg(lSessionId);

             if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
             {
                cQSqlQuery.first();

                if(cQSqlQuery.isValid())
                {
                   lRet = cQSqlQuery.value(0).toBool();
                }
                else
                {
                   lRet = EC(eDmFalse);
                }
             }
          }
       }
       else
       {
          lRet = EC(eDmFalse);
          INFO("Object is not locked.");
       }
    }

    return lRet;
}
