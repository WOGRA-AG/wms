#ifndef CWICOMMANDGETCLASS_H
#define CWICOMMANDGETCLASS_H

#include "CwiAbstractCommand.h"

class CwiCommandGetClass : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetClass(CwmscomData* p_pData);
    virtual ~CwiCommandGetClass();
    virtual void Execute();
};

#endif // CWICOMMANDGETCLASS_H
