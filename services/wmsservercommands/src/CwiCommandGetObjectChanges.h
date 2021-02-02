#ifndef CWICOMMANDGETOBJECTCHANGES_H
#define CWICOMMANDGETOBJECTCHANGES_H

#include "CwiAbstractCommand.h"

class CwiCommandGetObjectChanges : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetObjectChanges(CwmscomData* p_pData);
    virtual ~CwiCommandGetObjectChanges();
    virtual void Execute();
};

#endif // CWICOMMANDGETOBJECTCHANGES_H
