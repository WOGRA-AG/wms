#ifndef CWMSPLUGINSCOMMANDDEACTIVATEPLUGIN_H
#define CWMSPLUGINSCOMMANDDEACTIVATEPLUGIN_H

#include "CwmsPluginsCommandAbstract.h"

class CwmsPluginsCommandDeactivatePlugin : public CwmsPluginsCommandAbstract
{
public:
    CwmsPluginsCommandDeactivatePlugin();
    virtual QString GetCommand();
    virtual bool Run(QMap<QString,QString> p_qmArgs);
    virtual ~CwmsPluginsCommandDeactivatePlugin();
};

#endif // CWMSPLUGINSCOMMANDDEACTIVATEPLUGIN_H
