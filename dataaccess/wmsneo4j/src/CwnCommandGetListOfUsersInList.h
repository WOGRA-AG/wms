#ifndef CWNCOMMANDGETLISTOFUSERSINLIST_H
#define CWNCOMMANDGETLISTOFUSERSINLIST_H

#include "CwnCommandBase.h"
#include "CumUser.h"

#include <QVariant>
#include <QString>
#include <QList>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandGetListOfUsersInList : public CwnCommandBase
{
public:
    CwnCommandGetListOfUsersInList(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandGetListOfUsersInList();
    QList<CumUser*> getResult();

    void setGroupId(qint64 groupId);
   qint64 getGroupId();

    QString createQuery();
    QString queryCausedError;

private:
    QList<CumUser *> p_qvlUsers;
   qint64 groupId;


protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETLISTOFUSERSINLIST_H
