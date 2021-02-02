#ifndef CWMSPLUGINSHANDLER_H
#define CWMSPLUGINSHANDLER_H

// Forwards
class CwmsPluginsCommandAbstract;

class CwmsPluginsHandler
{
private:
    QMap<QString,QString> m_qmArguments;
    QMap<QString,CwmsPluginsCommandAbstract*> m_qmCommands;
    bool Validate();
    bool Init();

public:
    CwmsPluginsHandler(QMap<QString,QString> p_qmArguments);
    virtual ~CwmsPluginsHandler();

    bool Run();
};

#endif // CWMSPLUGINSHANDLER_H
