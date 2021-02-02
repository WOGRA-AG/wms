#ifndef CWMSPLUGINSCOMMANDABSTRACT_H
#define CWMSPLUGINSCOMMANDABSTRACT_H

// System and Qt Includes
#include <QString>
#include <QMap>

// Basetools Includes
#include "CwmsPluginManager.h"

class CwmsPluginsCommandAbstract
{
public:
    CwmsPluginsCommandAbstract();

    virtual QString GetCommand() = 0;
    virtual bool Run(QMap<QString,QString> p_qmArgs) = 0;
    virtual ~CwmsPluginsCommandAbstract();

protected:
    CwmsPluginManager m_PluginManager;
};

#endif // CWMSPLUGINSCOMMANDABSTRACT_H
