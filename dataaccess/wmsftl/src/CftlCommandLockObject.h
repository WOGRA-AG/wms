#ifndef CDBCOMMANDLOCKOBJECT_H
#define CDBCOMMANDLOCKOBJECT_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandLockObject : public CftlAbstractTransactionalCommand
{
private:
        CdmObject* m_rpObject;
public:
    CftlCommandLockObject(CdmObject* p_pObject,CftlDataAccess* p_pDataAccess);
    ~CftlCommandLockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOCKOBJECT_H
