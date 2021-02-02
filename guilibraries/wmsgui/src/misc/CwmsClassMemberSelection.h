/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsClassMemberSelection.h
 ** Started Implementation: 2012/09/10
 ** Description:
 ** 
 ** implements the selector for member variables and functions
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCLASSMEMBERSELECTION_H
#define CWMSCLASSMEMBERSELECTION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>

// Own Includes
#include "ui_CwmsClassMemberSelection.h"

// Forwards
class CdmClassMethod;
class CdmClass;
class CdmMember;

// TypeDefs


/* 
 * This class implements the selector for member variables and functions
 */
class CwmsClassMemberSelection : public QDialog, public Ui::CwmsClassMemberSelectionClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 13:43:45 2012-------*
    * @method  CwmsClassMemberSelection::CwmsClassMemberSelection // public                       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 13:43:45 2012----------*/
    CwmsClassMemberSelection( QWidget* p_pqwParent);

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 11:08:21 2012-------*
    * @method  CwmsClassMemberSelection::FillDialog          // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<QString, CdmClassMethod*>& p_rqmMethods  //                                   *
    * @param   bool p_bOnlyObjectMethods = false             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 11:08:21 2012----------*/
    void FillDialog(QMap<QString, CdmClassMethod*>& p_rqmMethods, bool p_bOnlyObjectMethods = false);

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 13:48:51 2012-------*
    * @method  CwmsClassMemberSelection::FillDialog          // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<long,CdmMember*>& p_rqmMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 13:48:51 2012----------*/
    void FillDialog(QMap<long,CdmMember*>& p_rqmMembers);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 13:50:29 2012-------*
    * @method  CwmsClassMemberSelection::GetSelectedValues   // public                            *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 13:50:29 2012----------*/
    QStringList GetSelectedValues();

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:54:25 2013-------*
    * @method  CwmsClassMemberSelection::GetFunctionSelection // public, static                   *
    * @return  QStringList                                   //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @param   bool p_bOnlyObjectMethods                     //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 10:54:25 2013----------*/
    static QStringList GetFunctionSelection(const CdmClass* p_pCdmClass,
                                            bool p_bOnlyObjectMethods,
                                            QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:55:32 2013-------*
    * @method  CwmsClassMemberSelection::GetMemberSelection  // public, static                    *
    * @return  QStringList                                   //                                   *
    * @param   const CdmClass* p_pCdmClass                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 10:55:32 2013----------*/
    static QStringList GetMemberSelection(const CdmClass* p_pCdmClass, QWidget* p_pqwParent);

    private slots:
    void MemberDoubleClickedSlot(QModelIndex p_qIndex);
};

#endif // CWMSCLASSMEMBERSELECTION_H
