#ifndef CDBCOMMANDREFRESHOBJECT_H
#define CDBCOMMANDREFRESHOBJECT_H

#include "CftlAbstractCommand.h"

class CdmObject;

class CftlCommandRefreshObject : public CftlAbstractCommand
{
private:
    CdmObject* m_rpObject;

public:
    CftlCommandRefreshObject(CdmObject* m_rpCdmObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandRefreshObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDREFRESHOBJECT_H
