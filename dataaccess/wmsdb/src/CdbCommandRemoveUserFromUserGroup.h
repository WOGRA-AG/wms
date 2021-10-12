#ifndef CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
#define CDBCOMMANDREMOVEUSERFROMUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandRemoveUserFromUserGroup : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lGroupId;
   qint64 m_lUserId;

public:
    CdbCommandRemoveUserFromUserGroup(qint64 p_lUser,qint64 p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandRemoveUserFromUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDREMOVEUSERFROMUSERGROUP_H
