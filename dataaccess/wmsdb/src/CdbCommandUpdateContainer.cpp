#include "CdmObjectContainer.h"
#include "CdmObject.h"

#include "CdbJournal.h"
#include "CdbCommandDeleteObject.h"
#include "CdbCommandUpdateObject.h"
#include "CdbCommandUpdateContainer.h"

CdbCommandUpdateContainer::CdbCommandUpdateContainer(CdmObjectContainer*& p_pContainer, long p_lSessionId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_rpObjectContainer(p_pContainer),
      m_lSessionId(p_lSessionId)
{
}

CdbCommandUpdateContainer::~CdbCommandUpdateContainer()
{

}

bool CdbCommandUpdateContainer::CheckValid()
{
    return (CHKPTR(m_rpObjectContainer) && m_lSessionId > 0);
}

int CdbCommandUpdateContainer::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if(m_rpObjectContainer->IsModified() || m_rpObjectContainer->IsNew())
    {
       if (m_rpObjectContainer->IsNew())
       {
          CdbJournal* pJournal = GetDataAccess()->GetJournal();

          if (pJournal)
          {
             lRet = pJournal->ObjectListModified(m_rpObjectContainer);
          }
       }

       // first step updating all objects
       QList<CdmObject*> qvlObjects;
       qvlObjects = m_rpObjectContainer->GetNewModifiedList();
       lRet = UpdateObjects(m_rpObjectContainer, qvlObjects, m_lSessionId);
       qvlObjects = m_rpObjectContainer->GetDeletedList();
       lRet = DeleteObjects(m_rpObjectContainer, qvlObjects, m_lSessionId);

       // second step update objectlist itself
       QSqlQuery cQSqlQuery;
       QString qstrQuery;
       // query for reading new id
       qstrQuery = QString("Update WMS_DM_OBJECTLIST set Keyname = '%1', LastChange = %2, ModifierId = %3, Caption = '%4', Comment = '%5', TempSessionId = 0, Tree = %6, config = '%7'"
                           " where ObjectListId = %8")
                           .arg(CwmsUtilities::MaskStringForChanges(m_rpObjectContainer->GetKeyname()))
                           .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                           .arg(m_rpObjectContainer->GetModifierId())
                           .arg(CwmsUtilities::MaskStringForChanges(m_rpObjectContainer->GetCaption()))
                           .arg(CwmsUtilities::MaskStringForChanges(m_rpObjectContainer->GetComment()))
                           .arg(CwmsUtilities::ConvertBoolToString(m_rpObjectContainer->IsTree()))
                           .arg(CwmsUtilities::MaskStringForChanges(m_rpObjectContainer->GetConfig()))
                           .arg(m_rpObjectContainer->GetId());

       lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

       if(lRet <= 0)
       {
          lRet = EC(eDmInvalidUpdateStatement);
          ERR("Update Objectlist itselves failed!!!");
       }
       else
       {
          lRet = UpdateRights(m_rpObjectContainer);
          m_rpObjectContainer->ResetNewModified();
       }
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    return lRet;
 }

 long CdbCommandUpdateContainer::UpdateObjects(CdmObjectContainer* p_pContainer,
                                       QList<CdmObject*>& p_rqlObjects,
                                       long p_lSessionId)
 {
    long lRet = CdmLogging::eDmObjectAccessError;
    QList<CdmObject*>::iterator qvlIt    = p_rqlObjects.begin();
    QList<CdmObject*>::iterator qvlItEnd = p_rqlObjects.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
       CdmObject* pCdmObject = (*qvlIt);

       if(CHKPTR(pCdmObject))
       {
 #ifdef WOGRA_DEBUG
          if (pCdmObject->GetObjectContainerId() == 0)
          {
             ERR("ObjectlistId in Object is 0.\n Objectinfo:\n" + pCdmObject->GetInfo());

          }
 #endif //
          long lObjectId = pCdmObject->GetId();

          CdbCommandUpdateObject command(p_lSessionId, pCdmObject, GetDataAccess());
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

 long CdbCommandUpdateContainer::DeleteObjects(CdmObjectContainer* p_pContainer,
                                       QList<CdmObject*>& p_rqlObjects,
                                       long p_lSessionId)
 {
    long lRet = CdmLogging::eDmObjectAccessError;
    QList<CdmObject*>::iterator qvlIt    = p_rqlObjects.begin();
    QList<CdmObject*>::iterator qvlItEnd = p_rqlObjects.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
       CdmObject* pCdmObject = (*qvlIt);

       if(CHKPTR(pCdmObject))
       {
 #ifdef WOGRA_DEBUG
          if (pCdmObject->GetObjectContainerId() == 0)
          {
             ERR("ObjectlistId in Object is 0.\n Objectinfo:\n" + pCdmObject->GetInfo());

          }
 #endif //
          long lObjectId = pCdmObject->GetId();
          CdbCommandDeleteObject command(lObjectId, p_lSessionId, GetDataAccess());
          lRet = command.Run();

          if(lRet > 0)
          {
             CdbJournal* pJournal = GetDataAccess()->GetJournal();

             if (pJournal)
             {
                lRet = pJournal->ObjectModified(pCdmObject);
             }

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

 long CdbCommandUpdateContainer::UpdateRights(CdmObjectContainer*& p_pContainer)
 {
    long lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(p_pContainer))
    {
       if(p_pContainer->IsAccessorListModified())
       {
          QSqlQuery cQSqlQuery;
          QString qstrQuery;
          // query for reading new id
          qstrQuery = QString("delete from WMS_DM_ACCESSORRIGHT where ObjectListId = %1")
             .arg(p_pContainer->GetId());

          lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

          if(lRet > 0)
          {
             QMap<int, EdmRight> qmRights = p_pContainer->GetAccessorMap();

             QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
             QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

             for (; qmIt != qmItEnd; ++qmIt)
             {
                 qstrQuery = QString("insert into WMS_DM_ACCESSORRIGHT (AccessorId, ObjectListId, AccessRight)"
                                     " values(%1, %2, %3)")
                                     .arg(qmIt.key())
                                     .arg(p_pContainer->GetId())
                                     .arg(qmIt.value());


                 lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

                 if(lRet <= 0)
                 {
                     lRet = EC(eDmInvalidUpdateStatement);
                     ERR("Update Objectlist itselves failed!!!");
                     break;
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
