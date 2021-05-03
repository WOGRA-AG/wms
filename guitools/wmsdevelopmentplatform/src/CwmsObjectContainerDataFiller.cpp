/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectContainerDataFiller.h
 ** Started Implementation: 2013/09/18
 ** Description:
 ** 
 ** implements static helpers for filling objectcontainers in ui.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsAdminMainWindowIf.h"
#include "CwmsClassDataFiller.h"
#include "CwmsObjectContainerDataFiller.h"

#define MAX_CONTAINERS 500

/** +-=---------------------------------------------------------Mo 23. Sep 08:40:16 2013----------*
 * @method  CwmsObjectContainerDataFiller::FillAllObjectContainersToView // public, static        *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pTree                             //                                   *
 * @param   bool p_bShowTechnicalClasses                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 08:40:16 2013----------*/
void CwmsObjectContainerDataFiller::FillAllObjectContainersToView(QTreeWidget* p_pTree,
                                                                  bool p_bShowTechnicalClasses)
{
    BODY_TRY
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();
        CdmClassManager* pClassManager = pCdmManager->GetClassManager();

      if (CHKPTR(p_pTree)           &&
          CHKPTR(pContainerManager) &&
          CHKPTR(pClassManager))
      {
          p_pTree->clear();
          QList<CdmClass*> qlClasses;
          pClassManager->GetClassList(qlClasses);

          QList<CdmClass*>::const_iterator qIt    = qlClasses.begin();
          QList<CdmClass*>::const_iterator qItEnd = qlClasses.end();

          for ( ; qIt != qItEnd; ++qIt)
          {
              CdmClass* pClass = *qIt;

              if (CHKPTR(pClass) &&
                  (p_bShowTechnicalClasses || !CwmsClassDataFiller::IsTechnicalClass(pClass)) &&
                  !pClass->IsAbstract())
              {
                  QTreeWidgetItem* pqtwClassItem = new QTreeWidgetItem(p_pTree);
                  pqtwClassItem->setText(0, pClass->GetFullQualifiedName());

                  if (!pClass->IsSingleton())
                  {
                      pqtwClassItem->setText(0, pClass->GetFullQualifiedName());
                      QList<QString>  qvlObjectLists = pContainerManager->GetContainerList(pClass->GetId());

                      QList<QString>::iterator qmIt    = qvlObjectLists.begin();
                      QList<QString>::iterator qmItEnd = qvlObjectLists.end();

                      QSet<QString> qsetAlreadyAddedContainers;
                      int iCount = 0;

                      for ( ; qmIt != qmItEnd; ++qmIt)
                      {
                          ++iCount;
                          QString qstrKeyname = *qmIt;

                          if (!qsetAlreadyAddedContainers.contains(qstrKeyname))
                          {
                              QTreeWidgetItem* pqlviOL = new QTreeWidgetItem(pqtwClassItem);
                              pqlviOL->setText(0, qstrKeyname);
                              pqlviOL->setData(1, Qt::UserRole, eWmsTreeItemTypeContainer);
                              qsetAlreadyAddedContainers.insert(qstrKeyname);
                          }

                          if (iCount >= MAX_CONTAINERS)
                          {
                              QTreeWidgetItem* pqlviOL = new QTreeWidgetItem(pqtwClassItem);
                              pqlviOL->setText(0, tr("0-Maximale Anzahl an dargestellten Containern (500) erreicht."));
                              break;
                          }
                      }

                      if (pqtwClassItem->childCount() <= 10)
                      {
                          pqtwClassItem->setExpanded(true);
                      }
                  }
                  else
                  {
                      pqtwClassItem->setText(0, pClass->GetFullQualifiedName() + " (Singleton)");
                      pqtwClassItem->setData(0, Qt::UserRole, pClass->GetFullQualifiedName());
                      pqtwClassItem->setData(1, Qt::UserRole, eWmsTreeItemTypeSingletonClass);
                  }
              }
          }
      }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 18. Sep 14:25:24 2013----------*
 * @method  CwmsObjectContainerDataFiller::FillObjectContainersToClass // public, static          *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 14:25:24 2013----------*/
void CwmsObjectContainerDataFiller::FillObjectContainersToClass(CdmClass* p_pClass,
                                                                QTreeWidgetItem* p_pItem)
{
    BODY_TRY
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());

        if (CHKPTR(p_pItem)  &&
            CHKPTR(p_pClass) &&
            CHKPTR(pContainerManager))
        {
            QTreeWidgetItem* pqlviOLItem = new QTreeWidgetItem(p_pItem);
            QList<QString>  qvlObjectLists = pContainerManager->GetContainerList(p_pClass->GetId());

            QList<QString>::iterator qmIt    = qvlObjectLists.begin();
            QList<QString>::iterator qmItEnd = qvlObjectLists.end();

            for ( ; qmIt != qmItEnd; ++qmIt)
            {
                QString qstrKeyname = *qmIt;
                //CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerByKeyname(qstrKeyname);
                QTreeWidgetItem* pqlviObjectContainer = new QTreeWidgetItem(pqlviOLItem);
                pqlviObjectContainer->setText(0, qstrKeyname);
                pqlviObjectContainer->setData(1, Qt::UserRole, eWmsTreeItemTypeContainer);
            }

            pqlviOLItem->setText(0, QObject::tr("Objektcontainer") + " (" + QString::number(qvlObjectLists.count()) + ")");
        }

        p_pItem->setExpanded(true);
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mi 18. Sep 15:07:56 2013----------*
 * @method  CwmsObjectContainerDataFiller::FillObjectContainersToClass // public, static          *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @param   QTreeWidget* p_pTreeWidget                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 15:07:56 2013----------*/
void CwmsObjectContainerDataFiller::FillObjectContainersToClass(CdmClass* p_pClass,
                                                                QTreeWidget* p_pTreeWidget)
{
    BODY_TRY
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());

        if (CHKPTR(p_pTreeWidget) &&
            CHKPTR(p_pClass)      &&
            CHKPTR(pContainerManager))
        {
            p_pTreeWidget->clear();
            QList<QString> qvlObjectLists = pContainerManager->GetContainerList(p_pClass->GetId());

            QList<QString>::iterator qmIt    = qvlObjectLists.begin();
            QList<QString>::iterator qmItEnd = qvlObjectLists.end();

            for ( ; qmIt != qmItEnd; ++qmIt)
            {
                QString qstrKeyname = *qmIt;
                QTreeWidgetItem* pqlviOL = new QTreeWidgetItem(p_pTreeWidget);
                pqlviOL->setText(0, qstrKeyname);
                pqlviOL->setData(1, Qt::UserRole, eWmsTreeItemTypeContainer);
            }
        }
    }
    BODY_CATCH
}
