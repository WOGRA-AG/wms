#include "CwnDataAccessConfigurator.h"

// System and QT Includes
#include <QQuickWindow>
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

CwnDataAccessConfigurator::CwnDataAccessConfigurator(QString p_qstrConfig):
m_pSettings(nullptr)
{
    m_pSettings = CwmsSettingsStoreFactory::GenerateDataAccessSettings(p_qstrConfig);
}

CwnDataAccessConfigurator::~CwnDataAccessConfigurator()
{
    DELPTR(m_pSettings);
}

QVariant CwnDataAccessConfigurator::getSettingsValue(QString p_qstrKey)
{
    if (!m_pSettings->contains(p_qstrKey))
    {
        ERR("Key not found. Key: " + p_qstrKey);
    }

    return m_pSettings->value(p_qstrKey);
}

void CwnDataAccessConfigurator::setSettingsValue(QString p_qstrKey, QVariant p_qValue)
{
    m_pSettings->setValue(p_qstrKey, p_qValue);
}


QString CwnDataAccessConfigurator::getServer()
{
    return getSettingsValue(SERVER).toString();
}

void CwnDataAccessConfigurator::setServer(QString p_qstrServer)
{
    setSettingsValue(SERVER, p_qstrServer);
}

int CwnDataAccessConfigurator::getPort()
{
    return getSettingsValue(PORT).toInt();
}

void CwnDataAccessConfigurator::setPort(int p_iPort)
{
    setSettingsValue(PORT, p_iPort);
}

QString CwnDataAccessConfigurator::getUser()
{
    return getSettingsValue(USER).toString();
}

void CwnDataAccessConfigurator::setUser(QString p_qstrUser)
{
    setSettingsValue(USER, p_qstrUser);
}

QString CwnDataAccessConfigurator::getPassword()
{
    return getSettingsValue(PASSWORD).toString();
}

void CwnDataAccessConfigurator::setPassword(QString p_qstrPassword)
{
    setSettingsValue(PASSWORD, p_qstrPassword);
}

void CwnDataAccessConfigurator::OpenConfigurator()
{
    QQuickWindow* view = CreateView();

    if (CHKPTR(view))
    {
       INFO("View created");
       view->setModality(Qt::WindowModal);
       view->show();
       INFO("View shown");
   }
}

QQuickWindow* CwnDataAccessConfigurator::CreateView()
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


QVariantMap CwnDataAccessConfigurator::getValueMap()
{
    QVariantMap qvMap;
    QVariantMap qvValues = CwmsSettingsStoreFactory::RetrieveValuesFromSettings(*m_pSettings);

    getMapInitValues(qvMap, qvValues);

    return qvMap;
}

void CwnDataAccessConfigurator::getMapInitValues(QVariantMap& qMap, QVariantMap& qValues)
{
    int iPos = 0;

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

}

void CwnDataAccessConfigurator::setValueMap(QVariantMap& p_rqMap)
{
    CwmsSettingsStoreFactory::SetValuesFromUiMapToSettings(p_rqMap, *m_pSettings);
}
