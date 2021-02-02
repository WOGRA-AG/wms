/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QScriptEngine>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsUtilities.h"

// own Includes
#include "IdmExecutorEngine.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CsaObject.h"
#include "CsaClass.h"
#include "CsaFactory.h"
#include "CsaObjectContainer.h"

CsaObjectContainer::CsaObjectContainer(CdmObjectContainer *p_pContainer, bool p_bThis)
: CsaModelElement(p_pContainer),
  m_bThis(p_bThis)
{
}

CsaObjectContainer::~CsaObjectContainer()
{
}

QObject *CsaObjectContainer::findObjectById(int p_iId)
{
    return getFactory()->createScriptObject(getInternals()->FindObjectById(p_iId));
}

QObject *CsaObjectContainer::findObjectByKeyname(QString qstr_Keyname)
{
    return getFactory()->createScriptObject(getInternals()->FindObjectByKeyname(qstr_Keyname));
}

QObject *CsaObjectContainer::copyObject(CsaObject *p_pObject)
{
   return getFactory()->createScriptObject(getInternals()->CopyObject(p_pObject->getInternals()));
}

QObject *CsaObjectContainer::createObject()
{
   CdmObject* pObject = getInternals()->CreateNewObject();

   if (pObject)
   {
      return getFactory()->createScriptObject(pObject);
   }
   else
   {
      ERR("Could not create Object over ScriptEngine!");
      return nullptr;
   }
}

QObject *CsaObjectContainer::createObject(QString p_qstrKeyname)
{
   CdmObject* pObject = getInternals()->CreateNewObject(p_qstrKeyname);

   if (pObject)
   {
      return getFactory()->createScriptObject(pObject);
   }
   else
   {
      ERR("Could not create Object over ScriptEngine!");
      return nullptr;
   }
}



int CsaObjectContainer::commit()
{
   return getInternals()->Commit();
}

int CsaObjectContainer::countOverallObjects()
{
   return getInternals()->CountObjectsOnDb();
}

int CsaObjectContainer::countLocalObjects()
{
   return getInternals()->CountObjects();
}

QVariantList CsaObjectContainer::getObjectList()
{
   QVariantList qvResult;
   QLinkedList<CdmObject*> qllObjects;
   getInternals()->GetObjectList(qllObjects);

   QLinkedList<CdmObject*>::iterator qllIt = qllObjects.begin();
   QLinkedList<CdmObject*>::iterator qllItEnd = qllObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CdmObject* pObject = *qllIt;
      CsaLocatedElement* csaObject = getFactory()->createScriptObject(pObject);
      QVariant qvObject;
      qvObject.setValue(csaObject);
      INFO("Object Content: " + qvObject.toString());
      qvResult.append(qvObject);
   }

   return qvResult;
}

void CsaObjectContainer::deleteObject(CsaObject *p_pObject)
{
   getInternals()->DeleteObject(p_pObject->getInternals());
}

void CsaObjectContainer::clearContainer()
{
   loadContainerComplete();
   getInternals()->DeleteAllObjects();
}

void CsaObjectContainer::clearContainerLocal()
{
   getInternals()->ClearContainerLocal();
}

bool CsaObjectContainer::isTree()
{
   return getInternals()->IsTree();
}

void CsaObjectContainer::setTree(bool p_bTree)
{
   getInternals()->SetTree(p_bTree);
}

bool CsaObjectContainer::hasOwner()
{
   return getInternals()->HasOwner();
}

CsaObject* CsaObjectContainer::getOwner()
{
   return static_cast<CsaObject*> (getFactory()->createScriptObject(getInternals()->GetOwner()));
}

void CsaObjectContainer::loadContainerComplete()
{
   CdmContainerManager* pManager = getInternals()->GetContainerManager();
   long lId = getInternals()->GetId();
   pManager->ReloadContainerComplete(getInternals()->GetId());
   CdmObjectContainer* pContainer = pManager->FindContainerById(lId);
   setElement(pContainer);
}

CdmObjectContainer *CsaObjectContainer::getInternals()
{
   return static_cast<CdmObjectContainer*>(getElement());
}

bool CsaObjectContainer::isImmutable()
{
   return getInternals()->IsImmutable();
}

bool CsaObjectContainer::hasCurrentUserReadAccess()
{
    const CdmRights& rights = getInternals()->GetRights();
    return rights.HasCurrentUserReadAccess();
}

bool CsaObjectContainer::hasCurrentUserWriteAccess()
{
    const CdmRights& rights = getInternals()->GetRights();
    return rights.HasCurrentUserReadAccess();
}

void CsaObjectContainer::setImmutable(bool p_bImmutable)
{
   getInternals()->SetImmutable(p_bImmutable);
}

QVariant CsaObjectContainer::getDetailedVariant()
{
   QVariantMap qVariantMap;
   CdmObjectContainer* pCdmContainer = getInternals();
   if(CHKPTR(pCdmContainer))
   {
      addVariantData(qVariantMap);

      const CdmClass* pClass = pCdmContainer->GetClass();

      if (CHKPTR(pClass))
      {
         CsaClass* pCsaClass = dynamic_cast<CsaClass*> (getFactory()->createScriptObject(const_cast<CdmClass*>(pClass)));

         if (CHKPTR(pCsaClass))
         {
            qVariantMap.insert(WMS_CLASS, pCsaClass->getRoughVariant());
         }
      }

      int iCount = pCdmContainer->CountObjectsOnDb();
      qVariantMap.insert(WMS_COUNT, iCount);
      qVariantMap.insert(WMS_URI, pCdmContainer->GetUri());
   }
   return qVariantMap;
}




