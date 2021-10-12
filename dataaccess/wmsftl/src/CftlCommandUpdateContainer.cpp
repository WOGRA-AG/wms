#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmSessionManager.h"

#include "CftlJournal.h"
#include "CftlCommandDeleteObject.h"
#include "CftlCommandUpdateObject.h"
#include "CftlCommandUpdateContainer.h"

CftlCommandUpdateContainer::CftlCommandUpdateContainer(CdmObjectContainer*& p_pContainer, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpObjectContainer(p_pContainer)
{
}

CftlCommandUpdateContainer::~CftlCommandUpdateContainer()
{

}

bool CftlCommandUpdateContainer::CheckValid()
{
    return (CHKPTR(m_rpObjectContainer));
}

int CftlCommandUpdateContainer::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(m_rpObjectContainer->IsModified() || m_rpObjectContainer->IsNew())
    {
        if (m_rpObjectContainer->IsNew())
        {
            CftlJournal* pJournal = GetDataAccess()->GetJournal();

            if (pJournal)
            {
                lRet = pJournal->ObjectListModified(m_rpObjectContainer);
            }
        }

        // first step updating all objects
        QList<CdmObject*> qvlObjects;
        qvlObjects = m_rpObjectContainer->GetNewModifiedList();

        if (qvlObjects.count() > 0)
        {
            lRet = UpdateObjects(m_rpObjectContainer, qvlObjects);
        }
        qvlObjects = m_rpObjectContainer->GetDeletedList();

        if (qvlObjects.count() > 0)
        {
            lRet = DeleteObjects(m_rpObjectContainer, qvlObjects);
        }

        // second step update objectlist itself
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        // query for reading new id
        cQSqlQuery.prepare("Update WMS_DM_CONTAINER set Keyname = ?, LastChange = ?, ModifierId = ?, Caption = ?, Comment = ?, TempSessionId = 0, Tree = ?"
                           " where ContainerId = ?");
        cQSqlQuery.addBindValue(m_rpObjectContainer->GetKeyname());
        cQSqlQuery.addBindValue(QDateTime::currentDateTime());
        cQSqlQuery.addBindValue(m_rpObjectContainer->GetModifierId());
        cQSqlQuery.addBindValue(m_rpObjectContainer->GetCaption());
        cQSqlQuery.addBindValue(m_rpObjectContainer->GetComment());
        cQSqlQuery.addBindValue(m_rpObjectContainer->IsTree());
        cQSqlQuery.addBindValue(m_rpObjectContainer->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            lRet = UpdateRights(m_rpObjectContainer);
            m_rpObjectContainer->ResetNewModified();
        }
        else
        {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update Objectlist itselves failed!!!");
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

qint64 CftlCommandUpdateContainer::UpdateObjects(CdmObjectContainer* p_pContainer,
                                               QList<CdmObject*>& p_rqlObjects)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    QList<CdmObject*>::iterator qvlIt    = p_rqlObjects.begin();
    QList<CdmObject*>::iterator qvlItEnd = p_rqlObjects.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        CdmObject* pCdmObject = (*qvlIt);

        if(CHKPTR(pCdmObject))
        {
           qint64 lObjectId = pCdmObject->GetId();
            CftlCommandUpdateObject command(pCdmObject, GetDataAccess());
            lRet = command.Run();

            if(!pCdmObject)
            {
                CdmDataAccessHelper::RemoveObjectFromObjectList(p_pContainer, lObjectId);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }

        if(lRet < 0)
        {
            ERR("Error occured while trying to update objects from object list!!!");
            break;
        }
    }

    return lRet;
}

qint64 CftlCommandUpdateContainer::DeleteObjects(CdmObjectContainer* p_pContainer,
                                               QList<CdmObject*>& p_rqlObjects)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    QList<CdmObject*>::iterator qvlIt    = p_rqlObjects.begin();
    QList<CdmObject*>::iterator qvlItEnd = p_rqlObjects.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        CdmObject* pCdmObject = (*qvlIt);

        if(CHKPTR(pCdmObject))
        {
           qint64 lObjectId = pCdmObject->GetId();
            CftlCommandDeleteObject command(pCdmObject, GetDataAccess());
            lRet = command.Run();

            if(lRet > 0)
            {
                CdmDataAccessHelper::DeleteObject(pCdmObject);
            }
            else
            {
                ERR("DeleteObject failed!");
            }

            if(!pCdmObject)
            {
                CdmDataAccessHelper::RemoveObjectFromObjectList(p_pContainer, lObjectId);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }

        if(lRet < 0)
        {
            ERR("Error occured while trying to update objects from object list!!!");
            break;
        }
    }

    return lRet;
}

qint64 CftlCommandUpdateContainer::UpdateRights(CdmObjectContainer*& p_pContainer)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(p_pContainer))
    {
        if(p_pContainer->IsAccessorListModified())
        {
            QSqlQuery cQSqlQuery(GetSqlDatabase());
            // query for reading new id
            cQSqlQuery.prepare("delete from WMS_DM_ACCESSORRIGHT where ObjectListId = ?");
            cQSqlQuery.addBindValue(p_pContainer->GetId());

            lRet = ExecuteQuery(cQSqlQuery);

            if(SUCCESSFULL(lRet))
            {
                QMap<int, EdmRight> qmRights = p_pContainer->GetAccessorMap();
                if (qmRights.count() > 0)
                {
                    QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
                    QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();
                    QVariantList qvlAccessorId;
                    QVariantList qvlContainerId;
                    QVariantList qvlRights;

                    for (; qmIt != qmItEnd; ++qmIt)
                    {
                        qvlAccessorId.append(qmIt.key());
                        qvlContainerId.append(p_pContainer->GetId());
                        qvlRights.append(qmIt.value());

                    }

                    cQSqlQuery.prepare("insert into WMS_DM_ACCESSORRIGHT (AccessorId, ObjectListId, AccessRight)"
                                       " values(?, ?, ?)");
                    cQSqlQuery.addBindValue(qvlAccessorId);
                    cQSqlQuery.addBindValue(qvlContainerId);
                    cQSqlQuery.addBindValue(qvlRights);

                    if(!cQSqlQuery.execBatch())
                    {
                        lRet = EC(eDmInvalidUpdateStatement);
                        ERR("Update Objectlist rights failed!!!");
                    }
                }
            }
        }
        else
        {
            lRet = EC(eDmOk);
        }
    }

    return lRet;
}
