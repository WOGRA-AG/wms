#ifndef CDBCOMMANDUNLOCKOBJECT_H
#define CDBCOMMANDUNLOCKOBJECT_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandUnlockObject : public CftlAbstractTransactionalCommand
{
private:
        CdmObject* m_rpObject;
public:
    CftlCommandUnlockObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    ~CftlCommandUnlockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUNLOCKOBJECT_H
