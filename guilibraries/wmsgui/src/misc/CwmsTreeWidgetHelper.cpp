// System and QT Includes
#include <CwmsQueryModelExportCsv.h>
#include <QHeaderView>
#include <QTreeWidget>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmQueryModel.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"


QTreeWidgetItem* CwmsTreeWidgetHelper::GetSelectedItem(QTreeWidget* p_pWidget)
{
    QTreeWidgetItem* pItem = nullptr;

    if (p_pWidget)
    {
        QList<QTreeWidgetItem*> qlItems = p_pWidget->selectedItems();

        if (qlItems.count() > 0)
        {
            pItem = qlItems[0];
        }
    }

    return pItem;
}

QList<QTreeWidgetItem*> CwmsTreeWidgetHelper::GetSelectedItems(QTreeWidget* p_pWidget)
{
    QList<QTreeWidgetItem*> qlItems;

    if(p_pWidget)
    {
        qlItems.append(p_pWidget->selectedItems());
    }

    return qlItems;
}

QList<QTreeWidgetItem*> CwmsTreeWidgetHelper::GetCheckedItems(QTreeWidget* p_pWidget)
{
    QList<QTreeWidgetItem*> qlItems;

    for(int iPos = 0; iPos < p_pWidget->topLevelItemCount(); ++iPos)
    {
        QTreeWidgetItem *pqtwItem = p_pWidget->topLevelItem(iPos);

        if(pqtwItem && pqtwItem->checkState(0) == Qt::Checked)
        {
            qlItems.insert(iPos, pqtwItem);
        }
    }

    return qlItems;
}

QList<QTreeWidgetItem*> CwmsTreeWidgetHelper::GetUncheckedItems(QTreeWidget* p_pWidget)
{
    QList<QTreeWidgetItem*> qlItems;

    for(int iPos = 0; iPos < p_pWidget->topLevelItemCount(); ++iPos)
    {
        QTreeWidgetItem *pqtwItem = p_pWidget->topLevelItem(iPos);

        if(pqtwItem && pqtwItem->checkState(0) == Qt::Unchecked)
        {
            qlItems.insert(iPos, pqtwItem);
        }
    }

    return qlItems;
}

CdmObject* CwmsTreeWidgetHelper::GetSelectedObject(QTreeWidget* p_pWidget)
{
    CdmObject* pObject = nullptr;
    QTreeWidgetItem* pItem = GetSelectedItem(p_pWidget);

    if (pItem)
    {
        pObject = GetItemObject(pItem);
    }

    return pObject;
}

QList<CdmObject*> CwmsTreeWidgetHelper::GetSelectedObjects(QTreeWidget* p_pWidget)
{
    QList<CdmObject*> qlObjects;
    QList<QTreeWidgetItem*> qlItems = p_pWidget->selectedItems();

    for (int iPos = 0; iPos < qlItems.count(); ++iPos)
    {
        QTreeWidgetItem* pItem = qlItems[iPos];

        if (pItem)
        {
            CdmObject* pObject = GetItemObject(pItem);

            if (pObject)
            {
                qlObjects.append(pObject);
            }
        }
    }
    return qlObjects;
}

CdmObject* CwmsTreeWidgetHelper::GetItemObject(QTreeWidgetItem* p_pItem)
{
    CdmObject* pObject = nullptr;

    if (p_pItem)
    {
        QString qstrUri = p_pItem->data(0, Qt::UserRole).toString();
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            pObject = static_cast<CdmObject*>(pManager->GetUriObject(qstrUri));
        }
    }

    return pObject;
}

void CwmsTreeWidgetHelper::SetObjectToItem(CdmObject* p_pObject, QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pObject) && CHKPTR(p_pItem))
    {
        p_pItem->setData(0, Qt::UserRole, p_pObject->GetUriInternal());
    }
}

QTreeWidgetItem* CwmsTreeWidgetHelper::CreateItemAtEnd(QTreeWidget* p_pqtwWidget)
{
    QTreeWidgetItem* pqtwItem = nullptr;

    if (CHKPTR(p_pqtwWidget))
    {
        if (p_pqtwWidget->topLevelItemCount() > 0)
        {
            pqtwItem = new QTreeWidgetItem(p_pqtwWidget, p_pqtwWidget->topLevelItem(p_pqtwWidget->topLevelItemCount() - 1));
        }
        else
        {
            pqtwItem = new QTreeWidgetItem(p_pqtwWidget);
        }
    }

    return pqtwItem;
}

QTreeWidgetItem* CwmsTreeWidgetHelper::GetItemAbove(QTreeWidgetItem* p_pqItem)
{
    QTreeWidgetItem* pqRet = nullptr;

    if (CHKPTR(p_pqItem))
    {
        QTreeWidgetItemIterator it(p_pqItem);
        pqRet = (*(--it));
    }

    return pqRet;
}

QTreeWidgetItem* CwmsTreeWidgetHelper::GetItemBelow(QTreeWidgetItem* p_pqItem)
{
    QTreeWidgetItem* pqRet = nullptr;

    if (CHKPTR(p_pqItem))
    {
        QTreeWidgetItemIterator it(p_pqItem);
        pqRet = (*(++it));
    }

    return pqRet;
}

void CwmsTreeWidgetHelper::ResizeColumnsToContent(QTreeView* p_pView)
{
    if (CHKPTR(p_pView) && p_pView->model())
    {
        int iColumns = p_pView->model()->columnCount();

        if (iColumns > 0)
        {
            for (int iCounter = 0; iCounter < iColumns; ++iCounter)
            {
                p_pView->resizeColumnToContents(iCounter);
            }
        }

        //p_pView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
}

void CwmsTreeWidgetHelper::SelectObject(QTreeWidget* p_pWidget, CdmObject* p_pObject)
{
    p_pWidget->clearSelection();

    if (p_pObject)
    {
        QString qstrUri = p_pObject->GetUriInternal();

        for (int pos = 0; pos < p_pWidget->topLevelItemCount(); ++pos)
        {
            QTreeWidgetItem* pItem = p_pWidget->topLevelItem(pos);

            if (CHKPTR(pItem))
            {
                if (qstrUri == pItem->data(0, Qt::UserRole).toString())
                {
                    pItem->setSelected(true);
                    break;
                }
                else
                {
                    if (SelectChildItem(pItem, qstrUri))
                    {
                        break;
                    }
                }
            }
        }
    }
}

void CwmsTreeWidgetHelper::SelectRow(QTreeView *p_pView, int p_iRowPos)
{
    p_pView->clearSelection();
    QModelIndex qmIndexLeft;
    QModelIndex qmIndexRight;
    QModelIndex qmRootIndex = p_pView->rootIndex();

    CdmQueryModel *pModel = dynamic_cast<CdmQueryModel*>(p_pView->model());

    QItemSelectionModel *pSelectionModel = p_pView->selectionModel();
    QItemSelection qiSelection = pSelectionModel->selection();
    pSelectionModel->setModel(pModel);

    if(pModel && pSelectionModel)
    {
        int iColumnCount = pModel->columnCount();
        pSelectionModel->clearSelection();
        qmIndexLeft = pModel->index(p_iRowPos, 0, qmRootIndex);
        qmIndexRight = pModel->index(p_iRowPos, iColumnCount - 1, qmRootIndex);
        qiSelection.select(qmIndexLeft, qmIndexRight);

        pSelectionModel->select(qiSelection, QItemSelectionModel::ClearAndSelect);
        p_pView->setSelectionModel(pSelectionModel);
    }
}

void CwmsTreeWidgetHelper::SelectObject(QTreeView *p_pView, CdmObject *p_pObject)
{
    p_pView->clearSelection();
    QModelIndex qmIndexLeft;
    QModelIndex qmIndexRight;
    QModelIndex qmRootIndex = p_pView->rootIndex();

    CdmQueryModel *pModel = dynamic_cast<CdmQueryModel*>(p_pView->model());

    QItemSelectionModel *pSelectionModel = p_pView->selectionModel();
    QItemSelection qiSelection = pSelectionModel->selection();
    pSelectionModel->setModel(pModel);

    if(pModel && pSelectionModel)
    {
        pSelectionModel->clearSelection();

        FindCorrectIndexesOfModel(qmIndexRight, qmIndexLeft, qmRootIndex, pModel, p_pObject);

        qiSelection.select(qmIndexLeft, qmIndexRight);

        pSelectionModel->select(qiSelection, QItemSelectionModel::ClearAndSelect);
        p_pView->setSelectionModel(pSelectionModel);
    }
}

void CwmsTreeWidgetHelper::FindCorrectIndexesOfModel(QModelIndex &qmIndexRight, QModelIndex &qmIndexLeft, QModelIndex &qmRootIndex, CdmQueryModel *&pModel, CdmObject *&p_pObject)
{
    CdmObject *pObject = nullptr;

    int iRowCount = pModel->rowCount(qmRootIndex);
    int iColumnCount = pModel->columnCount(qmRootIndex);

    for(int iRow = 0; iRow < iRowCount; ++iRow)
    {
        if(qmIndexRight.isValid())
        {
            break;
        }

        for(int iColumn = 0; iColumn < iColumnCount; ++iColumn)
        {
            qmIndexLeft = pModel->index(iRow, iColumn, qmRootIndex);
            pObject = pModel->GetObject(iRow);

            if(pObject->GetId() == p_pObject->GetId())
            {
                qmIndexRight = pModel->index(iRow, iColumnCount - 1, qmRootIndex);
                break;
            }
        }
    }
}

void CwmsTreeWidgetHelper::SelectItem(QTreeWidget* p_pWidget, int p_iCompareColumn, QString p_qstrCompareString)
{
    p_pWidget->clearSelection();

    for (int pos = 0; pos < p_pWidget->topLevelItemCount(); ++pos)
    {
        QTreeWidgetItem* pItem = p_pWidget->topLevelItem(pos);

        if (CHKPTR(pItem))
        {
            if (p_qstrCompareString == pItem->text(p_iCompareColumn))
            {
                pItem->setSelected(true);
                break;
            }
            else
            {
                if (SelectChildItemByText(pItem, p_iCompareColumn, p_qstrCompareString))
                {
                    break;
                }
            }
        }
    }
}

bool CwmsTreeWidgetHelper::SelectChildItemByText(QTreeWidgetItem* p_pItem, int p_iCompareColumn, QString p_qstrCompareString)
{
    bool bRet = false;

    for (int pos = 0; pos < p_pItem->childCount(); ++pos)
    {
        QTreeWidgetItem* pItem = p_pItem->child(pos);

        if (CHKPTR(pItem))
        {
            if (p_qstrCompareString == pItem->text(p_iCompareColumn))
            {
                pItem->setSelected(true);
                break;
            }
            else
            {
                if (SelectChildItemByText(pItem, p_iCompareColumn, p_qstrCompareString))
                {
                    break;
                }
            }
        }
    }

    return bRet;
}

bool CwmsTreeWidgetHelper::SelectChildItem(QTreeWidgetItem* p_pItem, QString p_qstrUri)
{
    bool bRet = false;

    for (int pos = 0; pos < p_pItem->childCount(); ++pos)
    {
        QTreeWidgetItem* pItem = p_pItem->child(pos);

        if (CHKPTR(pItem))
        {
            if (p_qstrUri == pItem->data(0, Qt::UserRole).toString())
            {
                pItem->setSelected(true);
                break;
            }
            else
            {
                if (SelectChildItem(pItem, p_qstrUri))
                {
                    break;
                }
            }
        }
    }

    return bRet;
}

void CwmsTreeWidgetHelper::ExportCsvToFile(QTreeView* p_pView, QString qstrHeadInformation, QString qstrFootInformation)
{
    QAbstractItemModel* pModel = p_pView->model();

    if (CHKPTR(pModel))
    {
        CwmsQueryModelExportCsv::ExportCsvToFile(*pModel, qstrHeadInformation, qstrFootInformation);
    }
}

void CwmsTreeWidgetHelper::ExportCsvToFile(QTreeView* p_pView)
{
    QAbstractItemModel* pModel = p_pView->model();

    if (CHKPTR(pModel))
    {
        CwmsQueryModelExportCsv::SaveModel(*pModel);
    }
}

QString CwmsTreeWidgetHelper::ExportCsv(QTreeView* p_pView)
{
    QString qstrContent;
    QAbstractItemModel* pModel = p_pView->model();

    if (CHKPTR(pModel))
    {
        CwmsQueryModelExportCsv::ExportCsv(*pModel);
    }

    return qstrContent;
}

QString CwmsTreeWidgetHelper::ExportCsv(QTreeView* p_pView, QModelIndexList& p_qlIndexes)
{
    QString qstrContent;

    QAbstractItemModel* pModel = p_pView->model();

    if (CHKPTR(pModel))
    {
        qstrContent = CwmsQueryModelExportCsv::ExportCsv(*pModel, p_qlIndexes);
    }

    return qstrContent;
}

void CwmsTreeWidgetHelper::ChangeCheckStateOfAllItem(QTreeWidget *p_pView, int p_iColumn, bool p_bSelected)
{
    for (int iPos = 0; iPos < p_pView->topLevelItemCount(); ++iPos)
    {
        QTreeWidgetItem* pItem = p_pView->topLevelItem(iPos);

        if (CHKPTR(pItem))
        {
            if (p_bSelected)
            {
                pItem->setCheckState(p_iColumn, Qt::Checked);
            }
            else
            {
                pItem->setCheckState(p_iColumn, Qt::Unchecked);
            }
        }
    }
}

bool CwmsTreeWidgetHelper::RemoveObjectFromWidget(QTreeWidget *pWidget, QTreeWidgetItem *pSelectedItem)
{
    bool bRet = false;

    int iIndex = pWidget->indexOfTopLevelItem(pSelectedItem);
    QTreeWidgetItem *pRemovedItem = pWidget->takeTopLevelItem(iIndex);

    if(CHKPTR(pRemovedItem))
    {
        bRet = true;
    }

    return bRet;
}

int CwmsTreeWidgetHelper::GetItemCount(QTreeWidget *pWidget)
{
    int iItemCount = 0;

    for (int iPos = 0; iPos < pWidget->topLevelItemCount(); ++iPos)
    {
        QTreeWidgetItem* pItem = pWidget->topLevelItem(iPos);

        if (CHKPTR(pItem))
        {
            iItemCount++;
        }
    }

    return iItemCount;
}

void CwmsTreeWidgetHelper::Init(QTreeView* p_pView)
{
    if (CHKPTR(p_pView))
    {
        QHeaderView* pQHeaderView = p_pView->header();

        if (pQHeaderView)
        {
            pQHeaderView->setStretchLastSection(false);
            pQHeaderView->setSortIndicator(0, Qt::AscendingOrder);
        }
    }
}

