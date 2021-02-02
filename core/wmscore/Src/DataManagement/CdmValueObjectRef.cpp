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


/** +-=---------------------------------------------------------Sa 20. Aug 10:48:01 2005----------*
 * @method  CdmValueObjectRef::CdmValueObjectRef                       // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the object reference.                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 10:48:01 2005----------*/
CdmValueObjectRef::CdmValueObjectRef(  long p_lDatabaseId,
                            long p_lId,
                            QString p_qstrKeyname,
                            CdmObject* p_pCdmObject )
   : CdmValueLong(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueObjectRef, p_pCdmObject),
  m_lObjectListId(0),
  m_bObjectConnected(false)
{
}


/** +-=---------------------------------------------------------Sa 20. Aug 10:48:24 2005----------*
 * @method  CdmValueObjectRef::CdmValueObjectRef                       // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the object reference.                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 10:48:24 2005----------*/
CdmValueObjectRef::CdmValueObjectRef(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValueLong(p_rqDomElement, p_pCdmObject),
  m_lObjectListId(0),
  m_bObjectConnected(false)
{
   XmlImportObjectRef(p_rqDomElement);
}

/** +-=---------------------------------------------------------Mo 16. Apr 13:52:42 2012----------*
 * @method  CdmValueObjectRef::CdmValueObjectRef             // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 13:52:42 2012----------*/
CdmValueObjectRef::CdmValueObjectRef(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueLong(p_rqvHash, p_pCdmObject),
   m_lObjectListId(0),
   m_bObjectConnected(false)
{
   m_lObjectListId = p_rqvHash[WMS_CONTAINERID].toInt();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:48:17 2005----------*
 * @method  CdmValueObjectRef::~CdmValueObjectRef                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueObjectRef                                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 12:48:17 2005----------*/
CdmValueObjectRef::~CdmValueObjectRef(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:41:06 2012-----------*
 * @method  CdmValueObjectRef::Deploy                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:41:06 2012-----------*/
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

/** +-=---------------------------------------------------------Di 20. Nov 10:45:44 2012----------*
 * @method  CdmValueObjectRef::SetValue                      // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lObjectListId                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @comment This emthod sets the object value.                                                    *
 *----------------last changed: --------------------------------Di 20. Nov 10:45:44 2012----------*/
void CdmValueObjectRef::SetValue(long p_lObjectListId, long p_lObjectId,
                                 QString p_qstrObjectKeyname, QString p_qstrContainerKeyname)
{
   CdmValueLong::SetValue(p_lObjectId);
   m_lObjectListId = p_lObjectListId;
   m_qstrObjectKeyname = p_qstrObjectKeyname;
   m_qstrContainerKeyname = p_qstrContainerKeyname;

   // TODO Strings filling
   /*
   CdmObject* pObject = GetObject();

   if (pObject)
   {
       m_qstrObjectKeyname = pObject->GetKeyname();

       CdmObjectContainer* pContainer = pObject->GetObjectContainer();

       if (CHKPTR(pContainer))
       {
           m_qstrContainerKeyname = pContainer->GetKeyname();
       }
   }
   else
   {
       m_lObjectListId = 0;
       CdmValueLong::SetValue(0);
       m_qstrObjectKeyname = "";
       m_qstrContainerKeyname = "";
   }
   */
}


/** +-=---------------------------------------------------------So 18. Jun 18:48:00 2006----------*
 * @method  CdmValueObjectRef::SetValue                           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Jun 18:48:00 2006----------*/
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

/** +-=---------------------------------------------------------Fr 8. Feb 16:01:17 2013-----------*
 * @method  CdmValueObjectRef::HasValue                      // public, const, virtual, slots     *
 * @return  bool                                             //                                   *
 * @comment This method returns if this Values has an value.                                      *
 *----------------last changed: --------------------------------Fr 8. Feb 16:01:17 2013-----------*/
bool CdmValueObjectRef::HasValue() const
{
   bool bRet = false;

   if (m_lObjectListId != 0 && GetValue() != 0)
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 10. Feb 18:36:25 2013----------*
 * @method  CdmValueObjectRef::SetValue                      // public, slots                     *
 * @return  void                                             //                                   *
 * @param   const CdmObject* p_pCdmObject                    //                                   *
 * @comment This method sets the value over the object itselves.                                  *
 *----------------last changed: --------------------------------So 10. Feb 18:36:25 2013----------*/
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

/** +-=---------------------------------------------------------Mo 11. Feb 09:55:39 2013----------*
 * @method  CdmValueObjectRef::GetObject                     // public, slots                     *
 * @return  CdmObject*                                       //                                   *
 * @comment returns the object of this object ref or nullptr if this object was not found.           *
 *----------------last changed: --------------------------------Mo 11. Feb 09:55:39 2013----------*/
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
            long lObjectId = GetValue();

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
              long lObjectId = GetValue();

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
    QLinkedList<QString> qlObjectlists;

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
                 QLinkedList<long> qllObjects;
                 pCdmList->GetObjectList(qllObjects);
                 QLinkedList<long>::iterator qmIt = qllObjects.begin();
                 QLinkedList<long>::iterator qmItEnd = qllObjects.end();
                 long lRefObjVal = this->GetValue();
                 long lObjId = -1;

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
    QLinkedList<QString> qlObjectlists;
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
                 QLinkedList<long> qllObjects;
                 pCdmList->GetObjectList(qllObjects);

                 QLinkedList<CdmObject*> qlObjects;

                 CdmObject *pObject = GetObject();
                 QString qstrRefValueKeyname = GetOriginalKeyname();
                 CdmValue *pCdmObjRefValue = pObject->GetValue(qstrRefValueKeyname);
                 if(pCdmObjRefValue)
                 {
                     CdmValueObjectRef *pCdmObjectRefFromEvent = ((CdmValueObjectRef*)pCdmObjRefValue);
                     long lObjRefValue = pCdmObjectRefFromEvent->GetValue();
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

/** +-=---------------------------------------------------------So 10. Feb 10:00:01 2013----------*
 * @method  CdmValueObjectRef::IsTypeOf                      // public, const, slots              *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment This method checks if this is object is type of the overgiven classname.              *
 *----------------last changed: --------------------------------So 10. Feb 10:00:01 2013----------*/
bool CdmValueObjectRef::IsTypeOf(QString p_qstrClassName) const
{
   bool bRet = false;

   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      long lClassId = pCdmMember->GetClassReference();

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


/** +-=---------------------------------------------------------So 9. Mrz 15:51:21 2008-----------*
 * @method  CdmValueObjectRef::ObjectRefModifiedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 9. Mrz 15:51:21 2008-----------*/
void CdmValueObjectRef::ObjectRefModifiedSlot()
{
   emit ObjectRefModifiedSignal(GetObject(), this);
}

/** +-=---------------------------------------------------------Di 20. Nov 10:47:16 2012----------*
 * @method  CdmValueObjectRef::GetObjectListId               // public, slots                     *
 * @return  long                                             //                                   *
 * @comment returns the Objectlist Id of this ObjectRef                                           *
 *----------------last changed: --------------------------------Di 20. Nov 10:47:16 2012----------*/
long CdmValueObjectRef::GetObjectListId()
{
   return m_lObjectListId;
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:33:30 2010----------*
 * @method  CdmValueObjectRef::SetDefaultValue               // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember*# p_pCdmMember                   //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:33:30 2010----------*/
void CdmValueObjectRef::SetDefaultValue(const CdmMember*)
{

   // has no default value will be ignored here
   INFO("This ValueType does not know default values.");
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:33:41 2010----------*
 * @method  CdmValueObjectRef::IsSmaller                     // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller then this.                                  *
 *----------------last changed: --------------------------------Mi 15. Sep 14:33:41 2010----------*/
int CdmValueObjectRef::IsSmaller(QVariant* ) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:33:50 2010----------*
 * @method  CdmValueObjectRef::IsSmallerEqual                // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is smaller or equal then this.                         *
 *----------------last changed: --------------------------------Mi 15. Sep 14:33:50 2010----------*/
int CdmValueObjectRef::IsSmallerEqual(QVariant* ) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:34:00 2010----------*
 * @method  CdmValueObjectRef::IsLarger                      // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger then this.                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:34:00 2010----------*/
int CdmValueObjectRef::IsLarger(QVariant* ) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:34:15 2010----------*
 * @method  CdmValueObjectRef::IsLargerEqual                 // public, const, virtual            *
 * @return  int                                              // invalid = -1 false = 0 true = 1   *
 * @param   QVariant* #p_pqVariant                           //                                   *
 * @comment returns if the overgiven Value is larger or equal then this.                          *
 *----------------last changed: --------------------------------Mi 15. Sep 14:34:15 2010----------*/
int CdmValueObjectRef::IsLargerEqual(QVariant* ) const
{

   ERR( "Not Comparable" );
   return EC(eDmInvalidCompareType);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:34:23 2010----------*
 * @method  CdmValueObjectRef::Add                           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   long# p_lAdd                                     //                                   *
 * @comment Adds p_dAdd to Value.                                                                 *
 *----------------last changed: --------------------------------Mi 15. Sep 14:34:23 2010----------*/
void CdmValueObjectRef::Add(long)
{

   // does nothing
   ERR( "Makes no sense for this ValueType." );
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:34:31 2010----------*
 * @method  CdmValueObjectRef::Subtract                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   long #p_lSubtract                                //                                   *
 * @comment subtracts p_dSubtract from value.                                                     *
 *----------------last changed: --------------------------------Mi 15. Sep 14:34:31 2010----------*/
void CdmValueObjectRef::Subtract(long )
{

   // does nothing
   ERR( "Makes no sense for this ValueType." );
}

/** +-=---------------------------------------------------------So 10. Feb 17:48:56 2013----------*
 * @method  CdmValueObjectRef::GetClass                      // public, const                     *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 17:48:56 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 17:48:34 2013----------*
 * @method  CdmValueObjectRef::GetClassId                    // public, const, slots              *
 * @return  long                                             //                                   *
 * @comment This method returns the Class id for this ref Value.o                                 *
 *----------------last changed: --------------------------------So 10. Feb 17:48:34 2013----------*/
long CdmValueObjectRef::GetClassId() const
{
   long lRet = 0;
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      lRet = pMember->GetClassReference();
   }
   return lRet;
}

/** +-=---------------------------------------------------------Sa 7. Jan 14:29:22 2006-----------*
 * @method  CdmValueObjectRef::CheckUnique                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:29:22 2006-----------*/
void CdmValueObjectRef::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------So 10. Feb 10:00:30 2013----------*
 * @method  CdmValueObjectRef::XmlExport                     // public, const, virtual            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdeValue                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:00:30 2013----------*/
void CdmValueObjectRef::XmlExport(QDomElement& p_rqdeValue) const
{
   XmlExportValue(p_rqdeValue);

   p_rqdeValue.setAttribute(WMS_CONTAINERID, QString::number(m_lObjectListId));
   p_rqdeValue.setAttribute(WMS_OBJECTID,     QString::number(GetValue()));
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:49:59 2005----------*
 * @method  CdmValueObjectRef::XmlImportObjectRef                 // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 10:49:59 2005----------*/
void CdmValueObjectRef::XmlImportObjectRef(  QDomElement& p_rqDomElement )
{
   m_lObjectListId = p_rqDomElement.attribute(WMS_CONTAINERID, "-1").toInt();
   SetValue(m_lObjectListId, p_rqDomElement.attribute(WMS_OBJECTID, "-1").toInt(),"","");
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:50:02 2005----------*
 * @method  CdmValueObjectRef::XmlImport                          // public                            *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @comment This method is the abstract method to which must be implemented in each derived class.*
 *----------------last changed: --------------------------------Sa 20. Aug 10:50:02 2005----------*/
void CdmValueObjectRef::XmlImport(  QDomElement& p_rqDomElement )
{
   XmlImportBase(p_rqDomElement);
   XmlImportValue(p_rqDomElement);
   XmlImportObjectRef(p_rqDomElement);
}

/** +-=---------------------------------------------------------So 10. Feb 10:00:39 2013----------*
 * @method  CdmValueObjectRef::GetDisplayString              // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 10:00:39 2013----------*/
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

/** +-=---------------------------------------------------------So 10. Feb 10:00:58 2013----------*
 * @method  CdmValueObjectRef::GetVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 10:00:58 2013----------*/
QVariant CdmValueObjectRef::GetVariant() const
{
   QVariantMap qmVariant = CdmValueLong::GetVariant().toMap();
   qmVariant.insert(WMS_CONTAINER, (int)m_lObjectListId);
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

/** +-=---------------------------------------------------------Mo 13. Mai 14:13:39 2013----------*
 * @method  CdmValueObjectRef::SetVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:13:39 2013----------*/
void CdmValueObjectRef::SetVariant(QVariantMap& p_rqvHash)
{
   CdmValueLong::SetVariant(p_rqvHash);
   m_lObjectListId = p_rqvHash[WMS_CONTAINERID].toInt();
}

/** +-=---------------------------------------------------------So 10. Feb 10:01:06 2013----------*
 * @method  CdmValueObjectRef::GetValueVariant               // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:01:06 2013----------*/
QVariant CdmValueObjectRef::GetValueVariant() const
{
   QString qstrUri;

   if (m_lObjectListId > 0 && GetValue() > 0)
   {
       if (m_qstrObjectKeyname.isEmpty() || m_qstrContainerKeyname.isEmpty())
       {
           qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), QString::number((int) m_lObjectListId), QString::number((int) GetValue()));
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

/** +-=---------------------------------------------------------Mi 7. Nov 13:59:58 2012-----------*
 * @method  CdmValueObjectRef::TryToCreateOwnerObject        // private                           *
 * @return  CdmObject*                                       // if nut successfull nullptr will be returned*
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 7. Nov 13:59:58 2012-----------*/
CdmObject* CdmValueObjectRef::TryToCreateOwnerObject()
{
   CdmObject* pCdmObject = nullptr;
   const CdmMember* pCdmMember = GetMember();
   QLinkedList<QString> qlObjectlists;

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

/** +-=---------------------------------------------------------Do 13. Dez 08:19:29 2012----------*
 * @method  CdmValueObjectRef::ResolveValue                  // public, virtual                   *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 08:19:29 2012----------*/
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

/** +-=---------------------------------------------------------Mo 11. Feb 11:34:12 2013----------*
 * @method  CdmValueObjectRef::ObjectRefModifiedSignal       // private, signals                  *
 * @return  void                                             //                                   *
 * @param   CdmObject*                                       //                                   *
 * @param   CdmValue*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:34:12 2013----------*/
