#ifndef CWMSUSERCOMMANDUPDATEUSER_H
#define CWMSUSERCOMMANDUPDATEUSER_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandUpdateUser : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandUpdateUser();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandUpdateUser();
};

#endif // CWMSUSERCOMMANDUPDATEUSER_H
