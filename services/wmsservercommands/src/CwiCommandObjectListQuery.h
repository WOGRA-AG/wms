#ifndef CWICOMMANDOBJECTLISTQUERY_H
#define CWICOMMANDOBJECTLISTQUERY_H

#include "CwiAbstractCommand.h"

class CwiCommandObjectListQuery : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandObjectListQuery(CwmscomData* p_pData);
    virtual ~CwiCommandObjectListQuery();
    virtual void Execute();
};

#endif // CWICOMMANDOBJECTLISTQUERY_H
