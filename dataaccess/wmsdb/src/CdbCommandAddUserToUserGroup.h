#ifndef CDBCOMMANDADDUSERTOUSERGROUP_H
#define CDBCOMMANDADDUSERTOUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandAddUserToUserGroup : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lGroupId;
   qint64 m_lUserId;

public:
    CdbCommandAddUserToUserGroup(qint64 p_lUser,qint64 p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandAddUserToUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDADDUSERTOUSERGROUP_H
