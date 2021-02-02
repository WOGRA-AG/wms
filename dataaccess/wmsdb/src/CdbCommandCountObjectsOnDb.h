#ifndef CDBCOMMANDCOUNTOBJECTSONDB_H
#define CDBCOMMANDCOUNTOBJECTSONDB_H

#include "CdbAbstractCommand.h"

class CdbCommandCountObjectsOnDb : public CdbAbstractCommand
{
private:
    CdmObjectContainer* m_rpContainer;
public:
    CdbCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCountObjectsOnDb();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCOUNTOBJECTSONDB_H
