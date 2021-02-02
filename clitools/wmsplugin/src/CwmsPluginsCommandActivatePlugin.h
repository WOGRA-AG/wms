#ifndef CWMSPLUGINSCOMMANDACTIVATEPLUGIN_H
#define CWMSPLUGINSCOMMANDACTIVATEPLUGIN_H

#include "CwmsPluginsCommandAbstract.h"

class CwmsPluginsCommandActivatePlugin : public CwmsPluginsCommandAbstract
{
public:
    CwmsPluginsCommandActivatePlugin();
    virtual QString GetCommand();
    virtual bool Run(QMap<QString,QString> p_qmArgs);
    virtual ~CwmsPluginsCommandActivatePlugin();
};

#endif // CWMSPLUGINSCOMMANDACTIVATEPLUGIN_H
