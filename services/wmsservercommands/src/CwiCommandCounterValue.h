#ifndef CWICOMMANDCOUNTERVALUE_H
#define CWICOMMANDCOUNTERVALUE_H

#include "CwiAbstractCommand.h"

class CwiCommandCounterValue : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandCounterValue(CwmscomData* p_pData);
    virtual ~CwiCommandCounterValue();
    virtual void Execute();
};

#endif // CWICOMMANDCOUNTERVALUE_H
