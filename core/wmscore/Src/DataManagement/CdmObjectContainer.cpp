/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qdom.h>
#include <QUuid>
#include <QList>

// WMS Commons Includes
#include "CwmsJson.h"

// own Includes
#include "CdmScheme.h"
#include "wmsdefines.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmMember.h"
#include "CdmContainerServices.h"
#include "CdmContainerManager.h"
#include "CdmValueObjectRef.h"
#include "CdmJournalItem.h"
#include "CdmContainerAdaptor.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "IdmDataAccess.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmMessageManager.h"


CdmObjectContainer::CdmObjectContainer( qint64 p_lDatabaseId,
                                        qint64 p_lId,
                                         QString p_qstrKeyname,
                                         CdmClass* p_pCdmClass )
    : CdmModelElement( p_lDatabaseId, p_lId, p_qstrKeyname),
      m_lClassId(0),
      m_bIsAccessorListModified(false),
      m_bIsTree(false),
      m_bImportMode(false),
      m_bIsImmutable(false)
{
    if(!p_pCdmClass)
    {
        ERR("Class is nullptr while creating objectlist. This Objectlist is invalid.");
        SetInvalid();
    }
    else
    {
        m_lClassId = p_pCdmClass->GetId();
    }



}

CdmObjectContainer::CdmObjectContainer(qint64 p_lId, CdmObjectContainer* p_pContainer )
    : CdmModelElement( p_pContainer->GetSchemeId(), p_lId, p_pContainer->GetKeyname() + QDateTime::currentDateTime().toString()),
      m_lClassId(p_pContainer->m_lClassId),
      m_bIsAccessorListModified(false),
      m_bIsTree(false),
      m_bImportMode(false),
      m_bIsImmutable(false)
{
    const CdmClass* pClass = p_pContainer->GetClass();
    QString qstrKeyname = pClass->GetKeyname();
    qstrKeyname += "_" + QUuid::createUuid().toString();
    SetKeyname(qstrKeyname);

    // now it is time to copy each object from the source objectlist to the new one
    CopyObjects(p_pContainer);

    // then all rights must be copied
    CopyRights(p_pContainer);
}


CdmObjectContainer::CdmObjectContainer(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname,qint64 p_lClassId)
    : CdmModelElement( p_lDatabaseId, p_lId, p_qstrKeyname),
      m_lClassId(p_lClassId),
      m_bIsAccessorListModified(false),
      m_bIsTree(false),
      m_bImportMode(false),
      m_bIsImmutable(false)
{
}



CdmObjectContainer::CdmObjectContainer(QVariantMap& p_rqvHash)
    : CdmModelElement(p_rqvHash),
      m_lClassId(0),
      m_bIsAccessorListModified(false),
      m_bIsTree(false),
      m_bImportMode(false),
      m_bIsImmutable(false)
{
    SetVariant(p_rqvHash);

}

CdmObjectContainer::CdmObjectContainer()
    : CdmModelElement(),
      m_lClassId(0),
      m_bIsAccessorListModified(false),
      m_bIsTree(false),
      m_bImportMode(false),
      m_bIsImmutable(false)
{
    FATAL("DO NOT CALL THIS. This method is for providing QML support!!!");

}

CdmObjectContainer::~CdmObjectContainer(  )
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = nullptr;
    QMap<qint64,CdmObject*>::iterator iIt = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator iItEnd = m_qmObjects.end();

    for(; iIt != iItEnd; ++iIt)
    {
        pCdmObject = iIt.value();
        if (pCdmObject)
        {
            DELPTR(pCdmObject);
        }
    }

    m_qmObjects.clear();
}

void CdmObjectContainer::SetImportMode(bool p_bMode)
{
    m_bImportMode = p_bMode;
}

void CdmObjectContainer::SetVariant(QVariantMap& p_rqvHash)
{
    CdmModelElement::SetVariant(p_rqvHash);
    SetVariantBaseData(p_rqvHash);
    QVariantList qvObjects = p_rqvHash[WMS_OBJECTS].toList();
    SetObjects(qvObjects);
}

void CdmObjectContainer::SetVariantBaseData(QVariantMap& p_rqvHash)
{
    QString qstrClassUri = p_rqvHash[WMS_CLASSURI].toString();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager) && m_lClassId == 0)
    {
        CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(pManager->GetUriObject(qstrClassUri));

        if (pElement)
        {
            if (pElement->IsClass())
            {
                m_lClassId = pElement->GetId();
            }
        }
    }

    m_qstrComment = p_rqvHash[WMS_COMMENT].toString();
    m_bIsTree = p_rqvHash[WMS_TREE].toBool();
    QVariantMap qvRights = p_rqvHash[WMS_ACCESSORRIGHTS].toMap();
    m_cCdmRights.SetVariant(qvRights);
}

void CdmObjectContainer::SetObjects(QVariantList& p_rqvObjects)
{
    QVariantList::iterator qvhIt = p_rqvObjects.begin();
    QVariantList::iterator qvhItEnd = p_rqvObjects.end();

    for (; qvhIt != qvhItEnd; ++qvhIt)
    {
        QVariantMap qvhObject = (*qvhIt).toMap();
       qint64 lId = qvhObject[WMS_ID].toInt();

        CdmObject* pCdmObjectLocal = FindObjectById(lId);

        if (!pCdmObjectLocal)
        {
            pCdmObjectLocal = new CdmObject(qvhObject);
            AddObject(pCdmObjectLocal);
        }
        else
        {
            pCdmObjectLocal->SetVariant(qvhObject);
        }

        if (pCdmObjectLocal->IsDeleted())
        {
            SetModified(); // The objectlist must be set modified if there are deleted objects in it
            m_qlDeletedObjects.append(pCdmObjectLocal);
        }
        else if (pCdmObjectLocal->IsModified() ||
                 pCdmObjectLocal->IsNew())
        {
            SetModified();
            m_qlNewModifiedObjects.append(pCdmObjectLocal);
        }
    }
}

QVariant CdmObjectContainer::GetVariantComplete() const
{
    DEPRECATED
    return GetVariant();
}

QVariant CdmObjectContainer::GetVariant() const
{
    SYNCHRONIZED;
    QVariantMap qvHash = GetContainerDataVariant().toMap();
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        QVariantList qvhObjects;

        if(!m_qmObjects.isEmpty())
        {
            QMap<qint64, CdmObject*>::const_iterator qIt = m_qmObjects.begin();
            QMap<qint64, CdmObject*>::const_iterator qItEnd = m_qmObjects.end();

            if (!pCdmManager->IsClientServerMode()) // only in odbc and sqlite mode you need to pack all objects (because you are the server)
            {

                for (; qIt != qItEnd; ++qIt)
                {
                    CdmObject* pCdmObject = qIt.value();

                    if (pCdmObject)
                    {
                        qvhObjects.append(pCdmObject->GetVariant());
                    }
                }
            }
            else // you are the client so you only need to send all modified, deleted or new objects back
            {
                for (; qIt != qItEnd; ++qIt)
                {
                    CdmObject* pCdmObject = qIt.value();

                    if (pCdmObject && (pCdmObject->IsModified() || pCdmObject->IsNew() || pCdmObject->IsDeleted()))
                    {
                        qvhObjects.append(pCdmObject->GetVariant());
                    }
                }
            }
        }

        qvHash.insert(WMS_OBJECTS, qvhObjects);
    }

    return qvHash;
}

QVariant CdmObjectContainer::GetContainerDataVariant() const
{
    QVariantMap qvHash = CdmModelElement::GetVariant().toMap();
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        qvHash.insert(WMS_CLASSID,static_cast<int>(m_lClassId));
        qvHash.insert(WMS_COMMENT, m_qstrComment);
        qvHash.insert(WMS_TREE, m_bIsTree);

        const CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            qvHash.insert(WMS_CLASSURI, pCdmClass->GetUriInternal());
        }

        qvHash.insert(WMS_ACCESSORRIGHTS, m_cCdmRights.GetVariant());
    }

    return qvHash;
}

bool CdmObjectContainer::IsTree() const
{
    return m_bIsTree;
}

void CdmObjectContainer::SetTree(bool p_bTree)
{
    if (m_bIsTree != p_bTree)
    {
        m_bIsTree = p_bTree;
        SetModified();
    }
}

void CdmObjectContainer::CopyObjects(CdmObjectContainer* p_pContainerSource)
{
    SYNCHRONIZED;
    int iObjectCount = 0;
    int iCompareCount = 0;

    if(CHKPTR(p_pContainerSource))
    {
        p_pContainerSource->Refresh();
        CdmObject* pCdmObject = nullptr;

        QMap<qint64,CdmObject*>::iterator iIt = p_pContainerSource->m_qmObjects.begin();
        QMap<qint64,CdmObject*>::iterator iItEnd = p_pContainerSource->m_qmObjects.end();
        iObjectCount = p_pContainerSource->m_qmObjects.count();

        for(; iIt != iItEnd; ++iIt)
        {
            pCdmObject = iIt.value();
            if (CHKPTR(pCdmObject))
            {
               qint64 lNewObjectId = GetNewObjectId();
                CdmObject* pCdmNewObject = new CdmObject(this, pCdmObject, lNewObjectId);
                pCdmNewObject->SetCreatorId(GetUserId());
                pCdmNewObject->SetModifierId(GetUserId());
                SetModified();
                ObjectModifiedSlot(pCdmNewObject);

                if (pCdmNewObject->IsValid())
                {
                    AddObject(pCdmNewObject);
                    pCdmNewObject->SetModified();
                    Commit();
                }
                else
                {
                    ERR("Copied Object is invalid!");
                }
            }
        }

        iCompareCount = m_qmObjects.count();

        if (iCompareCount == iObjectCount)
        {
            SetValid();
        }
        else
        {
            //SetInvalid();
            ERR("Copying Objectlist failed!");
        }
    }
}

int CdmObjectContainer::MoveObjectsTo(CdmObjectContainer *p_pDestContainer)
{
   SYNCHRONIZED;
   int iRet = CdmLogging::eDmUnknownObjectListError;

   int iObjectCount = 0;
   int iCompareCount = m_qmObjects.count();

   if(CHKPTR(p_pDestContainer) && IsValid() && p_pDestContainer->IsValid())
   {
      // Make a copy of the objects currently in this container.
      // This is necessary as the objects are removed one by one during
      // calls to CdmObject::MoveToObjectList(CdmObjectContainer*) and the
      // iterator breaks.
      QList<CdmObject*> tmpSrcObjects = m_qmObjects.values();

      for(auto srcObj = tmpSrcObjects.begin(); srcObj != tmpSrcObjects.end(); srcObj++)
      {
         if (CHKPTR(*srcObj))
         {
            iRet = (*srcObj)->MoveToObjectList(p_pDestContainer);
            if(!SUCCESSFULL(iRet))
            {
               ERR("Move object failed");
               break;
            }

            iRet = (*srcObj)->Commit();
            if(!SUCCESSFULL(iRet))
            {
               ERR("Commit object failed");
               break;
            }

            iObjectCount++;
         }
         else
         {
            iRet = EC(eDmInvalidPtr);
            break;
         }
      }

      if (iCompareCount == iObjectCount)
      {
         SetModified();
         iRet = EC(eDmOk);
      }
      else
      {
         SetInvalid();
         ERR("Moving Objectlist failed!");
      }
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:29:42 2005----------*
 * @method  CdmObjectContainer::CopyRights                        // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pCdmSourceObjectList            //                                   *
 * @comment This method copies all rights from the sourceobjectlist to this.                      *
 *----------------last changed: --------------------------------Sa 20. Aug 10:29:42 2005----------*/
void CdmObjectContainer::CopyRights(CdmObjectContainer* p_pCdmSourceObjectList)
{
    SYNCHRONIZED;
    if(CHKPTR(p_pCdmSourceObjectList))
    {
        QMap<int, EdmRight> qmRights = p_pCdmSourceObjectList->m_cCdmRights.GetRights();

        QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
        QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

        for(; qmIt != qmItEnd; ++qmIt)
        {
            m_cCdmRights.AddRight(qmIt.key(), qmIt.value());
        }
    }
}

void CdmObjectContainer::ClearContainerLocal()
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = nullptr;
    QMap<qint64,CdmObject*>::iterator iIt = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator iItEnd = m_qmObjects.end();

    for(; iIt != iItEnd; ++iIt)
    {
        pCdmObject = iIt.value();
        DELPTR(pCdmObject);
    }

    m_qmObjects.clear();
    m_qlNewModifiedObjects.clear();
    m_qlDeletedObjects.clear();
}

void CdmObjectContainer::RemoveObjectLocal(qint64 p_lObjectId)
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = FindObjectById(p_lObjectId);

    if(CHKPTR(pCdmObject))
    {
        m_qmObjects.remove(p_lObjectId);
        m_qlNewModifiedObjects.removeAll(pCdmObject);
        m_qlDeletedObjects.removeAll(pCdmObject);
        delete pCdmObject;
        pCdmObject = nullptr;

    }
}

void CdmObjectContainer::GetObjects(QList<qint64>&  p_rqllObjectIds,
                                    QList<CdmObject*>& p_rqllObjects)
{
    SYNCHRONIZED;
    LoadObjects(p_rqllObjectIds);
    QList<qint64>::iterator qlIt = p_rqllObjectIds.begin();
    QList<qint64>::iterator qlItEnd = p_rqllObjectIds.end();

    for (; qlIt != qlItEnd; ++qlIt)
    {
        CdmObject* pCdmObject = FindObjectById(*qlIt);

        if (pCdmObject)
        {
            p_rqllObjects.append(pCdmObject);
        }
    }
}

void CdmObjectContainer::RemoveObjectLocalWithoutDelete(qint64 p_lObjectId)
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = FindObjectByIdLocal(p_lObjectId);

    if(CHKPTR(pCdmObject))
    {
        SYNCHRONIZED;
        m_qmObjects.remove(p_lObjectId);
        disconnect(pCdmObject, SIGNAL(ObjectModifiedSignal(CdmObject*)), this, SLOT(ObjectModifiedSlot(CdmObject*)));
        disconnect(pCdmObject, SIGNAL(ObjectDeletedSignal(CdmObject*)), this, SLOT(ObjectDeletedSlot(CdmObject*)));
        disconnect(pCdmObject, SIGNAL(ObjectRefModifiedSignal(CdmObject*)), this, SLOT(ObjectRefModifiedSlot(CdmObject*)));
        disconnect(pCdmObject, SIGNAL(ObjectCommitedSignal(i)), this, SLOT(ObjectCommitedSlot));

        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectDeletedEvent(pCdmObject->GetId());
            }
        }
    }
}

CdmObject* CdmObjectContainer::FindObjectByKeyname(QString p_qstrKeyname)
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = nullptr;

    QMap<qint64,CdmObject*>::iterator qmIt = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator qmItEnd = m_qmObjects.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmObject* pObject = qmIt.value();

        if (CHKPTR(pObject) && pObject->GetKeyname() == p_qstrKeyname)
        {
            pCdmObject = pObject;
            break;
        }
    }

    if(!pCdmObject)
    {
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
            INFO("Try to load object");
            if(SUCCESSFULL(pIdmDataAccess->LoadObject(this,
                                          p_qstrKeyname,
                                          pCdmObject)))
            {
                if(pCdmObject)
                {
                    if (AddObject(pCdmObject) < 0)
                    {
                        DELPTR(pCdmObject);
                    }
                }
                else
                {
                    ERR("Object not found in DB");
                }
            }
            else
            {
                INFO("Cannot find object in DB. Maybe it is deleted!");
            }

        }
        else
        {
            FATAL("Can not reach DataAccessObject.\n No Loading possible.");
        }
    }

    if(pCdmObject)
    {
        if (pCdmObject->IsDeleted())
        {
            pCdmObject = nullptr;
        }
    }
    else
    {
        INFO("Can not find Object with Keyname: " + p_qstrKeyname +"." );
    }


    return pCdmObject;
}

CdmObject* CdmObjectContainer::FindObjectById(qint64 p_lObjectId)
{
    CdmObject* pCdmObject = nullptr;

    if(IsValid() && p_lObjectId > 0)
    {
        // First of All Check User
        if(CheckReadAccess())
        {
            // then check lockingstate
            SYNCHRONIZED;
            pCdmObject = m_qmObjects[p_lObjectId];
            
            if(!pCdmObject)
            {
                IdmDataAccess* pIdmDataAccess = GetDataAccess();

                if(CHKPTR(pIdmDataAccess))
                {
                    INFO("Try to load object");
                    if(pIdmDataAccess->LoadObject(this,
                                                  p_lObjectId,
                                                  pCdmObject) < 0)
                    {
                        INFO("Cannot find object in DB. Maybe it is deleted!");
                    }
                    else
                    {
                        if(pCdmObject)
                        {
                            if (AddObject(pCdmObject) < 0)
                            {
                                DELPTR(pCdmObject);
                            }
                        }
                        else
                        {
                            ERR("Object not found in DB");
                        }
                    }
                }
                else
                {
                    FATAL("Can not reach DataAccessObject.\n No Loading possible.");
                }
            }
            
            if(pCdmObject)
            {
                if (pCdmObject->IsDeleted())
                {
                    pCdmObject = nullptr;
                }
            }
            else
            {
                INFO("Can not find Object with Id: " + QString::number( p_lObjectId ) +"." );
            }
        }
        else
        {
            ERR("User with Id " + QString::number(GetSessionId()) + "has no right to access this objectlist.");
        }
    }

    return pCdmObject;
}

CdmObject* CdmObjectContainer::FindObjectByIdLocal(qint64 p_lObjectId)
{
    CdmObject* pCdmObject = nullptr;

    if(IsValid())
    {
        // Frist of All Check User
        if(CheckReadAccess())
        {
            // then check lockingstate
            SYNCHRONIZED;
            pCdmObject = m_qmObjects[p_lObjectId];
            
            if(!pCdmObject)
            {
                INFO("Object not found local");
            }
            
            if(pCdmObject)
            {
                if(pCdmObject->IsDeleted())
                {
                    pCdmObject = nullptr;
                }
                else
                {
                    pCdmObject->InitObject(GetClass());
                }
            }
            else
            {
                INFO("Can not find Object with Id: " + QString::number( p_lObjectId ) +"." );
            }


        }
        else
        {
            ERR("User with Id " + QString::number(GetSessionId()) + "has no right to access this objectlist.");
        }
    }

    return pCdmObject;
}

qint64 CdmObjectContainer::LoadObjects(const QList<qint64>& p_rqvlObjectIds, bool p_bWithChildren)
{
    SYNCHRONIZED;
   qint64 lRet = CdmLogging::eDmUnknownObjectError;
    QList<qint64> qvlObjectIds;
    QList<qint64>::const_iterator qvlIt = p_rqvlObjectIds.begin();
    QList<qint64>::const_iterator qvlItEnd = p_rqvlObjectIds.end();

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        if (!FindObjectByIdLocal(*qvlIt))
        {
            qvlObjectIds.append(*qvlIt);
        }
    }

    IdmDataAccess* pIdmDataAccess = GetDataAccess();
    CdmObjectContainer* pContainer = this;

    if (CHKPTR(pIdmDataAccess) && qvlObjectIds.count() > 0)
    {
        lRet = pIdmDataAccess->LoadObjects(qvlObjectIds, pContainer);


        // now load all objects which contains to the loaded objects in this objectlist
        if (lRet > 0 && p_bWithChildren)
        {
            LoadChildrenObjects(qvlObjectIds);
        }
    }
    else
    {
        lRet = EC(eDmOk);
    }

    return lRet;
}

void CdmObjectContainer::LoadChildrenObjects(const QList<qint64>& p_rqvlObjectIds)
{
    SYNCHRONIZED;
    const CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        QMap<qint64,qint64> qmObjectToLoad; //<objectid,objectlistid>
        QMap<qint64, CdmMember*> qmMembers;
        pCdmClass->GetMemberMap(qmMembers);


        // Iterating over all members to findout which members are objectrefs
        QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
        QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            qmObjectToLoad.clear();
            CdmMember* pCdmMember = qmIt.value();

            if (CHKPTR(pCdmMember) && pCdmMember->GetValueType() == eDmValueObjectRef)
            {
                QList<qint64>::const_iterator qvlIt = p_rqvlObjectIds.begin();
                QList<qint64>::const_iterator qvlItEnd = p_rqvlObjectIds.end();

                for (; qvlIt != qvlItEnd; ++qvlIt)
                {
                    CdmObject* pCdmObject = FindObjectByIdLocal(*qvlIt);

                    if (pCdmObject)
                    {
                        CdmValueObjectRef* pCdmObjectRef = dynamic_cast<CdmValueObjectRef*>(pCdmObject->GetValue(pCdmMember->GetKeyname()));

                        if (pCdmObjectRef && pCdmObjectRef->GetValue() > 0 && pCdmObjectRef->GetObjectListId() > 0)
                        {
                            qmObjectToLoad.insert(pCdmObjectRef->GetValue(), pCdmObjectRef->GetObjectListId());
                        }

                    }
                    else
                    {
                        WARNING("This object should be loaded! ObjectId: " + QString::number(*qvlIt));
                    }
                }
            }

            if (qmObjectToLoad.count() > 0)
            {
                LoadObjectRefs(qmObjectToLoad);
            }
        }
    }
}

void CdmObjectContainer::LoadObjectRefs(QMap<qint64,qint64>& p_rqmObjectRefs)
{
    SYNCHRONIZED;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if (CHKPTR(pContainerManager))
    {
        QList<qint64> qvlObjectLists;

        QMap<qint64,qint64>::iterator qmIt = p_rqmObjectRefs.begin();
        QMap<qint64,qint64>::iterator qmItEnd = p_rqmObjectRefs.end();

        //iterator over the map and find out how many different objectlists there are
        for (; qmIt != qmItEnd; ++qmIt)
        {
           qint64 lObjectListId = qmIt.value();

            if(!qvlObjectLists.contains(lObjectListId))
            {
                qvlObjectLists.append(lObjectListId);
            }
        }


        // now find all objecttids to one ojectlist
        QList<qint64>::iterator qvlIt = qvlObjectLists.begin();
        QList<qint64>::iterator qvlItEnd = qvlObjectLists.end();

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
           qint64 lObjectListId = (*qvlIt);

            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(lObjectListId);

            if (CHKPTR(pContainer))
            {
                QList<qint64> qvlObjects;

                qmIt = p_rqmObjectRefs.begin();
                qmItEnd = p_rqmObjectRefs.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    if (qmIt.value() == lObjectListId)
                    {
                        qvlObjects.append(qmIt.key());
                    }
                }

                // we load only one iteration step. Usually we don't need more
                //pContainer->LoadObjects(qvlObjects, false);
                pContainer->LoadObjects(qvlObjects, true);
            }
        }
    }
}

CdmObject* CdmObjectContainer::FindObjectByIndex(int p_iIndex)
{
    SYNCHRONIZED;
    CdmObject* pCdmObject = nullptr;

    QMap<qint64,CdmObject*>::iterator qmIt    = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator qmItEnd = m_qmObjects.end();

    int iCounter = 0;

    for(; qmIt != qmItEnd; ++qmIt)
    {
        if (iCounter == p_iIndex)
        {
            pCdmObject = qmIt.value();
            break;
        }

        ++iCounter;
    }

    return pCdmObject;
}

int CdmObjectContainer::AddObject(CdmObject* p_pCdmObject)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (CHKPTR(p_pCdmObject))
    {
        //      p_pCdmObject->setParent(this);
        if (p_pCdmObject->CdmModelElement::IsValid())
        {
            if (p_pCdmObject->m_lClassId == m_lClassId)
            {
                SYNCHRONIZED;
                iRet = EC(eDmOk);
                m_qmObjects.insert(p_pCdmObject->GetId(), p_pCdmObject);
                connect(p_pCdmObject, SIGNAL(ObjectModifiedSignal(CdmObject*)), this, SLOT(ObjectModifiedSlot(CdmObject*)));
                connect(p_pCdmObject, SIGNAL(ObjectDeletedSignal(CdmObject*)), this, SLOT(ObjectDeletedSlot(CdmObject*)));
                connect(p_pCdmObject, SIGNAL(ObjectRefModifiedSignal(CdmObject*)), this, SLOT(ObjectRefModifiedSlot(CdmObject*)));
                //connect(p_pCdmObject, SIGNAL(ObjectCommitedSignal), this, SLOT(ObjectCommitedSlot));

                p_pCdmObject->SetObjectContainer(this);

                if (p_pCdmObject->IsNew())
                {
                    SetModified();
                    m_qlNewModifiedObjects.append(p_pCdmObject);
                }
            }
            else
            {
                WARNING("Object has the wrong class. Can not be added to this list.\n ObjectInfo:\n" + p_pCdmObject->GetInfo())
                iRet = EC(eDmWrongObjectClass);
            }
        }
        else
        {
            ERR("Object To Add is Invalid. Can not be added.\nObjectInfo:\n" + p_pCdmObject->GetInfo())
            iRet = EC(eDmInvalidObject);
        }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
        ERR("Object to add does not exist. NullPointer overgiven." )
    }

    return iRet;
}

qint64 CdmObjectContainer::CountObjects() const
{
   return m_qmObjects.count();
}

qint64 CdmObjectContainer::Refresh()
{
  qint64 lRet = 0;
   IdmDataAccess* pIdmDataAccess = GetDataAccess();

   if (CHKPTR(pIdmDataAccess))
   {
       lRet = pIdmDataAccess->RefreshObjectContainer(this);
   }

   return lRet;
}

/** +-=---------------------------------------------------------So 10. Feb 09:48:45 2013----------*
 * @method  CdmObjectContainer::CountModifiedObjects              // public, const, slots              *
 * @return qint64                                             //                                   *
 * @comment This method counts the number of modified objects.                                    *
 *----------------last changed: --------------------------------So 10. Feb 09:48:45 2013----------*/
qint64 CdmObjectContainer::CountModifiedObjects() const
{
    SYNCHRONIZED;
   qint64 lRet = 0;
    QMap<qint64,CdmObject*>::const_iterator iIt = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::const_iterator iItEnd = m_qmObjects.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmObject* pCdmObject = iIt.value();
        if (CHKPTR(pCdmObject))
        {
            if (pCdmObject->IsModified() || pCdmObject->IsNew() || pCdmObject->IsDeleted())
            {
                lRet++;
            }
        }
    }

    return lRet;
}

bool CdmObjectContainer::CheckReadAccess() const
{
    return m_cCdmRights.HasCurrentUserReadAccess();
}

bool CdmObjectContainer::CheckWriteAccess() const
{
    return m_cCdmRights.HasCurrentUserWriteAccess();
}

CdmObject* CdmObjectContainer::CreateNewObject(QString p_qstrKeyname)
{
    CdmObject* pCdmObject = nullptr;

    if(CheckWriteAccess())
    {
        if(m_lClassId >= 0)
        {
           qint64 lNewObjectId = GetNewObjectId();

            if(lNewObjectId > 0)
            {
                const CdmClass* pClass = GetClass();

                if (CHKPTR(pClass))
                {
                    if(pClass->IsEventSourcingActive() || pClass->IsEventClass())
                    {
                        pCdmObject = new CdmObject(GetSchemeId(), lNewObjectId, p_qstrKeyname, pClass, this);
                        pCdmObject->SetCreatorId(GetUserId());
                        pCdmObject->SetModifierId(GetUserId());
                        pCdmObject->SetNew();
                        AddObject(pCdmObject);
                        CdmExecutor::GetExecutor()->GetFunction()->CallConstructor(pCdmObject);
                    }
                    else
                    {
                        pCdmObject = new CdmObject(GetSchemeId(), lNewObjectId, p_qstrKeyname, pClass, this);
                        pCdmObject->SetCreatorId(GetUserId());
                        pCdmObject->SetModifierId(GetUserId());
                        pCdmObject->SetNew();
                        AddObject(pCdmObject);
                        CdmExecutor::GetExecutor()->GetFunction()->CallConstructor(pCdmObject);
                    }
                }
            }
            else
            {
                ERR("GetNewObjectId returned a invalid new objectid!!!");
            }
        }
        else
        {
            FATAL("Not Possible to Execute this Method because there is no valid Class id.");
        }
    }
    else
    {
        ERR("No Writeaccess for this objectlist!!!");
    }

    return pCdmObject;
}

CdmObject* CdmObjectContainer::CreateNewObject()
{
    QString qstrKeyname = GenerateKeyname();
    return CreateNewObject(qstrKeyname);
}

CdmObject* CdmObjectContainer::CreateObject(qint64 p_lObjectId)
{
    return new CdmObject(m_lSchemeId,
                         p_lObjectId,
                         GetClassId(),
                         GetId());
}

qint64 CdmObjectContainer::GetNewObjectId()
{
   qint64 lId = CdmLogging::eDmUnknownObjectError;

    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(CHKPTR(pIdmDataAccess))
    {
        lId = pIdmDataAccess->GetNewObjectId(this);
    }
    else
    {
        lId = EC(eDmInvalidPtr);
        FATAL( "Not possible to execute this Method because there is no valid DataAccess Pointer." );
    }

    return lId;
}

qint64 CdmObjectContainer::GetClassId() const
{
    return m_lClassId;
}

const CdmClass* CdmObjectContainer::GetClass() const
{
    CdmClass* pClass = nullptr;

    CdmClassManager* pCdmClassManager = GetClassManager();

    if(CHKPTR(pCdmClassManager))
    {
        pClass = pCdmClassManager->FindClassById(m_lClassId);
    }

    return pClass;
}

CdmObject* CdmObjectContainer::CopyObject(const CdmObject* p_pCdmObject)
{
    CdmObject* pCdmCopiedObject = nullptr;

    if(CHKPTR(p_pCdmObject))
    {
        // using copy constructor
       qint64 lNewObjectId = GetNewObjectId();

        pCdmCopiedObject = new CdmObject(*p_pCdmObject, lNewObjectId);
        pCdmCopiedObject->SetObjectContainer(this);
        AddObject(pCdmCopiedObject);
        Commit();
    }

    return pCdmCopiedObject;
}

int CdmObjectContainer::DeleteObject(CdmObject* p_pCdmObject)
{
    SYNCHRONIZED;
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (CHKPTR(p_pCdmObject))
    {
        p_pCdmObject->SetDeleted();

        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectDeletedEvent(p_pCdmObject->GetId());
            }
        }

        iRet = EC(eDmOk);
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

void CdmObjectContainer::DeleteAllObjects()
{
    SYNCHRONIZED;
    QMap<qint64,CdmObject*>::iterator iIt = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator iItEnd = m_qmObjects.end();

    for(; iIt != iItEnd; ++iIt)
    {
        CdmObject* pCdmObject = iIt.value();

        if (pCdmObject)
        {
            pCdmObject->SetDeleted();
        }
    }

    Commit();
    ClearContainerLocal();
}

int CdmObjectContainer::DeleteObject(qint64 p_lObjectId)
{
    int iRet = CdmLogging::eDmUnknownObjectError;

    CdmObject* pCdmObject = FindObjectById(p_lObjectId);

    if (CHKPTR(pCdmObject))
    {
        iRet = DeleteObject(pCdmObject);
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

void CdmObjectContainer::GetObjectList(QList<CdmObject*>& p_rqvlObjects)
{
    SYNCHRONIZED;
    QMap<qint64,CdmObject*>::iterator qmIt    = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator qmItEnd = m_qmObjects.end();

    CdmObject* pCdmObject = nullptr;

    for(; qmIt != qmItEnd; ++qmIt)
    {
        pCdmObject = qmIt.value();

        if(CHKPTR(pCdmObject))
        {
            p_rqvlObjects.append(pCdmObject);
        }
        else
        {
            ERR("nullptr pointer in Objectmap!!! ObjectId: " + QString::number(qmIt.key()));
        }
    }
}

bool CdmObjectContainer::IsTypeOf(QString p_qstrClassName) const
{
    bool bRet = false;

    const CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        if (pCdmClass->IsInherited(p_qstrClassName) > 0)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool CdmObjectContainer::IsExactTypeOf(QString p_qstrClassName) const
{
    bool bRet = false;

    const CdmClass* pCdmClass = GetClass();

    if (CHKPTR(pCdmClass))
    {
        if (pCdmClass->GetFullQualifiedName() == p_qstrClassName)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool CdmObjectContainer::IsTypeOf(CdmClass* p_pClass) const
{
    bool bRet = false;

    if (p_pClass)
    {
        const CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->IsInherited(p_pClass) > 0)
            {
                bRet = true;
            }
        }
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

bool CdmObjectContainer::IsExactTypeOf(CdmClass* p_pClass) const
{
    bool bRet = false;

    if (p_pClass)
    {
        const CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->GetId() == p_pClass->GetId())
            {
                bRet = true;
            }
        }
    }
    else
    {
        bRet = true;
    }

    return bRet;
}

void CdmObjectContainer::GetObjectList(QList<qint64>& p_rqvlObjects)
{
    SYNCHRONIZED;
    QMap<qint64,CdmObject*>::iterator qmIt    = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator qmItEnd = m_qmObjects.end();

    CdmObject* pCdmObject = nullptr;

    for(; qmIt != qmItEnd; ++qmIt)
    {
        pCdmObject = qmIt.value();
        if(pCdmObject)
        {
            p_rqvlObjects.append(pCdmObject->GetId());
        }
    }
}

void CdmObjectContainer::SetAllLocalObjectsDeleted()
{
    SYNCHRONIZED;
    QMap<qint64,CdmObject*>::iterator qmIt    = m_qmObjects.begin();
    QMap<qint64,CdmObject*>::iterator qmItEnd = m_qmObjects.end();

    CdmObject* pCdmObject = nullptr;

    for(; qmIt != qmItEnd; ++qmIt)
    {
        pCdmObject = qmIt.value();
        if(CHKPTR(pCdmObject))
        {
            pCdmObject->SetDeleted();
        }
    }
}

void CdmObjectContainer::ObjectModifiedSlot(  CdmObject* p_pCdmObject )
{
    SYNCHRONIZED;
    if(CHKPTR(p_pCdmObject))
    {
        SetModified();

        if (!m_qlDeletedObjects.contains(p_pCdmObject) &&
                !m_qlNewModifiedObjects.contains(p_pCdmObject))
        {
            m_qlNewModifiedObjects.append(p_pCdmObject);
        }

        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectModifiedEvent(p_pCdmObject->GetId());
            }
        }
    }
}

void CdmObjectContainer::ObjectRefModifiedSlot(CdmObject* p_pCdmObject)
{
    SYNCHRONIZED;
    if(CHKPTR(p_pCdmObject))
    {
        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectRefModifiedEvent(p_pCdmObject->GetId());
            }
        }
    }
}

void CdmObjectContainer::ObjectDeletedSlot(CdmObject* p_pCdmObject)
{
    SYNCHRONIZED;
    if(CHKPTR(p_pCdmObject))
    {
        SetModified();

        if (!m_qlDeletedObjects.contains(p_pCdmObject))
        {
            m_qlDeletedObjects.append(p_pCdmObject);
            m_qlNewModifiedObjects.removeOne(p_pCdmObject);
        }

        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectDeletedEvent(p_pCdmObject->GetId());
            }
        }
    }
}

QList<CdmObject*> CdmObjectContainer::GetDeletedList()
{
    return m_qlDeletedObjects;
}

QList<CdmObject*> CdmObjectContainer::GetNewModifiedList()
{
    return m_qlNewModifiedObjects;
}

void CdmObjectContainer::ObjectCommitedSlot(int p_iId)
{
    SYNCHRONIZED;
    if (!m_bImportMode)
    {
        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {
            CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

            if(CHKPTR(pCdmObjectFactory))
            {
                pCdmObjectFactory->ObjectCommitedEvent(p_iId);
            }
        }
    }
}

// NOTE use strong method name for use from BMS
void CdmObjectContainer::TriggerObjectCommittedEventAfterDbReload()
{
    ObjectCommitedSlot(-2);
}

void CdmObjectContainer::RefreshObjectKeyname(CdmObject* pObject)
{
    CdmClass* pClass = pObject->GetClass();

    if (CHKPTR(pClass))
    {
        const CdmMember* pMember = pClass->GetCaptionMember();

        if (pMember != nullptr && pMember->IsUnique())
        {
            QString qstrKeyname = pObject->GetDisplayString(pMember->GetKeyname());

            if (!qstrKeyname.isEmpty())
            {
                pObject->SetKeyname(qstrKeyname);
                pObject->SetCaption(qstrKeyname);
            }
        }
    }
}

void CdmObjectContainer::CommitDeleteObjects()
{
    QList<CdmObject*>::iterator qllIt = m_qlDeletedObjects.begin();
    QList<CdmObject*>::iterator qllItEnd = m_qlDeletedObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CdmObject *pObject = (*qllIt);
        pObject->SetValid();
        CdmExecutor::GetExecutor()->GetFunction()->CallDestructor(pObject);
        pObject->DeleteOwnerRefs();
    }
}

void CdmObjectContainer::CommitUpdateObjects()
{
    QList<CdmObject*>::iterator qllIt = m_qlNewModifiedObjects.begin();
    QList<CdmObject*>::iterator qllItEnd = m_qlNewModifiedObjects.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        QVariantList qlParams;
        CdmObject* pObject = *qllIt;

        if (CHKPTR(pObject))
        {
            // check if we can use the keyname from display member
            RefreshObjectKeyname(pObject);

            CdmExecutorFunction* pExecutor = CdmExecutor::GetExecutor()->GetFunction();

            if (CHKPTR(pExecutor))
            {
                pExecutor->ExecuteFunction(SCRIPT_COMMIT, pObject, qlParams);
            }
        }
    }
}

int CdmObjectContainer::CommitDeleteContainer()
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(pIdmDataAccess)
    {
        SetModifierId(GetUserId());
        iRet = pIdmDataAccess->DeleteObjectContainer(GetId());
        UpdateFactoriesObjectModified();
        ObjectCommitedSlot(0);
    }

    return iRet;
}

int CdmObjectContainer::CommitUpdateContainer()
{
    int iRet = CdmLogging::eDmUnknownObjectError;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if(pIdmDataAccess)
    {
        CdmObjectContainer* pContainer = this;
        CdmExecutor::GetExecutor()->SetCommitRunning(this, true);
        if (CdmExecutor::ExecuteValidation(this))
        {
            SetModifierId(GetUserId());
            CommitDeleteObjects();
            CommitUpdateObjects();
            CdmExecutor::GetExecutor()->SetCommitRunning(this, false);
            iRet = pIdmDataAccess->UpdateObjectContainer(pContainer);

            if(iRet > 0)
            {
                ResetNewModified();
            }

            UpdateFactoriesObjectModified();
            ObjectCommitedSlot(0);
        }
        else
        {
            iRet = CdmLogging::eDmValidationFailed;
        }
    }

    return iRet;
}

int CdmObjectContainer::Commit()
{
    SYNCHRONIZED;
    int iRet = CdmLogging::eDmUnknownObjectError;

    if (IsDeleted())
    {
        iRet = CommitDeleteContainer();
    }
    else if (IsNew() || IsModified())
    {
        iRet = CommitUpdateContainer();
    }
    else
    {
        // nothing to be updated
        iRet = CdmLogging::eDmOk;
    }

    return iRet;
}

void CdmObjectContainer::UpdateFactoriesObjectModified()
{
    SYNCHRONIZED;
    QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qvlObjectFactories.begin();
    QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qvlObjectFactories.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {
        CdmContainerAdaptor* pCdmObjectFactory = (*qvlIt);

        if(CHKPTR(pCdmObjectFactory))
        {
            pCdmObjectFactory->ObjectModifiedEvent(-1);
        }
    }
}

void CdmObjectContainer::SetComment(QString p_qstrComment)
{
    m_qstrComment = p_qstrComment;
}

QString CdmObjectContainer::GetComment() const
{
    QString qstrComment = m_qstrComment.mid(0, 999);
    return qstrComment;
}

void CdmObjectContainer::AddAccessorRight(qint64 p_lUserId, EdmRight p_eUmAccessRight)
{
    m_cCdmRights.AddRight(p_lUserId, p_eUmAccessRight);
    SetModified();
    m_bIsAccessorListModified = true;
}

QMap<int, EdmRight> CdmObjectContainer::GetAccessorMap() const
{
    return m_cCdmRights.GetRights();
}

void CdmObjectContainer::RemoveAccessorRight(qint64 p_lUserId)
{
    if (m_cCdmRights.HasRightConfigured(p_lUserId))
    {
        m_cCdmRights.DeleteRight(p_lUserId);
        SetModified();
        m_bIsAccessorListModified = true;
    }
}

void CdmObjectContainer::UpdateAccessorRight(qint64 p_lUserId, EdmRight p_eUmAccessRight)
{
    RemoveAccessorRight(p_lUserId);
    AddAccessorRight(p_lUserId, p_eUmAccessRight);
}

bool CdmObjectContainer::IsAccessorListModified() const
{
    return m_bIsAccessorListModified;
}

void CdmObjectContainer::SetDeleted()
{
    CdmModelElement::SetDeleted();
}


qint64 CdmObjectContainer::CountObjectsOnDb()
{
   qint64 lRet = 0;
    IdmDataAccess* pIdmDataAccess = GetDataAccess();

    if (CHKPTR(pIdmDataAccess))
    {
        lRet = pIdmDataAccess->CountObjectsOnDb(this);
    }

    return lRet;
}

void CdmObjectContainer::AddObjectFactory(CdmContainerAdaptor* p_pCdmObjectFactory)
{
    if(CHKPTR(p_pCdmObjectFactory))
    {
        if (!m_qvlObjectFactories.contains(p_pCdmObjectFactory))
        {
            m_qvlObjectFactories.append(p_pCdmObjectFactory);
            INFO("Added ObjectFactory");
        }
        else
        {
            INFO ("ObjectFactory already in list!");
        }
    }
}

QList<CdmContainerAdaptor*> CdmObjectContainer::GetObjectFactoryList()
{
    return m_qvlObjectFactories;
}

void CdmObjectContainer::RemoveObjectFactory(CdmContainerAdaptor* p_pCdmObjectFactory)
{
    SYNCHRONIZED;
    if(CHKPTR(p_pCdmObjectFactory))
    {
        if (m_qvlObjectFactories.contains(p_pCdmObjectFactory))
        {
            m_qvlObjectFactories.removeAll(p_pCdmObjectFactory);
            INFO("Removed ObjectFactory");
        }
        else
        {
            INFO ("ObjectFactory not found in list!");
        }
    }
}

QString CdmObjectContainer::GetInfo() const
{
    QString qstrRet;

    qstrRet = CdmModelElement::GetInfo();
    qstrRet += "\n\n";

    qstrRet += "Container Informations:\n";

    qstrRet += "Class:      \n\n";

    const CdmClass* pCdmClass = GetClass();

    if (pCdmClass)
    {
        qstrRet += pCdmClass->GetInfo();
    }
    else
    {
        qstrRet += "nullptr\n";
    }

    qstrRet += "Tree Container: ";

    if (IsTree())
    {
        qstrRet += "Yes\n";
    }
    else
    {
        qstrRet += "No\n";
    }
    qstrRet += "Objects: " + QString::number(m_qmObjects.count()) + "\n";

    return qstrRet;
}

void CdmObjectContainer::SetModified()
{
    if (!IsModified())
    {
        CdmModelElement::SetModified();
    }
}

void CdmObjectContainer::ResetNewModified()
{
    if (IsModified() || IsNew())
    {
        m_qlNewModifiedObjects.clear();
        m_qlDeletedObjects.clear();
        CdmModelElement::ResetNewModified();
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 10:26:54 2012----------*
 * @method  CdmObjectContainer::GetChanges                        // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QList<CdmJournalItem*>& p_rqllChanges            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 10:26:54 2012----------*/
void CdmObjectContainer::GetChanges(QList<CdmJournalItem*>& p_rqllChanges)
{
    QDate qdTo = QDate::currentDate();
    QDate qdFrom = QDate(2012,1,1);
    GetChanges(qdFrom, qdTo, p_rqllChanges);
}

/** +-=---------------------------------------------------------Di 20. Nov 10:27:02 2012----------*
 * @method  CdmObjectContainer::GetChanges                        // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QDate p_qdFrom                                   //                                   *
 * @param   QDate p_qdTo                                     //                                   *
 * @param   QList<CdmJournalItem*>& p_rqllChanges            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 10:27:02 2012----------*/
void CdmObjectContainer::GetChanges(QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqllChanges)
{
    IdmDataAccess* pCdmAccess = GetDataAccess();

    if (CHKPTR(pCdmAccess))
    {
        pCdmAccess->GetObjectContainerModifications(this,
                                                    p_qdFrom,
                                                    p_qdTo,
                                                    p_rqllChanges);
    }
}

/** +-=---------------------------------------------------------Do 29. Nov 11:27:08 2012----------*
 * @method  CdmObjectContainer::HasOwner                          // public, slots                     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 29. Nov 11:27:08 2012----------*/
bool CdmObjectContainer::HasOwner()
{
    return (GetOwner() != nullptr);
}

bool CdmObjectContainer::HasDeploymentRelevantOwner() const
{
    bool bRet = false;

    CdmObject* pOwner = GetOwner();

    if (pOwner)
    {
        CdmObjectContainer* pContainer = pOwner->GetObjectContainer();

        if (CHKPTR(pContainer))
        {
            bRet = pContainer->IsDeploymentRelevant();
        }
    }

    return bRet;
}


CdmObject* CdmObjectContainer::GetOwner() const
{
    CdmObject* pCdmObject = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            pDataAccess->GetOwner(this, pCdmObject);
        }
    }

    return pCdmObject;
}

/** +-=---------------------------------------------------------So 10. Feb 09:53:26 2013----------*
 * @method  CdmObjectContainer::IsContainer                      // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:53:26 2013----------*/
bool CdmObjectContainer::IsContainer() const
{
    return true;
}

/** +-=---------------------------------------------------------Do 29. Nov 11:53:30 2012----------*
 * @method  CdmObjectContainer::IsDeploymentRelevant              // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 29. Nov 11:53:30 2012----------*/
bool CdmObjectContainer::IsDeploymentRelevant()
{
    bool bRet = false;
    const CdmClass* pClass = GetClass();

    if (pClass)
    {
        if (IsTechnicalDeploymentRelevant() ||
            HasDeploymentRelevantOwner())
        {
            bRet = true;
        }
    }

    return bRet;
}

bool CdmObjectContainer::IsTechnicalDeploymentRelevant() const
{
    bool bRet = false;
    const CdmClass* pClass = GetClass();

    if (pClass)
    {
        QString qstrKeyname = pClass->GetKeyname();

        if (qstrKeyname.startsWith(WMS_TECHNICAL) ||
                qstrKeyname.startsWith(WMS_WORKFLOW) ||
                qstrKeyname.startsWith(WMS_PERMANENT) ||
                HasDeploymentRelevantOwner())
        {
            bRet = true;
        }

        if (!bRet)
        {
           const CdmClass* pClass = GetClass();

           if (pClass->IsSingleton())
           {
              bRet = true;
           }
        }
    }

    return bRet;
}

/** +-=---------------------------------------------------------Mo 3. Dez 14:20:30 2012-----------*
 * @method  CdmObjectContainer::Deploy                            // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 14:20:30 2012-----------*/
void CdmObjectContainer::Deploy(QVariantMap& p_rqvHash)
{
    CdmModelElement::Deploy(p_rqvHash);
    SetVariantBaseData(p_rqvHash);

    QVariantList qvObjects = p_rqvHash[WMS_OBJECTS].toList();

    for (int iCounter = 0; iCounter < qvObjects.count(); ++iCounter)
    {
        QVariantMap qvObject = qvObjects[iCounter].toMap();
        QString qstrKeyname = qvObject[WMS_KEYNAME].toString();

        if (IsDeploymentObjectKeynameValid(qstrKeyname))
        {
            CdmObject* pObject = FindObjectByKeyname(qstrKeyname);

            if (!pObject)
            {
                pObject = CreateNewObject(qstrKeyname);
            }

            if (CHKPTR(pObject))
            {
                pObject->Deploy(qvObject);
            }
        }
    }

    SetModified();
    Commit();
}

bool CdmObjectContainer::IsDeploymentObjectKeynameValid(QString& p_rqstrKeyname)
{
    return (p_rqstrKeyname != "NewObject");
}

const CdmRights& CdmObjectContainer::GetRights() const
{
    return m_cCdmRights;
}

QString CdmObjectContainer::GetConfig() const
{
    QVariantMap qvMap;
    qvMap.insert("Immutable", IsImmutable());

    CwmsJson json;
    return json.serialize(qvMap);
}

void CdmObjectContainer::SetConfig(QString p_qstrConfig)
{
    if (!p_qstrConfig.isEmpty())
    {
        CwmsJson json;
        QVariantMap qvMap = json.parse(p_qstrConfig).toMap();
        SetImmutable(qvMap["Immutable"].toBool());
    }
}

bool CdmObjectContainer::IsImmutable() const
{
    return m_bIsImmutable;
}

void CdmObjectContainer::SetImmutable(bool p_bImmutable)
{
    m_bIsImmutable = p_bImmutable;
    SetModified();
}
