#ifndef CDBCOMMANDGETNEWCLASSID_H
#define CDBCOMMANDGETNEWCLASSID_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandGetNewClassId : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lSchemeId;
   qint64 m_lSessionId;

public:
    CftlCommandGetNewClassId(qint64 p_lSessionId,qint64 p_lSchemeId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetNewClassId();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDGETNEWCLASSID_H
