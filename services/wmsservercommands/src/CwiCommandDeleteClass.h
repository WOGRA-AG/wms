#ifndef CWICOMMANDDELETECLASS_H
#define CWICOMMANDDELETECLASS_H

#include "CwiAbstractCommand.h"

class CwiCommandDeleteClass : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandDeleteClass(CwmscomData* p_pData);
    virtual ~CwiCommandDeleteClass();
    virtual void Execute();
};

#endif // CWICOMMANDDELETECLASS_H
