/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsListWidgetHelper.h
 ** Started Implementation: 2012/09/13
 ** Description:
 ** 
 ** implements helper functions for listwidget
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSLISTWIDGETHELPER_H
#define CWMSLISTWIDGETHELPER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"

// Forwards
class QListWidget;
class QListWidgetItem;
class CdmObject;
// TypeDefs


/* 
 * This class implements helper functions for listwidget
 */
class WMSGUI_API CwmsListWidgetHelper
{

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 11:10:37 2012-------*
    * @method  CwmsListWidgetHelper::GetSelectedItem         // public, static                    *
    * @return  QListWidgetItem*                              //                                   *
    * @param   QListWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:10:37 2012----------*/
    static QListWidgetItem* GetSelectedItem(QListWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 11:12:11 2012-------*
    * @method  CwmsListWidgetHelper::MoveItemUp              // public, static                    *
    * @return  void                                          //                                   *
    * @param   QListWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:12:11 2012----------*/
    static void MoveItemUp(QListWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 11:24:38 2012-------*
    * @method  CwmsListWidgetHelper::MoveItemDown            // public, static                    *
    * @return  void                                          //                                   *
    * @param   QListWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 11:24:38 2012----------*/
    static void MoveItemDown(QListWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------Fr 15. Mrz 10:39:40 2013-------*
    * @method  CwmsListWidgetHelper::SetObjectToItem         // public, static                    *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pObject                          //                                   *
    * @param   QListWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 15. Mrz 10:39:40 2013----------*/
    static void SetObjectToItem(CdmObject* p_pObject, QListWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Fr 15. Mrz 10:39:58 2013-------*
    * @method  CwmsListWidgetHelper::GetItemObject           // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QListWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 15. Mrz 10:39:58 2013----------*/
    static CdmObject* GetItemObject(QListWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Fr 15. Mrz 10:40:22 2013-------*
    * @method  CwmsListWidgetHelper::GetSelectedObject       // public, static                    *
    * @return  CdmObject*                                    //                                   *
    * @param   QListWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 15. Mrz 10:40:22 2013----------*/
    static CdmObject* GetSelectedObject(QListWidget* p_pWidget);
    static void SelectRow(QListWidget *p_pWidget, int p_iRow);
    static void SelectObject(QListWidget *p_pWidget, CdmObject *p_pObject);
};

#endif // CWMSLISTWIDGETHELPER_H
