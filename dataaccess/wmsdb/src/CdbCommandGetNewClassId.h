#ifndef CDBCOMMANDGETNEWCLASSID_H
#define CDBCOMMANDGETNEWCLASSID_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandGetNewClassId : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lSchemeId;
   qint64 m_lSessionId;

public:
    CdbCommandGetNewClassId(qint64 p_lSessionId,qint64 p_lSchemeId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetNewClassId();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETNEWCLASSID_H
