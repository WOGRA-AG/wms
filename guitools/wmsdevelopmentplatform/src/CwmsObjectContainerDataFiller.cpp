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
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

#include "CwmsTreeWidgetHelper.h"

// Own Includes
#include "CwmsAdminMainWindowIf.h"
#include "CwmsClassDataFiller.h"
#include "CwmsObjectContainerDataFiller.h"

#define MAX_CONTAINERS 500

void CwmsObjectContainerDataFiller::FillAllObjectContainersToView(QTreeWidget* p_pTree,
                                                                  bool p_bShowTechnicalClasses,
                                                                  int p_iLimit)
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
                        FillObjectContainersToClass(pClass, pqtwClassItem, p_iLimit);

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

            CwmsTreeWidgetHelper::ResizeColumnsToContent(p_pTree);
            p_pTree->sortByColumn(0, Qt::AscendingOrder);

        }
    }
    BODY_CATCH
}

void CwmsObjectContainerDataFiller::FillObjectContainersToClass(CdmClass* p_pClass,
                                                                QTreeWidgetItem* p_pItem,
                                                                int p_iLimit)
{
    BODY_TRY
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && CHKPTR(p_pClass) && CHKPTR(p_pItem))
    {
        IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

        if (CHKPTR(pIdmDataAccess))
        {
            QMap<qint64, QString> qmObjectLists;

            pIdmDataAccess->GetContainerList(pCdmManager->GetCurrentScheme()->GetId(),
                                             p_pClass->GetId(),
                                             qmObjectLists);

            QMap<qint64, QString>::iterator qmIt    = qmObjectLists.begin();
            QMap<qint64, QString>::iterator qmItEnd = qmObjectLists.end();
            int iCounter = 0;

            for ( ; qmIt != qmItEnd; ++qmIt)
            {
                if (iCounter > p_iLimit && p_iLimit > 0)
                {
                    break;
                }
                else
                {
                    ++iCounter;
                }


                QString qstrKeyname = *qmIt;
                QTreeWidgetItem* pqlviOL = new QTreeWidgetItem(p_pItem);
                pqlviOL->setText(0, qmIt.value());
                pqlviOL->setData(0, Qt::UserRole, qmIt.key());
                pqlviOL->setData(1, Qt::UserRole, eWmsTreeItemTypeContainer);
            }
        }

        p_pItem->setExpanded(true);
    }
    BODY_CATCH
}

void CwmsObjectContainerDataFiller::FillObjectContainersToClass(CdmClass* p_pClass,
                                                                QTreeWidget* p_pTreeWidget)
{
    BODY_TRY
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && CHKPTR(p_pClass) && CHKPTR(p_pTreeWidget))
    {
        IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

        if (CHKPTR(pIdmDataAccess))
        {
            QMap<qint64, QString> qmObjectLists;

            pIdmDataAccess->GetContainerList(pCdmManager->GetCurrentScheme()->GetId(),
                                             p_pClass->GetId(),
                                             qmObjectLists);
            p_pTreeWidget->clear();

            QMap<qint64, QString>::iterator qmIt    = qmObjectLists.begin();
            QMap<qint64, QString>::iterator qmItEnd = qmObjectLists.end();

            for ( ; qmIt != qmItEnd; ++qmIt)
            {
                QString qstrKeyname = *qmIt;
                QTreeWidgetItem* pqlviOL = new QTreeWidgetItem(p_pTreeWidget);
                pqlviOL->setText(0, qmIt.value());
                pqlviOL->setData(0, Qt::UserRole, qmIt.key());
                pqlviOL->setData(1, Qt::UserRole, eWmsTreeItemTypeContainer);
            }
        }
    }
    BODY_CATCH
}
