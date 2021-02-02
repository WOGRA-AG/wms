#ifndef CWMSUSERCOMMANDADDUSERTOGROUP_H
#define CWMSUSERCOMMANDADDUSERTOGROUP_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandAddUserToGroup : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandAddUserToGroup();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandAddUserToGroup();
};

#endif // CWMSUSERCOMMANDADDUSERTOGROUP_H
