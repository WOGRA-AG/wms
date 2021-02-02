#ifndef CDBCOMMANDADDUSERTOUSERGROUP_H
#define CDBCOMMANDADDUSERTOUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandAddUserToUserGroup : public CdbAbstractCommandTransactional
{
private:
    long m_lGroupId;
    long m_lUserId;

public:
    CdbCommandAddUserToUserGroup(long p_lUser, long p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandAddUserToUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDADDUSERTOUSERGROUP_H
