#ifndef CDBCOMMANDGETGROUPSOFUSER_H
#define CDBCOMMANDGETGROUPSOFUSER_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandGetGroupsOfUser : public CftlAbstractCommand
{
private:
   qint64 m_lUserId;
    QList<CumUserGroup*> m_qllGroups;

public:
    CftlCommandGetGroupsOfUser(qint64 p_lUser, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetGroupsOfUser();
    QList<CumUserGroup*> GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDGETGROUPSOFUSER_H
