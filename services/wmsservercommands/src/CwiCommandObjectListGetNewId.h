#ifndef CWICOMMANDOBJECTLISTGETNEWID_H
#define CWICOMMANDOBJECTLISTGETNEWID_H

#include "CwiAbstractCommand.h"

class CwiCommandObjectListGetNewId : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandObjectListGetNewId(CwmscomData* p_pData);
    virtual ~CwiCommandObjectListGetNewId();
    virtual void Execute();
};

#endif // CWICOMMANDOBJECTLISTGETNEWID_H
