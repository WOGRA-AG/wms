// System and Qt Includes
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <qquickitem.h>
#include <qqmlcomponent.h>
#include <QQmlContext>
#include <QDebug>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaManager.h"
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CdmLogging.h"

// BASETOOLS Includes
#include "cwmsbtplattforminformation.h"
#include "CwmsFormManager.h"
#include "CwmsScriptableLogger.h"
#include "CwmsScriptableMailer.h"
#include "CwmsScriptableMessage.h"
#include "CwmsScriptablePlugin.h"
#include "CwmsScriptablePrinter.h"
#include "CwmsScriptableStatic.h"
#include "CwmsScriptableWorkflow.h"
#include "CwmsScriptableWql.h"
#include "CwmsScriptableUi.h"
#include "CwmsScriptableGeoServices.h"
#include "CwmsScriptableHttpClient.h"
#include "CwmsScriptableFile.h"
#include "CwmsScriptableSql.h"
#include "CwmsScriptableTimer.h"

// own Includes
#include "CwmsQmlHelper.h"
#include "CwmsqmlImageProvider.h"
#include "CwmsQmlEngineInitializer.h"

CwmsQmlEngineInitializer::CwmsQmlEngineInitializer(QObject* parent)
: QObject(parent),
  m_pEngine(nullptr),
  m_pFactory(nullptr),
  m_pCentralWindow(nullptr)
{
    m_pFactory = new CsaFactory();
    m_pEngine = new QQmlApplicationEngine(this);
    m_pEngine->addImageProvider(QLatin1String("wmsImages"), new CwmsqmlImageProviderImage());
    m_pEngine->addImageProvider(QLatin1String("wmsPixmaps"), new CwmsqmlImageProviderPixmap());
    m_pEngine->addImportPath("qrc:/qml/");
    QQuickWindow::setDefaultAlphaBuffer(false);
    fillDefaultProperties();
    fillTypes();
}

CwmsQmlEngineInitializer::~CwmsQmlEngineInitializer()
{
    DELPTR(m_pEngine);
    DELPTR(m_pFactory);
}


void CwmsQmlEngineInitializer::fillTypes()
{
    CwmsQmlHelper::registerTypes();
}

void CwmsQmlEngineInitializer::fillDefaultProperties()
{
    addContextPropertyToEngine("wmsApp", this);
    addContextPropertyToEngine("wmsFactory", m_pFactory);
    addContextPropertyToEngine("message", new CwmsScriptableMessage());
    addContextPropertyToEngine("mail", new CwmsScriptableMailer());
    addContextPropertyToEngine("printing", new CwmsScriptablePrinter());
    addContextPropertyToEngine("wql", new CwmsScriptableWql());
    addContextPropertyToEngine("workflow", new CwmsScriptableWorkflow());
    addContextPropertyToEngine("log", new CwmsScriptableLogger());
    addContextPropertyToEngine("plugin", new CwmsScriptablePlugin());
    addContextPropertyToEngine("staticExec", new CwmsScriptableStatic());
    addContextPropertyToEngine("geo", new CwmsScriptableGeoServices());
    addContextPropertyToEngine("httpClient", new CwmsScriptableHttpClient());
    addContextPropertyToEngine("file", new CwmsScriptableFile());
    addContextPropertyToEngine("sql", new CwmsScriptableSql());
    addContextPropertyToEngine("timer", new CwmsScriptableTimer());
}

QQmlContext *CwmsQmlEngineInitializer::getRootContext()
{
    return m_pEngine->rootContext();
}

void CwmsQmlEngineInitializer::addContextPropertyToEngine(QString p_qstrName, QObject *p_pObject)
{
    QQmlContext* pRoot = getRootContext();

    if (CHKPTR(pRoot))
    {
        pRoot->setContextProperty(p_qstrName, p_pObject);
    }
}

void CwmsQmlEngineInitializer::addContextPropertyToEngine(QString p_qstrName, QVariant p_qvValue)
{
    QQmlContext* pRoot = getRootContext();

    if (CHKPTR(pRoot))
    {
        pRoot->setContextProperty(p_qstrName, p_qvValue);
    }
}

void CwmsQmlEngineInitializer::showWindowModal(QQuickWindow* p_pWindow)
{
    showWindow(true, p_pWindow);
}

void CwmsQmlEngineInitializer::showWindowNotModal( QQuickWindow* p_pWindow)
{
    showWindow(false, p_pWindow);
}

void CwmsQmlEngineInitializer::showWindow(bool p_bModal, QQuickWindow* p_pWindow)
{
    if (p_pWindow)
    {
        if (p_bModal)
        {
            p_pWindow->setModality(Qt::WindowModal);
        }

        CwmsbtPlattformInformation info;

        if ((info.isMobile() || info.isTablet()) && !info.IsSimulating())
        {
            p_pWindow->showMaximized();
        }
        else
        {
            p_pWindow->show();
        }
    }
    else
    {
        ERR(tr("Could not create Window."));
    }
}

QString CwmsQmlEngineInitializer::loadUi(CsaObject *p_pObject)
{
    QString qstrQml;

    if (CHKPTR(p_pObject))
    {
        CwmsFormManager cFormManager;
        qstrQml = cFormManager.GetUserDefinedUi(p_pObject->getInternals());
    }

    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(CsaObject *p_pElement)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadUi(p_pElement);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_pElement->getKeyname()));
		pItem = component.create(context);
	}

	return pItem;
}

QString CwmsQmlEngineInitializer::loadUi(CsaObjectContainer *p_pContainer)
{
    QString qstrQml;

    if (CHKPTR(p_pContainer))
    {
        CwmsFormManager cFormManager;
        qstrQml = cFormManager.GetUserDefinedUi(p_pContainer->getInternals());
    }

    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(CsaObjectContainer *p_pElement)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadUi(p_pElement);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_pElement->getKeyname()));
		pItem = component.create(context);
	}

	return pItem;
}

QString CwmsQmlEngineInitializer::loadUi(CdmObject *p_pElement)
{
    QString qstrQml;
    CwmsFormManager cFormManager;
    qstrQml = cFormManager.GetUserDefinedUi(p_pElement);
    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(CdmObject *p_pElement)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadUi(p_pElement);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_pElement->GetKeyname()));
		pItem = component.create(context);
	}

	return pItem;
}


QString CwmsQmlEngineInitializer::loadUi(CdmObjectContainer *p_pElement)
{
    QString qstrQml;
    CwmsFormManager cFormManager;
    qstrQml = cFormManager.GetUserDefinedUi(p_pElement);
    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(CdmObjectContainer *p_pElement)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadUi(p_pElement);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_pElement->GetKeyname()));
		pItem = component.create(context);
	}

	return pItem;
}


QString CwmsQmlEngineInitializer::loadUi(QString p_qstrName)
{
    QString qstrQml;
    CwmsFormManager cFormManager;
    qstrQml = cFormManager.GetUserDefinedUi(p_qstrName);
    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(QString p_qstrName)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadUi(p_qstrName);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_qstrName));
		pItem = component.create(context);
	}

	return pItem;
}

QString CwmsQmlEngineInitializer::loadUi(QUrl p_Url)
{
    QString qstrQml;

    QFile qFile(p_Url.toString());

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream qStream(&qFile);
        qstrQml = qStream.readAll();
    }
    else
    {
        ERR("Could not open file " + p_Url.toString());
    }

    return qstrQml;
}

QObject* CwmsQmlEngineInitializer::openUi(QUrl p_Url)
{
	QObject* pItem = nullptr;
	QQmlComponent component(m_pEngine, p_Url);
	QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
	component.loadUrl(p_Url);
	pItem = component.create(context);
	return pItem;
}


QString CwmsQmlEngineInitializer::loadWmsLibrary(QString p_qstrName, QString p_qstrVersion)
{
    QString qstrQml;
    CwmsFormManager cFormManager;
    qstrQml = cFormManager.GetWmsLibrary(p_qstrName, p_qstrVersion);
    return qstrQml;
}


QObject* CwmsQmlEngineInitializer::initWmsLibrary(QString p_qstrName, QString p_qstrVersion)
{
	QObject* pItem = nullptr;
	QString qstrQml = loadWmsLibrary(p_qstrName, p_qstrVersion);

	if (!qstrQml.isEmpty())
	{
		QQmlComponent component(m_pEngine);
		QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
		QByteArray qbaSource;
		qbaSource.append(qstrQml);
		component.setData(qbaSource, QUrl(p_qstrName));
		pItem = component.create(context);
	}

	return pItem;
}

void CwmsQmlEngineInitializer::showWindowUi(QUrl p_qFilename)
{
    INFO("Loading Url: " + p_qFilename.toDisplayString());
    int rootObjectsCount = prepareEngine();
    INFO("Root Object count: " + QString::number(rootObjectsCount));
    m_pEngine->load(p_qFilename);
    INFO("Looking for first root Object");
    rootObjectsCount = m_pEngine->rootObjects().count();
    QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);
    showCreatedWindow(pFirstTopLevelObject);

}

int CwmsQmlEngineInitializer::prepareEngine()
{
    INFO("Importpath: " + m_pEngine->importPathList().join(";"));
    qDebug( ) << m_pEngine->importPathList().join(";");
    int rootObjectsCount = m_pEngine->rootObjects().count();
    m_pEngine->clearComponentCache();
    return rootObjectsCount;
}

void CwmsQmlEngineInitializer::showCreatedWindow(QObject* pFirstTopLevelObject)
{
    if (pFirstTopLevelObject)
    {
        INFO("First root object found")
                m_pCentralWindow = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);
    }
    else
    {
        ERR("No root Object created.")
    }

    if (m_pCentralWindow)
    {
        INFO("Connect to destructor")
                connect(m_pCentralWindow, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
        showWindowModal(m_pCentralWindow);
    }
    else
    {
        ERR("QML Window not created!")
    }
}

void CwmsQmlEngineInitializer::addElements(CdmModelElement* p_pElement)
{
    if (p_pElement->IsObject())
    {
        CsaLocatedElement* pElement =
                m_pFactory->createScriptObject(p_pElement);
        if (pElement)
        {
            CsaObject* pObject = dynamic_cast<CsaObject*>(pElement);

            if (pObject)
            {
                getRootContext()->setContextProperty("element", pObject);
            }
        }
    }
    else if (p_pElement->IsContainer())
    {
        CsaLocatedElement* pElement =
                m_pFactory->createScriptObject(p_pElement);

        if (pElement)
        {
            CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(pElement);

            if (pContainer)
            {
                getRootContext()->setContextProperty("element", pContainer);
            }
        }
    }

    getRootContext()->setContextProperty("wms", m_pFactory->getManager());
}
