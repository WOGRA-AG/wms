#ifndef CWICOMMANDLOCKOBJECT_H
#define CWICOMMANDLOCKOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandLockObject : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandLockObject(CwmscomData* p_pData);
    virtual ~CwiCommandLockObject();
    virtual void Execute();
};

#endif // CWICOMMANDLOCKOBJECT_H
