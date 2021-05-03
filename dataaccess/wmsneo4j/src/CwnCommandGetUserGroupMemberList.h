#ifndef CWNCOMMANDGETUSERGROUPMEMBERLIST_H
#define CWNCOMMANDGETUSERGROUPMEMBERLIST_H

#include "CwnCommandBase.h"
#include "CumUserGroup.h"

#include <QVariant>
#include <QString>
#include <QList>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandGetUserGroupMemberList : public CwnCommandBase
{
public:
    CwnCommandGetUserGroupMemberList(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandGetUserGroupMemberList();
    QList<CumUserGroup *> getResult();

    void setUserId(long userId);
    long getUserId();

    QString createQuery();
    QString queryCausedError;

private:
    QList<CumUserGroup *> p_rqvlUserGroups;
    long userId;


protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETUSERGROUPMEMBERLIST_H


