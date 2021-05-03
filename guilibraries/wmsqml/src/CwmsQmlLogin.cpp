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

CwmsQmlLogin::CwmsQmlLogin(QString p_qstrAppliactionName, CwmsInitApplication* p_pInit, QWidget* parent)
: m_cCdmSettings(eDmSettingsModeClient),
  m_qstrApplicationName(p_qstrAppliactionName),
  m_pInit(p_pInit),
  m_pView(nullptr)
{
   Q_UNUSED(parent);
}

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


void CwmsQmlLogin::login(QString p_qstrApplicationName,
                      QString p_qstrCaption,
                      CwmsInitApplication* p_pInit,
                      QWidget* p_pqwParent )
{
   CwmsQmlLogin* pCwmsLogin = new CwmsQmlLogin(p_qstrApplicationName, p_pInit, p_pqwParent);
   pCwmsLogin->openLoginDialog();
   pCwmsLogin->setCaption(p_qstrCaption);
}

bool CwmsQmlLogin::autoLogin(QString p_qstrApplicationName,
                            QString p_qstrLogin,
                            QString p_qstrPassword)
{
   return loginP(p_qstrApplicationName, p_qstrLogin, p_qstrPassword);
}

bool CwmsQmlLogin::loginP(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword)
{
   Q_UNUSED(p_qstrApplication);
    CdmMessageManager::StartAsyncMessageCollection();
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

   CdmMessageManager::EndAndShowAsyncMessageCollection();

   return bRet;
}



QString CwmsQmlLogin::getLoginError()
{
    return m_qstrLoginError;
}
