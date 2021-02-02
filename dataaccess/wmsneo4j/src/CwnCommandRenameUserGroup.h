#ifndef CWNCOMMANDRENAMEUSERGROUP_H
#define CWNCOMMANDRENAMEUSERGROUP_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandRenameUserGroup : public CwnCommandBase
{
public:
    CwnCommandRenameUserGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandRenameUserGroup();

    void setGroupId(long groupid);
    long getGroupId();

    void setGroupname(QString groupname);
    QString getGroupname();
    QString queryCausedError;

private:
    long groupid;
    QString groupname;
    QString createQuery();

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDRENAMEUSERGROUP_H
