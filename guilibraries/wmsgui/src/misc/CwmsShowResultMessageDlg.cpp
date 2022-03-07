/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsShowResultMessageDlg.cpp
 ** Started Implementation: 2013/02/08
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CwmsShowResultMessageDlg.h"


/** +-=---------------------------------------------------------Fr 8. Feb 14:43:11 2013-----------*
 * @method  CwmsShowResultMessageDlg::CwmsShowResultMessageDlg // public                          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 14:43:11 2013-----------*/
CwmsShowResultMessageDlg::CwmsShowResultMessageDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 8. Feb 14:43:41 2013-----------*
 * @method  CwmsShowResultMessageDlg::~CwmsShowResultMessageDlg // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsShowResultMessageDlg                                      *
 *----------------last changed: --------------------------------Fr 8. Feb 14:43:41 2013-----------*/
CwmsShowResultMessageDlg::~CwmsShowResultMessageDlg()
{
}

/** +-=---------------------------------------------------------Fr 8. Feb 14:44:24 2013-----------*
 * @method  CwmsShowResultMessageDlg::FillDialog             // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QString p_qstrResultText                         //                                   *
 * @param   QString p_qstrResult                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 14:44:24 2013-----------*/
void CwmsShowResultMessageDlg::FillDialog(QString p_qstrCaption,
                                          QString p_qstrResultText,
                                          QString p_qstrResult)
{
   setWindowTitle(p_qstrCaption);
   m_pqlResultHeader->setText(p_qstrCaption);
   m_pqlResultText->setText(p_qstrResultText);
   m_pqtbResult->setPlainText(p_qstrResult);
}


/** +-=---------------------------------------------------------Fr 8. Feb 14:45:07 2013-----------*
 * @method  CwmsShowResultMessageDlg::ShowResult             // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QString p_qstrResultText                         //                                   *
 * @param   QString p_qstrResult                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 14:45:07 2013-----------*/
void CwmsShowResultMessageDlg::ShowResult(QString p_qstrCaption,
                                          QString p_qstrResultText,
                                          QString p_qstrResult,
                                          QWidget* p_pqwParent)
{
   CwmsShowResultMessageDlg cDlg(p_pqwParent);
   cDlg.FillDialog(p_qstrCaption, p_qstrResultText, p_qstrResult);
   cDlg.exec();
}
