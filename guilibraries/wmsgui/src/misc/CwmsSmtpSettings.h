/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsSmtpSettings.h
 ** Started Implementation: 2010/01/11
 ** Description:
 ** 
 ** Implements the configurator for smtp
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSMTPSETTINGS_H
#define CWMSSMTPSETTINGS_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "CwmsSmtpConfiguration.h"
#include "ui_CwmsSmtpSettings.h"
#include "wmsgui.h"


// Forwards


// Enumerations

/* 
 * This class implements the configurator for smtp
 */
class WMSGUI_API CwmsSmtpSettings : public QDialog, public Ui::CwmsSmtpSettingsClass
{
   Q_OBJECT

      CwmsSmtpConfiguration m_cCwmsSmtpConfiguration;


   public:
   /** +-=---------------------------------------------------------Mo 11. Jan 21:37:10 2010-------*
    * @method  CwmsSmtpSettings::CwmsSmtpSettings              // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Jan 21:37:10 2010----------*/
    CwmsSmtpSettings( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mo 11. Jan 21:37:28 2010-------*
    * @method  CwmsSmtpSettings::~CwmsSmtpSettings             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSmtpSettings                                            *
    *----------------last changed: -----------------------------Mo 11. Jan 21:37:28 2010----------*/
    virtual ~CwmsSmtpSettings( );

   private:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:41:39 2012-------*
    * @method  CwmsSmtpSettings::FillDialog                  // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsSmtpConfiguration p_cCbmsConfigurator     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:41:39 2012----------*/
    void FillDialog(CwmsSmtpConfiguration p_cCbmsConfigurator);

   private:
   /** +-=---------------------------------------------------------Mo 11. Jan 21:38:35 2010-------*
    * @method  CwmsSmtpSettings::SaveSettings                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Jan 21:38:35 2010----------*/
    void SaveSettings();

   public:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:42:40 2012-------*
    * @method  CwmsSmtpSettings::Edit                        // public, static                    *
    * @return  void                                          //                                   *
    * @param   CwmsSmtpConfiguration p_cCbmsConfigurator     //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:42:40 2012----------*/
    static void Edit(CwmsSmtpConfiguration p_cCbmsConfigurator, QWidget* p_pqwParent);
};

#endif //

