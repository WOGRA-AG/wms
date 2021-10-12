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

    void setGroupId(qint64 groupId);
   qint64 getGroupId();

    void setUserId(qint64 userId);
   qint64 getUserId();

    QString createQuery();
    QString queryCausedError;

private:
   qint64 groupId;
   qint64 userId;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDREMOVEUSERFROMGROUP_H

