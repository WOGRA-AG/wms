#ifndef CDBCOMMANDDELETEUSERGROUP_H
#define CDBCOMMANDDELETEUSERGROUP_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandDeleteUserGroup : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lGroupId;

public:
    CdbCommandDeleteUserGroup(qint64 p_lgroupId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteUserGroup();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDDELETEUSERGROUP_H
