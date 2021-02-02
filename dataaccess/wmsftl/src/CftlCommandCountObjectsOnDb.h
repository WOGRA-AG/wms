#ifndef CDBCOMMANDCOUNTOBJECTSONDB_H
#define CDBCOMMANDCOUNTOBJECTSONDB_H

#include "CftlAbstractCommand.h"

class CftlCommandCountObjectsOnDb : public CftlAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
public:
    CftlCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCountObjectsOnDb();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCOUNTOBJECTSONDB_H
