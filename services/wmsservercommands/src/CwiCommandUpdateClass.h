#ifndef CWICOMMANDUPDATECLASS_H
#define CWICOMMANDUPDATECLASS_H

#include "CwiAbstractCommand.h"

class CwiCommandUpdateClass : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandUpdateClass(CwmscomData* p_pData);
    virtual ~CwiCommandUpdateClass();
    virtual void Execute();
};

#endif // CWICOMMANDUPDATECLASS_H
