// System and QT Includes
#include <QQuickWindow>
#include <QSqlDatabase>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// WMS Commons Includes
#include "CwmsSettingsStoreFactory.h"
#include "wmsdefines.h"

// WMS Includes
#include "CdmValue.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CftlDataAccessConfigurator.h"

CftlDataAccessConfigurator::CftlDataAccessConfigurator(QString p_qstrConfig)
: m_pSettings(nullptr)
{
    m_pSettings = CwmsSettingsStoreFactory::GenerateDataAccessSettings(p_qstrConfig);
}

CftlDataAccessConfigurator::~CftlDataAccessConfigurator()
{
}


QVariant CftlDataAccessConfigurator::getSettingsValue(QString p_qstrKey)
{
    return m_pSettings->value(p_qstrKey);
}

void CftlDataAccessConfigurator::setSettingsValue(QString p_qstrKey, QVariant p_qValue)
{
    m_pSettings->setValue(p_qstrKey, p_qValue);
}


QString CftlDataAccessConfigurator::getServer()
{
    return getSettingsValue("Server").toString();
}

void CftlDataAccessConfigurator::setServer(QString p_qstrServer)
{
    setSettingsValue("Server", p_qstrServer);
}

int CftlDataAccessConfigurator::getPort()
{
    return getSettingsValue("Port").toInt();
}

void CftlDataAccessConfigurator::setPort(int p_iPort)
{
    setSettingsValue("Port", p_iPort);
}

QString CftlDataAccessConfigurator::getDriver()
{
    return getSettingsValue("Driver").toString();
}

int CftlDataAccessConfigurator::getDriverIndex()
{
   QString qstrDriver = getDriver();
   QStringList drivers = QSqlDatabase::drivers();
   drivers.removeAll("QSQLITE");
   drivers.removeAll("QSQLITE2");
   return drivers.indexOf(qstrDriver);
}

QStringList CftlDataAccessConfigurator::getDrivers()
{
    QStringList drivers = QSqlDatabase::drivers();
    drivers.removeAll("QSQLITE");
    drivers.removeAll("QSQLITE2");
    return drivers;
}

void CftlDataAccessConfigurator::setDriver(QString p_qstrDriver)
{
    setSettingsValue("Driver", p_qstrDriver);
}

QString CftlDataAccessConfigurator::getDatabase()
{
    return getSettingsValue("Database").toString();
}

void CftlDataAccessConfigurator::setDatabase(QString p_qstrDatabase)
{
    setSettingsValue("Database", p_qstrDatabase);
}

QString CftlDataAccessConfigurator::getUser()
{
    return getSettingsValue("User").toString();
}

void CftlDataAccessConfigurator::setUser(QString p_qstrUser)
{
    setSettingsValue("User", p_qstrUser);
}

QString CftlDataAccessConfigurator::getPassword()
{
    return getSettingsValue("Password").toString();
}

void CftlDataAccessConfigurator::setPassword(QString p_qstrPassword)
{
    setSettingsValue("Password", p_qstrPassword);
}

QString CftlDataAccessConfigurator::getDialect()
{
    return getSettingsValue("Dialect").toString();
}

QString CftlDataAccessConfigurator::getConnectOptions()
{
    return getSettingsValue("ConnectOptions").toString();
}

void CftlDataAccessConfigurator::setConnectOptions(QString p_qstrConnectOptions)
{
    setSettingsValue("ConnectOptions", p_qstrConnectOptions);
}

bool CftlDataAccessConfigurator::testDatabaseConnection(QString p_qstrHost,
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

void CftlDataAccessConfigurator::OpenConfigurator()
{
    QStringList qstrlDrivers = QSqlDatabase::drivers();
    qstrlDrivers.removeAll("QSQLITE");
    qstrlDrivers.removeAll("QSQLITE2");
    m_pEngine->rootContext()->setContextProperty("drivers", QVariant::fromValue(qstrlDrivers));
    QQuickWindow* view = CreateView();

    if (CHKPTR(view))
    {
       INFO("View created");
       view->setModality(Qt::WindowModal);
       INFO("View shown");
   }
}

QQuickWindow* CftlDataAccessConfigurator::CreateView()
{
    QQuickWindow* view = nullptr;
    QObject* pThis = dynamic_cast<QObject*>(this);

    m_pEngine = new QQmlApplicationEngine(this);
    m_pEngine->rootContext()->setContextProperty("settings", pThis);

    QQuickWindow::setDefaultAlphaBuffer(false);
    QString qstrImportPath = "qrc:/qml/";
    m_pEngine->addImportPath(qstrImportPath);
    INFO("Importpath: " + qstrImportPath);
    QUrl url("qrc:/qml/WmsdbDataAccessPlugin.qml");
    m_pEngine->load(url);
    INFO("Looking for first root Object")
    QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);

    if (pFirstTopLevelObject)
    {
       INFO("First root object found")
       view = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);
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


QVariantMap CftlDataAccessConfigurator::getValueMap()
{
    QVariantMap qvMap;
    QVariantMap qvValues = CwmsSettingsStoreFactory::RetrieveValuesFromSettings(*m_pSettings);

    getMapInitValues(qvMap, qvValues);

    return qvMap;
}

void CftlDataAccessConfigurator::getMapInitValues(QVariantMap& qMap, QVariantMap& qValues)
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

void CftlDataAccessConfigurator::setValueMap(QVariantMap& p_rqMap)
{
    CwmsSettingsStoreFactory::SetValuesFromUiMapToSettings(p_rqMap, *m_pSettings);
}
