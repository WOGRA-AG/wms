/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsHelp.h
 ** Started Implementation: 2012/09/05
 ** Description:
 ** 
 ** implements a simple help viewer
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSHELP_H
#define CWMSHELP_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_CwmsHelp.h"

// Forwards


// TypeDefs

#include "wmsgui.h"

/* 
 * This class implements a simple help viewer
 */
class WMSGUI_API CwmsHelp : public QDialog, public Ui::CwmsHelpClass
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:48:11 2012--------*
    * @method  CwmsHelp::CwmsHelp                            // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 11:48:11 2012-----------*/
    CwmsHelp( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:49:20 2012--------*
    * @method  CwmsHelp::~CwmsHelp                           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsHelp                                                   *
    *----------------last changed: -----------------------------Mi 5. Sep 11:49:20 2012-----------*/
    virtual ~CwmsHelp( );

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:49:44 2012--------*
    * @method  CwmsHelp::ShowHelp                            // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrHelp                            //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 11:49:44 2012-----------*/
    static void ShowHelp(QString p_qstrHelp, QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 5. Sep 11:50:50 2012--------*
    * @method  CwmsHelp::ShowLicence                         // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrHelp                            //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 11:50:50 2012-----------*/
    static void ShowLicence(QString p_qstrHelp, QWidget* p_pqwParent);
};

#endif // CWMSHELP_H
