#ifndef CDBCOMMANDADDUSERTOUSERGROUP_H
#define CDBCOMMANDADDUSERTOUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandAddUserToUserGroup : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lGroupId;
   qint64 m_lUserId;

public:
    CftlCommandAddUserToUserGroup(qint64 p_lUser,qint64 p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandAddUserToUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDADDUSERTOUSERGROUP_H
