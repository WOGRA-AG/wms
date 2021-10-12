#ifndef CDBCOMMANDGETNEWCONTAINERID_H
#define CDBCOMMANDGETNEWCONTAINERID_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandGetNewContainerId : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lClassId;
   qint64 m_lSessionId;

public:
    CdbCommandGetNewContainerId(qint64 p_lClassId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewContainerId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWCONTAINERID_H
