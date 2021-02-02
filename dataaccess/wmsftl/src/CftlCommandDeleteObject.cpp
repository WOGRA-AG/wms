// System and Qt Includes
#include <QSqlQuery>
#include <QDate>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes
#include "CftlJournal.h"
#include "CftlCommandCheckObjectLocked.h"
#include "CftlCommandDeleteObject.h"

CftlCommandDeleteObject::CftlCommandDeleteObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpObject(p_pObject)
{
}

CftlCommandDeleteObject::~CftlCommandDeleteObject()
{

}

bool CftlCommandDeleteObject::CheckValid()
{
    return (CHKPTR(m_rpObject) && CHKPTR(GetDataAccess()));
}

int CftlCommandDeleteObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(GetDataAccess()))
    {
        CftlCommandCheckObjectLocked checkObjectLocked(m_rpObject, GetDataAccess());

        if(!checkObjectLocked.Run())
        {
            QString qstrTableName = GetClassTableNameFromObject(m_rpObject);

            if (!qstrTableName.isEmpty())
            {
                QSqlQuery cQSqlQuery(GetSqlDatabase());
                QString qstrQuery = QString("delete from %1 where %2 = ?")
                        .arg(qstrTableName)
                        .arg(FTL_OBJECT_ID_FIELD_NAME);
                cQSqlQuery.prepare(qstrQuery);
                cQSqlQuery.addBindValue((int)m_rpObject->GetId());

                if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                {
                    cQSqlQuery.prepare("delete from WMS_DM_OBJECT_REFERENCE where (ObjectId = ? and ContainerId = ?) or (Ref_Object_ID = ? and Ref_Container_ID = ?)");
                    cQSqlQuery.addBindValue((int)m_rpObject->GetId());
                    cQSqlQuery.addBindValue((int)m_rpObject->GetObjectContainerId());
                    cQSqlQuery.addBindValue((int)m_rpObject->GetId());
                    cQSqlQuery.addBindValue((int)m_rpObject->GetObjectContainerId());

                    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                    {
                        CftlJournal* pJournal = GetDataAccess()->GetJournal();

                        if (pJournal)
                        {
                            lRet = pJournal->ObjectDeleted(m_rpObject->GetId());
                        }
                    }
                }
                else
                {
                    lRet = EC(eDmInvalidDeleteStatement);
                    ERR("The query execution failed!!");
                }
            }
            else
            {
                ERR("Tablename for object not found");
            }
        }
        else
        {
            lRet = EC(eDmObjectDeathLock);
            ERR("Cannot delete object because it's locked.");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;

}
