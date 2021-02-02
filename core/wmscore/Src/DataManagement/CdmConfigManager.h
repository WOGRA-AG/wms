#ifndef CDMCONFIGMANAGER_H
#define CDMCONFIGMANAGER_H

#include <QVariantMap>

#include "datamanager.h"

#define TEMPORARY_DATA "TempData"

class WMSMANAGER_API CdmConfigManager
{
private:
    QVariantMap m_qmConfig;
public:
    CdmConfigManager();
    virtual ~CdmConfigManager();
    void SetConfig(QString p_qstrConfig);
    QString GetConfig() const;
    void SetConfigItem(QString p_qstrKey, QVariant p_qvValue);
    void SetTemporaryData(QString p_qstrKey, QVariant p_qvValue);
    QVariant GetConfigItem(QString p_qstrKey) const;
    QVariant GetTemporaryData(QString p_qstrKey) const;
    bool HasTemporaryData(QString p_qstrKey) const;
};

#endif // CDMCONFIGMANAGER_H
