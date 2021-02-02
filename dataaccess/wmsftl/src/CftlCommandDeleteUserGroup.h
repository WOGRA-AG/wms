#ifndef CDBCOMMANDDELETEUSERGROUP_H
#define CDBCOMMANDDELETEUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandDeleteUserGroup : public CftlAbstractTransactionalCommand
{
private:
    long m_lGroupId;

public:
    CftlCommandDeleteUserGroup(long p_lgroupId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDDELETEUSERGROUP_H
