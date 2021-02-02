#ifndef CWMSUSERCOMMANDREMOVEUSERFROMGROUP_H
#define CWMSUSERCOMMANDREMOVEUSERFROMGROUP_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandRemoveUserFromGroup : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandRemoveUserFromGroup();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandRemoveUserFromGroup();
};

#endif // CWMSUSERCOMMANDREMOVEUSERFROMGROUP_H
