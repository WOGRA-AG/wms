#ifndef CDBCOMMANDGETNEWCLASSID_H
#define CDBCOMMANDGETNEWCLASSID_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandGetNewClassId : public CdbAbstractCommandTransactional
{
private:
    long m_lSchemeId;
    long m_lSessionId;

public:
    CdbCommandGetNewClassId(long p_lSessionId, long p_lSchemeId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewClassId();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETNEWCLASSID_H
