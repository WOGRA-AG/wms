#ifndef CDBCOMMANDDELETEUSERGROUP_H
#define CDBCOMMANDDELETEUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandDeleteUserGroup : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lGroupId;

public:
    CftlCommandDeleteUserGroup(qint64 p_lgroupId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDDELETEUSERGROUP_H
