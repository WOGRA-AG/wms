#ifndef CDBCOMMANDGETGROUPUSERLIST_H
#define CDBCOMMANDGETGROUPUSERLIST_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandGetGroupUserList : public CdbAbstractCommand
{
private:
   qint64 m_lGroupId;
    QList<CumUser*> m_qllUserList;

    int ReadAllUsers();
    int ReadGroupUsers();
public:
    CdbCommandGetGroupUserList(qint64 p_lGroup, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetGroupUserList();
    QList<CumUser*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPUSERLIST_H
