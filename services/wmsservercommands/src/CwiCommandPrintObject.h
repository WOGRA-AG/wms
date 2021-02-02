#ifndef CWICOMMANDPRINTOBJECT_H
#define CWICOMMANDPRINTOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandPrintObject : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandPrintObject(CwmscomData* p_pData);
    virtual ~CwiCommandPrintObject();
    virtual void Execute();
};

#endif // CWICOMMANDPRINTOBJECT_H
