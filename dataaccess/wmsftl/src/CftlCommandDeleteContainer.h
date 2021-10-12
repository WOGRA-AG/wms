#ifndef CDBCOMMANDDELETECONTAINER_H
#define CDBCOMMANDDELETECONTAINER_H

#include "CftlAbstractTransactionalCommand.h"


class CftlCommandDeleteContainer : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lContainerId;
public:
    CftlCommandDeleteContainer(qint64 p_lContainerId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteContainer();

protected:
    bool CheckValid();
    virtual const CdmClass *GetClassFromContainerId(qint64 p_lId);
    int Execute();
};

#endif // CDBCOMMANDDELETECONTAINER_H
