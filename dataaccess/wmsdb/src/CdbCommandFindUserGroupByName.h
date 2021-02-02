#ifndef CDBCOMMANDFINDUSERGROUPBYNAME_H
#define CDBCOMMANDFINDUSERGROUPBYNAME_H

#include "CdbCommandFindUserGroupByName.h"

//Own Includes
#include "CdbAbstractCommand.h"

//Forwards
class CdbDataAccess;
class CumUserGroup;

class CdbCommandFindUserGroupByName : public CdbAbstractCommand
{
private:
    QString m_qstrGroupName;
    CumUserGroup* m_pGroup;
    QString m_qstrSchemeUri;
public:
    CdbCommandFindUserGroupByName(QString p_qstrGroupName, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandFindUserGroupByName();
    CumUserGroup* GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDFINDUSERGROUPBYNAME_H
