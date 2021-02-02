#ifndef CDBCOMMANDGETGROUPUSERLIST_H
#define CDBCOMMANDGETGROUPUSERLIST_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandGetGroupUserList : public CdbAbstractCommand
{
private:
    long m_lGroupId;
    QLinkedList<CumUser*> m_qllUserList;

    int ReadAllUsers();
    int ReadGroupUsers();
public:
    CdbCommandGetGroupUserList(long p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetGroupUserList();
    QLinkedList<CumUser*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPUSERLIST_H
