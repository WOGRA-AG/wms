/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSLOGINIF_H
#define CWMSLOGINIF_H

#ifdef WURZELBLA
#define slots
#endif



// System and QT Includes
#include <QDialog>
#include <QSettings>


// own Includes
#include "wmsgui.h"
#include "CdmSettings.h"
#include "ui_cwmslogindlg.h"


// forwards
class CdmDataAccess;


class WMSGUI_API CwmsGuiLoginIf : public QDialog, public Ui::CwmsLoginDlg
{
   Q_OBJECT

   private:
      CdmSettings m_cCdmSettings;
      QSettings m_qSettings;
      QString m_qstrApplicationName;

public:
      virtual ~CwmsGuiLoginIf(  );

   /** +-=---------------------------------------------------------Thu Dec 18 15:22:42 2003-------*
    * @method  CwmsLoginIf::CancelClickedSlot                // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to cancel the login.                    *
    *---------------------------------------------------------------Thu Dec 18 15:22:42 2003------*/
    protected slots:
      virtual void CancelClickedSlot(  );

   /** +-=---------------------------------------------------------Thu Dec 18 15:23:11 2003-------*
    * @method  CwmsLoginIf::OKClickedSlot                    // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user wants to login to the system.                 *
    *---------------------------------------------------------------Thu Dec 18 15:23:11 2003------*/
    protected slots:
      virtual void OKClickedSlot(  );

   public:
   /** +-=---------------------------------------------------------Sa 22. Jan 13:14:52 2005*
    * @method  CwmsLoginIf::SetCaption                       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment Sets the Caption of the Login Dialog.                                              *
    *----------------last changed: -----------------------------Sa 22. Jan 13:14:52 2005----------*/
void SetCaption(  QString p_qstrCaption );

   public:
   /** +-=---------------------------------------------------------Sa 22. Jan 13:16:36 2005*
    * @method  CwmsLoginIf::SetApplicationInfoText           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrLoginLabel                      //                                   *
    * @comment Sets the Text of the Login Label.                                                  *
    *----------------last changed: -----------------------------Sa 22. Jan 13:16:36 2005----------*/
void SetApplicationInfoText(  QString p_qstrLoginLabel );

   public:
    CwmsGuiLoginIf( QString p_qstrAppliactionName, QWidget* parent = nullptr);

   public:
   /** +-=---------------------------------------------------------Do 29. Dez 13:57:34 2005*
    * @method  CwmsLoginIf::Login                            // public, static                    *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrApplicationName                 //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QString p_qstrApplicationInfoText             //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment This static memeber function starts the login screen waits for user input and will *
    *          do all the stuff for creating a workable WMS, inlcusive communication settings and *
    *          so on.                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 13:57:34 2005----------*/
static bool Login(QString p_qstrApplicationName,
                  QWidget* p_pqwParent );

static  bool TryLogin(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrApplicationName, CwmsGuiLoginIf* pCwmsLoginIf);

private slots:
   /** +-=---------------------------------------------------------Fr 9. Mai 19:13:41 2008--------*
    * @method  CwmsLoginIf::ClientSettingsClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user clicks on the clientsettings button. it       *
    *          opens the clientsettings app.                                                      *
    *----------------last changed: -----------------------------Fr 9. Mai 19:13:41 2008-----------*/
void ClientSettingsClickedSlot( );


/** +-=---------------------------------------------------------Fr 9. Mai 19:13:41 2008--------*
* @method  CwmsLoginIf::LdapSettingsClickedSlot        // private, slots                    *
* @return  void                                          //                                   *
* @comment This slot will be called if the user clicks on the ldapsettings button. it       *
*          opens the ldapsettings app.                                                      *
*----------------last changed: -----------------------------Fr 29. Augsut 19:13:41 2014-----------*/
void LdapSettingsClickedSlot( );
bool LdapLogin(QString username, QString passwd);
};


#endif
