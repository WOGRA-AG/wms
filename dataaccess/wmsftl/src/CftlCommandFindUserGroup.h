#ifndef CDBCOMMANDFINDUSERGROUP_H
#define CDBCOMMANDFINDUSERGROUP_H

#include "CftlCommandFindUserGroup.h"

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;
class CumUserGroup;

class CftlCommandFindUserGroup : public CftlAbstractCommand
{
private:
    long m_lGroupId;
    CumUserGroup* m_pGroup;
    QString m_qstrGroupName;
    QString m_qstrSchemeUri;

    int FindUserGroupById();
    int FindUserGroupByName();

public:
    CftlCommandFindUserGroup(long p_lGroup, CftlDataAccess* p_pDataAccess);
    CftlCommandFindUserGroup(QString p_qstrName, QString m_qstrSchemeUri, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandFindUserGroup();
    CumUserGroup* GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};


#endif // CDBCOMMANDFINDUSERGROUP_H
