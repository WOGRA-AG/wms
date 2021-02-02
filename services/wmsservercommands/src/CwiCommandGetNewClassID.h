#ifndef CWICOMMANDGETNEWCLASSID_H
#define CWICOMMANDGETNEWCLASSID_H

#include "CwiAbstractCommand.h"

class CwiCommandGetNewClassID : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetNewClassID(CwmscomData* p_pData);
    virtual ~CwiCommandGetNewClassID();
    virtual void Execute();
};

#endif // CWICOMMANDGETNEWCLASSID_H
