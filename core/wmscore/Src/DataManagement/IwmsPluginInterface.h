#ifndef IWMSPLUGININTERFACE_H
#define IWMSPLUGININTERFACE_H

// forwards
class QAction;

class IwmsPluginInterface
{
public:
    virtual ~IwmsPluginInterface(){};

    virtual QStringList functionClasses() const = 0;
    virtual QObject* getFunctionClass(const QString functionClass) = 0;
    virtual QString getVersion() = 0;
    virtual QString getName() = 0;
    virtual QList<QAction*> getWmsDpActions() = 0;
    virtual QList<QAction*> getWmsRuntimeActions() = 0;
    virtual void init() = 0;
};

Q_DECLARE_INTERFACE(IwmsPluginInterface, "com.wogra.iwmsplugin_interface/1.0")
#endif // // IWMSPLUGININTERFACE_H
