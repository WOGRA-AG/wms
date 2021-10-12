#ifndef CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
#define CDBCOMMANDREMOVEUSERFROMUSERGROUP_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandRemoveUserFromUserGroup : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lGroupId;
   qint64 m_lUserId;

public:
    CftlCommandRemoveUserFromUserGroup(qint64 p_lUser,qint64 p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandRemoveUserFromUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
