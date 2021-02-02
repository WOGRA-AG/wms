/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoeInsertTableDlg.h
 ** Started Implementation: 2008/12/03
 ** Description:
 ** 
 ** implements the dialog for isnerting tables to the editor.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef COEINSERTTABLEDLG_H
#define COEINSERTTABLEDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>


// Own Includes
#include "ui_CoeInsertTableDlg.h"

// Forwards
class QTextCursor;

// Enumerations

// Nmespaces
using namespace Ui;


/* 
 * This class implements the inserttable dlg
*/
class CoeInsertTableDlg : public QDialog, public CoeInsertTableDlgClass
{
   Q_OBJECT


   public:
   /** +-=---------------------------------------------------------Mi 3. Dez 19:03:49 2008--------*
    * @method  CoeInsertTableDlg::CoeInsertTableDlg          // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 3. Dez 19:03:49 2008-----------*/
    CoeInsertTableDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 3. Dez 19:04:08 2008--------*
    * @method  CoeInsertTableDlg::~CoeInsertTableDlg         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CoeInsertTableDlg                                          *
    *----------------last changed: -----------------------------Mi 3. Dez 19:04:08 2008-----------*/
    virtual ~CoeInsertTableDlg( );

   public:
   /** +-=---------------------------------------------------------Mi 3. Dez 19:04:59 2008--------*
    * @method  CoeInsertTableDlg::InsertTableInTextDocument  // public                            *
    * @return  void                                          //                                   *
    * @param   QTextCursor* p_pCursor                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 3. Dez 19:04:59 2008-----------*/
    void InsertTableInTextDocument(QTextCursor* p_pCursor);
};


#endif // // COEINSERTTABLEDLG_H
