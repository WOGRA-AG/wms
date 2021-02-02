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



// own Includes
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmObjectAdaptor.h"
#include "CdmContainerAdaptor.h"



CdmContainerAdaptor::CdmContainerAdaptor(CdmObjectContainer* p_pContainer)
   : m_lDbId(0),
  m_lContainerId(0)
{
   if(p_pContainer)
   {
      m_lDbId = p_pContainer->GetSchemeId();
      m_lContainerId = p_pContainer->GetId();
      p_pContainer->AddObjectFactory(this);
   }
}

CdmContainerAdaptor::CdmContainerAdaptor(long m_lDbId, long m_lObjectListId)
   : m_lDbId(m_lDbId),
  m_lContainerId(m_lObjectListId)
{
   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pContainer->AddObjectFactory(this);
   }
}

CdmContainerAdaptor::CdmContainerAdaptor()
   : m_lDbId(0),
  m_lContainerId(0)
{
   // does nothing
}


CdmContainerAdaptor::~CdmContainerAdaptor()
{
   if (GetSchemeId() > 0)
   {
      ResetContainer();
   }
}

long CdmContainerAdaptor::GetSchemeId() const
{
   return m_lDbId;
}

void CdmContainerAdaptor::ResetContainer()
{
   CdmObjectContainer* pContainer = GetContainer();

   if (pContainer)
   {
      pContainer->RemoveObjectFactory(this);
   }

   m_lDbId = 0;
   m_lContainerId = 0;
}

void CdmContainerAdaptor::SetContainer(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))
   {
      if (p_pContainer->GetSchemeId() != m_lDbId || p_pContainer->GetId() != m_lContainerId)
      {
         CdmObjectContainer* pContainerOld = GetContainer();

         if (pContainerOld)
         {
            pContainerOld->RemoveObjectFactory(this);
         }
         
         m_lDbId = p_pContainer->GetSchemeId();
         m_lContainerId = p_pContainer->GetId();

         p_pContainer->AddObjectFactory(this);
      }
   }
}

void CdmContainerAdaptor::SetContainer(long p_lDbId, long p_lObjectListId)
{
   m_lDbId = p_lDbId;
   m_lContainerId = p_lObjectListId;

   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pContainer->AddObjectFactory(this);
   }
}

void CdmContainerAdaptor::SetContainer(QString p_qstrObjectListKeyname)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());

      if(CHKPTR(pContainerManager))
      {
         CdmObjectContainer* pContainer = nullptr;
         pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrObjectListKeyname);
         SetContainer(pContainer);
      }
   }
}

CdmObjectContainer* CdmContainerAdaptor::GetContainer() const
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(pCdmManager)
   {
      CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

      if(CHKPTR(pContainerManager))
      {
         pContainer = pContainerManager->FindEmptyContainerById(m_lContainerId);
      }
   }

   return pContainer;
}

void CdmContainerAdaptor::ReloadContainerComplete() const
{
    CdmObjectContainer* pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        CdmContainerManager* pContainerManager = pContainer->GetContainerManager();

        if(CHKPTR(pContainerManager))
        {
            pContainer->Refresh();
        }
    }
}

const CdmClass* CdmContainerAdaptor::GetClass() const
{
   const CdmClass* pCdmClass = nullptr;
   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pCdmClass = pContainer->GetClass();
   }

   return pCdmClass;
}

CdmObject* CdmContainerAdaptor::CreateObject(  QString p_qstrCaption )
{
   CdmObject* pCdmObject = nullptr;

   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pCdmObject = pContainer->CreateNewObject();

      if(CHKPTR(pCdmObject))
      {
         pCdmObject->SetCaption(p_qstrCaption);
      }
   }


   return pCdmObject;
}

long CdmContainerAdaptor::DeleteObject(CdmObjectAdaptor* p_pCdmObjectAdaptor)
{
   long lRet = 0;

   if(CHKPTR(p_pCdmObjectAdaptor))
   {
      CdmObjectContainer* pContainer = GetContainer();

      if(CHKPTR(pContainer))
      {
         lRet = pContainer->DeleteObject(p_pCdmObjectAdaptor->GetObjectId());
      }
   }

   return lRet;
}

CdmObject* CdmContainerAdaptor::FindObject(long p_lObjectId)
{
   CdmObject* pCdmObject = nullptr;
   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pCdmObject = pContainer->FindObjectById(p_lObjectId);
   }

   return pCdmObject;
}

long CdmContainerAdaptor::DeleteObject(long p_lObjectId)
{
   long lRet = 0;
   CdmObjectContainer* pContainer = GetContainer();
   
   if(CHKPTR(pContainer))
   {
      lRet = pContainer->DeleteObject(p_lObjectId);
   }
   
   return lRet;
}

void CdmContainerAdaptor::Commit()
{
   CdmObjectContainer* pContainer = GetContainer();

   if(CHKPTR(pContainer))
   {
      pContainer->Commit();
   }
}

bool CdmContainerAdaptor::IsValid()
{
   return (GetContainer() != nullptr);
}

void CdmContainerAdaptor::ObjectDeletedEvent(long p_lObjectId)
{
   Q_UNUSED(p_lObjectId);
}

void CdmContainerAdaptor::ObjectCreatedEvent(long p_lObjectId)
{
   Q_UNUSED(p_lObjectId);
}

void CdmContainerAdaptor::ObjectModifiedEvent(long p_lObjectId)
{
   Q_UNUSED(p_lObjectId);
}

void CdmContainerAdaptor::ObjectRefModifiedEvent(long p_lObjectId)
{
   Q_UNUSED(p_lObjectId);
}

void CdmContainerAdaptor::ObjectCommitedEvent(long p_lObjectId)
{
   Q_UNUSED(p_lObjectId);
}

