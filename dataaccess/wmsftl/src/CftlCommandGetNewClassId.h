#ifndef CDBCOMMANDGETNEWCLASSID_H
#define CDBCOMMANDGETNEWCLASSID_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandGetNewClassId : public CftlAbstractTransactionalCommand
{
private:
    long m_lSchemeId;
    long m_lSessionId;

public:
    CftlCommandGetNewClassId(long p_lSessionId, long p_lSchemeId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetNewClassId();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETNEWCLASSID_H
