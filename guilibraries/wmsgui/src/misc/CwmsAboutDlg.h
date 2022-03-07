/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsAboutDlg.h
 ** Started Implementation: 2012/09/05
 ** Description:
 ** 
 ** implements the about dlg for displaying in apps
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSABOUTDLG_H
#define CWMSABOUTDLG_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsApplication.h"
#include "ui_CwmsAboutDlg.h"

// Forwards
class CwmsRuntime;

// TypeDefs


/* 
 * This class implements the about dlg for displaying in apps
 */
class WMSGUI_API CwmsAboutDlg : public QDialog, public Ui::CwmsAboutDlgClass
{
   Q_OBJECT

   private:
      QString m_qstrLicence;

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 10:46:26 2012--------*
    * @method  CwmsAboutDlg::CwmsAboutDlg                    // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 10:46:26 2012-----------*/
    CwmsAboutDlg( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 10:46:34 2012--------*
    * @method  CwmsAboutDlg::~CwmsAboutDlg                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsAboutDlg                                               *
    *----------------last changed: -----------------------------Mi 5. Sep 10:46:34 2012-----------*/
    virtual ~CwmsAboutDlg( );

   private:
   /** +-=---------------------------------------------------------Mi 5. Sep 10:51:15 2012--------*
    * @method  CwmsAboutDlg::FillDialog                      // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplication p_cApp                        //                                   *
    * @param   CwmsRuntime* p_pCwmsRuntime                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 10:51:15 2012-----------*/
    void FillDialog(CwmsApplication p_cApp, CwmsRuntime* p_pCwmsRuntime);

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 10:52:19 2012--------*
    * @method  CwmsAboutDlg::ShowAboutDialog                 // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsApplication p_cApp                        //                                   *
    * @param   CwmsRuntime* p_pCwmsRuntime                   //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 10:52:19 2012-----------*/
    static void ShowAboutDialog(CwmsApplication p_cApp,
                                CwmsRuntime* p_pCwmsRuntime,
                                QWidget* p_pqwParent);

    private slots:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:13:20 2012--------*
    * @method  CwmsAboutDlg::LicenceClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 11:13:20 2012-----------*/
void LicenceClickedSlot( );
};

#endif // CWMSABOUTDLG_H
