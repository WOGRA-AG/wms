#ifndef CDBCOMMANDGETNEWCONTAINERID_H
#define CDBCOMMANDGETNEWCONTAINERID_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandGetNewContainerId : public CdbAbstractCommandTransactional
{
private:
    long m_lClassId;
    long m_lSessionId;

public:
    CdbCommandGetNewContainerId(long p_lClassId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewContainerId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWCONTAINERID_H
