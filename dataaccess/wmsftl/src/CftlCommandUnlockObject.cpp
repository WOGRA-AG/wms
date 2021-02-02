// WMS Includes
#include "CdmObject.h"


// Own Includes
#include "CftlCommandUnlockObject.h"

CftlCommandUnlockObject::CftlCommandUnlockObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
   m_rpObject(p_pObject)
{
}

CftlCommandUnlockObject::~CftlCommandUnlockObject()
{

}

bool CftlCommandUnlockObject::CheckValid()
{
    return (m_rpObject != nullptr);
}

int CftlCommandUnlockObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
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
        cQSqlQuery.addBindValue(QVariant());
        cQSqlQuery.addBindValue(QVariant());
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
    return lRet;
}
