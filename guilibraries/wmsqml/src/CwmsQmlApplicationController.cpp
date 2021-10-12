
// System and Qt Includes
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QQuickView>
#include <QQuickWindow>


// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
//#include "CdmObjectContainer.h"
#include "CsaObject.h"
#include "CdmDataProvider.h"
#include "CdmQueryModel.h"
#include "CsaObjectContainer.h"
#include "CsaManager.h"
#include "CdmSessionManager.h"

// Basetools Includes
#include "CwmsFormManager.h"
#include "CwmsFormUserDefined.h"
#include "CwmsInitApplication.h"
#include "CwmsContext.h"
#include "cwmsbtplattforminformation.h"
#include "CwmsScriptableLogger.h"
#include "CwmsScriptableMailer.h"
#include "CwmsScriptableMessage.h"
#include "CwmsScriptablePlugin.h"
#include "CwmsScriptablePrinter.h"
#include "CwmsScriptableStatic.h"
#include "CwmsScriptableWorkflow.h"
#include "CwmsScriptableWql.h"
#include "CwmsScriptableUi.h"

// own Includes
#include "CwmsqmlApplication.h"
#include "CwmsqmlImageProvider.h"
#include "CwmsQmlApplicationSelection.h"
#include "CwmsqmlApplicationModule.h"
#include "CwmsQmlHelper.h"
#include "CwmsQmlDatabaseSelection.h"
#include "CwmsQmlStyle.h"
#include "CwmsQmlWidget.h"
#include "CwmsQmlApplicationController.h"

CwmsQmlApplicationController* CwmsQmlApplicationController::m_spController = nullptr;

CwmsQmlApplicationController::CwmsQmlApplicationController(QString p_qstrApplication,
                                                           CwmsInitApplication* p_pInit,
                                                           QObject* p_pParent)
    : CwmsQmlEngineInitializer(p_pParent),
      m_bDevelopmentMode(false),
      m_cLogin(p_qstrApplication, p_pInit),
      m_rpItem(nullptr),
      m_rpInit(p_pInit),
      m_pStyle(nullptr),
      m_pApplication(nullptr)
{
    m_pFactory->setParent(this);

    addContextPropertyToEngine("wmsLogin", &m_cLogin);
    addContextPropertyToEngine("wmsConfig",   &m_cDataAccessConfiguration);
    addContextPropertyToEngine("wmsDataAccessModel",
                               QVariant::fromValue(m_cDataAccessConfiguration.getDataAccessList()));

    m_pStyle = CwmsQmlStyle::createStyle(this);
    addContextPropertyToEngine("wmsStyle",   m_pStyle);
}

CwmsQmlApplicationController::~CwmsQmlApplicationController()
{
}

CwmsQmlApplicationController *CwmsQmlApplicationController::createController(QString p_qstrApplication,
                                                                             CwmsInitApplication* p_pInit,
                                                                             QObject* p_pParent)
{
    if (!m_spController)
    {
        m_spController = new CwmsQmlApplicationController(p_qstrApplication, p_pInit, p_pParent);
    }

    return m_spController;
}

CwmsQmlApplicationController *CwmsQmlApplicationController::getController()
{
    return m_spController;
}

bool CwmsQmlApplicationController::isMobile()
{
    CwmsbtPlattformInformation info;
    return info.isMobile();
}

QString CwmsQmlApplicationController::getClientConfigurationQmlDialog(QString p_qstrConfig)
{
    QObject* pConfig = m_cDataAccessConfiguration.getDataAccessConfiguration(p_qstrConfig);
    addContextPropertyToEngine("settings", pConfig);
    return m_cDataAccessConfiguration.getDataAccessConfigurationFilename(p_qstrConfig);
}

void CwmsQmlApplicationController::openWindow()
{
    showWindowUi(QUrl("qrc:/qml/WmsWindow.qml"));
}

void CwmsQmlApplicationController::createCustomMainWindow(QString p_qstrName, QString p_qstrQml)
{
   QByteArray qbaSource;
   qbaSource.append(p_qstrQml);
   prepareEngine();
   m_pEngine->loadData(qbaSource, QUrl(p_qstrName));
   QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);

   showCreatedWindow(pFirstTopLevelObject);
}

QQuickWindow* CwmsQmlApplicationController::getCentralWindow()
{
    return m_pCentralWindow;
}

void CwmsQmlApplicationController::pushViewToStack(qint64 p_lModuleId, QString p_qstrUiName, QString p_qstrModelElementUri)
{
    CwmsQmlWidget* pWidget = new CwmsQmlWidget();

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    pWidget->setLocatedElement(pManager->GetUriObject(p_qstrModelElementUri));
    pWidget->setModuleId(p_lModuleId);
    pWidget->setUiName(p_qstrUiName);
    pWidget->setMainWindow(false);
    m_qlWidgetStack.push(pWidget);
}

CwmsQmlWidget* CwmsQmlApplicationController::popViewFromStack()
{
    CwmsQmlWidget* pView = nullptr;

    if (!m_qlWidgetStack.isEmpty())
    {
        pView = m_qlWidgetStack.pop();
    }
    else
    {
        ERR("View stack is empty!");
    }

    return pView;
}


void CwmsQmlApplicationController::loginSuccessfull()
{
    addContextPropertyToEngine("loginObj", nullptr);
    addContextPropertyToEngine("config",   nullptr);
    addContextPropertyToEngine("dataAccessModel", nullptr);
    addContextPropertyToEngine("wms", m_pFactory->getManager());
    if (CHKPTR(m_rpInit))
    {
        m_rpInit->StateFinished(true);
    }
}

void CwmsQmlApplicationController::selectionSuccessfull()
{
    if (CHKPTR(m_rpInit))
    {
        m_rpInit->StateFinished(true);
    }
}

bool CwmsQmlApplicationController::needsDatabaseSelection()
{
    bool bRet = false;
    if (CHKPTR(m_rpInit))
    {
        CwmsQmlDatabaseSelection cSelection(m_rpInit);
        QStringList qstrlDbList = cSelection.getDatabaseList();

        if (qstrlDbList.count() > 1)
        {
            bRet = true;
        }
        else
        {
            if (qstrlDbList.count() == 1)
            {
                cSelection.loadSelection(qstrlDbList[0]);
                m_rpInit->StateFinished(true);
            }
            else
            {
                ERR("No Databases found.");
                m_rpInit->StateFinished(false);
            }

            bRet = false;
        }
    }
    return bRet;
}

bool CwmsQmlApplicationController::needsApplicationSelection()
{
    bool bRet = false;
    if (CHKPTR(m_rpInit))
    {
        QStringList qstrlApps = CwmsApplication::GetApplicationList();

        if (qstrlApps.count() > 1)
        {
            bRet = true;
        }
        else
        {
            if (qstrlApps.count() == 1)
            {
                CwmsQmlApplicationSelection cSelection(m_rpInit);
                cSelection.loadSelection(qstrlApps[0]);
                m_rpInit->StateFinished(true);
            }
            else
            {
                ERR("No Applications found.");
                m_rpInit->StateFinished(false);
            }
        }
    }
    return bRet;
}

bool CwmsQmlApplicationController::needsSelection()
{
    bool bRet = false;
    if (CHKPTR(m_rpInit))
    {
        if (m_rpInit->GetState() == eInitStateDbSelection)
        {
            bRet = needsDatabaseSelection();
        }
        else if (m_rpInit->GetState() == eInitStateApplicationSelection)
        {
            bRet = needsApplicationSelection();
        }
    }
    return bRet;
}

void CwmsQmlApplicationController::loadSelection(QString p_qstrSelection)
{
    if (CHKPTR(m_rpInit))
    {
        if (m_rpInit->GetState() == eInitStateDbSelection)
        {
            CwmsQmlDatabaseSelection cSelection(m_rpInit);
            cSelection.loadSelection(p_qstrSelection);
            m_rpInit->StateFinished(true);
        }
        else if (m_rpInit->GetState() == eInitStateApplicationSelection)
        {
            CwmsQmlApplicationSelection cSelection(m_rpInit);
            cSelection.loadSelection(p_qstrSelection);
            m_rpInit->StateFinished(true);
        }
    }
}

bool CwmsQmlApplicationController::hasCustomMainWindow()
{
    bool bRet = false;

    CwmsContext* pContext = CwmsContext::GetContext();

    if (CHKPTR(pContext))
    {
        CwmsApplication cApp = pContext->GetApplication();
        CdmObject* pObject = cApp.GetMainWindow();

        if (pObject)
        {
            bRet = true;
        }
    }

    return bRet;
}

QString CwmsQmlApplicationController::getDefaultMainWindowName()
{
    QString qstrName;
    CwmsbtPlattformInformation cInfo;

    if (cInfo.isMobile())
    {
        qstrName = "WmsMainWindowMobile.qml";
    }
    else
    {
        qstrName = "WmsMainWindowTablet.qml";
    }

    return qstrName;
}

QString CwmsQmlApplicationController::loadCustomMainWindow()
{
    QString qstrQml;
    CwmsContext* pContext = CwmsContext::GetContext();

    if (CHKPTR(pContext))
    {
        CwmsApplication cApp = pContext->GetApplication();
        CdmObject* pObject = cApp.GetMainWindow();

        if (CHKPTR(pObject))
        {
            CwmsFormUserDefined cForm(pObject);
            qstrQml = cForm.GetUICode();
        }
    }

    return qstrQml;
}

void CwmsQmlApplicationController::goBack()
{
    // ToDo
}

QStringList CwmsQmlApplicationController::getModuleList()
{
    QStringList qstrlModules;

    if (!m_pApplication)
    {
        initApplication();
    }

    qstrlModules = m_pApplication->getModuleList();
    return qstrlModules;
}

CsaObject* CwmsQmlApplicationController::getDefaultModule()
{
    CsaObject* pObject = nullptr;
    CwmsqmlApplication* pApp = getApplication();

    if (CHKPTR(pApp))
    {
        pObject = pApp->loadDefaultModule();
    }

    return pObject;
}

void CwmsQmlApplicationController::initApplication()
{
    CwmsContext* pContext = CwmsContext::GetContext();
    CwmsbtPlattformInformation cInfo;

    if (CHKPTR(pContext))
    {
        m_pApplication = new CwmsqmlApplication();
        m_pApplication->setApplication(pContext->GetApplication());
        m_pApplication->setParent(this);
    }
    if (cInfo.isTablet() && cInfo.IsSimulating())
    {
        m_pCentralWindow->setX(250);
        m_pCentralWindow->setY(200);
        m_pCentralWindow->setWidth(1024);
        m_pCentralWindow->setHeight(768);
    }
}

CwmsqmlApplication* CwmsQmlApplicationController::getApplication()
{
    if (!m_pApplication)
    {
        initApplication();
    }

    return m_pApplication;
}

void CwmsQmlApplicationController::setDevelopmentMode(bool bDevelopmentMode)
{
    m_bDevelopmentMode = bDevelopmentMode;
}

QStringList CwmsQmlApplicationController::getDatabaseList()
{
    CwmsQmlDatabaseSelection cDatabaseSelection(nullptr);
    return cDatabaseSelection.getDatabaseList();
}

QStringList CwmsQmlApplicationController::getApplicationList()
{
    return CwmsApplication::GetApplicationList();
}

QStringList CwmsQmlApplicationController::getSelectionList()
{
    QStringList qstrList;
    if (CHKPTR(m_rpInit))
    {
        if (m_rpInit->GetState() == eInitStateDbSelection)
        {
            qstrList = getDatabaseList();
        }
        else if (m_rpInit->GetState() == eInitStateApplicationSelection)
        {
            qstrList = getApplicationList();
        }
    }
    return qstrList;
}

void CwmsQmlApplicationController::setCurrentContent(QQuickItem* p_pItem)
{
    m_rpItem = p_pItem;
}

QQuickItem* CwmsQmlApplicationController::getCurrentContent()
{
    return m_rpItem;
}

void CwmsQmlApplicationController::quit()
{
    CdmSessionManager::GetSessionManager()->Logout();
    exit(0);
}

QString CwmsQmlApplicationController::getContainerEditorName()
{
    QString qstrName;
    CwmsbtPlattformInformation cInfo;

    if (cInfo.isMobile())
    {
        qstrName = "WmsContainerEditorMobile.qml";
    }
    else
    {
        qstrName = "WmsContainerEditorTablet.qml";
    }

    return qstrName;
}

CsaFactory* CwmsQmlApplicationController::getFactory()
{
    return m_pFactory;
}


CsaObjectContainer* CwmsQmlApplicationController::convertContainer(CdmObjectContainer* p_pContainer)
{
    return CsaFactory::convertContainer(p_pContainer, m_pFactory);
}

CsaObject* CwmsQmlApplicationController::convertObject(CdmObject* p_pObject)
{
    return CsaFactory::convertObject(p_pObject, m_pFactory);
}
