// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>

#include "CwmsUtilities.h"

// own Includes
#include "wmsdefines.h"
#include "CdmJsonToObjectMapper.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmValueObjectRef.h"


CdmValueObjectRef::CdmValueObjectRef( qint64 p_lDatabaseId,
                           qint64 p_lId,
                            QString p_qstrKeyname,
                            CdmObject* p_pCdmObject )
   : CdmValueLong(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueObjectRef, p_pCdmObject),
  m_lObjectListId(0),
  m_bObjectConnected(false)
{
}

CdmValueObjectRef::CdmValueObjectRef(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueLong(p_rqvHash, p_pCdmObject),
   m_lObjectListId(0),
   m_bObjectConnected(false)
{
   m_lObjectListId = p_rqvHash[WMS_CONTAINERID].toInt();
}

CdmValueObjectRef::~CdmValueObjectRef(  )
{
   // nothing to do
}

void CdmValueObjectRef::Deploy(QVariantMap& p_rqvHash)
{
    QString qstrClassUri = p_rqvHash[WMS_CLASSURI].toString();
    QString qstrObjectUri = p_rqvHash[WMS_OBJECTURI].toString();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        if (!qstrObjectUri.isEmpty())
        {
            CdmModelElement* pElement = (CdmModelElement*)pManager->GetUriObject(qstrObjectUri);

            if (pElement)
            {
                if (pElement->IsObject())
                {
                    CdmObject* pObject = dynamic_cast<CdmObject*>(pElement);
                    SetValue(pObject);
                }
                else
                {
                    ERR("Wrong Type in Uri Object");
                }
            }
            else
            {
                m_qstrReferenceUri = qstrObjectUri;
                CdmContainerManager* pOlManager = GetContainerManager();

                if (CHKPTR(pOlManager))
                {
                    pOlManager->AddDeploymentResolveValue(this);
                }
            }
        }
    }
}

void CdmValueObjectRef::SetValue(qint64 p_lObjectListId,qint64 p_lObjectId,
                                 QString p_qstrObjectKeyname, QString p_qstrContainerKeyname)
{
   CdmValueLong::SetValue(p_lObjectId);
   m_lObjectListId = p_lObjectListId;
   m_qstrObjectKeyname = p_qstrObjectKeyname;
   m_qstrContainerKeyname = p_qstrContainerKeyname;
}

void CdmValueObjectRef::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    CdmObject* pObject = nullptr;
    CdmObjectContainer* pContainer = nullptr;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if(CHKPTR(pContainerManager))
    {
        if (CwmsUtilities::IsNumber(p_qstrValue2))
        {
            pContainer = pContainerManager->FindContainerById(p_qstrValue2.toInt());
        }
        else
        {
            pContainer = pContainerManager->FindContainerByKeyname(p_qstrValue2);
        }

        if (pContainer)
        {
            if (CwmsUtilities::IsNumber(p_qstrValue))
            {
                pObject = pContainer->FindObjectById(p_qstrValue.toInt());
            }
            else
            {
                pObject = pContainer->FindObjectByKeyname(p_qstrValue);
            }
        }
    }

    SetValue(pObject);
}

bool CdmValueObjectRef::HasValue() const
{
   bool bRet = false;

   if (m_lObjectListId != 0 && GetValue() != 0)
   {
      bRet = true;
   }

   return bRet;
}

void CdmValueObjectRef::SetValue(const CdmObject* p_pCdmObject)
{
    if (p_pCdmObject)
    {
        const CdmMember* pMember = GetMember();
        CdmClassManager* pCdmClassManager = GetClassManager();

        if (CHKPTR(pMember) &&
            CHKPTR(pCdmClassManager))
        {
            CdmClass* pClass = pCdmClassManager->FindClassById(pMember->GetClassReference());

            if (p_pCdmObject->IsTypeOf(pClass))
            {
                m_lObjectListId = p_pCdmObject->GetObjectContainerId();
                CdmValueLong::SetValue(p_pCdmObject->GetId());
                m_qstrObjectKeyname = p_pCdmObject->GetKeyname();
                CdmObjectContainer* pContainer = p_pCdmObject->GetObjectContainer();

                if (CHKPTR(pContainer))
                {
                    m_qstrContainerKeyname = pContainer->GetKeyname();
                }
            }
            else
            {
                ERR("Wrong type to add to this value!")
            }
        }
    }
    else
    {
        m_lObjectListId = 0;
        CdmValueLong::SetValue(0);
        m_qstrContainerKeyname.clear();
        m_qstrObjectKeyname.clear();
        INFO("There is no valid pointer for setting value.")
    }
}

void CdmValueObjectRef::SetEventValue(const CdmObject *p_pCdmObject, const CdmObject *pEventObject)
{
    if(p_pCdmObject)
    {
        const CdmMember *pMember = GetEventMember(pEventObject);
        if(pMember)
        {
            int iClassRefId = pMember->GetClassReference();

            CdmClass* pClass = GetClassManager()->FindClassById(iClassRefId);

            if (p_pCdmObject->IsTypeOf(pClass))
            {
               m_lObjectListId = p_pCdmObject->GetObjectContainerId();
               CdmValueLong::SetValue(p_pCdmObject->GetId());
            }
            else
            {
               ERR("Wrong type to add to this value!");
            }
        }
    }
    else
    {
       m_lObjectListId = 0;
       CdmValueLong::SetValue(0);
       INFO("There is no valid pointer for setting value.");
    }
}

CdmObject* CdmValueObjectRef::GetObject()
{
   CdmObject* pCdmObject = nullptr;
   CdmObjectContainer* pContainer = nullptr;
   CdmContainerManager* pContainerManager = GetContainerManager();

   if(CHKPTR(pContainerManager))
   {
      if (m_lObjectListId > 0)
      {
         pContainer = pContainerManager->FindEmptyContainerById(m_lObjectListId);

         if(CHKPTR(pContainer))
         {
           qint64 lObjectId = GetValue();

            if (lObjectId > 0)
            {
               pCdmObject = pContainer->FindObjectById(lObjectId);

               if (pCdmObject && !m_bObjectConnected)
               {
                  connect(pCdmObject, SIGNAL(ObjectModifiedSignal(CdmObject*)), 
                          this, SLOT(ObjectRefModifiedSlot()));
                  m_bObjectConnected = true;
               }
            }
         }
         else
         {
            ERR("ObjectList not found for searching object.");
         }
      }
      else
      {
         INFO("No value stored in this objectref!");
      }
   }
   else
   {
      FATAL("There is no Object List Manager for finding ObjectList.");
   }

   if (pCdmObject)
   {
      INFO("Object Found in System.");
   }
   else
   {
      const CdmMember* pCdmMember = GetMember();

      if (CHKPTR(pCdmMember) && pCdmMember->IsOwner())
      {
         pCdmObject = TryToCreateOwnerObject();
      }
   }

   return pCdmObject;
}

CdmObject *CdmValueObjectRef::GetEventObject()
{
    CdmObject* pCdmObject = nullptr;
    CdmObjectContainer* pContainer = nullptr;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if(CHKPTR(pContainerManager))
    {
        if (m_lObjectListId > 0)
        {
           pContainer = pContainerManager->FindEmptyContainerById(m_lObjectListId);

           if(CHKPTR(pContainer))
           {
             qint64 lObjectId = GetValue();

              if (lObjectId > 0)
              {
                 pCdmObject = pContainer->FindObjectById(lObjectId);

                 if (pCdmObject && !m_bObjectConnected)
                 {
                    connect(pCdmObject, SIGNAL(ObjectModifiedSignal(CdmObject*)),
                            this, SLOT(ObjectRefModifiedSlot()));
                    m_bObjectConnected = true;
                 }
              }
              else
              {
                 ERR("ObjectList but no object stored in this objectref!!!");
              }
           }
           else
           {
              ERR("ObjectList not found for searching object.");
           }
        }
        else
        {
           INFO("No value stored in this objectref!");
        }
    }
    else
    {
       FATAL("There is no Object List Manager for finding ObjectList.");
    }

    if (pCdmObject)
    {
       INFO("Object Found in System.");
    }
    else
    {
       const CdmMember* pCdmMember = GetMember();

       if (CHKPTR(pCdmMember) && pCdmMember->IsOwner())
       {
          pCdmObject = TryToGetOwnerObject();
       }
    }

    return pCdmObject;
}

CdmObject *CdmValueObjectRef::GetReferenceObjectFromEvent(CdmObject *pEventObject)
{
    CdmObject *pCdmObject = nullptr;
    const CdmMember* pCdmMember = GetEventMember(pEventObject);

    if (CHKPTR(pCdmMember) && pCdmMember->IsOwner())
    {
       pCdmObject = TryToGetOwnerObjectByEventObject(pEventObject);
    }

    return pCdmObject;
}

CdmObject* CdmValueObjectRef::TryToGetOwnerObject()
{
    CdmObject *pCdmObject = nullptr;
    const CdmMember* pCdmMember = GetMember();
    QList<QString> qlObjectlists;

    if(CHKPTR(pCdmMember) && pCdmMember->IsOwner())
    {
        CdmContainerManager* pCdmOLManager = pCdmMember->GetContainerManager();

        if (CHKPTR(pCdmOLManager))
        {
          CdmClassManager* pClassManager = GetClassManager();

          if (CHKPTR(pClassManager))
          {
              CdmClass* pCdmClass = pClassManager->FindClassById(GetMember()->GetClassReference());

              if (CHKPTR(pCdmClass))
              {
                  qlObjectlists = pCdmOLManager->GetContainerList(pCdmClass->GetFullQualifiedName());
              }
          }

          if (qlObjectlists.count() > 1)
          {
             WARNING("Not possible to identify unique objectcontainer Taking first!!!");
          }
          else if (qlObjectlists.count() == 0)
          {
             WARNING("No Objectcontainer found creating one");
             QString qstrKeyname = GenerateKeyname();

               if (pCdmOLManager->CreateContainer(pCdmMember->GetClassReference(), qstrKeyname) > 0)
               {
                  CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);

                  if (CHKPTR(pContainer))
                  {
                     qlObjectlists.append(pContainer->GetKeyname());
                  }
                  else
                  {
                     FATAL("Could not create objectcontainer. Object creation failed!");
                  }
               }
               else
               {
                  FATAL("Could not create objectcontainer. Object creation failed!");
               }
            }
         }

          if (qlObjectlists.count() > 0)
          {
             QString qstrKeyname = (*qlObjectlists.begin());

             CdmObjectContainer* pCdmList = pCdmOLManager->FindEmptyContainerByKeyname(qstrKeyname);

             if (CHKPTR(pCdmList))
             {
                 QList<qint64> qllObjects;
                 pCdmList->GetObjectList(qllObjects);
                 QList<qint64>::iterator qmIt = qllObjects.begin();
                 QList<qint64>::iterator qmItEnd = qllObjects.end();
                qint64 lRefObjVal = this->GetValue();
                qint64 lObjId = -1;

                 for(; qmIt != qmItEnd; ++qmIt)
                 {
                     if((*qmIt) == lRefObjVal)
                     {
                         lObjId = (*qmIt);
                         break;
                     }
                 }

                 pCdmObject = pCdmList->FindObjectById(lObjId);
                 if(pCdmObject)
                 {
                    SetValue(pCdmObject);
                    CdmObject* pOwnerObject = const_cast<CdmObject*>(CdmValue::GetObject());
                    pCdmObject->Commit();
                    pOwnerObject->Commit();
                 }
             }
          }
    }
    return pCdmObject;
}

CdmObject *CdmValueObjectRef::TryToGetOwnerObjectByEventObject(CdmObject *pEventObject)
{
    CdmObject *pCdmObject = nullptr;
    const CdmMember* pCdmMember = GetEventMember(pEventObject);
    QList<QString> qlObjectlists;
    if(CHKPTR(pCdmMember) && pCdmMember->IsOwner())
    {
        CdmContainerManager* pCdmOLManager = pCdmMember->GetContainerManager();
        if (CHKPTR(pCdmOLManager))
        {
          CdmClassManager* pClassManager = GetClassManager();

          if (CHKPTR(pClassManager))
          {
              CdmClass* pCdmClass = pClassManager->FindClassById(pCdmMember->GetClassReference());

              if (CHKPTR(pCdmClass))
              {
                  qlObjectlists = pCdmOLManager->GetContainerList(pCdmClass->GetFullQualifiedName());
              }
          }

          if (qlObjectlists.count() > 1)
          {
             WARNING("Not possible to identify unique objectcontainer Taking first!!!");
          }
          else if (qlObjectlists.count() == 0)
          {
             WARNING("No Objectcontainer found creating one");
             QString qstrKeyname = GenerateKeyname();

               if (pCdmOLManager->CreateContainer(pCdmMember->GetClassReference(), qstrKeyname) > 0)
               {
                  CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);

                  if (CHKPTR(pContainer))
                  {
                     qlObjectlists.append(pContainer->GetKeyname());
                  }
                  else
                  {
                     FATAL("Could not create objectcontainer. Object creation failed!");
                  }
               }
               else
               {
                  FATAL("Could not create objectcontainer. Object creation failed!");
               }
            }
         }

          if (qlObjectlists.count() > 0)
          {
             QString qstrKeyname = (*qlObjectlists.begin());

             CdmObjectContainer* pCdmList = pCdmOLManager->FindContainerByKeyname(qstrKeyname);

             if (CHKPTR(pCdmList))
             {
                 QList<qint64> qllObjects;
                 pCdmList->GetObjectList(qllObjects);

                 QList<CdmObject*> qlObjects;

                 CdmObject *pObject = GetObject();
                 QString qstrRefValueKeyname = GetOriginalKeyname();
                 CdmValue *pCdmObjRefValue = pObject->GetValue(qstrRefValueKeyname);
                 if(pCdmObjRefValue)
                 {
                     CdmValueObjectRef *pCdmObjectRefFromEvent = ((CdmValueObjectRef*)pCdmObjRefValue);
                    qint64 lObjRefValue = pCdmObjectRefFromEvent->GetValue();
                     qllObjects.append(lObjRefValue);
                     pCdmList->GetObjects(qllObjects, qlObjects);
                 }

                 if(!qllObjects.isEmpty() && !qlObjects.isEmpty())
                 {
                     pCdmObject = (*qlObjects.begin());
                     if(pCdmObject)
                     {
                        SetEventValue(pCdmObject, pEventObject);
                        CdmObject* pOwnerObject = const_cast<CdmObject*>(CdmValue::GetObject());
                        pCdmObject->Commit();
                        pOwnerObject->Commit();
                     }
                 }
                 else
                 {
                     pCdmObject = pCdmList->CreateNewObject(pCdmMember->GetKeyname());
                     SetEventValue(pCdmObject, pEventObject);
                     CdmObject *pOwnerObject = const_cast<CdmObject*>(CdmValue::GetObject());
                     pCdmObject->Commit();
                     pOwnerObject->Commit();
                 }
             }
          }
    }
    return pCdmObject;
}

bool CdmValueObjectRef::IsTypeOf(QString p_qstrClassName) const
{
   bool bRet = false;

   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
     qint64 lClassId = pCdmMember->GetClassReference();

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(GetSchemeId());

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(lClassId);

            if (CHKPTR(pCdmClass))
            {
               if (pCdmClass->IsInherited(p_qstrClassName) > 0)
               {
                  bRet = true;
               }
            }
         }
      }
   }

   return bRet;
}

void CdmValueObjectRef::ObjectRefModifiedSlot()
{
   emit ObjectRefModifiedSignal(GetObject(), this);
}

qint64 CdmValueObjectRef::GetObjectListId()
{
   return m_lObjectListId;
}

void CdmValueObjectRef::SetDefaultValue(const CdmMember*)
{
   // has no default value will be ignored here
   INFO("This ValueType does not know default values.");
}

CdmClass* CdmValueObjectRef::GetClass() const
{
   CdmClass* pClass = nullptr;
   CdmClassManager* pClassManager = GetClassManager();

   if (CHKPTR(pClassManager))
   {
      pClass = pClassManager->FindClassById(GetClassId());
   }

   return pClass;
}

qint64 CdmValueObjectRef::GetClassId() const
{
  qint64 lRet = 0;
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      lRet = pMember->GetClassReference();
   }
   return lRet;
}

QString CdmValueObjectRef::GetDisplayString() const
{
   QString qstrDisplayString;
   const CdmObject* pObject = const_cast<CdmValueObjectRef*>(this)->GetObject();

   if (pObject)
   {
      qstrDisplayString = pObject->GetCaption();
   }

   return qstrDisplayString;
}

QVariant CdmValueObjectRef::GetVariant() const
{
   QVariantMap qmVariant = CdmValueLong::GetVariant().toMap();
   qmVariant.insert(WMS_CONTAINER, m_lObjectListId);
   const CdmObject* pObject = (const_cast<CdmValueObjectRef*>(this))->GetObject();
   if (pObject)
   {
      qmVariant.insert(WMS_OBJECTURI, pObject->GetUriInternal());

	  if (GetScheme()->IsInDeploymentMode())
	  {
          QString qstrUri = pObject->GetUriInternal();
          GetScheme()->AddDeploymentRelevantElement(qstrUri);
	  }
   }
   else if (m_lObjectListId != 0)
   {
       WARNING("Reference Object not found");
       qmVariant.insert(WMS_OBJECTURI, "");
   }
   else
   {
       qmVariant.insert(WMS_OBJECTURI, "");
   }

   return qmVariant;
}

void CdmValueObjectRef::SetVariant(QVariantMap& p_rqvHash)
{
   CdmValueLong::SetVariant(p_rqvHash);
   m_lObjectListId = p_rqvHash[WMS_CONTAINERID].toInt();
}

QVariant CdmValueObjectRef::GetValueVariant() const
{
   QString qstrUri;

   if (m_lObjectListId > 0 && GetValue() > 0)
   {
       if (m_qstrObjectKeyname.isEmpty() || m_qstrContainerKeyname.isEmpty())
       {
           qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), QString::number( m_lObjectListId), QString::number( GetValue()));
       }
       else
       {
           qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), m_qstrContainerKeyname, m_qstrObjectKeyname);
       }
   }


   return qstrUri;
}


void CdmValueObjectRef::SetValueVariantMap(QVariant& p_rqVariant)
{
    const CdmMember* pMember = GetMember();

    if (CHKPTR(pMember))
    {
        if(pMember->IsOwner())
        {
            CdmObject *object = GetObject(); // if there is no object, one will be created

            if(object)
            {
                QVariantMap qvm = p_rqVariant.toMap();
                CdmJsonToObjectMapper::ConvertVariantMap(object, qvm); // data will be written to the object.
            }
        }
        else
        {
            QVariantMap qvm = p_rqVariant.toMap();
            QString qstrSelfLink = CdmJsonToObjectMapper::GetSelfLink(qvm);
            CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

            if (CHKPTR(pProvider))
            {
                auto pElement = pProvider->GetUriObject(qstrSelfLink);

                if(pElement)
                {
                    auto pObject = dynamic_cast<CdmObject*>(pElement);

                    if (pObject)
                    {
                        SetValue(pObject);
                    }
                    else
                    {
                        ERR("Element found but is not an object with this uri: " + qstrSelfLink);
                    }
                }
                else
                {
                    ERR("No Object found with this uri: " + qstrSelfLink);
                }
            }
        }
    }
}

void CdmValueObjectRef::SetValueVariantUri(QVariant& p_rqVariant)
{
    CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pProvider))
    {
        QString qstrUri = p_rqVariant.toString();
        auto pElement = pProvider->GetUriObject(qstrUri);

        if(pElement)
        {
            auto pObject = dynamic_cast<CdmObject*>(pElement);

            if (pObject)
            {
                SetValue(pObject);
            }
            else
            {
                ERR("Element found but is not an object with this uri: " + qstrUri);
            }
        }
        else
        {
            ERR("No Object found with this uri: " + qstrUri);
        }
    }
}

void CdmValueObjectRef::SetValueVariant(QVariant& p_rqVariant)
{
    if (p_rqVariant.typeName() == QString("QVariantMap"))
    {
        SetValueVariantMap(p_rqVariant);
    }
    else if (p_rqVariant.typeName() == QString("QString"))
    {
        SetValueVariantUri(p_rqVariant);
    }
}

CdmObject* CdmValueObjectRef::TryToCreateOwnerObject()
{
   CdmObject* pCdmObject = nullptr;
   const CdmMember* pCdmMember = GetMember();
   QList<QString> qlObjectlists;

   if (CHKPTR(pCdmMember) && pCdmMember->IsOwner())
   {
      CdmContainerManager* pCdmOLManager = pCdmMember->GetContainerManager();

      if (CHKPTR(pCdmOLManager))
      {
        CdmClassManager* pClassManager = GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pCdmClass = pClassManager->FindClassById(GetMember()->GetClassReference());

            if (CHKPTR(pCdmClass))
            {
                qlObjectlists = pCdmOLManager->GetContainerList(pCdmClass->GetFullQualifiedName());
            }
        }

        if (qlObjectlists.count() > 1)
        {
           WARNING("Not possible to identify unique objectcontainer Taking first!!!");
        }
        else if (qlObjectlists.count() == 0)
        {
           WARNING("No Objectcontainer found creating one");
           QString qstrKeyname = GenerateKeyname();

             if (pCdmOLManager->CreateContainer(pCdmMember->GetClassReference(), qstrKeyname) > 0)
             {
                CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);

                if (CHKPTR(pContainer))
                {
                   qlObjectlists.append(pContainer->GetKeyname());
                }
                else
                {
                   FATAL("Could not create objectcontainer. Object creation failed!");
                }
             }
             else
             {
                FATAL("Could not create objectcontainer. Object creation failed!");
             }
          }
       }

        if (qlObjectlists.count() > 0)
        {
           QString qstrKeyname = (*qlObjectlists.begin());

           CdmObjectContainer* pCdmList = pCdmOLManager->FindEmptyContainerByKeyname(qstrKeyname);

           if (CHKPTR(pCdmList))
           {
              pCdmObject = pCdmList->CreateNewObject();

              if (CHKPTR(pCdmObject))
              {
                 SetValue(pCdmObject);
                 CdmObject* pOwnerObject = const_cast<CdmObject*>(CdmValue::GetObject());
                 pCdmObject->Commit();
                 pOwnerObject->Commit();
              }
           }
        }
  }

  return pCdmObject;
}

bool CdmValueObjectRef::ResolveValue()
{
   bool bRet = false;

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmModelElement* pElement = (CdmModelElement*)pManager->GetUriObject(m_qstrReferenceUri);

      if (pElement)
      {
         if (pElement->IsObject())
         {
            CdmObject* pObject = dynamic_cast<CdmObject*> (pElement);
            SetValue(pObject);
            bRet = true;
         }
         else
         {
            ERR("Wrong Type in Uri Object");
         }
      }
      else
      {
          ERR("Could not resolve Object with URI " + m_qstrReferenceUri + " in ValueRef " + GetKeyname());
      }
   }

   return bRet;
}


void CdmValueObjectRef::Restore(QString p_qstrValue)
{
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        auto pUriObject = pDataProvider->GetUriObject(p_qstrValue);

        if (pUriObject)
        {
            if (pUriObject->IsObject())
            {
                auto pObject = dynamic_cast<CdmObject*>(pUriObject);

                if (CHKPTR(pObject))
                {
                    SetValue(pObject);
                }
            }
        }
        else
        {
            ERR("Object which should be restored does not exist.")
        }
    }
}
