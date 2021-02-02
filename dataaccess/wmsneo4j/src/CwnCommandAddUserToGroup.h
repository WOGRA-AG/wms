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

#endif // CWNCOMMANDADDUSERTOGROUP_H
