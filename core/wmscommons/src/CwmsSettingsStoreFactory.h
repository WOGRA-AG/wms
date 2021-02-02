#ifndef CWMSSETTINGSSTOREFACTORY_H
#define CWMSSETTINGSSTOREFACTORY_H

// System and Qt Includes
#include <QVariant>
#include <QMutex>

#include "wmscommons.h"

enum EwmsSettingsConfigType
{
    eWmsSettingsConfigTypeServer,
    eWmsSettingsConfigTypeClient
};

class QSettings;

class WMSCOMMONS_API CwmsSettingsStoreFactory
{
public:
    static QSettings *GenerateServerSettings();
    static QSettings *GenerateClientSettings();
    static QSettings *GenerateServerDataAccessSettings();
    static QSettings *GenerateClientDataAccessSettings();
    static QSettings *GenerateDataAccessSettings(QString p_qstrConfigName);
    static QString ReadDataAccessConfigName(EwmsSettingsConfigType p_eType);
    static QSettings *GenerateDatAccessConfigSettings();
    static QSettings *GenerateDatAccessConfigSettings(QString p_qstrConfigName);
    static QVariantMap RetrieveValuesFromSettings(QSettings &p_rSettings);
    static void SetValuesFromMapToSettings(QVariantMap &p_rqMap, QSettings &p_rqSettings);
    static void SetDataAccessConfigName(EwmsSettingsConfigType p_eType, QString p_qstrConfig);
    static QString ReadDataAccessConfigFile(EwmsSettingsConfigType p_eType);
    static void SetValuesFromUiMapToSettings(QVariantMap &p_rqMap, QSettings &p_rqSettings);
private:
    static QSettings *GenerateSettings(QString p_qstrPrefix);
    static QSettings *GenerateDataAccessSettings(EwmsSettingsConfigType p_eType);
    static QMutex m_qMutex;
};

#endif // CWMSSETTINGSSTOREFACTORY_H
