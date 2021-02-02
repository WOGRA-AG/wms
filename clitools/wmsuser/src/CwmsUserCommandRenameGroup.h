#ifndef CWMSUSERCOMMANDRENAMEGROUP_H
#define CWMSUSERCOMMANDRENAMEGROUP_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandRenameGroup : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandRenameGroup();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandRenameGroup();
};

#endif // CWMSUSERCOMMANDRENAMEGROUP_H
