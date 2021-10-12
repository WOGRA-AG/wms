#ifndef CWNCOMMANDADDUSERTOGROUP_H
#define CWNCOMMANDADDUSERTOGROUP_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QVariantList>
#include <QString>

// Forwards
class CwnConfiguration;

class CwnCommandAddUserToGroup : public CwnCommandBase
{
public:
    CwnCommandAddUserToGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandAddUserToGroup();

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

#endif // CWNCOMMANDADDUSERTOGROUP_H
