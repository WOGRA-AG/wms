#ifndef CDBCOMMANDGETGROUPSOFUSER_H
#define CDBCOMMANDGETGROUPSOFUSER_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandGetGroupsOfUser : public CdbAbstractCommand
{
private:
    long m_lUserId;
    QList<CumUserGroup*> m_qllGroups;

public:
    CdbCommandGetGroupsOfUser(long p_lUser, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetGroupsOfUser();
    QList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPSOFUSER_H
