#ifndef CDBCOMMANDFINDUSERGROUPBYID_H
#define CDBCOMMANDFINDUSERGROUPBYID_H

#include "CdbCommandFindUserGroupById.h"

//Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;
class CumUserGroup;

class CdbCommandFindUserGroupById : public CdbAbstractCommand
{
private:
    int m_iGroupId;
    CumUserGroup* m_pGroup;
public:
    CdbCommandFindUserGroupById(int p_iGroupId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindUserGroupById();
    CumUserGroup* GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDUSERGROUPBYID_H
