

// System and QT Includes
#include <QVariant>
#include <QThread>
#include <QObject>

// WMS Commons Includes
#include "CwmsSettingsStoreFactory.h"

// WMS Manager Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsServerSettings.h"

CwmsServerSettings::CwmsServerSettings()
	: m_pSettings(nullptr)
{
    m_pSettings = CwmsSettingsStoreFactory::GenerateServerSettings();
}

CwmsServerSettings::~CwmsServerSettings()
{
	DELPTR(m_pSettings);
}

QVariant CwmsServerSettings::getSettingsValue(QString p_qstrKey)
{
    return m_pSettings->value(p_qstrKey);
}

void CwmsServerSettings::setSettingsValue(QString p_qstrKey, QVariant p_qValue)
{
    m_pSettings->setValue(p_qstrKey, p_qValue);
    m_pSettings->sync();
}

QString CwmsServerSettings::getLoggingPath()
{
    return getSettingsValue("Logging_Path").toString();
}

bool CwmsServerSettings::getLoggingInformation()
{
    return getSettingsValue("Logging_Information").toBool();
}

bool CwmsServerSettings::getLoggingError()
{
    return getSettingsValue("Logging_Error").toBool();
}

bool CwmsServerSettings::getLoggingWarning()
{
    return getSettingsValue("Logging_Warning").toBool();
}

bool CwmsServerSettings::getLoggingFatal()
{
    return getSettingsValue("Logging_Fatal").toBool();
}

bool CwmsServerSettings::getLoggingActive()
{
    return getSettingsValue("Logging_Active").toBool();
}

int CwmsServerSettings::getConfigMaxThreadCount()
{
    return getSettingsValue("Config_MaxThreadCount").toInt();
}

int CwmsServerSettings::getPort()
{
    return getSettingsValue("Config_Port").toInt();
}

bool CwmsServerSettings::getMultiThreaded()
{
    return getSettingsValue("Config_MultiThread").toBool();
}

bool CwmsServerSettings::getCompression()
{
    return getSettingsValue("Config_Compression").toBool();
}

bool CwmsServerSettings::getSsl()
{
    return getSettingsValue("Config_Ssl").toBool();
}

bool CwmsServerSettings::getMaxTrials()
{
    return getSettingsValue("Config_MaxTrials").toBool();
}

QString CwmsServerSettings::getServerUser()
{
   QString qstrServerUser = getSettingsValue("Server_User").toString();
   return qstrServerUser;
}

QString CwmsServerSettings::getServerUserPassword()
{
   QString qstrServerPassword = getSettingsValue("Server_Password").toString();
   return qstrServerPassword;
}

QVariantMap CwmsServerSettings::getValueMap()
{
    QVariantMap qvMap = CwmsSettingsStoreFactory::RetrieveValuesFromSettings(*m_pSettings);

    if (qvMap.isEmpty())
    {
        qvMap = getMapInitValues();
    }

    return qvMap;
}

QVariantMap CwmsServerSettings::getMapInitValues()
{
    QVariantMap qMap;

    qMap.insert("Logging_Path", QVariant());
    qMap.insert("Logging_Information", QVariant(false));
    qMap.insert("Logging_Error", QVariant(true));
    qMap.insert("Logging_Warning", QVariant(false));
    qMap.insert("Logging_Fatal", QVariant(true));
    qMap.insert("Logging_Active", QVariant(true));
    qMap.insert("Config_MaxThreadCount", QVariant(10));
    qMap.insert("Config_Port", QVariant(0));
    qMap.insert("Config_MultiThread", QVariant(true));
    qMap.insert("Config_Compression", QVariant(true));
    qMap.insert("Config_Ssl", QVariant(true));
    qMap.insert("Config_MaxTrials", QVariant(true));
    qMap.insert("Server_User", QVariant());
    qMap.insert("Server_Password", QVariant());

    return qMap;
}

void CwmsServerSettings::setValueMap(QVariantMap& p_rqMap)
{
    CwmsSettingsStoreFactory::SetValuesFromMapToSettings(p_rqMap, *m_pSettings);
}
