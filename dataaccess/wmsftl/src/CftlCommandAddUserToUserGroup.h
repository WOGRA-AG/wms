#ifndef CDBCOMMANDADDUSERTOUSERGROUP_H
#define CDBCOMMANDADDUSERTOUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandAddUserToUserGroup : public CftlAbstractTransactionalCommand
{
private:
    long m_lGroupId;
    long m_lUserId;

public:
    CftlCommandAddUserToUserGroup(long p_lUser, long p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandAddUserToUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDADDUSERTOUSERGROUP_H
