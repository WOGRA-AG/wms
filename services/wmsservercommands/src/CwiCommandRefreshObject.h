#ifndef CWICOMMANDREFRESHOBJECT_H
#define CWICOMMANDREFRESHOBJECT_H

#include "CwiAbstractCommand.h"

class CwiCommandRefreshObject : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandRefreshObject(CwmscomData* p_pData);
    virtual ~CwiCommandRefreshObject();
    virtual void Execute();
};

#endif // CWICOMMANDREFRESHOBJECT_H
