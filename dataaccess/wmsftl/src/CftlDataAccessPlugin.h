#ifndef CODBCDATAACCESSPLUGIN_H
#define CODBCDATAACCESSPLUGIN_H

// System and QT Includes
#include <QObject>

// WMS Includes
#include "CftlDataAccess.h"
#include "IwmsDataAccessPlugin.h"

// Own Includes

// Forwards
class CftlDataAccessConfigurator;

class CftlDataAccessPluginImpl : public IwmsDataAccessPlugin
{

private:
    CftlDataAccessConfigurator* m_pConfigurator;

public:
	CftlDataAccessPluginImpl();
	virtual ~CftlDataAccessPluginImpl();
    virtual IdmDataAccess* getDbAccess(QString p_qstrApplication);
    virtual QString getVersion();
    virtual QString getName();
    virtual QString getConfigurationUiName();
    virtual QObject* getConfigurationObject(QString p_qstrApplication);
    virtual void openConfigurationEditor(QString p_qstrApplication);
    virtual bool allowsRfc(QString p_qstrApplication){ Q_UNUSED(p_qstrApplication); return false; }
	virtual QVariantMap GetConfigurationMap(QString p_qstrApplication);
	virtual void SetConfigurationMap(QString p_qstrApplication, QVariantMap& p_rMap);
};


class CftlDataAccessPlugin : public QObject, public CftlDataAccessPluginImpl
{
	Q_OBJECT
	Q_INTERFACES(IwmsDataAccessPlugin)
	Q_PLUGIN_METADATA(IID "com.wogra.iwmsdataaccessplugin/1.0")
};
#endif
