#ifndef CWMSUSERCOMMANDDEACTIVATEUSER_H
#define CWMSUSERCOMMANDDEACTIVATEUSER_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandDeactivateUser : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandDeactivateUser();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandDeactivateUser();
};

#endif // CWMSUSERCOMMANDDEACTIVATEUSER_H
