#ifndef CWNCOMMANDCREATEUSERGROUP_H
#define CWNCOMMANDCREATEUSERGROUP_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;


class CwnCommandCreateUserGroup : public CwnCommandBase
{
public:
    CwnCommandCreateUserGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandCreateUserGroup();

    void setGroupName(QString groupName);
    QString getGroupName();
    QString createQuery();
    QString queryCausedError;

private:
    QString groupName;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCREATEUSERGROUP_H
