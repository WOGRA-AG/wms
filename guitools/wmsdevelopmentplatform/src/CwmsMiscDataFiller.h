/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectContainerDataFiller.h
 ** Started Implementation: 2013/09/20
 ** Description:
 ** 
 ** implements static helpers for filling misc data in ui.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSMISCDATAFILLER_H
#define CWMSMISCDATAFILLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsAdminMainWindowIf.h"

// Forwards
class QTreeWidget;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsMiscDataFiller : public QObject
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:24:57 2013-------*
    * @method  CwmsMiscDataFiller::FillApplications          // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:24:57 2013----------*/
    static void FillApplications(QTreeWidget* p_pTreeWidget);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:27:01 2013-------*
    * @method  CwmsMiscDataFiller::FillApplications          // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pTreeWidgetItem            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:27:01 2013----------*/
    static void FillApplications(QTreeWidgetItem* p_pTreeWidgetItem);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:28:23 2013-------*
    * @method  CwmsMiscDataFiller::FillForms                 // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:28:23 2013----------*/
    static void FillForms(QTreeWidget* p_pTreeWidget);

   private:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:29:13 2013-------*
    * @method  CwmsMiscDataFiller::FillForms                 // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:29:13 2013----------*/
    static void FillForms(QTreeWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:30:26 2013-------*
    * @method  CwmsMiscDataFiller::FillForms                 // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @param   QString p_qstrObjectList                      //                                   *
    * @param   EwmsTreeItemType p_eType                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:30:26 2013----------*/
    static void FillForms(QTreeWidgetItem* p_pItem,
                          QString p_qstrObjectList,
                          EwmsTreeItemType p_eType);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:31:04 2013-------*
    * @method  CwmsMiscDataFiller::FillReports               // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:31:04 2013----------*/
    static void FillReports(QTreeWidget* p_pTreeWidget);

   private:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:31:42 2013-------*
    * @method  CwmsMiscDataFiller::FillReports               // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* pItem                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:31:42 2013----------*/
    static void FillReports(QTreeWidgetItem* pItem);

   private:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:32:43 2013-------*
    * @method  CwmsMiscDataFiller::FillReports               // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* pParent                      //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:32:43 2013----------*/
    static void FillReports(QTreeWidgetItem* pParent, CdmClass* p_pClass);

   private:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:33:03 2013-------*
    * @method  CwmsMiscDataFiller::FillReports               // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pParent                    //                                   *
    * @param   CdmQuery* pQuery                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:33:03 2013----------*/
    static void FillReports(QTreeWidgetItem* p_pParent, CdmQuery* pQuery);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:34:35 2013-------*
    * @method  CwmsMiscDataFiller::FillViews                 // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:34:35 2013----------*/
    static void FillViews(QTreeWidget* p_pTreeWidget);

   private:
   /** +-=---------------------------------------------------------Fr 20. Sep 16:34:54 2013-------*
    * @method  CwmsMiscDataFiller::FillViews                 // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pParent                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 16:34:54 2013----------*/
    static void FillViews(QTreeWidgetItem* p_pParent);

   public:
   /** +-=---------------------------------------------------------So 22. Sep 12:54:00 2013-------*
    * @method  CwmsMiscDataFiller::FillWorkflows             // public, static                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 22. Sep 12:54:00 2013----------*/
    static void FillWorkflows(QTreeWidget* p_pTreeWidget);

    static void FillLanguages(QComboBox *p_pLanguages);
    public:
    static void FillResources(QTreeWidgetItem *p_pItem);
private:
   /** +-=---------------------------------------------------------So 22. Sep 12:56:40 2013-------*
    * @method  CwmsMiscDataFiller::FillWorkflows             // private, static                   *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pParent                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 22. Sep 12:56:40 2013----------*/
    static void FillWorkflows(QTreeWidgetItem* p_pParent);
public:
    static void FillLibraries(QTreeWidgetItem* p_pItem);
    static void FilterTreeWidgetsUnderRootElement(QString p_qstrFilter, QTreeWidget *p_pTreeWidget);
private:
    static void FillInteractiveComponents(QTreeWidgetItem *p_pItem);
};
#endif //
