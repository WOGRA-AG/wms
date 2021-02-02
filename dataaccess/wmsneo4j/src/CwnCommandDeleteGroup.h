#ifndef CWNCOMMANDDELETEGROUP_H
#define CWNCOMMANDDELETEGROUP_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnConfiguration;

class CwnCommandDeleteGroup : public CwnCommandBase
{
public:
    CwnCommandDeleteGroup(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandDeleteGroup();

    void setGroupId(long groupId);
    long getGroupId();
    QString createQuery();
    QString queryCausedError;

private:
    long groupId;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEGROUP_H
