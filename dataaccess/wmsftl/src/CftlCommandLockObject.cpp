//WMS Core includes
#include "CdmSessionManager.h"
#include "CdmObject.h"

// own Includes
#include "CftlCommandCheckObjectLocked.h"
#include "CftlCommandLockObject.h"

CftlCommandLockObject::CftlCommandLockObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpObject(p_pObject)
{
}

CftlCommandLockObject::~CftlCommandLockObject()
{

}

bool CftlCommandLockObject::CheckValid()
{
    return (m_rpObject != nullptr);
}

int CftlCommandLockObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    CftlCommandCheckObjectLocked command(m_rpObject, GetDataAccess());
    lRet = command.Run();

    if(!lRet)
    {
        QString qstrTableName = GetClassTableNameFromObject(m_rpObject);

        if (!qstrTableName.isEmpty())
        {
            QString qstrQuery = QString("update %1 set %2 = ?, %3 = ? where %4 = ?")
                    .arg(qstrTableName)
                    .arg(FTL_LOCKED)
                    .arg(FTL_LOCKED_TIMESTAMP)
                    .arg(FTL_OBJECT_ID_FIELD_NAME);

            QSqlQuery cQSqlQuery(GetSqlDatabase());
            cQSqlQuery.prepare(qstrQuery);
            cQSqlQuery.addBindValue((int)CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
            cQSqlQuery.addBindValue(QDateTime::currentDateTime());
            cQSqlQuery.addBindValue((int)m_rpObject->GetId());

            if (SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
            {
                lRet = EC(eDmTrue);
            }
            else
            {
                lRet = EC(eDmInvalidInsertStatement);
            }
        }
    }
    else
    {
        INFO("Object is locked by another user.");
        lRet = EC(eDmObjectDeathLock);
    }

    return lRet;
}
