#ifndef CDBCOMMANDGETNEWCONTAINERID_H
#define CDBCOMMANDGETNEWCONTAINERID_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"


class CftlCommandGetNewContainerId : public CftlAbstractTransactionalCommand
{
private:
    long m_lClassId;

public:
    CftlCommandGetNewContainerId(long p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetNewContainerId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWCONTAINERID_H
