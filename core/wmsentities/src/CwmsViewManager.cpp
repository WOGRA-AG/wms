/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsViewManager.cpp
 ** Started Implementation: 2012/08/24
 ** Description:
 **
 ** implements the manager for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QList>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmScheme.h"
#include "CdmClassManager.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"

// own Includes
#include "CwmsViewManager.h"


CwmsViewManager::CwmsViewManager()
{
   CheckViewDataStructure();
}

CwmsViewManager::~CwmsViewManager()
{
}

void CwmsViewManager::CheckViewDataStructure()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

      if (CHKPTR(pCdmClassManager))
      {
         CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname("Technical_View");

         if (!pCdmClass)
         {
            CreateViewClass(pCdmClassManager);
         }
      }
   }
}

void CwmsViewManager::CreateViewClass(CdmClassManager* p_pCdmClassManager)
{
   if (CHKPTR(p_pCdmClassManager))
   {
      CdmClass* pCdmClass = p_pCdmClassManager->CreateClass("Technical_View");

      if (CHKPTR(pCdmClass))
      {
         pCdmClass->SetCaption(tr("Sichten"));
         pCdmClass->SetComment(tr("Speichert Datenbanksichten."));
         CdmClassGroup* pCdmClassGroupInfo = pCdmClass->CreateGroup(tr("Information"), 1, nullptr);
         CdmClassGroup* pCdmClassGroupDetails = pCdmClass->CreateGroup(tr("Details"), 1, nullptr);
         pCdmClass->Commit();

         CdmMember* pCdmMember = nullptr;
         pCdmMember = pCdmClass->CreateMember("Id", eDmValueCounter, true, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Id"));
            pCdmMember->SetComment(tr("Die eindeutige Id der Sicht"));
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Name", eDmValueString, true, 200);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Name"));
            pCdmMember->SetComment(tr("Name der Datensicht"));
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("WQL", eDmValueCharacterDocument, true, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Abfrage"));
            pCdmMember->SetComment(tr("Die auszuführende Abfrage"));
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("Comment", eDmValueCharacterDocument, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Kommentar"));
            pCdmMember->SetComment(tr("Die Beschreibung zur Abfrage"));
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Reference", eDmValueInt, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Referenz"));
            pCdmMember->SetComment(tr("Die ID der Objektliste auf der die Abfrage ausgeführt wird"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("Valid", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Gültig"));
            pCdmMember->SetComment(tr("Die ID der Objektliste auf der die Abfrage  ausgeführt wird"));
            pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmClass->UpdateVersion();
         pCdmClass->Commit();

         CdmContainerManager* pCdmOLManager = pCdmClass->GetContainerManager();

         if (CHKPTR(pCdmOLManager))
         {
            QString qstrOLName = "TechnicalViews";
            pCdmOLManager->CreateContainer(pCdmClass, qstrOLName);
         }
      }
   }
}

CdmObjectContainer* CwmsViewManager::GetContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalViews");
}

void CwmsViewManager::GetViewList(QList<CdmObject*>& p_rqlViews)
{
   CdmObjectContainer* pContainer = GetContainer();

   if (CHKPTR(pContainer))
   {
      pContainer->GetObjectList(p_rqlViews);
   }
}

CwmsView CwmsViewManager::GetViewById(long p_lObjectId)
{
   CwmsView cView;
   CdmObjectContainer* pContainer = GetContainer();

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = pContainer->FindObjectById(p_lObjectId);
      cView.SetObject(pCdmObject);
   }

   return cView;
}

CwmsView CwmsViewManager::GetViewByName(QString p_qstrName)
{
   CwmsView cView;
   QString qstrQuery = "select from TechnicalViews where Name = \"" + p_qstrName +"\"";
   CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrQuery);

   if (pQuery)
   {
      QList<long> qllResults = pQuery->GetResultList();

      if (qllResults.count() > 0)
      {
         cView = GetViewById(*(qllResults.begin()));
      }

      DELPTR(pQuery);
   }

   return cView;
}

CwmsView CwmsViewManager::GetViewByUri(QString p_qstrUri)
{
    CwmsView cView;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
       auto pViewObject = dynamic_cast<CdmObject*> (pCdmManager->GetUriObject(p_qstrUri));
       cView.SetObject(pViewObject);
    }

    return cView;
}
