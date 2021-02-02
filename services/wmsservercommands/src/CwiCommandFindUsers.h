#ifndef CWICOMMANDFINDUSERS_H
#define CWICOMMANDFINDUSERS_H

// own include
#include "IwiCommand.h"

class CwiCommandFindUsers : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;

public:
    CwiCommandFindUsers(CwmscomData* p_pData);
    ~CwiCommandFindUsers();
    virtual void Execute();
};

#endif // CWICOMMANDFINDUSERS_H
