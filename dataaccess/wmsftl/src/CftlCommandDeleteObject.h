#ifndef CDBCOMMANDDELETEOBJECT_H
#define CDBCOMMANDDELETEOBJECT_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"


class CftlCommandDeleteObject : public CftlAbstractTransactionalCommand
{
private:
    CdmObject* m_rpObject;

public:
    CftlCommandDeleteObject(CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETEOBJECT_H
