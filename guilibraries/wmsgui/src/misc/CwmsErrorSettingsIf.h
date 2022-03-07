/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSERRORSETTINGSIF_H
#define CWMSERRORSETTINGSIF_H


// System and QT Includes
#include <qmap.h>


// own Includes
#include "ui_CwmsErrorSettings.h"

// forwards


class CwmsErrorSettingsIf : public QDialog, public Ui::CwmsErrorSettingsDlg
{

   private:
      QMap<QString,int> m_rqmFileSeverities;



   public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:18:23 2010-------*
    * @method  CwmsErrorSettingsIf::CwmsErrorSettingsIf      // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @param   Qt::WFlags fl = 0                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 08:18:23 2010----------*/
    CwmsErrorSettingsIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Sa 28. Jul 11:44:26 2007-------*
    * @method  CwmsErrorSettingsIf::~CwmsErrorSettingsIf     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsErrorSettingsIf                                        *
    *----------------last changed: Wolfgang Graßhof-------------Sa 28. Jul 11:44:26 2007----------*/
    virtual ~CwmsErrorSettingsIf( );

   public:
   /** +-=---------------------------------------------------------Sa 28. Jul 11:46:15 2007-------*
    * @method  CwmsErrorSettingsIf::SetFileSeverities        // public                            *
    * @return  void                                          //                                   *
    * @param   QMap<QString, int>& p_rqmSeverities           //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Sa 28. Jul 11:46:15 2007----------*/
    void SetFileSeverities(QMap<QString, int>& p_rqmSeverities);

   private:
   /** +-=---------------------------------------------------------Sa 28. Jul 11:46:51 2007-------*
    * @method  CwmsErrorSettingsIf::FillTable                // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the tables with the fileseverities settings.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 28. Jul 11:46:51 2007----------*/
    void FillTable();
};

#endif //
