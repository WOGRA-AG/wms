#ifndef CWICOMMANDGETNEWOBJECTID_H
#define CWICOMMANDGETNEWOBJECTID_H

#include "CwiAbstractCommand.h"

class CwiCommandGetNewObjectId : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetNewObjectId(CwmscomData* p_pData);
    virtual ~CwiCommandGetNewObjectId();
    virtual void Execute();
};

#endif // CWICOMMANDGETNEWOBJECTID_H
