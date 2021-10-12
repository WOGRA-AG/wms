#include "CwnCommandUpdateContainer.h"
#include "CwnCommandDeleteObject.h"
#include "CwnCommandUpdateObject.h"

#include "CwnJournal.h"
#include "CwnHelper.h"

#include <qiterator.h>

#include "CwnCommandStdHeader.h"

CwnCommandUpdateContainer::CwnCommandUpdateContainer(CdmObjectContainer *&p_pContainer,qint64 p_lSessionId, CwnDataAccess *p_pDataAccess):CwnCommandBase(p_pDataAccess),
m_rpObjectContainer(p_pContainer),
m_lSessionId(p_lSessionId)
{

}

CwnCommandUpdateContainer::~CwnCommandUpdateContainer()
{

}

void CwnCommandUpdateContainer::interpretAnswer(QVariant &Ret)
{
    bool bRet = false;

    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());
    this->answer=nullptr;

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=EC(eDmInvalidSelectStatement);

    }
    else
    {

        const QVariantList* results = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        QVariantList::ConstIterator it;

        for (it=results->begin(); it!=results->end(); ++it)
        {
            const QVariantMap* data = static_cast<const QVariantMap*>(it->data());
            const QVariantList* dataList = static_cast<const QVariantList*>(data->find("data")->data());

            // Wurde überhaupt etwas zurückgegeben?
            if(dataList->count() >0)
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
                const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                if(list->at(0).toInt()>0)
                    bRet = true;
                else
                    bRet = false;
            }


            if(!bRet)
            {
                ConnectAndExecute(rollbackTransaction,nullptr,this->location,nullptr);
                ERR("Something did go wrong with updateing the container.");
                break;
            }
        }

        if(bRet)
        {
            ConnectAndExecute(commitTransaction,nullptr,this->location,nullptr);
            Ret = 1;
            m_rpObjectContainer->ResetNewModified();
        }
    }
}

int CwnCommandUpdateContainer::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(m_rpObjectContainer->IsModified() || m_rpObjectContainer->IsNew())
    {
       if (m_rpObjectContainer->IsNew())
       {
          CwnJournal* pJournal = GetDataAccess()->GetJournal();

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
       // query for reading new id
       this->answer=nullptr;

       QString qstrCypher = QString("MATCH (oc:WMS_DM_OBJECTLIST) WHERE id(oc)=%1 "
                                    "OPTIONAL MATCH ()<-[a:WMS_CONTAINER_MODIFIED_BY]-(oc) DELETE a WITH oc ")
               .arg(m_rpObjectContainer->GetId());

       qstrCypher += QString("SET oc.Keyname = '%1', oc.LastChange = %2, oc.Caption = \'%3\', oc.Comment = '%4', oc.Tree = \'%5\', oc.Config = \'%6\' WITH oc ")
                           .arg(CwnHelper::MaskStringForChanges(m_rpObjectContainer->GetKeyname()))
                           .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()))
                           .arg(CwnHelper::MaskStringForChanges(m_rpObjectContainer->GetCaption()))
                           .arg(CwnHelper::MaskStringForChanges(m_rpObjectContainer->GetComment()))
                           .arg(CwnHelper::ConvertBoolToString(m_rpObjectContainer->IsTree()))
                           .arg(CwnHelper::base64_encode(m_rpObjectContainer->GetConfig()));

       if(m_rpObjectContainer->GetModifierId()!=0){
           qstrCypher += QString("MATCH (u:User) WHERE id(u)=%1 CREATE (oc)-[:WMS_CONTAINER_MODIFIED_BY]->(u) WITH oc ")
                            .arg(m_rpObjectContainer->GetUserId());
       }


       qstrCypher += QString("RETURN id(oc);");

       //qDebug()<< qstrQuery;
       payload = startJsonWCommand(qstrCypher);

       UpdateRights(m_rpObjectContainer);

       payload += endJsonCommand();

       //qDebug() << payload;
       queryCausedError = payload;
       ConnectAndExecute(openTransaction,payload,nullptr,nullptr);
       QVariant Ret;
       interpretAnswer(Ret);
       lRet = Ret.toInt();
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return static_cast<int>(lRet);
}

bool CwnCommandUpdateContainer::CheckValid()
{
    return (CHKPTR(m_rpObjectContainer) && m_lSessionId > 0);
}

qint64 CwnCommandUpdateContainer::UpdateObjects(CdmObjectContainer* p_pContainer,
                                      QList<CdmObject*>& p_rqlObjects,
                                     qint64 p_lSessionId)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
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
        qint64 lObjectId = pCdmObject->GetId();

         CwnCommandUpdateObject command(p_lSessionId, pCdmObject, GetDataAccess());
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

qint64 CwnCommandUpdateContainer::DeleteObjects(CdmObjectContainer* p_pContainer,
                                      QList<CdmObject*>& p_rqlObjects,
                                     qint64 p_lSessionId)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
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
        qint64 lObjectId = pCdmObject->GetId();
         CwnCommandDeleteObject command(lObjectId, p_lSessionId, GetDataAccess());
         lRet = command.Run();

         if(lRet > 0)
         {
            CwnJournal* pJournal = GetDataAccess()->GetJournal();

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

void CwnCommandUpdateContainer::UpdateRights(CdmObjectContainer*& p_pContainer)
{
   if(CHKPTR(p_pContainer))
   {
      if(p_pContainer->IsAccessorListModified())
      {
        QString qstrQuery;
        // query for reading new id
        qstrQuery = QString("OPTIONAL MATCH (oc:WMS_DM_OBJECTLIST)-[r:rights]->(u) WHERE id(oc)=%1 DELETE r RETURN DISTINCT 1 ")
            .arg(p_pContainer->GetId());

        payload += addJsonCommand(qstrQuery);


        QMap<int, EdmRight> qmRights = p_pContainer->GetAccessorMap();

        QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
        QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            qstrQuery = QString("MATCH (u),(oc:WMS_DM_OBJECTLIST) WHERE id(u)=%1 AND id(oc)=%2 CREATE (oc)-[r:rights]->(u) SET r.rightId=%3, r.type=\'WMS_ACCESSOR_RIGHTS\' RETURN id(oc) ")
                                .arg(qmIt.key())
                                .arg(p_pContainer->GetId())
                                .arg(qmIt.value());
            payload += addJsonCommand(qstrQuery);
        }
     }
   }
}
