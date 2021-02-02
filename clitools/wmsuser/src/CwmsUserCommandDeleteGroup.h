#ifndef CWMSUSERCOMMANDDELETEGROUP_H
#define CWMSUSERCOMMANDDELETEGROUP_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandDeleteGroup : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandDeleteGroup();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandDeleteGroup();
};

#endif // CWMSUSERCOMMANDDELETEGROUP_H
