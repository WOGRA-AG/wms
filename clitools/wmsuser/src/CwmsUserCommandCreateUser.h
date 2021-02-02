#ifndef CWMSUSERCOMMANDCREATEUSER_H
#define CWMSUSERCOMMANDCREATEUSER_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandCreateUser : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandCreateUser();
    virtual ~CwmsUserCommandCreateUser();
    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);

};

#endif // CWMSUSERCOMMANDCREATEUSER_H
