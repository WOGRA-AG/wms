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
#include <QLinkedList>

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


/** +-=---------------------------------------------------------Fr 24. Aug 10:08:34 2012----------*
 * @method  CwmsViewManager::CwmsViewManager                 // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:08:34 2012----------*/
CwmsViewManager::CwmsViewManager()
{
   CheckViewDataStructure();
}

/** +-=---------------------------------------------------------Fr 24. Aug 10:08:44 2012----------*
 * @method  CwmsViewManager::~CwmsViewManager                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsViewManager                                               *
 *----------------last changed: --------------------------------Fr 24. Aug 10:08:44 2012----------*/
CwmsViewManager::~CwmsViewManager()
{
}

/** +-=---------------------------------------------------------Fr 24. Aug 10:09:13 2012----------*
 * @method  CwmsViewManager::CheckViewDataStructure          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:09:13 2012----------*/
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

/** +-=---------------------------------------------------------Fr 24. Aug 10:09:29 2012----------*
 * @method  CwmsViewManager::CreateViewClass                 // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:09:29 2012----------*/
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

/** +-=---------------------------------------------------------Fr 24. Aug 10:10:31 2012----------*
 * @method  CwmsViewManager::GetObjectList                   // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:10:31 2012----------*/
CdmObjectContainer* CwmsViewManager::GetObjectList()
{
   return CdmDataProvider::GetObjectContainer("TechnicalViews");
}

/** +-=---------------------------------------------------------Fr 24. Aug 10:15:45 2012----------*
 * @method  CwmsViewManager::GetViewList                     // public                            *
 * @return  void                                             //                                   *
 * @param   QLinkedList<CdmObject*>& p_rqlViews              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 10:15:45 2012----------*/
void CwmsViewManager::GetViewList(QLinkedList<CdmObject*>& p_rqlViews)
{
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      pContainer->GetObjectList(p_rqlViews);
   }
}

/** +-=---------------------------------------------------------Fr 24. Aug 11:06:02 2012----------*
 * @method  CwmsViewManager::GetView                         // public                            *
 * @return  CwmsView                                         //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:06:02 2012----------*/
CwmsView CwmsViewManager::GetView(long p_lObjectId)
{
   CwmsView cView;
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = pContainer->FindObjectById(p_lObjectId);
      cView.SetObject(pCdmObject);
   }

   return cView;
}

/** +-=---------------------------------------------------------Fr 24. Aug 11:06:21 2012----------*
 * @method  CwmsViewManager::GetView                         // public                            *
 * @return  CwmsView                                         //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:06:21 2012----------*/
CwmsView CwmsViewManager::GetView(QString p_qstrName)
{
   CwmsView cView;
   QString qstrQuery = "select from TechnicalViews where Name = \"" + p_qstrName +"\"";
   CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrQuery);

   if (pQuery)
   {
      QLinkedList<long> qllResults = pQuery->GetResultList();

      if (qllResults.count() > 0)
      {
         cView = GetView(*(qllResults.begin()));
      }

      DELPTR(pQuery);
   }

   return cView;
}
