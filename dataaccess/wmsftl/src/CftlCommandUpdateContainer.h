#ifndef CDBCOMMANDUPDATECONTAINER_H
#define CDBCOMMANDUPDATECONTAINER_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandUpdateContainer : public CftlAbstractTransactionalCommand
{
private:
    CdmObjectContainer* m_rpObjectContainer;

    long DeleteObjects(CdmObjectContainer *p_pContainer, QLinkedList<CdmObject *> &p_rqlObjects);
    long UpdateObjects(CdmObjectContainer *p_pContainer, QLinkedList<CdmObject *> &p_rqlObjects);
    long UpdateRights(CdmObjectContainer *&p_pContainer);
public:
    CftlCommandUpdateContainer(CdmObjectContainer*& p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUpdateContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATECONTAINER_H
