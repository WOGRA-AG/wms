// System and QT Includes
#include <qtreewidget.h>
#include <qapplication.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmQueryBuilder.h"
#include "CdmQueryEnhanced.h"
#include "CdmSessionManager.h"

// WMS GUI INcludes
#include "CwmsApplicationManager.h"
#include "CwmsFormManager.h"
#include "CwmsReportManager.h"
#include "CwmsViewManager.h"
#include "CwmsWorkflowManager.h"

// Own Includes
#include "CwmsObjectContainerDataFiller.h"
#include "CwmsAdminMainWindowIf.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsMiscDataFiller.h"

/** +-=---------------------------------------------------------Fr 20. Sep 16:24:57 2013----------*
 * @method  CwmsMiscDataFiller::FillApplications             // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:24:57 2013----------*/
void CwmsMiscDataFiller::FillApplications(QTreeWidget* p_pTreeWidget)
{
   p_pTreeWidget->clear();
   QTreeWidgetItem* pApplications = new QTreeWidgetItem(p_pTreeWidget);
   pApplications->setText(0, QObject::tr("Applikationen"));
   pApplications->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);
   FillApplications(pApplications);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTreeWidget);
   p_pTreeWidget->sortByColumn(0, Qt::AscendingOrder);
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:27:01 2013----------*
 * @method  CwmsMiscDataFiller::FillApplications             // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pTreeWidgetItem               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:27:01 2013----------*/
void CwmsMiscDataFiller::FillApplications(QTreeWidgetItem* p_pTreeWidgetItem)
{
   CwmsApplicationManager cAppManager;
   QStringList qstrlApps = cAppManager.GetApplicationList();

   for (int iCounter = 0; iCounter < qstrlApps.count(); ++iCounter)
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(p_pTreeWidgetItem);
      pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeApplication);
      pqlviItem->setText(0, qstrlApps.at(iCounter));
   }

   p_pTreeWidgetItem->setExpanded(true);
}


/** +-=---------------------------------------------------------Fr 20. Sep 16:28:23 2013----------*
 * @method  CwmsMiscDataFiller::FillForms                    // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:28:23 2013----------*/
void CwmsMiscDataFiller::FillForms(QTreeWidget* p_pTreeWidget)
{
  p_pTreeWidget->clear();
  QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pTreeWidget);
  pItem->setText(0, QObject::tr("Formulare"));
  pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
  FillForms(pItem);
  pItem->setExpanded(true);

  pItem = new QTreeWidgetItem(p_pTreeWidget);
  pItem->setText(0, QObject::tr("Bibliotheken"));
  pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
  FillLibraries(pItem);
  pItem->setExpanded(true);

  pItem = new QTreeWidgetItem(p_pTreeWidget);
  pItem->setText(0, QObject::tr("Resourcen"));
  pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
  FillResources(pItem);
  CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTreeWidget);
  p_pTreeWidget->sortByColumn(0, Qt::AscendingOrder);
}

void CwmsMiscDataFiller::FillLibraries(QTreeWidgetItem* p_pItem)
{
   CwmsFormManager cFormManager;
   CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

   if (pContainer)
   {
      QString qstrWql = QString("select Name, Version from \"%1\"").arg(pContainer->GetKeyname());
      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iPos = 0; iPos < pQuery->GetResultCount(); ++iPos)
         {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pItem);
            pItem->setData(0, Qt::UserRole, (int)pQuery->GetObjectIdAt(iPos));
            pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFormLibrary);
            pItem->setText(0, pQuery->GetResultAt(0, iPos).toString());
            pItem->setText(1, pQuery->GetResultAt(1, iPos).toString());
         }
      }
   }
   else
   {
       ERR("Form Library Container not found.");
   }
}

void CwmsMiscDataFiller::FillResources(QTreeWidgetItem* p_pItem)
{
   CwmsFormManager cFormManager;
   CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

   if (CHKPTR(pContainer))
   {
      QString qstrWql = QString("select Name, Type from \"%1\"").arg(pContainer->GetKeyname());
      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iPos = 0; iPos < pQuery->GetResultCount(); ++iPos)
         {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pItem);
            pItem->setData(0, Qt::UserRole, (int)pQuery->GetObjectIdAt(iPos));
            pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeResource);
            pItem->setText(0, pQuery->GetResultAt(0, iPos).toString());
            pItem->setText(1, pQuery->GetResultAt(1, iPos).toString());
         }
      }
   }
}

void CwmsMiscDataFiller::FillInteractiveComponents(QTreeWidgetItem* p_pItem)
{
   CwmsFormManager cFormManager;
   CdmObjectContainer* pContainer = cFormManager.GetInteractiveComponentContainer();

   if (CHKPTR(pContainer))
   {
      QString qstrWql = QString("select Name from \"%1\"").arg(pContainer->GetKeyname());
      CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
         for (int iPos = 0; iPos < pQuery->GetResultCount(); ++iPos)
         {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pItem);
            pItem->setData(0, Qt::UserRole, (int)pQuery->GetObjectIdAt(iPos));
            pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeInteractiveComponentForm);
            pItem->setText(0, pQuery->GetResultAt(0, iPos).toString());
         }
      }
   }
   else
   {
       ERR("Interactive Container not found!");
   }
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:29:13 2013----------*
 * @method  CwmsMiscDataFiller::FillForms                    // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:29:13 2013----------*/
void CwmsMiscDataFiller::FillForms(QTreeWidgetItem* p_pItem)
{
   CwmsFormManager cFormManager;

   QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Benutzerdefinierte Formulare"));

   FillForms(pqlviItem, "TechnicalFormUserDefined", eWmsTreeItemTypeFormUserDefined);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Standardformulare"));

   FillForms(pqlviItem, "TechnicalFormStandardObjectLists", eWmsTreeItemTypeFormStandardObjectList);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Generische Objektformulare"));

   FillForms(pqlviItem, "TechnicalFormObjects", eWmsTreeItemTypeFormGenericObject);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Sicht konfigurierte Formulare"));

   FillForms(pqlviItem, "TechnicalFormViewObjectLists", eWmsTreeItemTypeFormViewObjectList);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Objekt konfigurierte Formulare"));

   FillForms(pqlviItem, "TechnicalFormObjectObjectLists", eWmsTreeItemTypeFormObjectObjectList);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(p_pItem);
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   pqlviItem->setText(0, QObject::tr("Suchformulare"));

   FillForms(pqlviItem, "TechnicalFormSearch", eWmsTreeItemTypeFormSearch);
   pqlviItem->setExpanded(true);

   pqlviItem = new QTreeWidgetItem(pqlviItem);
   pqlviItem->setText(0, QObject::tr("Interactive Components"));
   pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeForm);
   FillInteractiveComponents(pqlviItem);
    pqlviItem->setExpanded(true);
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:30:26 2013----------*
 * @method  CwmsMiscDataFiller::FillForms                    // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @param   QString p_qstrObjectList                         //                                   *
 * @param   EwmsTreeItemType p_eType                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:30:26 2013----------*/
void CwmsMiscDataFiller::FillForms(QTreeWidgetItem* p_pItem,
                                   QString p_qstrObjectList,
                                   EwmsTreeItemType p_eType)
{
   if (p_pItem)
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (pCdmManager)
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

         if (CHKPTR(pCdmClassManager))
         {
            QString qstrWql = "select Name, Class_Uri from \"" + p_qstrObjectList + "\"";

            CdmQueryEnhanced* pQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

            if (pQuery)
            {
               for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
               {
                  QString qstrName = pQuery->GetResultAt(0,iCounter).toString();
                  QString qstrUri =  pQuery->GetResultAt(1,iCounter).toString();
                  int iObjectId = pQuery->GetObjectIdAt(iCounter);

                  QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pItem);
                  pItem->setData(1, Qt::UserRole, p_eType);
                  pItem->setData(0, Qt::UserRole, iObjectId);
                  pItem->setText(0, qstrName);
                  CdmModelElement* pElement = (CdmModelElement*)pCdmManager->GetUriObject(qstrUri);

                  if (pElement && pElement->IsClass())
                  {
                     QString qstrClass = pElement->GetCaption() + " (" + pElement->GetKeyname() + ")";
                     pItem->setText(1, qstrClass);
                  }
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:31:04 2013----------*
 * @method  CwmsMiscDataFiller::FillReports                  // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:31:04 2013----------*/
void CwmsMiscDataFiller::FillReports(QTreeWidget* p_pTreeWidget)
{
   p_pTreeWidget->clear();
   QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pTreeWidget);
   pItem->setText(0, QObject::tr("Berichte"));
   pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);

   FillReports(pItem);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTreeWidget);
   p_pTreeWidget->sortByColumn(0, Qt::AscendingOrder);
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:31:42 2013----------*
 * @method  CwmsMiscDataFiller::FillReports                  // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* pItem                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:31:42 2013----------*/
void CwmsMiscDataFiller::FillReports(QTreeWidgetItem* pItem)
{
   CwmsReportManager cManager;
   QStringList qlClassKeynames;
   cManager.GetClassesWithReports(qlClassKeynames);
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && CHKPTR(pItem))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();
      if(CHKPTR(pCdmDatabase))
      {
          CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmDatabase->GetId());

          for (int iCounter = 0; iCounter < qlClassKeynames.count(); ++iCounter)
          {
             CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(qlClassKeynames[iCounter]);

             if (pCdmClass)
             {
                FillReports(pItem, pCdmClass);
             }
          }

          pItem->setExpanded(true);
      }
   }
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:32:43 2013----------*
 * @method  CwmsMiscDataFiller::FillReports                  // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* pParent                         //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:32:43 2013----------*/
void CwmsMiscDataFiller::FillReports(QTreeWidgetItem* pParent, CdmClass* p_pClass)
{
   CwmsReportManager cManager;
   if (p_pClass) // can be nullptr if class was deleted
   {
      QTreeWidgetItem* pqlviClass = new QTreeWidgetItem(pParent);
      pqlviClass->setText(0, p_pClass->GetCaption() + " (" + p_pClass->GetFullQualifiedName() + ")");
      pqlviClass->setText(1, p_pClass->GetFullQualifiedName());
      pqlviClass->setData(0, Qt::UserRole, (int)p_pClass->GetId());
      pqlviClass->setData(1, Qt::UserRole, eWmsTreeItemTypeClass);

      CdmQueryEnhanced* pQuery = cManager.GetReportsByClassKeyname(p_pClass->GetFullQualifiedName());

      if (pQuery && pQuery->GetResultCount() > 0)
      {  
         FillReports(pqlviClass, pQuery);      
      }

      pqlviClass->setExpanded(true);
      DELPTR(pQuery);
   }
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:33:03 2013----------*
 * @method  CwmsMiscDataFiller::FillReports                  // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pParent                       //                                   *
 * @param   CdmQueryEnhanced* pQuery                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:33:03 2013----------*/
void CwmsMiscDataFiller::FillReports(QTreeWidgetItem* p_pParent, CdmQueryEnhanced* pQuery)
{
   QTreeWidgetItem* pqlviList = new QTreeWidgetItem(p_pParent);
   pqlviList->setText(0, QObject::tr("Objektcontainer"));
   pqlviList->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);
               
   QTreeWidgetItem* pqlviObject = new QTreeWidgetItem(p_pParent);
   pqlviObject->setText(0, QObject::tr("Objekt"));
   pqlviObject->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();
   
      for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
      {
         QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
         int iLanguage = pQuery->GetResultAt(1, iCounter).toInt();
         QString qstrLanguage = pCdmDatabase->GetLanguage(iLanguage);
         EwmsTemplateType eType = (EwmsTemplateType)pQuery->GetResultAt(2, iCounter).toInt(); 
         int iObjectId = pQuery->GetObjectIdAt(iCounter);
         QTreeWidgetItem* pqlviItem = nullptr;

         if (eType == eWmsTemplateTypeList)
         {
            pqlviItem = new QTreeWidgetItem(pqlviList);
         }
         else
         {
            pqlviItem = new QTreeWidgetItem(pqlviObject);
         }

         pqlviItem->setText(0, qstrName);
         pqlviItem->setText(1, qstrLanguage);
         pqlviItem->setData(0, Qt::UserRole, iObjectId);
         pqlviItem->setData(1, Qt::UserRole, eWmsTreeItemTypeReport);
      }

      if (pqlviObject->childCount() == 0)
      {
         DELPTR(pqlviObject);
      }
      else
      {
         pqlviObject->setExpanded(true);
      }

      if (pqlviList->childCount() == 0)
      {
         DELPTR(pqlviList);
      }
      else
      {
         pqlviList->setExpanded(true);
      }
   }
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:34:35 2013----------*
 * @method  CwmsMiscDataFiller::FillViews                    // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:34:35 2013----------*/
void CwmsMiscDataFiller::FillViews(QTreeWidget* p_pTreeWidget)
{
   p_pTreeWidget->clear();
   QTreeWidgetItem* pItem = new QTreeWidgetItem(p_pTreeWidget);
   pItem->setText(0, QObject::tr("Sichten"));
   pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);
   FillViews(pItem);
   pItem->setExpanded(true);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTreeWidget);
   p_pTreeWidget->sortByColumn(0, Qt::AscendingOrder);
}

/** +-=---------------------------------------------------------Fr 20. Sep 16:34:54 2013----------*
 * @method  CwmsMiscDataFiller::FillViews                    // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pParent                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 16:34:54 2013----------*/
void CwmsMiscDataFiller::FillViews(QTreeWidgetItem* p_pParent)
{
   QList<CdmObject*> qllObjects;

   CwmsViewManager cCwmsViewManager;
   cCwmsViewManager.GetViewList(qllObjects);

   QList<CdmObject*>::iterator qllIt = qllObjects.begin();
   QList<CdmObject*>::iterator qllItEnd = qllObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CwmsView cCwmsView(*qllIt);
      
      if (cCwmsView.IsValid())
      {
         QTreeWidgetItem* pqItem = new QTreeWidgetItem(p_pParent);
         pqItem->setText(0, cCwmsView.GetName());
         pqItem->setData(0, Qt::UserRole, QVariant((int)cCwmsView.GetObjectId()));
         pqItem->setData(1, Qt::UserRole, eWmsTreeItemTypeView);
      }
   }
}

void CwmsMiscDataFiller::FilterTreeWidgetsUnderRootElement(QString p_qstrFilter, QTreeWidget* p_pTreeWidget)
{
    QString qstrFilter = p_qstrFilter;
    QTreeWidgetItem* pitem = p_pTreeWidget->topLevelItem(0);

    if (CHKPTR(pitem))
    {
        for (int counter = 0; counter < pitem->childCount(); ++counter)
        {
            QTreeWidgetItem* pItem = pitem->child(counter);

            if (CHKPTR(pItem))
            {
                if (qstrFilter.isEmpty())
                {
                    pItem->setHidden(false);
                }
                else
                {
                    QString qstrView = pItem->text(0);

                    if (qstrView.contains(qstrFilter))
                    {
                        pItem->setHidden(false);
                    }
                    else
                    {
                        pItem->setHidden(true);
                    }
                }
            }
        }
    }
}


/** +-=---------------------------------------------------------So 22. Sep 12:54:00 2013----------*
 * @method  CwmsMiscDataFiller::FillWorkflows                // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 22. Sep 12:54:00 2013----------*/
void CwmsMiscDataFiller::FillWorkflows(QTreeWidget* p_pTreeWidget)
{
   p_pTreeWidget->clear();
   QTreeWidgetItem* pWorkflows = new QTreeWidgetItem(p_pTreeWidget);
   pWorkflows->setText(0, QObject::tr("Geschäftsprozesse"));
   pWorkflows->setData(1, Qt::UserRole, eWmsTreeItemTypeNone);
   FillWorkflows(pWorkflows);
   pWorkflows->setExpanded(true);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTreeWidget);
   p_pTreeWidget->sortByColumn(0, Qt::AscendingOrder);
}

/** +-=---------------------------------------------------------So 22. Sep 12:56:40 2013----------*
 * @method  CwmsMiscDataFiller::FillWorkflows                // private, static                   *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pParent                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 22. Sep 12:56:40 2013----------*/
void CwmsMiscDataFiller::FillWorkflows(QTreeWidgetItem* p_pParent)
{
   QList<CdmObject*> qllObjects;
   CwmsWorkflowManager cCwmsWorkflowManager;
   cCwmsWorkflowManager.GetWorkflowList(qllObjects);

   QList<CdmObject*>::iterator qllIt = qllObjects.begin();
   QList<CdmObject*>::iterator qllItEnd = qllObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CwmsWorkflowDefinition cCwmsWorkflow(*qllIt);

      if (cCwmsWorkflow.IsValid())
      {
         QTreeWidgetItem* pqItem = new QTreeWidgetItem(p_pParent);
         pqItem->setText(0, cCwmsWorkflow.GetName());
         pqItem->setData(0, Qt::UserRole, QVariant((int)cCwmsWorkflow.GetObjectId()));
         pqItem->setData(1, Qt::UserRole, eWmsTreeItemTypeWorkflow);
      }
   }
}

void CwmsMiscDataFiller::FillLanguages(QComboBox* p_pLanguages)
{
    if (CHKPTR(p_pLanguages))
    {
        p_pLanguages->clear();
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pCdmManager))
       {
          CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

          if (CHKPTR(pCdmDatabase))
          {
             QMap<int, QString> qmLanguages = pCdmDatabase->GetLanguageMap();
             QMap<int, QString>::iterator qmIt = qmLanguages.begin();
             QMap<int, QString>::iterator qmItEnd = qmLanguages.end();

             for (; qmIt != qmItEnd; ++qmIt)
             {
                p_pLanguages->addItem(qmIt.value(), qmIt.value());
             }

             p_pLanguages->setEnabled(true);
          }
       }
    }
}
