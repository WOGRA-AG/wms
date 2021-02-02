#ifndef CWICOMMANDGETGROUPUSERLIST_H
#define CWICOMMANDGETGROUPUSERLIST_H

#include"CwiAbstractCommand.h"
#include "CumUserManager.h"

class CwiCommandGetGroupUserList : public CwiAbstractCommand
{
private:
    CwmscomData* m_rpData;
    QLinkedList<CumUser*> m_qlUserList;
    QVariantList m_qlUserListToVariant;
    CumUserManager* pCumUserManager;

    long ReadAllUsers();
    QVariantList GetResultToVariant(QLinkedList<CumUser*> ql_userList);

public:
    CwiCommandGetGroupUserList(CwmscomData* p_pData);
    ~CwiCommandGetGroupUserList();
    virtual void Execute();
    QLinkedList<CumUser*> GetResult();
};

#endif // CWICOMMANDGETGROUPUSERLIST_H
