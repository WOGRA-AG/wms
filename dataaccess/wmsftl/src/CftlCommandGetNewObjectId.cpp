// System and Qt Includes
#include <QSqlQuery>
#include <QDateTime>
#include <QUuid>

// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsUtilities.h"
#include "CftlCommandGetNewObjectId.h"

#define INIT_OBJECT_NAME "NewObject"

CftlCommandGetNewObjectId::CftlCommandGetNewObjectId(const CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_rpContainer(p_pContainer)
{
}

CftlCommandGetNewObjectId::~CftlCommandGetNewObjectId()
{

}

bool CftlCommandGetNewObjectId::CheckValid()
{
    return (CHKPTR(m_rpContainer) && CHKPTR(GetDataAccess()));
}

int CftlCommandGetNewObjectId::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    QString qstrTableName = GetClassTableNameFromContainer(m_rpContainer);
    QDateTime qdtCreatedDate = QDateTime::currentDateTime();
    QString qstrTempKeyname = QUuid::createUuid().toString()
            .remove("-")
            .remove("{")
            .remove("}");

    QSqlQuery cQuery(GetSqlDatabase());
    QString qstrQuery = QString("insert into %1 (%2, %3, %4, %5, %6, %7, %8) values(?, ?, ?, ?, ?, ?, ?)")
            .arg(qstrTableName)
            .arg(FTL_CONTAINER_ID_FIELD_NAME)
            .arg(FTL_OBJECT_KEYNAME_FIELD_NAME)
            .arg(FTL_MODIFIER_ID)
            .arg(FTL_CREATOR_ID)
            .arg(FTL_CREATED)
            .arg(FTL_LAST_MODIFIED)
            .arg(FTL_SESSION_ID);

    cQuery.prepare(qstrQuery);
    cQuery.addBindValue(m_rpContainer->GetId());
    cQuery.addBindValue(qstrTempKeyname);
    cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    cQuery.addBindValue(qdtCreatedDate);
    cQuery.addBindValue(qdtCreatedDate);
    cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        QString qstrQuery = QString("select %1 from %2 where %3 = ? and %4 = ? and %5 = ? and %6 = ?")
                .arg(FTL_OBJECT_ID_FIELD_NAME)
                .arg(qstrTableName)
                .arg(FTL_CONTAINER_ID_FIELD_NAME)
                .arg(FTL_MODIFIER_ID)
                .arg(FTL_SESSION_ID)
                .arg(FTL_OBJECT_KEYNAME_FIELD_NAME);
        cQuery.prepare(qstrQuery);
        cQuery.addBindValue(m_rpContainer->GetId());
        cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
        cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
        cQuery.addBindValue(qstrTempKeyname);

        if (SUCCESSFULL(ExecuteQuery(cQuery)))
        {
            cQuery.first();
            if(cQuery.isValid())
            {
               // Value in col 0 is ObjectId
               lRet = cQuery.value(0).toInt();
            }
            else
            {
               lRet = EC(eDmNoUniqueId);
               ERR("Inserted ObjectId not found. This is strange, because the insert was successfull.");
            }
         }
         else
         {
            lRet = EC(eDmInvalidSelectStatement);
            ERR("Getting new Object Id failed (SELECT COMMAND).");
         }
    }
    else
    {
       lRet = EC(eDmInvalidInsertStatement);
       ERR("Getting new Object Id failed (INSERT COMMAND).");
    }

    return lRet;
}
