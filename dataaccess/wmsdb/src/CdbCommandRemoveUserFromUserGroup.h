#ifndef CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
#define CDBCOMMANDREMOVEUSERFROMUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandRemoveUserFromUserGroup : public CdbAbstractCommandTransactional
{
private:
    long m_lGroupId;
    long m_lUserId;

public:
    CdbCommandRemoveUserFromUserGroup(long p_lUser, long p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRemoveUserFromUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
