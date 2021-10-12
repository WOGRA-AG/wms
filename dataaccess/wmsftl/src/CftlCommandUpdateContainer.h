#ifndef CDBCOMMANDUPDATECONTAINER_H
#define CDBCOMMANDUPDATECONTAINER_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandUpdateContainer : public CftlAbstractTransactionalCommand
{
private:
    CdmObjectContainer* m_rpObjectContainer;

   qint64 DeleteObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects);
   qint64 UpdateObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects);
   qint64 UpdateRights(CdmObjectContainer *&p_pContainer);
public:
    CftlCommandUpdateContainer(CdmObjectContainer*& p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUpdateContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATECONTAINER_H
