#ifndef CWNCOMMANDREMOVEUSERFROMGROUP_H
#define CWNCOMMANDREMOVEUSERFROMGROUP_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnConfiguration;

class CwnCommandRemoveUserFromGroup : public CwnCommandBase
{
public:
    CwnCommandRemoveUserFromGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandRemoveUserFromGroup();

    void setGroupId(long groupId);
    long getGroupId();

    void setUserId(long userId);
    long getUserId();

    QString createQuery();
    QString queryCausedError;

private:
    long groupId;
    long userId;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDREMOVEUSERFROMGROUP_H

