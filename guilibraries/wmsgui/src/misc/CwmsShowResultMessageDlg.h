/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsShowResultMessageDlg.h
 ** Started Implementation: 2013/02/08
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSHOWRESULTMESSAGEDLG_H
#define CWMSSHOWRESULTMESSAGEDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_CwmsShowResultMessageDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements the ui for displaying results of functions
 */
class CwmsShowResultMessageDlg : public QDialog, public Ui::CwmsShowResultMessageDlgClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 14:43:11 2013--------*
    * @method  CwmsShowResultMessageDlg::CwmsShowResultMessageDlg // public                       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 14:43:11 2013-----------*/
    CwmsShowResultMessageDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 14:43:41 2013--------*
    * @method  CwmsShowResultMessageDlg::~CwmsShowResultMessageDlg // public, virtual             *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsShowResultMessageDlg                                   *
    *----------------last changed: -----------------------------Fr 8. Feb 14:43:41 2013-----------*/
    virtual ~CwmsShowResultMessageDlg( );

   private:
   /** +-=---------------------------------------------------------Fr 8. Feb 14:44:24 2013--------*
    * @method  CwmsShowResultMessageDlg::FillDialog          // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QString p_qstrResultText                      //                                   *
    * @param   QString p_qstrResult                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 14:44:24 2013-----------*/
    void FillDialog(QString p_qstrCaption, QString p_qstrResultText, QString p_qstrResult);

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 14:45:07 2013--------*
    * @method  CwmsShowResultMessageDlg::ShowResult          // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QString p_qstrResultText                      //                                   *
    * @param   QString p_qstrResult                          //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 14:45:07 2013-----------*/
    static void ShowResult(QString p_qstrCaption,
                           QString p_qstrResultText,
                           QString p_qstrResult,
                           QWidget* p_pqwParent);
};

#endif // CWMSSHOWRESULTMESSAGEDLG_H
