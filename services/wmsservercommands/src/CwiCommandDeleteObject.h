#ifndef CWICOMMANDDELETEOBJECT_H
#define CWICOMMANDDELETEOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandDeleteObject : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;

public:
    CwiCommandDeleteObject(CwmscomData* p_pData);
    virtual ~CwiCommandDeleteObject();
    virtual void Execute();
};

#endif // CWICOMMANDDELETEOBJECT_H
