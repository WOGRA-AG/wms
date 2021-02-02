#ifndef CWNCOMMANDGETUSERGROUPLIST_H
#define CWNCOMMANDGETUSERGROUPLIST_H

#include "CwnCommandBase.h"
#include "CumUserGroup.h"

#include <QVariant>
#include <QString>
#include <QLinkedList>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandGetUserGroupList : public CwnCommandBase
{
public:
    CwnCommandGetUserGroupList(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandGetUserGroupList();
    QLinkedList<CumUserGroup *> getResult();

    QString createQuery();
    QString queryCausedError;

private:
    QLinkedList<CumUserGroup *> p_rqvlUserGroups;


protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETUSERGROUPLIST_H

