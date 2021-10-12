// System and Qt Includes
#include <QSqlQuery>

// WMS Includes
#include "CdmObject.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CftlCommandCheckObjectLocked.h"

// Defines
#define LOCK_TIMEOUT_SECS 300

CftlCommandCheckObjectLocked::CftlCommandCheckObjectLocked(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpObject(p_pObject)
{
}

CftlCommandCheckObjectLocked::~CftlCommandCheckObjectLocked()
{

}

bool CftlCommandCheckObjectLocked::CheckValid()
{
    return (m_rpObject != nullptr && CHKPTR(GetDataAccess()));
}

int CftlCommandCheckObjectLocked::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    QString qstrTableName = GetClassTableNameFromObject(m_rpObject);

    if (!qstrTableName.isEmpty())
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        QString qstrQuery = QString("select %1, %2 from %3 where %4 = ?")
                .arg(FTL_LOCKED)
                .arg(FTL_LOCKED_TIMESTAMP)
                .arg(qstrTableName)
                .arg(FTL_OBJECT_ID_FIELD_NAME);

        cQSqlQuery.prepare(qstrQuery);
        cQSqlQuery.addBindValue(m_rpObject->GetId());

        if (SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
                if (!cQSqlQuery.value(0).isNull())
                {
                   qint64 lSessionId = cQSqlQuery.value(0).toInt();
                    QDateTime qdtLockTimeStamp = cQSqlQuery.value(1).toDateTime();

                    QDateTime current = QDateTime::currentDateTime();

                    if (qdtLockTimeStamp.secsTo(current) >= LOCK_TIMEOUT_SECS)
                    {
                        if (lSessionId != CdmSessionManager::GetSessionManager()->GetCurrentSessionId())
                        {
                            lRet = EC(eDmTrue);
                        }
                        else
                        {
                            lRet = EC(eDmFalse);
                        }
                    }
                    else
                    {
                        lRet = EC(eDmFalse);
                    }
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
        lRet = CdmLogging::eDmLockingError;
        ERR("Tablename for object not ofund.");
    }

    return lRet;
}
