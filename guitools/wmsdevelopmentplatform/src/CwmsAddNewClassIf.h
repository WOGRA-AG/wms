/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsAddNewClassIf.h
 ** Started Implementation: 2008/05/23
 ** Description:
 ** 
 ** implements the class creation dlg
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

#ifndef CWMSADDNEWCLASSIF_H
#define CWMSADDNEWCLASSIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_cwmsaddnewclass.h"


// Forwards


// Enumerations

/* 
 * This class implements the class creation dlg
 */
class CwmsAddNewClassIf : public QDialog, public Ui::CwmsAddNewClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Mo 27. Aug 18:34:23 2012-------*
    * @method  CwmsAddNewClassIf::CwmsAddNewClassIf          // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 18:34:23 2012----------*/
    CwmsAddNewClassIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Fr 23. Mai 20:29:44 2008-------*
    * @method  CwmsAddNewClassIf::~CwmsAddNewClassIf         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsAddNewClassIf                                          *
    *----------------last changed: -----------------------------Fr 23. Mai 20:29:44 2008----------*/
    virtual ~CwmsAddNewClassIf( );

    private slots:
   /** +-=---------------------------------------------------------Fr 23. Mai 20:30:33 2008-------*
    * @method  CwmsAddNewClassIf::OKClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 23. Mai 20:30:33 2008----------*/
void OKClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 23. Mai 20:30:46 2008-------*
    * @method  CwmsAddNewClassIf::CancelClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 23. Mai 20:30:46 2008----------*/
void CancelClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 27. Dez 12:32:55 2012-------*
    * @method  CwmsAddNewClassIf::Validate                   // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 27. Dez 12:32:55 2012----------*/
    bool Validate();
};

#endif //

