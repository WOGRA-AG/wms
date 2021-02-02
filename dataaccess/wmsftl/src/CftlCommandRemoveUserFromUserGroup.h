#ifndef CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
#define CDBCOMMANDREMOVEUSERFROMUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandRemoveUserFromUserGroup : public CftlAbstractTransactionalCommand
{
private:
    long m_lGroupId;
    long m_lUserId;

public:
    CftlCommandRemoveUserFromUserGroup(long p_lUser, long p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandRemoveUserFromUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
