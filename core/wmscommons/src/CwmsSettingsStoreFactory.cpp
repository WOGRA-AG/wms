// System and Qt Includes
#include <QFileInfo>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>

// own Includes
#include "wmsdefines.h"
#include "CwmsSettingsStoreFactory.h"

QMutex CwmsSettingsStoreFactory::m_qMutex(QMutex::Recursive);

QSettings* CwmsSettingsStoreFactory::GenerateServerSettings()
{
    return GenerateSettings(SERVER_CONFIG_NAME);
}

QSettings* CwmsSettingsStoreFactory::GenerateClientSettings()
{
    return GenerateSettings(CLIENT_CONFIG_NAME);
}

QSettings* CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings()
{
    return GenerateSettings(DATA_ACCESS_CONFIG_SECTION);
}

QSettings* CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings(QString p_qstrConfigName)
{
    return GenerateSettings(DATA_ACCESS_CONFIG_SECTION "/" + p_qstrConfigName);
}

QSettings* CwmsSettingsStoreFactory::GenerateSettings(QString p_qstrPrefix)
{
    QMutexLocker lock(&m_qMutex);
    QString qstrPath = qApp->applicationDirPath() + "/conf/";

    QFileInfo qFileInfo(qstrPath);
    if (!qFileInfo.isWritable())
    {
        qstrPath = QDir::homePath() + "/wms.conf/";
    }

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, qstrPath);
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, qstrPath);

    QSettings* pSettings = new QSettings(QSettings::IniFormat,QSettings::UserScope, WMS, WMS);

    pSettings->beginGroup(p_qstrPrefix);
    return pSettings;
}

QSettings* CwmsSettingsStoreFactory::GenerateServerDataAccessSettings()
{
    return GenerateDataAccessSettings(eWmsSettingsConfigTypeServer);
}

QSettings* CwmsSettingsStoreFactory::GenerateClientDataAccessSettings()
{
    return GenerateDataAccessSettings(eWmsSettingsConfigTypeClient);
}

QSettings* CwmsSettingsStoreFactory::GenerateDataAccessSettings(QString p_qstrConfigName)
{
    return GenerateSettings(DATA_ACCESS_CONFIG_SECTION "/" + p_qstrConfigName);
}

QSettings* CwmsSettingsStoreFactory::GenerateDataAccessSettings(EwmsSettingsConfigType p_eType)
{
    QSettings* pClientDataAccessSettings = nullptr;
    QString qstrDataAccessConfig = ReadDataAccessConfigName(p_eType);

    if (!qstrDataAccessConfig.isEmpty())
    {
        pClientDataAccessSettings = GenerateDataAccessSettings(qstrDataAccessConfig);
    }

    return pClientDataAccessSettings;
}

QString CwmsSettingsStoreFactory::ReadDataAccessConfigFile(EwmsSettingsConfigType p_eType)
{
    QString qstrFile;

    QString qstrDataAccessConfig = ReadDataAccessConfigName(p_eType);

    if (!qstrDataAccessConfig.isEmpty())
    {
        QSettings* pClientDataAccessSettings = nullptr;
        pClientDataAccessSettings = GenerateDataAccessSettings(qstrDataAccessConfig);

        if (pClientDataAccessSettings)
        {
            qstrFile = pClientDataAccessSettings->value(DATA_ACCESS_PLUGIN_FILE).toString();
            delete pClientDataAccessSettings;
        }
    }

    return qstrFile;
}

QString CwmsSettingsStoreFactory::ReadDataAccessConfigName(EwmsSettingsConfigType p_eType)
{
    QString qstrDataAccessConfig;
    QSettings* pSettings = nullptr;

    if (p_eType == eWmsSettingsConfigTypeClient)
    {
        pSettings = GenerateClientSettings();
    }
    else if (p_eType == eWmsSettingsConfigTypeServer)
    {
        pSettings = GenerateServerSettings();
    }

    if (pSettings)
    {
        qstrDataAccessConfig = pSettings->value(DATA_ACCESS_CONFIG, "").toString();
        delete pSettings;
        pSettings = nullptr;
    }

    return qstrDataAccessConfig;
}

void CwmsSettingsStoreFactory::SetDataAccessConfigName(EwmsSettingsConfigType p_eType, QString p_qstrConfig)
{
    QSettings* pSettings = nullptr;

    if (p_eType == eWmsSettingsConfigTypeClient)
    {
        pSettings = GenerateClientSettings();
    }
    else if (p_eType == eWmsSettingsConfigTypeServer)
    {
        pSettings = GenerateServerSettings();
    }

    if (pSettings)
    {
        pSettings->setValue(DATA_ACCESS_CONFIG, p_qstrConfig);
        delete pSettings;
        pSettings = nullptr;
    }
}

QVariantMap CwmsSettingsStoreFactory::RetrieveValuesFromSettings(QSettings &p_rSettings)
{
    QVariantMap qMap;

    QStringList qstrlKeys = p_rSettings.allKeys();

    for (int iPos = 0; iPos < qstrlKeys.count(); ++iPos)
    {
        qMap.insert(qstrlKeys[iPos],p_rSettings.value(qstrlKeys[iPos]));
    }

    return qMap;
}

void CwmsSettingsStoreFactory::SetValuesFromMapToSettings(QVariantMap &p_rqMap, QSettings &p_rqSettings)
{
    QVariantMap::iterator qIt = p_rqMap.begin();
    QVariantMap::iterator qItEnd = p_rqMap.end();

    for (; qIt != qItEnd; ++qIt)
    {
        p_rqSettings.setValue(qIt.key(), qIt.value());
    }
}

void CwmsSettingsStoreFactory::SetValuesFromUiMapToSettings(QVariantMap &p_rqMap, QSettings &p_rqSettings)
{
    QVariantMap::iterator qIt = p_rqMap.begin();
    QVariantMap::iterator qItEnd = p_rqMap.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qmValue = qIt.value().toMap();
        QVariant qvValue = qmValue[VALUE];

        p_rqSettings.setValue(qmValue[NAME].toString(), qvValue);
    }
}
