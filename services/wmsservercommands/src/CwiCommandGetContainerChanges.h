#ifndef CWICOMMANDGETCONTAINERCHANGES_H
#define CWICOMMANDGETCONTAINERCHANGES_H

#include "CwiAbstractCommand.h"

class CwiCommandGetContainerChanges : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetContainerChanges(CwmscomData* p_pData);
    virtual ~CwiCommandGetContainerChanges();
    virtual void Execute();
};

#endif // CWICOMMANDGETCONTAINERCHANGES_H
