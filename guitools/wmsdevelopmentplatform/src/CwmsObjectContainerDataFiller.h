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

#ifndef CWMSOBJECTCONTAINERDATAFILLER_H
#define CWMSOBJECTCONTAINERDATAFILLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
// Own Includes


// Forwards
class QTreeWidget;
class CdmClass;
class QTreeWidgetItem;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsObjectContainerDataFiller : public QObject
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Mo 23. Sep 08:40:16 2013-------*
    * @method  CwmsObjectContainerDataFiller::FillAllObjectContainersToView // public, static     *
    * @return  void                                          //                                   *
    * @param   QTreeWidget* p_pTree                          //                                   *
    * @param   bool p_bShowTechnicalClasses                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 08:40:16 2013----------*/
    static void FillAllObjectContainersToView(QTreeWidget* p_pTree, bool p_bShowTechnicalClasses);

   public:
   /** +-=---------------------------------------------------------Mi 18. Sep 14:25:24 2013-------*
    * @method  CwmsObjectContainerDataFiller::FillObjectContainersToClass // public, static       *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 14:25:24 2013----------*/
    static void FillObjectContainersToClass(CdmClass* p_pClass, QTreeWidgetItem* p_pItem);

   public:
   /** +-=---------------------------------------------------------Mi 18. Sep 15:07:56 2013-------*
    * @method  CwmsObjectContainerDataFiller::FillObjectContainersToClass // public, static       *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @param   QTreeWidget* p_pTreeWidget                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 15:07:56 2013----------*/
    static void FillObjectContainersToClass(CdmClass* p_pClass, QTreeWidget* p_pTreeWidget);
};

#endif //
