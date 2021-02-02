#ifndef CWMSDATAACCESSCONFIGURATION_H
#define CWMSDATAACCESSCONFIGURATION_H


// WMSManager Includes
#include "CdmDataAccessConfiguration.h"

// own Includes
#include "basetools.h"

// Forwards
class IwmsDataAccessPlugin;

class BASETOOLS_API CwmsDataAccessConfiguration : public CdmDataAccessConfiguration
{
    Q_OBJECT
private:
    QStringList getDynamicDataAccessList();
    QStringList getStaticDataAccessList();
    void addPlugin(IwmsDataAccessPlugin* pPlugin, QString p_qstrFilename);
public:
    CwmsDataAccessConfiguration();
    ~CwmsDataAccessConfiguration();
    void deleteConfiguration(QString p_qstrConfig);
public slots:
    virtual QStringList getDataAccessList();
    QStringList getConfigurationList();
    QString getConfigurationPluginName(QString p_qstrConfig);
    void setConfigurationPluginName(QString p_qstrConfig, QString p_qstrPlugin);
};

#endif // CWMSDATAACCESSCONFIGURATION_H
