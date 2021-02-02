#ifndef CWNCOMMANDFINDUSERGROUPBYNAME_H
#define CWNCOMMANDFINDUSERGROUPBYNAME_H

#include "CwnCommandFindUserGroupByName.h"

//Own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnUserManager;
class CumUserGroup;
class CwnConfiguration;

class CwnCommandFindUserGroupByName : public CwnCommandBase
{
private:
    QString m_qstrGroupName;
    CumUserGroup* m_pGroup;
    QVariantList m_dataList;
public:
    CwnCommandFindUserGroupByName(QString p_qstrName, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandFindUserGroupByName();

    QString queryCausedError;
    QString createQuery();
    CumUserGroup* GetResult();
protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();
};

#endif // CWNCOMMANDFINDUSERGROUPBYNAME_H
