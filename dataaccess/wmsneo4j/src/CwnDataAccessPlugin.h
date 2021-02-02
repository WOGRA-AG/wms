#ifndef CWNDATAACCESSPLUGIN_H
#define CWNDATAACCESSPLUGIN_H


// System and QT Includes
#include <QObject>

// WMS Includes
#include "IwmsDataAccessPlugin.h"
#include "CwnDataAccess.h"

// Own Includes

class CwnDataAccessConfigurator;

class CwnDataAccessPlugin : public QObject, public IwmsDataAccessPlugin
{
    Q_OBJECT
    Q_INTERFACES(IwmsDataAccessPlugin)
    Q_PLUGIN_METADATA(IID "com.wogra.iwmsdataaccessplugin/1.0")

private:
    CwnDataAccessConfigurator* m_pConfigurator;

public:
    CwnDataAccessPlugin();
    virtual ~CwnDataAccessPlugin();
    virtual IdmDataAccess* getDbAccess(QString p_qstrApplication);
    virtual QString getVersion();
    virtual QString getName();
    virtual QString getConfigurationUiName();
    virtual QObject* getConfigurationObject(QString p_qstrApplication);
    virtual void openConfigurationEditor(QString p_qstrApplication);
    virtual QVariantMap GetConfigurationMap(QString p_qstrApplication);
    virtual void SetConfigurationMap(QString p_qstrApplication, QVariantMap& p_rMap);
    virtual bool allowsRfc(QString p_qstrApplication){ Q_UNUSED(p_qstrApplication); return false; }
};


#endif // CWNDATAACCESSPLUGIN_H
