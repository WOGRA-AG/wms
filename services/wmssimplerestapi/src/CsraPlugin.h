#ifndef CSRAPLUGIN_H
#define CSRAPLUGIN_H

// System and Qt includes
#include <QObject>

// own includes
#include "IwmsServerPlugin.h"

// forwards
class CwmscomHandler;

class CsraPlugin : public QObject, public IwmsServerPlugin
{
    Q_OBJECT
    Q_INTERFACES(IwmsServerPlugin)
    Q_PLUGIN_METADATA(IID "com.wogra.iwmsserverplugin/1.0")

public:
    CsraPlugin();
    virtual ~CsraPlugin(){};

    // IwmsServerPlugin interface
public:
    virtual QString getVersion();
    virtual QString getName();
    virtual void init();
private:
    void AddWmsHandling(CwmscomHandler *p_pHandler);
};



#endif // CSRAPLUGIN_H
