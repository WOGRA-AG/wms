#ifndef CDBCOMMANDGETNEWOBJECTID_H
#define CDBCOMMANDGETNEWOBJECTID_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandGetNewObjectId : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lContainerId;
   qint64 m_lSessionId;
public:
    CdbCommandGetNewObjectId(qint64 p_lContainerId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewObjectId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWOBJECTID_H
