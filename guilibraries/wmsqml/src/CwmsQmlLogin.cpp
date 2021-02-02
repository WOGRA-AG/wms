/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes 
#include <QQuickWindow>
#include <QQuickItem>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// WMSQML Includes
#include "CwmsQmlApplicationController.h"
#include "CwqQmlObjectViewer.h"

// Own Includes
#include "CwmsInitApplication.h"
#include "CwmsDataAccessConfiguration.h"
#include "CwmsQmlLogin.h"

QString CwmsQmlLogin::m_qstrLoginError = "";

/** +-=---------------------------------------------------------Di 28. Sep 08:16:36 2010----------*
 * @method  CwmsLogin::CwmsLogin                         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrAppliactionName                    //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 08:16:36 2010----------*/
CwmsQmlLogin::CwmsQmlLogin(QString p_qstrAppliactionName, CwmsInitApplication* p_pInit, QWidget* parent)
: m_cCdmSettings(eDmSettingsModeClient),
  m_qstrApplicationName(p_qstrAppliactionName),
  m_pInit(p_pInit),
  m_pView(nullptr)
{
   Q_UNUSED(parent);
}

/** +-=---------------------------------------------------------Thu Dec 18 13:37:17 2003----------*
 * @method  CwmsLogin::~CwmsLogin                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsLogin                                                   *
 *---------------------------------------------------------------Thu Dec 18 13:37:17 2003---------*/
CwmsQmlLogin::~CwmsQmlLogin(  )
{
    DELPTR(m_pView);
}

QUrl CwmsQmlLogin::getDialogUrl()
{
    return QUrl("qrc:/qml/WmsLogin.qml");
}

void CwmsQmlLogin::openLoginDialog()
{
    // Old Stuff should not be used!!!!
   INFO("In Open Settings");
   QObject* pThis = dynamic_cast<QObject*>(this);
   INFO("This pointer casted to QObject");
   CwqQmlObjectViewer* pViewer = new CwqQmlObjectViewer(nullptr);
   INFO("QML Viewer created"); 
   m_pView = pViewer->CreateView("qrc:/qml/WmsLogin.qml", "loginObj", pThis);

   if (CHKPTR(m_pView))
   {
      INFO("View created");
      m_pView->setTitle(m_qstrApplicationName);
      pViewer->ShowModal();
   }
   else
   {
      m_pInit->StateFinished(false);
   }
}



void CwmsQmlLogin::registerToQml()
{
    qmlRegisterUncreatableType<CwmsQmlLogin>("com.wogra.wmsqml", 1, 0, "WmsLogin", "WmsLogin can oonly be created by the system");
}

void CwmsQmlLogin::cancel()
{
    m_pInit->StateFinished(false);
}

void CwmsQmlLogin::loginSuccessfull()
{
    m_pInit->StateFinished(true);
}



/** +-=---------------------------------------------------------Thu Dec 18 15:23:11 2003----------*
 * @method  CwmsLogin::Login                       // public, virtual, slots         *
 * @return  bool                                             //                                   *
 * @comment This slot will be called if the user wants to login to the system.                    *
 *---------------------------------------------------------------Thu Dec 18 15:23:11 2003---------*/
bool CwmsQmlLogin::login()
{
   CwmsQmlApplicationController* pController = CwmsQmlApplicationController::getController();

   QQuickItem* pItem = pController->getCurrentContent();
   QString qstrLogin = pItem->property("login").toString();
   QString qstrPassword = pItem->property("password").toString();

    if (pItem->property("saveLogin").toBool())
    {
        m_cCdmSettings.SetWmsLogin(qstrLogin);
        m_cCdmSettings.SetPassword(qstrPassword);
        m_cCdmSettings.SetStoreWmsLogin(true);
    }
    else
    {
        m_cCdmSettings.SetWmsLogin("");
        m_cCdmSettings.SetPassword("");
        m_cCdmSettings.SetStoreWmsLogin(false);
    }

    return loginP(m_qstrApplicationName, qstrLogin, qstrPassword);
}

/** +-=---------------------------------------------------------Sa 22. Jan 13:14:52 2005----------*
 * @method  CwmsLogin::SetCaption                          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment Sets the Caption of the Login Dialog.                                                 *
 *----------------last changed: --------------------------------Sa 22. Jan 13:14:52 2005----------*/
void CwmsQmlLogin::setCaption(QString p_qstrCaption)
{
   if (CHKPTR(m_pView))
   {
      m_pView->setTitle(p_qstrCaption);
   }
}

QString CwmsQmlLogin::getLogin()
{
    return m_cCdmSettings.GetWmsLogin();
}

void CwmsQmlLogin::setLogin(QString p_qstrLogin)
{
    m_cCdmSettings.SetWmsLogin(p_qstrLogin);
}

QString CwmsQmlLogin::getPassword()
{
    return m_cCdmSettings.GetPassword();
}

void CwmsQmlLogin::setPassword(QString p_qstrPassword)
{
    m_cCdmSettings.SetPassword(p_qstrPassword);
}

bool CwmsQmlLogin::getStoreUserData()
{
    return m_cCdmSettings.GetStoreWmsLogin();
}

void CwmsQmlLogin::setStoreUserData(bool p_bStoreUserData)
{
    m_cCdmSettings.SetStoreWmsLogin(p_bStoreUserData);
}


/** +-=---------------------------------------------------------Do 29. Dez 13:57:34 2005----------*
 * @method  CwmsLogin::Login                               // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrApplicationName                    //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment This static memeber function starts the login screen waits for user input and will    *
 *          do all the stuff for creating a workable WMS, inlcusive communication settings and    *
 *          so on.                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 13:57:34 2005----------*/
void CwmsQmlLogin::login(QString p_qstrApplicationName,
                      QString p_qstrCaption,
                      CwmsInitApplication* p_pInit,
                      QWidget* p_pqwParent )
{
   CwmsQmlLogin* pCwmsLogin = new CwmsQmlLogin(p_qstrApplicationName, p_pInit, p_pqwParent);
   pCwmsLogin->openLoginDialog();
   pCwmsLogin->setCaption(p_qstrCaption);
}

/** +-=---------------------------------------------------------Mi 20. Feb 22:57:08 2008----------*
 * @method  CwmsLogin::AutoLogin                           // public, static                    *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrApplicationName                    //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment This static memeber function starts the login screen waits for user input and         *
 *          will                                                                                  *
 *          do all the stuff for creating a workable WMS, inlcusive communication settings        *
 *          and                                                                                   *
 *          so on.                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Mi 20. Feb 22:57:08 2008----------*/
bool CwmsQmlLogin::autoLogin(QString p_qstrApplicationName,
                            QString p_qstrLogin,
                            QString p_qstrPassword)
{
   return loginP(p_qstrApplicationName, p_qstrLogin, p_qstrPassword);
}

/** +-=---------------------------------------------------------Di 28. Sep 09:10:42 2010----------*
 * @method  CwmsLogin::LoginP                              // private, static                   *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment Does the real login.                                                                  *
 *----------------last changed: --------------------------------Di 28. Sep 09:10:42 2010----------*/
bool CwmsQmlLogin::loginP(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword)
{
    Q_UNUSED(p_qstrApplication);
   bool bRet = false;
   CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();
   int iRet = pSessionManager->CreateNewSession(p_qstrLogin,
                                                p_qstrPassword);

   if (iRet > 0)
   {
       bRet = true;
   }
   else
   {
       if(iRet == CdmLogging::eDmNoLicenceLeft)
       {
          m_qstrLoginError = tr("Es steht keine Lizenz zur Verfügung. Bitte kontaktieren Sie Ihren Administrator");
       }
       else if (iRet == CdmLogging::eDmUserNotFound)
       {
          m_qstrLoginError = tr("Falscher Benutzername oder Passwort");
       }
       else if (iRet == CdmLogging::eDmSessionCreationError)
       {
          m_qstrLoginError = tr("Es konnte keine neue Sitzung gestartet werden.");
       }
       else if (iRet == CdmLogging::eDmInvalidPtr)
       {
          m_qstrLoginError =  tr("Es konnte keine Verbindung zur Datenbank aufgebaut werden.");
       }
       else
       {
          m_qstrLoginError = tr("Es konnte keine Verbindung zur Datenbank aufgebaut werden.\n"
                                "Bitte überprüfen Sie Ihre Client Einstellungen.");

       }
   }

   return bRet;
}



QString CwmsQmlLogin::getLoginError()
{
    return m_qstrLoginError;
}
