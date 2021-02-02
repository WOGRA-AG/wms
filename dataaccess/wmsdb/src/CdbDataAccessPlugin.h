#ifndef CODBCDATAACCESSPLUGIN_H
#define CODBCDATAACCESSPLUGIN_H

// System and QT Includes
#include <QObject>

// WMS Includes
#include "CdbDataAccess.h"
#include "IwmsDataAccessPlugin.h"

// Own Includes

// Forwards
class CdbDataAccessConfigurator;

class CdbDataAccessPluginImpl : public IwmsDataAccessPlugin
{

private:
    CdbDataAccessConfigurator* m_pConfigurator;

public:
	CdbDataAccessPluginImpl();
	virtual ~CdbDataAccessPluginImpl();
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


class CdbDataAccessPlugin : public QObject, public CdbDataAccessPluginImpl
{
	Q_OBJECT
	Q_INTERFACES(IwmsDataAccessPlugin)
	Q_PLUGIN_METADATA(IID "com.wogra.iwmsdataaccessplugin/1.0")
};
#endif
