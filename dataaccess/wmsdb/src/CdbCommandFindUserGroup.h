#ifndef CDBCOMMANDFINDUSERGROUP_H
#define CDBCOMMANDFINDUSERGROUP_H

#include "CdbCommandFindUserGroup.h"

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;
class CumUserGroup;

class CdbCommandFindUserGroup : public CdbAbstractCommand
{
private:
    long m_lGroupId;
    CumUserGroup* m_pGroup;
    QString m_qstrGroupName;

public:
    CdbCommandFindUserGroup(long p_lGroup, CdbDataAccess* p_pDataAccess);
    CdbCommandFindUserGroup(QString p_lGroup, CdbDataAccess* p_DataAccess);
    virtual ~CdbCommandFindUserGroup();
    CumUserGroup* GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};


#endif // CDBCOMMANDFINDUSERGROUP_H
