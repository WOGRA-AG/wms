#ifndef CWICOMMANDFINDGROUP_H
#define CWICOMMANDFINDGROUP_H

// own include
#include "IwiCommand.h"

class CwiCommandFindGroup : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;

public:
    CwiCommandFindGroup(CwmscomData* p_pData);
    ~CwiCommandFindGroup();
    virtual void Execute();
};

#endif // CWICOMMANDFINDGROUP_H
