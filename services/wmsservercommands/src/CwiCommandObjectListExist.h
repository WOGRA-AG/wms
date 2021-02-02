#ifndef CWICOMMANDOBJECTLISTEXIST_H
#define CWICOMMANDOBJECTLISTEXIST_H

#include "CwiAbstractCommand.h"

class CwiCommandObjectListExist : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandObjectListExist(CwmscomData* p_pData);
    virtual ~CwiCommandObjectListExist();
    virtual void Execute();
};

#endif // CWICOMMANDOBJECTLISTEXIST_H
