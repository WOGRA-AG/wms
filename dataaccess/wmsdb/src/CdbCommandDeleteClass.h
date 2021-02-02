#ifndef CDBCOMMANDDELETECLASS_H
#define CDBCOMMANDDELETECLASS_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandDeleteClass : public CdbAbstractCommandTransactional
{
private:
    long m_lClassId;

public:
    CdbCommandDeleteClass(long p_lClassId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteClass();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETECLASS_H
