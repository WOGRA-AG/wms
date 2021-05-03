#ifndef CWICOMMANDGETGROUPUSERLIST_H
#define CWICOMMANDGETGROUPUSERLIST_H

#include"CwiAbstractCommand.h"
#include "CumUserManager.h"

class CwiCommandGetGroupUserList : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;
    QList<CumUser*> m_qlUserList;
    QVariantList m_qlUserListToVariant;
    CumUserManager* pCumUserManager;

    long ReadAllUsers();
    QVariantList GetResultToVariant(QList<CumUser*> ql_userList);

public:
    CwiCommandGetGroupUserList(CwmscomData* p_pData);
    ~CwiCommandGetGroupUserList();
    virtual void Execute();
    QList<CumUser*> GetResult();
};

#endif // CWICOMMANDGETGROUPUSERLIST_H
