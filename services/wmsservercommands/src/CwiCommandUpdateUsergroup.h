#ifndef CWICOMMANDUPDATEUSERGROUP_H
#define CWICOMMANDUPDATEUSERGROUP_H

#include "CwiAbstractCommand.h"

class CwiCommandUpdateUsergroup : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandUpdateUsergroup(CwmscomData *p_pData);
    virtual ~CwiCommandUpdateUsergroup();
    virtual void Execute();
};

#endif // CWICOMMANDUPDATEUSERGROUP_H
