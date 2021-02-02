#ifndef CWMSUSERHANDLER_H
#define CWMSUSERHANDLER_H

class CwmsUserCommandAbstract;

class CwmsUserHandler
{
private:
    QMap<QString,QString> m_qmArguments;
    QMap<QString,CwmsUserCommandAbstract*> m_qmCommands;
    bool Validate();
    bool Init();

public:
    CwmsUserHandler(QMap<QString,QString> p_qmArguments);
    virtual ~CwmsUserHandler();
    bool Run();
};


#endif // CWMSUSERHANDLER_H
