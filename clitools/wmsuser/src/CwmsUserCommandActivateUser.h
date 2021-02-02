#ifndef CWMSUSERCOMMANDACTIVATEUSER_H
#define CWMSUSERCOMMANDACTIVATEUSER_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandActivateUser : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandActivateUser();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
};

#endif // CWMSUSERCOMMANDACTIVATEUSER_H
