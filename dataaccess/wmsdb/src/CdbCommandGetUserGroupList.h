#ifndef CDBCOMMANDGETUSERGROUPLIST_H
#define CDBCOMMANDGETUSERGROUPLIST_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandGetUserGroupList : public CdbAbstractCommand
{
private:
    QLinkedList<CumUserGroup*> m_qllUserGroups;
    QString m_qstrSchemeUri;
public:
    CdbCommandGetUserGroupList(CdbDataAccess* p_pDataAccess, QString p_qstrSchemeUri);
    virtual ~CdbCommandGetUserGroupList();
    QLinkedList<CumUserGroup*> GetResult();

protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETUSERGROUPLIST_H
