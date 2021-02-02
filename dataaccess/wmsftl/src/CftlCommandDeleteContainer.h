#ifndef CDBCOMMANDDELETECONTAINER_H
#define CDBCOMMANDDELETECONTAINER_H

#include "CftlAbstractTransactionalCommand.h"


class CftlCommandDeleteContainer : public CftlAbstractTransactionalCommand
{
private:
    long m_lContainerId;
public:
    CftlCommandDeleteContainer(long p_lContainerId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteContainer();

protected:
    bool CheckValid();
    virtual const CdmClass *GetClassFromContainerId(long p_lId);
    int Execute();
};

#endif // CDBCOMMANDDELETECONTAINER_H
