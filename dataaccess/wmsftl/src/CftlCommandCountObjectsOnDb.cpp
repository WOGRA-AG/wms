#include "CdmObjectContainer.h"

#include "CftlCommandCountObjectsOnDb.h"

CftlCommandCountObjectsOnDb::CftlCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer)
{
}

CftlCommandCountObjectsOnDb::~CftlCommandCountObjectsOnDb()
{

}

bool CftlCommandCountObjectsOnDb::CheckValid()
{
    return CHKPTR(m_rpContainer);
}

int CftlCommandCountObjectsOnDb::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(m_rpContainer))
    {
        long lContainerId = m_rpContainer->GetId();

        if (lContainerId > 0)
        {
            QString qstrTableName = GetClassTableNameFromContainerId(lContainerId);

            if (!qstrTableName.isEmpty())
            {
                QSqlQuery cQSqlQuery(GetSqlDatabase());
                QString qstrQuery = QString("select COUNT(*) from %1 where %2 = ?")
                        .arg(qstrTableName)
                        .arg(FTL_CONTAINER_ID_FIELD_NAME);
                cQSqlQuery.prepare(qstrQuery);
                cQSqlQuery.addBindValue((int)lContainerId);

                lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

                if(lRet > 0)
                {
                    cQSqlQuery.first();

                    if(cQSqlQuery.isValid())
                    {
                        lRet = cQSqlQuery.value(0).toInt();
                    }
                    else
                    {
                        lRet = CdmLogging::eDmFalse;
                    }
                }
            }
            else
            {
                ERR("Could not find table name for objectcontainer");
            }
        }
    }

    return lRet;
}
