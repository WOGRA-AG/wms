#ifndef CWMSUSERCOMMANDLISTGROUPS_H
#define CWMSUSERCOMMANDLISTGROUPS_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandListGroups : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandListGroups();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
};

#endif // CWMSUSERCOMMANDLISTGROUPS_H
