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
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmMember.h"
#include "CdmValueContainerRef.h"
#include "CdmJsonToObjectMapper.h"


CdmValueContainerRef::CdmValueContainerRef( qint64 p_lDatabaseId,
                                   qint64 p_lId,
                                    QString p_qstrKeyname,
                                    CdmObject* p_pCdmObject )
   : CdmValueLong(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueContainerRef, p_pCdmObject)
{
   // nothing to do
}


CdmValueContainerRef::CdmValueContainerRef(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueLong(p_rqvHash, p_pCdmObject)
{
}

CdmValueContainerRef::~CdmValueContainerRef(  )
{
   // nothing to do
}

void CdmValueContainerRef::Deploy(QVariantMap& p_rqvHash)
{
   QString qstrObjectListUri = p_rqvHash[WMS_CONTAINERURI].toString();

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      if (!qstrObjectListUri.isEmpty())
      {
        CdmModelElement* pElement = dynamic_cast<CdmModelElement*> (pManager->GetUriObject(qstrObjectListUri));

         if (pElement)
         {
            if (pElement->IsContainer())
            {
               SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
            }
            else
            {
               ERR("Wrong Type in Uri Object");
            }
         }
         else
         {
            m_qstrReferenceUri = qstrObjectListUri;
            CdmContainerManager* pOlManager = GetContainerManager();

            if (CHKPTR(pOlManager))
            {
               pOlManager->AddDeploymentResolveValue(this);
            }
         }
      }
   }
}

CdmObjectContainer* CdmValueContainerRef::GetContainer()
{
   CdmObjectContainer* pContainer = GetEmptyContainer();

   if (!pContainer)
   {
       const CdmMember* pCdmMember = GetMember();

       if (CHKPTR(pCdmMember))
       {
           const CdmObject* pObject = GetObject();

           if (CHKPTR(pObject))
           {
               if (pCdmMember->IsOwner() && !pObject->IsDeleted())
               {
                   CdmContainerManager* pContainerManager = GetContainerManager();

                   if(CHKPTR(pContainerManager))
                   {
                       QString qstrKeyname = GenerateKeyname();
                       pContainerManager->CreateContainer(pCdmMember->GetClassReference(), qstrKeyname);
                       pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);

                       if (CHKPTR(pContainer))
                       {
                           pContainer->SetTree(pCdmMember->IsTree());
                           SetValue(pContainer);
                           pContainer->Commit();
                       }
                   }
               }
           }
       }
   }

   return pContainer;
}

bool CdmValueContainerRef::IsTypeOf(QString p_qstrClassName) const
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


CdmObjectContainer* CdmValueContainerRef::GetEmptyContainer()
{
   CdmObjectContainer* pContainer = nullptr;
   CdmContainerManager* pContainerManager = GetContainerManager();

   if(CHKPTR(pContainerManager))
   {
      pContainer = pContainerManager->FindEmptyContainerById(GetValue());
   }
   else
   {
      FATAL("There is no Object List Manager for finding ObjectList.");
   }

   return pContainer;
}

void CdmValueContainerRef::SetValue(CdmObjectContainer* p_pContainer)
{
   if(p_pContainer)
   {
      const CdmMember* pMember = GetMember();

      if (CHKPTR(pMember))
      {
         int iClassRefId = pMember->GetClassReference();

         CdmClass* pClass = GetClassManager()->FindClassById(iClassRefId);

         if (p_pContainer->IsTypeOf(pClass))
         {
            CdmValueLong::SetValue(p_pContainer->GetId());
            m_qstrContainerKeyname = p_pContainer->GetKeyname();
         }
         else
         {
            ERR("Wrong type to add to this value!");
         }
      }
   }
   else
   {
      CdmValueLong::SetValue(0);
      m_qstrContainerKeyname = "";
   }
}

void CdmValueContainerRef::SetValue(qint64 p_lObjectListId)
{
   CdmValueLong::SetValue(p_lObjectListId);
   CdmObjectContainer* pContainer = GetEmptyContainer();
   SetValue(pContainer);
}

void CdmValueContainerRef::SetValue(qint64 p_lObjectListId, QString p_qstrContainerKeyname)
{
   CdmValueLong::SetValue(p_lObjectListId);
   m_qstrContainerKeyname = p_qstrContainerKeyname;
}

void CdmValueContainerRef::SetDefaultValue(const CdmMember*)
{
   // has no default value will be ignored
   INFO("This Value type can not have default values.");
}

qint64 CdmValueContainerRef::GetClassId() const
{
  qint64 lRet = 0;
   const CdmMember* pMember = GetMember();

   if (CHKPTR(pMember))
   {
      lRet = pMember->GetClassReference();
   }
   return lRet;
}

bool CdmValueContainerRef::HasValue() const
{
   bool bRet = false;

   if (GetValue() != 0)
   {
      bRet = true;
   }

   return bRet;
}

CdmClass* CdmValueContainerRef::GetClass()
{
   CdmClass* pClass = nullptr;
   CdmClassManager* pClassManager = GetClassManager();

   if (CHKPTR(pClassManager))
   {
      pClass = pClassManager->FindClassById(GetClassId());
   }

   return pClass;
}

QString CdmValueContainerRef::GetDisplayString() const
{
   QString qstrDisplayString;
   CdmObjectContainer* pContainer = (const_cast<CdmValueContainerRef*>(this))->GetContainer();

   if(pContainer)
   {
      qstrDisplayString = pContainer->GetCaption();
   }
   
   return qstrDisplayString;
}

QVariant CdmValueContainerRef::GetVariant() const
{
   QVariantMap qmVariant = CdmValueLong::GetVariant().toMap();
   CdmObjectContainer* pObjectList = (const_cast<CdmValueContainerRef*>(this))->GetContainer();

   if (pObjectList)
   {
      qmVariant.insert(WMS_CONTAINERURI, pObjectList->GetUriInternal());
   }
   
   return qmVariant;
}

QVariant CdmValueContainerRef::GetValueVariant() const
{
    QString qstrUri;

    if (GetValue() > 0)
    {
        if (m_qstrContainerKeyname.isEmpty())
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), QString::number(static_cast<int> (GetValue())));
        }
        else
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_OBJECT, GetSchemeName(), m_qstrContainerKeyname);
        }
    }

    return qstrUri;
}

void CdmValueContainerRef::SetValueVariant(QVariant& p_rqVariant)
{
   QVariantMap qvHash = p_rqVariant.toMap();
   QString qstrUri;

   if (qvHash.contains(WMS_CONTAINERID))
   {
        SetValue(qvHash[WMS_CONTAINERID].toInt());
        return;
   }
   else if (qvHash.contains(WMS_URI))
   {
       qstrUri = qvHash[WMS_URI].toString();
   }
   else
   {
       qstrUri = CdmJsonToObjectMapper::GetSelfLink(qvHash);
   }

   if (!qstrUri.isEmpty())
   {
       CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

       if (CHKPTR(pProvider))
       {
           auto pElement = pProvider->GetUriObject(qstrUri);

           if(pElement)
           {
               SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
           }
       }
   }
   else
   {
       SetValue(nullptr);
   }
}

void CdmValueContainerRef::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    CdmObjectContainer* pContainer = nullptr;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if(CHKPTR(pContainerManager))
    {
        if (CwmsUtilities::IsNumber(p_qstrValue))
        {
            pContainer = pContainerManager->FindEmptyContainerById(p_qstrValue.toInt());
        }
        else
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrValue);
        }

        SetValue(pContainer);
    }
}

bool CdmValueContainerRef::ResolveValue()
{
    bool bRet = false;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (m_qstrReferenceUri.isEmpty())
    {
        return true;
    }

    if (CHKPTR(pManager))
    {
        CdmModelElement* pElement = dynamic_cast<CdmModelElement*> (pManager->GetUriObject(m_qstrReferenceUri));

        if (pElement)
        {
            if (pElement->IsContainer())
            {
                SetValue(dynamic_cast<CdmObjectContainer*>(pElement));
                bRet = true;
            }
            else
            {
                ERR("Wrong Type in Uri Object");
            }
        }
    }

    return bRet;
}

void CdmValueContainerRef::Restore(QString p_qstrValue)
{
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        auto pContainer = pDataProvider->GetUriObject(p_qstrValue);

        if (pContainer && pContainer->IsContainer())
        {
            auto pContainerObj = dynamic_cast<CdmObjectContainer*>(pContainer);

            if (CHKPTR(pContainerObj))
            {
                SetValue(pContainerObj);
            }
        }
        else
        {
            ERR("Container which has to be restoered in this value does not exist.");
        }
    }
}
