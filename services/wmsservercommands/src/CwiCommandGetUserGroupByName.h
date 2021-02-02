#ifndef CWICOMMANDGETUSERGROUPBYNAME_H
#define CWICOMMANDGETUSERGROUPBYNAME_H

#include "CwiAbstractCommand.h"

class CwiCommandGetUserGroupByName : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;
public:
    CwiCommandGetUserGroupByName(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserGroupByName();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERGROUPBYNAME_H
