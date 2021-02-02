#ifndef CWICOMMANDISOBJECTUSED_H
#define CWICOMMANDISOBJECTUSED_H

#include "CwiAbstractCommand.h"

class CwiCommandIsObjectUsed : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandIsObjectUsed(CwmscomData* p_pData);
    virtual ~CwiCommandIsObjectUsed();
    virtual void Execute();
};

#endif // CWICOMMANDISOBJECTUSED_H
