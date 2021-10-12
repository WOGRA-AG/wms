// System and Qt Includes
#include <QSqlQuery>

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// Own Includes
#include "CftlJournal.h"
#include "CftlCommandDeleteContainer.h"

CftlCommandDeleteContainer::CftlCommandDeleteContainer(qint64 p_lContainerId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lContainerId(p_lContainerId)
{
}

CftlCommandDeleteContainer::~CftlCommandDeleteContainer()
{
}

bool CftlCommandDeleteContainer::CheckValid()
{
    return (m_lContainerId > 0);
}

const CdmClass *CftlCommandDeleteContainer::GetClassFromContainerId(qint64 p_lId)
{
    const CdmClass* pClass = nullptr;
    CdmDataProvider* pDataProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmContainerManager* pContainerManager = pDataProvider->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(p_lId);

            if (CHKPTR(pContainer))
            {
                 pClass = pContainer->GetClass();
                 pContainerManager->RemoveContainerLocally(pContainer);
            }
        }
    }

    return pClass;

}

int CftlCommandDeleteContainer::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(GetDataAccess()))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        QString qstrTableName = GetClassTableNameFromContainerId(m_lContainerId);

        if (!qstrTableName.isEmpty())
        {
            QString qstrQuery = QString("delete from %1 where %2 = ?")
                    .arg(qstrTableName)
                    .arg(FTL_CONTAINER_ID_FIELD_NAME);

            cQSqlQuery.prepare(qstrQuery);
            cQSqlQuery.addBindValue(m_lContainerId);

            if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
            {
                cQSqlQuery.prepare("delete from WMS_DM_CONTAINER_REFERENCE where ContainerId = ?");
                cQSqlQuery.addBindValue(m_lContainerId);

                if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                {
                    cQSqlQuery.prepare("delete from WMS_DM_CONTAINER where ContainerId = ?");
                    cQSqlQuery.addBindValue(m_lContainerId);
                    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                    {
                        CftlJournal* pJournal = GetDataAccess()->GetJournal();

                        if (pJournal)
                        {


                            lRet = pJournal->ObjectListDeleted(m_lContainerId);

                        }
                    }
                }
                else
                {
                    ERR("Deleting in reference table doesn't work");
                    lRet = EC(eDmInvalidDeleteStatement);
                }
            }
            else
            {
                ERR("Delete Container failed!!!");
                lRet = EC(eDmInvalidDeleteStatement);
            }
        }
        else
        {
            ERR("Could not found tablename for container");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}


