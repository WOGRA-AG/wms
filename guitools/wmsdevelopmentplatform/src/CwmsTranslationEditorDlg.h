/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsTranslationEditorDlg.h
 ** Started Implementation: 2012/08/17
 ** Description:
 ** 
 ** implementes the editor for translations in enterprise manager
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSTRANSLATIONEDITORDLG_H
#define CWMSTRANSLATIONEDITORDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "ui_CwmsTranslationEditorDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements the editor for translations in enterprise manager
 */
class CwmsTranslationEditorDlg : public QDialog, public Ui::CwmsTranslationEditorDlgClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:27:49 2012-------*
    * @method  CwmsTranslationEditorDlg::CwmsTranslationEditorDlg // public                       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:27:49 2012----------*/
    CwmsTranslationEditorDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:28:17 2012-------*
    * @method  CwmsTranslationEditorDlg::~CwmsTranslationEditorDlg // public, virtual             *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsTranslationEditorDlg                                   *
    *----------------last changed: -----------------------------Fr 17. Aug 15:28:17 2012----------*/
    virtual ~CwmsTranslationEditorDlg( );

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:32:09 2012-------*
    * @method  CwmsTranslationEditorDlg::FillDialog          // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iLanguageId                             //                                   *
    * @param   QString p_qstrTranslation                     //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:32:09 2012----------*/
    void FillDialog(QString p_iLanguageId, QString p_qstrTranslation, QString p_qstrComment);

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:32:04 2012-------*
    * @method  CwmsTranslationEditorDlg::FillDialog          // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iLanguageId                             //                                   *
    * @param   QString p_qstrTranslation                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:32:04 2012----------*/
    void FillDialog(QString p_iLanguageId, QString p_qstrTranslation);

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:31:05 2012-------*
    * @method  CwmsTranslationEditorDlg::OKClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:31:05 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:31:17 2012-------*
    * @method  CwmsTranslationEditorDlg::Validate            // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:31:17 2012----------*/
    bool Validate();

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:56:51 2012-------*
    * @method  CwmsTranslationEditorDlg::GetLanguageId       // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:56:51 2012----------*/
    QString GetLanguage();

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:57:01 2012-------*
    * @method  CwmsTranslationEditorDlg::GetComment          // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:57:01 2012----------*/
    QString GetComment();

   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:57:11 2012-------*
    * @method  CwmsTranslationEditorDlg::GetTranslation      // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:57:11 2012----------*/
    QString GetTranslation();

   public:
   /** +-=---------------------------------------------------------Mo 20. Aug 13:19:19 2012-------*
    * @method  CwmsTranslationEditorDlg::FillDialog          // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 13:19:19 2012----------*/
    void FillDialog();
};

#endif // CWMSTRANSLATIONEDITORDLG_H
