#ifndef CWNCOMMANDFINDUSERGROUPBYID_H
#define CWNCOMMANDFINDUSERGROUPBYID_H

#include "CwnCommandFindUserGroupById.h"

//Own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnUserManager;
class CumUserGroup;
class CwnConfiguration;

class CwnCommandFindUserGroupById : public CwnCommandBase
{
private:
    int m_iGroupId;
    CumUserGroup* m_pGroup;
    QVariantList m_dataList;
public:
    CwnCommandFindUserGroupById(int p_iGroupId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandFindUserGroupById();

    QString queryCausedError;
    QString createQuery();
    CumUserGroup* GetResult();
protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();
};

#endif // CWNCOMMANDFINDUSERGROUPBYID_H
