#ifndef CWMSUSERCOMMANDDELETEUSER_H
#define CWMSUSERCOMMANDDELETEUSER_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandDeleteUser : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandDeleteUser();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandDeleteUser();
};

#endif // CWMSUSERCOMMANDDELETEUSER_H
