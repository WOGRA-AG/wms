#ifndef IWMSDATAACCESSPLUGIN_H
#define IWMSDATAACCESSPLUGIN_H

#include <QString>
#include <QObject>

// Forwards
class IdmDataAccess;

class IwmsDataAccessPlugin
{
public:
   virtual IdmDataAccess* getDbAccess(QString p_qstrApplication) = 0;
   virtual QString getVersion() = 0;
   virtual QString getName() = 0;
   virtual QString getConfigurationUiName() = 0;
   virtual QObject* getConfigurationObject(QString p_qstrApplication) = 0;
   virtual void openConfigurationEditor(QString p_qstrApplication) = 0;
   virtual bool allowsRfc(QString p_qstrApplication) = 0;
   virtual QVariantMap GetConfigurationMap(QString p_qstrApplication) = 0;
   virtual void SetConfigurationMap(QString p_qstrApplication, QVariantMap& p_rMap) = 0;
};

#ifndef Q_OS_IOS
Q_DECLARE_INTERFACE(IwmsDataAccessPlugin, "com.wogra.iwmsdataaccessplugin/1.0")
#endif
#endif // // IWMSDATAACCESSPLUGIN_H
