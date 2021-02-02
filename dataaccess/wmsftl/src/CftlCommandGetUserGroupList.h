#ifndef CDBCOMMANDGETUSERGROUPLIST_H
#define CDBCOMMANDGETUSERGROUPLIST_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandGetUserGroupList : public CftlAbstractCommand
{
private:
    QLinkedList<CumUserGroup*> m_qllUserGroups;
public:
    CftlCommandGetUserGroupList(CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetUserGroupList();
    QLinkedList<CumUserGroup*> GetResult();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETUSERGROUPLIST_H
