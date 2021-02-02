#ifndef CDBCOMMANDDELETEUSERGROUP_H
#define CDBCOMMANDDELETEUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandDeleteUserGroup : public CdbAbstractCommandTransactional
{
private:
    long m_lGroupId;

public:
    CdbCommandDeleteUserGroup(long p_lgroupId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDDELETEUSERGROUP_H
