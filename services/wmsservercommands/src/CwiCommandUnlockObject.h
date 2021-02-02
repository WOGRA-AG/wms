#ifndef CWICOMMANDUNLOCKOBJECT_H
#define CWICOMMANDUNLOCKOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandUnlockObject : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandUnlockObject(CwmscomData* p_pData);
    virtual ~CwiCommandUnlockObject();
    virtual void Execute();
};

#endif // CWICOMMANDUNLOCKOBJECT_H
