// System and QT Includes
#include <QQuickWindow>
#include <QSqlDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qquickitem.h>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsSettingsStoreFactory.h"

// WMS Includes
#include "CdmValue.h"
#include "CdmLogging.h"
#include "CdmDataAccessHelper.h"
#include "CdmMessageManager.h"



// Own Includes
#include "CdbDataAccessConfigurator.h"

CdbDataAccessConfigurator::CdbDataAccessConfigurator(QString p_qstrConfig)
: m_pSettings(nullptr)
{
    m_pSettings = CwmsSettingsStoreFactory::GenerateDataAccessSettings(p_qstrConfig);
}

CdbDataAccessConfigurator::~CdbDataAccessConfigurator()
{
    DELPTR(m_pSettings);
}

QVariant CdbDataAccessConfigurator::getSettingsValue(QString p_qstrKey)
{
    if (!m_pSettings->contains(p_qstrKey))
    {
        ERR("Key not found. Key: " + p_qstrKey);
    }

    return m_pSettings->value(p_qstrKey);
}

void CdbDataAccessConfigurator::setSettingsValue(QString p_qstrKey, QVariant p_qValue)
{
    m_pSettings->setValue(p_qstrKey, p_qValue);
}


QString CdbDataAccessConfigurator::getServer()
{
    return getSettingsValue(SERVER).toString();
}

void CdbDataAccessConfigurator::setServer(QString p_qstrServer)
{
    setSettingsValue(SERVER, p_qstrServer);
}

int CdbDataAccessConfigurator::getPort()
{
    return getSettingsValue(PORT).toInt();
}

void CdbDataAccessConfigurator::setPort(int p_iPort)
{
    setSettingsValue(PORT, p_iPort);
}

QString CdbDataAccessConfigurator::getDriver()
{
    return getSettingsValue(DRIVER).toString();
}

int CdbDataAccessConfigurator::getDriverIndex()
{
   QString qstrDriver = getDriver();
   QStringList drivers = QSqlDatabase::drivers();
   drivers.removeAll("QSQLITE");
   drivers.removeAll("QSQLITE2");
   return drivers.indexOf(qstrDriver);
}

QStringList CdbDataAccessConfigurator::getDrivers()
{
    QStringList drivers = QSqlDatabase::drivers();
    drivers.removeAll("QSQLITE");
    drivers.removeAll("QSQLITE2");
    return drivers;
}

void CdbDataAccessConfigurator::setDriver(QString p_qstrDriver)
{
    setSettingsValue(DRIVER, p_qstrDriver);
}

QString CdbDataAccessConfigurator::getDatabase()
{
    return getSettingsValue(DATABASE).toString();
}

void CdbDataAccessConfigurator::setDatabase(QString p_qstrDatabase)
{
    setSettingsValue(DATABASE, p_qstrDatabase);
}

QString CdbDataAccessConfigurator::getUser()
{
    return getSettingsValue(USER).toString();
}

void CdbDataAccessConfigurator::setUser(QString p_qstrUser)
{
    setSettingsValue(USER, p_qstrUser);
}

QString CdbDataAccessConfigurator::getPassword()
{
    return getSettingsValue(PASSWORD).toString();
}

void CdbDataAccessConfigurator::setPassword(QString p_qstrPassword)
{
    setSettingsValue(PASSWORD, p_qstrPassword);
}

QString CdbDataAccessConfigurator::getConnectOptions()
{
    return getSettingsValue(CONNECT_OPTIONS).toString();
}

void CdbDataAccessConfigurator::setConnectOptions(QString p_qstrConnectOptions)
{
    setSettingsValue(CONNECT_OPTIONS, p_qstrConnectOptions);
}

bool CdbDataAccessConfigurator::testDatabaseConnection(QString p_qstrHost,
                                                       QString p_qstrDatabase,
                                                       int p_iPort,
                                                       QString p_qstrDriver,
                                                       QString p_qstrUsername,
                                                       QString p_qstrPassword,
                                                       QString p_qstrConfig)
{
    bool bRet = false;

    {
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase(p_qstrDriver, "Test");
        db.setDatabaseName(p_qstrDatabase);
        db.setHostName(p_qstrHost);
        db.setUserName(p_qstrUsername);
        db.setPassword(p_qstrPassword);

        if (p_iPort > 0)
        {
           db.setPort(p_iPort);
        }

        db.setConnectOptions(p_qstrConfig);

        if (db.open())
        {
            bRet = true;
        }

        db.close();
    }

    QSqlDatabase::removeDatabase("Test");
    return bRet;
}

void CdbDataAccessConfigurator::OpenConfigurator()
{
    QStringList qstrlDrivers = QSqlDatabase::drivers();
    qstrlDrivers.removeAll("QSQLITE");
    qstrlDrivers.removeAll("QSQLITE2");
    QQuickWindow* view = CreateView();
    m_pEngine->rootContext()->setContextProperty("drivers", QVariant::fromValue(qstrlDrivers));


    if (CHKPTR(view))
    {
       INFO("View created");
       view->setModality(Qt::WindowModal);
	   view->show();
       INFO("View shown");
   }
}

QQuickWindow* CdbDataAccessConfigurator::CreateView()
{
    QQuickWindow* view = nullptr;
    QObject* pThis = dynamic_cast<QObject*>(this);

    m_pEngine = new QQmlApplicationEngine(this);
    m_pEngine->rootContext()->setContextProperty("settings", pThis);

    QQuickWindow::setDefaultAlphaBuffer(false);
    QString qstrImportPath = "qrc:/wmsdbqml/";
    m_pEngine->addImportPath(qstrImportPath);
    INFO("Importpath: " + qstrImportPath);
    QUrl url("qrc:/wmsdbqml/WmsdbDataAccessPlugin.qml");
    m_pEngine->load(url);
    INFO("Looking for first root Object")
    QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);

    if (pFirstTopLevelObject)
    {
       INFO("First root object found")
       view = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);

	   if (!view)
	   {
		   QQuickItem* pItem = qobject_cast<QQuickItem*>(pFirstTopLevelObject);

		   if (pItem)
		   {
			   view = new QQuickWindow();
			   pItem->setParentItem(view->contentItem());
		   }
	   }
    }
    else
    {
      ERR("No root Object created.")
    }

    if (view)
    {
      INFO("Connect to destructor")
      connect(view, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
    }
    else
    {
      ERR("QML Window not created!")
    }

    return view;
}


QVariantMap CdbDataAccessConfigurator::getValueMap()
{
    QVariantMap qvMap;
    QVariantMap qvValues = CwmsSettingsStoreFactory::RetrieveValuesFromSettings(*m_pSettings);

    getMapInitValues(qvMap, qvValues);

    return qvMap;
}

void CdbDataAccessConfigurator::getMapInitValues(QVariantMap& qMap, QVariantMap& qValues)
{
    QVariantMap qmDriver;
    int iPos = 0;
    qmDriver.insert(NAME, DRIVER);
    qmDriver.insert(POSITION, iPos++);
    qmDriver.insert(LABEL, tr("Driver"));
    qmDriver.insert(TYPE, eDmValueEnum);
    qmDriver.insert(SELECTION, getDrivers());
    qmDriver.insert(VALUE, qValues[DRIVER]);
    qMap.insert(DRIVER, qmDriver);

    QVariantMap qmDb;
    qmDb.insert(NAME, DATABASE);
    qmDb.insert(POSITION, iPos++);
    qmDb.insert(LABEL, tr("Database Name"));
    qmDb.insert(TYPE, eDmValueString);
    qmDb.insert(VALUE, qValues[DATABASE]);
    qMap.insert(DATABASE, qmDb);

    QVariantMap qmServer;
    qmServer.insert(NAME, SERVER);
    qmServer.insert(POSITION, iPos++);
    qmServer.insert(LABEL, tr("Server Name or IP"));
    qmServer.insert(TYPE, eDmValueString);
    qmServer.insert(VALUE, qValues[SERVER]);
    qMap.insert(SERVER, qmServer);

    QVariantMap qmPort;
    qmPort.insert(NAME, PORT);
    qmPort.insert(POSITION, iPos++);
    qmPort.insert(LABEL, tr("Server Port"));
    qmPort.insert(TYPE, eDmValueInt);
    qmPort.insert(VALUE, qValues[PORT]);
    qMap.insert(PORT, qmPort);

    QVariantMap qmUser;
    qmUser.insert(NAME, USER);
    qmUser.insert(POSITION, iPos++);
    qmUser.insert(LABEL, tr("Database Login Name"));
    qmUser.insert(TYPE, eDmValueString);
    qmUser.insert(VALUE, qValues[USER]);
    qMap.insert(USER, qmUser);

    QVariantMap qmPassword;
    qmPassword.insert(NAME, PASSWORD);
    qmPassword.insert(POSITION, iPos++);
    qmPassword.insert(LABEL, tr("Database Password"));
    qmPassword.insert(TYPE, eDmValueString);
    qmPassword.insert(OPTION, ENCRYPTED);
    qmPassword.insert(VALUE, qValues[PASSWORD]);
    qMap.insert(PASSWORD, qmPassword);

    QVariantMap qmConnectOptions;
    qmConnectOptions.insert(NAME, CONNECT_OPTIONS);
    qmConnectOptions.insert(POSITION, iPos++);
    qmConnectOptions.insert(LABEL, tr("Connection Options"));
    qmConnectOptions.insert(TYPE, eDmValueString);
    qmConnectOptions.insert(VALUE, qValues[CONNECT_OPTIONS]);
    qMap.insert(CONNECT_OPTIONS, qmConnectOptions);
}

void CdbDataAccessConfigurator::setValueMap(QVariantMap& p_rqMap)
{
    CwmsSettingsStoreFactory::SetValuesFromUiMapToSettings(p_rqMap, *m_pSettings);
}
