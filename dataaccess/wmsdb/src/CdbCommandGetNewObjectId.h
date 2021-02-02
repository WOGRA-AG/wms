#ifndef CDBCOMMANDGETNEWOBJECTID_H
#define CDBCOMMANDGETNEWOBJECTID_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandGetNewObjectId : public CdbAbstractCommandTransactional
{
private:
    long m_lContainerId;
    long m_lSessionId;
public:
    CdbCommandGetNewObjectId(long p_lContainerId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewObjectId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWOBJECTID_H
