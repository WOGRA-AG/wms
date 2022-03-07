/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsShowMessageListDlg.h
 ** Started Implementation: 2013/02/08
 ** Description:
 ** 
 ** implements the ui for displaying message lists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSHOWMESSAGELISTDLG_H
#define CWMSSHOWMESSAGELISTDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_CwmsShowMessageListDlg.h"

// Forwards


// TypeDefs


/* 
 * This class implements the ui for displaying message lists
 */
class CwmsShowMessageListDlg : public QDialog, public Ui::CwmsShowMessageListDlgClass
{
   Q_OBJECT

    private:
    QString m_qstrMessages;

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 15:16:44 2013--------*
    * @method  CwmsShowMessageListDlg::CwmsShowMessageListDlg // public                           *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:16:44 2013-----------*/
    CwmsShowMessageListDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 15:17:07 2013--------*
    * @method  CwmsShowMessageListDlg::~CwmsShowMessageListDlg // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsShowMessageListDlg                                     *
    *----------------last changed: -----------------------------Fr 8. Feb 15:17:07 2013-----------*/
    virtual ~CwmsShowMessageListDlg( );

   private:
   /** +-=---------------------------------------------------------Fr 8. Feb 15:21:25 2013--------*
    * @method  CwmsShowMessageListDlg::FillDialog            // private                           *
    * @return  void                                          //                                   *
    * @param   QStringList m_qstrlMessage                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:21:25 2013-----------*/
    void FillDialog(QStringList m_qstrlMessage);

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 15:25:33 2013--------*
    * @method  CwmsShowMessageListDlg::ShowMessages          // public, static                    *
    * @return  void                                          //                                   *
    * @param   QStringList p_qstrlMessages                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 8. Feb 15:25:33 2013-----------*/
    static void ShowMessages(QStringList p_qstrlMessages, QWidget* p_pqwParent);

    public slots:
    void SaveClickedSlot();
};

#endif // CWMSSHOWMESSAGELISTDLG_H
