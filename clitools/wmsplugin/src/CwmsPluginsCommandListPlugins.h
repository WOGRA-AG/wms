#ifndef CWMSPLUGINSCOMMANDLISTPLUGINS_H
#define CWMSPLUGINSCOMMANDLISTPLUGINS_H

#include "CwmsPluginsCommandAbstract.h"

class CwmsPluginsCommandListPlugins : public CwmsPluginsCommandAbstract
{
public:
    CwmsPluginsCommandListPlugins();
    virtual QString GetCommand();
    virtual bool Run(QMap<QString,QString> p_qmArgs);
    virtual ~CwmsPluginsCommandListPlugins();
};

#endif // CWMSPLUGINSCOMMANDLISTPLUGINS_H
