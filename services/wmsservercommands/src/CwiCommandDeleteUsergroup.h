#ifndef CWICOMMANDDELETEUSERGROUP_H
#define CWICOMMANDDELETEUSERGROUP_H

#include "CwiAbstractCommand.h"

class CwiCommandDeleteUsergroup : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandDeleteUsergroup(CwmscomData *p_pData);
    virtual ~CwiCommandDeleteUsergroup();
    virtual void Execute();
};

#endif // CWICOMMANDDELETEUSERGROUP_H
