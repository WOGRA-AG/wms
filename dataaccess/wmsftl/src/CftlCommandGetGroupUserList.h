#ifndef CDBCOMMANDGETGROUPUSERLIST_H
#define CDBCOMMANDGETGROUPUSERLIST_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandGetGroupUserList : public CftlAbstractCommand
{
private:
    long m_lGroupId;
    QLinkedList<CumUser*> m_qllUserList;

    int ReadAllUsers();
    int ReadGroupUsers();
    QString CreateSelectPart();
    CumUser *CreateUserObjectFromQuery(QSqlQuery &p_rQuery);
public:
    CftlCommandGetGroupUserList(long p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetGroupUserList();
    QLinkedList<CumUser*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPUSERLIST_H
