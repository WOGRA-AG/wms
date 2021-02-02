#ifndef CWICOMMANDGETUSERGROUPBYID_H
#define CWICOMMANDGETUSERGROUPBYID_H

#include "CwiAbstractCommand.h"

class CwiCommandGetUserGroupById : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetUserGroupById(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserGroupById();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERGROUPBYID_H
