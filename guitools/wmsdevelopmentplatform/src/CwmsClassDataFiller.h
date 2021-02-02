/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectContainerDataFiller.h
 ** Started Implementation: 2013/09/18
 ** Description:
 ** 
 ** implements static helpers for filling class in ui.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCLASSDATAFILLER_H
#define CWMSCLASSDATAFILLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
// Own Includes


// Forwards
class QTreeWidget;
class QComboBox;
class CdmClass;
class CdmClassManager;
class QTreeWidgetItem;
class CdmPackage;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsClassDataFiller : public QObject
{
   Q_OBJECT

   private:
   /** +-=---------------------------------------------------------Mi 18. Sep 19:04:29 2013-------*
    * @method  CwmsClassDataFiller::FillFunctions            // private, static                   *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QTreeWidgetItem* p_pqtwClass                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 19:04:29 2013----------*/
    static void FillFunctions(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);

   private:
   /** +-=---------------------------------------------------------Mi 18. Sep 19:04:54 2013-------*
    * @method  CwmsClassDataFiller::FillMembersAndGroups     // private, static                   *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QTreeWidgetItem* p_pqtwClass                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 19:04:54 2013----------*/
    static void FillMembersAndGroups(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);

    static void FillPackage(CdmPackage *p_pPackage, QTreeWidgetItem *p_pParent);
   static bool IsTechnicalPackage(CdmPackage *p_pPackage);
public:
   /** +-=---------------------------------------------------------Mi 18. Sep 19:05:12 2013-------*
    * @method  CwmsClassDataFiller::FillClass                // public, static                    *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QTreeWidgetItem* p_pqtwClass                  //                                   *
    * @param   bool p_bAddObjectContainers                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 19:05:12 2013----------*/
    static void FillClass(CdmClass* p_pCdmClass,
                          QTreeWidgetItem* p_pqtwClass,
                          bool p_bAddObjectContainers);

   public:
   /** +-=---------------------------------------------------------Mi 18. Sep 19:10:00 2013-------*
    * @method  CwmsClassDataFiller::FillClasses              // public, static                    *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pClassManager              //                                   *
    * @param   QTreeWidgetItem* p_pParent                    //                                   *
    * @param   bool p_bAddObjectContainers                   //                                   *
    * @param   bool p_bShowTechnicalItems                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 19:10:00 2013----------*/
    static void FillClasses(CdmClassManager* p_pClassManager,
                            QTreeWidgetItem* p_pParent,
                            bool p_bAddObjectContainers,
                            bool p_bShowTechnicalItems);

   public:
   /** +-=---------------------------------------------------------Fr 20. Sep 15:42:52 2013-------*
    * @method  CwmsClassDataFiller::FillClassesToComboBox    // public, static                    *
    * @return  void                                          //                                   *
    * @param   QComboBox* p_pComboBox                        //                                   *
    * @param   bool p_bAddAbstractClasses                    //                                   *
    * @param   bool p_bFilterMode                            //                                   *
    * @param   bool p_bShowTechnicalClasses                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 15:42:52 2013----------*/
    static void FillClassesToComboBox(QComboBox* p_pComboBox,
                                      bool p_bAddAbstractClasses,
                                      bool p_bFilterMode,
                                      bool p_bShowTechnicalClasses);

   public:
   /** +-=---------------------------------------------------------Do 19. Sep 08:16:59 2013-------*
    * @method  CwmsClassDataFiller::IsTechnicalClass         // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Sep 08:16:59 2013----------*/
    static bool IsTechnicalClass(CdmClass* p_pClass);
};

#endif //
