/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsTreeWidgetHelper.h
 ** Started Implementation: 2012/09/13
 ** Description:
 ** 
 ** implements helper functions for treewidget
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

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
   /** +-=---------------------------------------------------------Do 13. Sep 11:15:33 2012-------*
    * @method  CwmsTreeWidgetHelper::GetSelectedItem         // public, static                    *
    * @return  QTreeWidgetItem*                              //                                   *
    * @param   QTreeWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:15:33 2012----------*/
    static QTreeWidgetItem* GetSelectedItem(QTreeWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------So 28. Okt 11:28:05 2012-------*
    * @method  CwmsTreeWidgetHelper::CreateItemAtEnd         // public, static                    *
    * @return  QTreeWidgetItem*                              //                                   *
    * @param   QTreeWidget* p_pqtwWidget                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 28. Okt 11:28:05 2012----------*/
    static QTreeWidgetItem* CreateItemAtEnd(QTreeWidget* p_pqtwWidget);

   public:
   /** +-=---------------------------------------------------------So 28. Okt 12:06:44 2012-------*
    * @method  CwmsTreeWidgetHelper::GetItemAbove            // public, static                    *
    * @return  QTreeWidgetItem*                              //                                   *
    * @param   QTreeWidgetItem* p_pqItem                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 28. Okt 12:06:44 2012----------*/
    static QTreeWidgetItem* GetItemAbove(QTreeWidgetItem* p_pqItem);

   public:
   /** +-=---------------------------------------------------------So 28. Okt 12:07:53 2012-------*
    * @method  CwmsTreeWidgetHelper::GetItemBelow            // public, static                    *
    * @return  QTreeWidgetItem*                              //                                   *
    * @param   QTreeWidgetItem* p_pqItem                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 28. Okt 12:07:53 2012----------*/
    static QTreeWidgetItem* GetItemBelow(QTreeWidgetItem* p_pqItem);

   public:
   /** +-=---------------------------------------------------------Do 14. Mrz 12:33:05 2013-------*
    * @method  CwmsTreeWidgetHelper::GetSelectedObject       // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QTreeWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Mrz 12:33:05 2013----------*/
    static CdmObject* GetSelectedObject(QTreeWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------Do 14. Mrz 12:41:01 2013-------*
    * @method  CwmsTreeWidgetHelper::SetObjectToItem         // public, static                    *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pObject                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Mrz 12:41:01 2013----------*/
    static void SetObjectToItem(CdmObject* p_pObject, QTreeWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Fr 15. Mrz 09:45:49 2013-------*
    * @method  CwmsTreeWidgetHelper::GetItemObject           // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 15. Mrz 09:45:49 2013----------*/
    static CdmObject* GetItemObject(QTreeWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Do 13. Jun 10:32:24 2013-------*
    * @method  CwmsTreeWidgetHelper::ResizeColumnsToContent  // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeView* p_pView                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Jun 10:32:24 2013----------*/
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
