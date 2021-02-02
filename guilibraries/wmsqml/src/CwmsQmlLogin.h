/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSQMLLOGIN_H
#define CWMSQMLLOGIN_H

// System and QT Includes
#include <QDialog>
#include <QUrl>

// own Includes
#include "wmsqml_global.h"
#include "CdmSettings.h"

// forwards
class QQuickWindow;
class CwmsInitApplication;


class WMSQML_EXPORT CwmsQmlLogin : public QObject
{
   Q_OBJECT

   private:
      CdmSettings m_cCdmSettings;
      QString m_qstrApplicationName;
      CwmsInitApplication* m_pInit;
      QQuickWindow* m_pView;
      static QString m_qstrLoginError;
      
   /** +-=---------------------------------------------------------Thu Dec 18 13:37:17 2003-------*
    * @method  CwmsLogin::~CwmsLogin                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsLogin                                                *
    *                                                                                             *
    *---------------------------------------------------------------Thu Dec 18 13:37:17 2003------*/
   public:
      virtual ~CwmsQmlLogin(  );


   public:
   /** +-=---------------------------------------------------------Sa 22. Jan 13:14:52 2005*
    * @method  CwmsLogin::SetCaption                       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment Sets the Caption of the Login Dialog.                                              *
    *----------------last changed: -----------------------------Sa 22. Jan 13:14:52 2005----------*/
    void setCaption(  QString p_qstrCaption );


   public:
   /** +-=---------------------------------------------------------Di 28. Sep 08:16:36 2010-------*
    * @method  CwmsLogin::CwmsLogin                      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrAppliactionName                 //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 08:16:36 2010----------*/
    CwmsQmlLogin(QString p_qstrAppliactionName, CwmsInitApplication* p_pInit, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 29. Dez 13:57:34 2005*
    * @method  CwmsLogin::Login                            // public, static                    *
    * @return  void                                          //                                   *
    * @param   QString p_qstrApplicationName                 //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment This static memeber function starts the login screen waits for user input and will *
    *          do all the stuff for creating a workable WMS, inlcusive communication settings and *
    *          so on.                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 13:57:34 2005----------*/
static void login(QString p_qstrApplicationName,
                  QString p_qstrCaption,
                  CwmsInitApplication* p_pInit,
                  QWidget* p_pqwParent );

   public:
   /** +-=---------------------------------------------------------Di 28. Sep 09:10:42 2010-------*
    * @method  CwmsLogin::LoginP                           // private, static                   *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment Does the real login.                                                               *
    *----------------last changed: -----------------------------Di 28. Sep 09:10:42 2010----------*/
    static bool loginP(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword);

   public:
   /** +-=---------------------------------------------------------Mi 20. Feb 22:57:08 2008-------*
    * @method  CwmsLogin::AutoLogin                        // public, static                    *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrApplicationName                 //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment This static memeber function starts the login screen waits for user input and      *
    *          will                                                                               *
    *          do all the stuff for creating a workable WMS, inlcusive communication settings     *
    *          and                                                                                *
    *          so on.                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Mi 20. Feb 22:57:08 2008----------*/
    static bool autoLogin(QString p_qstrApplicationName,
                          QString p_qstrLogin,
                          QString p_qstrPassword);

public:
    void openLoginDialog();
    static void registerToQml();

public slots:
    void setStoreUserData(bool p_bStoreUserData);
    bool getStoreUserData();
    void setPassword(QString p_qstrPassword);
    QString getPassword();
    void setLogin(QString p_qstrLogin);
    QString getLogin();
    void cancel();
    void loginSuccessfull();
    QString getLoginError();
    QUrl getDialogUrl();
    virtual bool login();


};

#endif
