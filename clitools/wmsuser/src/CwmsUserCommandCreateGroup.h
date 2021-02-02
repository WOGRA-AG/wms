#ifndef CWMSUSERCOMMANDCREATEGROUP_H
#define CWMSUSERCOMMANDCREATEGROUP_H

#include "CwmsUserCommandAbstract.h"

class CwmsUserCommandCreateGroup : public CwmsUserCommandAbstract
{
public:
    CwmsUserCommandCreateGroup();

    // CwmsUserCommandAbstract interface
public:
    virtual QString GetCommand();
    virtual bool Run(QMap<QString, QString> p_qmArgs);
    virtual ~CwmsUserCommandCreateGroup();
};

#endif // CWMSUSERCOMMANDCREATEGROUP_H
