#ifndef CWICOMMANDCREATEOBJECT_H
#define CWICOMMANDCREATEOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandCreateObject : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandCreateObject(CwmscomData* p_pData);
    virtual ~CwiCommandCreateObject();
    virtual void Execute();
};

#endif // CWICOMMANDCREATEOBJECT_H
