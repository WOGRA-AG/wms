#ifndef CDBCOMMANDGETNEWCONTAINERID_H
#define CDBCOMMANDGETNEWCONTAINERID_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"


class CftlCommandGetNewContainerId : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lClassId;

public:
    CftlCommandGetNewContainerId(qint64 p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetNewContainerId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWCONTAINERID_H
