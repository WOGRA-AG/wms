#ifndef CWMSUSERCOMMANDLISTUSERS_H
#define CWMSUSERCOMMANDLISTUSERS_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandListUsers : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandListUsers();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
};

#endif // CWMSUSERCOMMANDLISTUSERS_H
