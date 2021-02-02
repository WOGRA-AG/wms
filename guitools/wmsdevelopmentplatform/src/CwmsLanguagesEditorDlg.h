/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsLanguagesEditorDlg.h
 ** Started Implementation: 2012/08/18
 ** Description:
 ** 
 ** Implements the editor for languages at the db
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSLANGUAGESEDITORDLG_H
#define CWMSLANGUAGESEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_CwmsLanguagesEditorDlg.h"

// Forwards
class CdmScheme;

// TypeDefs


/* 
 * This class implements the editor for languages at the db
 */
class CwmsLanguagesEditorDlg : public QDialog, public Ui::CwmsLanguagesClass
{
   Q_OBJECT

   private:
      CdmScheme* m_rpCdmDatabase;

   public:
   /** +-=---------------------------------------------------------Sa 18. Aug 11:11:59 2012-------*
    * @method  CwmsLanguagesEditorDlg::CwmsLanguagesEditorDlg // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 18. Aug 11:11:59 2012----------*/
    CwmsLanguagesEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Sa 18. Aug 11:12:14 2012-------*
    * @method  CwmsLanguagesEditorDlg::~CwmsLanguagesEditorDlg // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsLanguagesEditorDlg                                     *
    *----------------last changed: -----------------------------Sa 18. Aug 11:12:14 2012----------*/
    virtual ~CwmsLanguagesEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Sa 18. Aug 11:12:27 2012-------*
    * @method  CwmsLanguagesEditorDlg::FillDialog            // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 18. Aug 11:12:27 2012----------*/
    void FillDialog();

    private slots:
   /** +-=---------------------------------------------------------Sa 18. Aug 11:45:32 2012-------*
    * @method  CwmsLanguagesEditorDlg::AddClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 18. Aug 11:45:32 2012----------*/
void AddClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Sa 18. Aug 11:45:49 2012-------*
    * @method  CwmsLanguagesEditorDlg::RemoveClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 18. Aug 11:45:49 2012----------*/
void RemoveClickedSlot( );
};

#endif // CWMSLANGUAGESEDITORDLG_H
