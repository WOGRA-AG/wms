#ifndef CWMSTREEWIDGETHELPER_H
#define CWMSTREEWIDGETHELPER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QModelIndex>

// Own Includes
#include "wmsgui.h"

// Forwards
class CdmQueryModel;
class QTreeWidget;
class QTreeView;
class QTreeWidgetItem;
class CdmObject;
class QAbstractItemModel;

// TypeDefs


/* 
 * This class implements helper functions for treewidget
 */
class WMSGUI_API CwmsTreeWidgetHelper
{

public:
    static QTreeWidgetItem* GetSelectedItem(QTreeWidget* p_pWidget);
    static QTreeWidgetItem* CreateItemAtEnd(QTreeWidget* p_pqtwWidget);
    static QTreeWidgetItem* GetItemAbove(QTreeWidgetItem* p_pqItem);
    static QTreeWidgetItem* GetItemBelow(QTreeWidgetItem* p_pqItem);
    static CdmObject* GetSelectedObject(QTreeWidget* p_pWidget);
    static void SetObjectToItem(CdmObject* p_pObject, QTreeWidgetItem* p_pItem);
    static CdmObject* GetItemObject(QTreeWidgetItem* p_pItem);
    static void ResizeColumnsToContent(QTreeView* p_pView);
    static QList<CdmObject *> GetSelectedObjects(QTreeWidget *p_pWidget);
    static void SelectObject(QTreeWidget *p_pWidget, CdmObject *p_pObject);
    static void SelectItem(QTreeWidget *p_pWidget, int p_iCompareColumn, QString p_qstrCompareString);
    static QString ExportCsv(QTreeView *p_pView);
    static QString ExportCsv(QTreeView *p_pView, QModelIndexList &p_qlIndexes);
    static void SelectObject(QTreeView *p_pView, CdmObject *p_pObject);
    static QList<QTreeWidgetItem *> GetSelectedItems(QTreeWidget *p_pWidget);
    static QList<QTreeWidgetItem *> GetCheckedItems(QTreeWidget *p_pWidget);
    static QList<QTreeWidgetItem *> GetUncheckedItems(QTreeWidget *p_pWidget);
    static int GetItemCount(QTreeWidget *pWidget);
    static bool RemoveObjectFromWidget(QTreeWidget *pWidget, QTreeWidgetItem *pSelectedItem);
    static void ChangeCheckStateOfAllItem(QTreeWidget *p_pView, int p_iColumn, bool p_bSelected);
    static void SelectRow(QTreeView *p_pView, int p_iRowPos);
    static void Init(QTreeView*);
    static void ExportCsvToFile(QTreeView *p_pView, QString qstrHeadInformation, QString qstrFootInformation);
    static void ExportCsvToFile(QTreeView *p_pView);
private:
    static bool SelectChildItem(QTreeWidgetItem *p_pItem, QString p_qstrUri);
    static bool SelectChildItemByText(QTreeWidgetItem *p_pItem, int p_iCompareColumn, QString p_qstrCompareString);
    static void FindCorrectIndexesOfModel(QModelIndex &qmIndexRight, QModelIndex &qmIndexLeft, QModelIndex &qmRootIndex, CdmQueryModel *&pModel, CdmObject *&p_pObject);
};

#endif // CWMSTREEWIDGETHELPER_H
