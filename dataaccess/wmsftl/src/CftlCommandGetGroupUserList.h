#ifndef CDBCOMMANDGETGROUPUSERLIST_H
#define CDBCOMMANDGETGROUPUSERLIST_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandGetGroupUserList : public CftlAbstractCommand
{
private:
   qint64 m_lGroupId;
    QList<CumUser*> m_qllUserList;

    int ReadAllUsers();
    int ReadGroupUsers();
    QString CreateSelectPart();
    CumUser *CreateUserObjectFromQuery(QSqlQuery &p_rQuery);
public:
    CftlCommandGetGroupUserList(qint64 p_lGroup, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetGroupUserList();
    QList<CumUser*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPUSERLIST_H
