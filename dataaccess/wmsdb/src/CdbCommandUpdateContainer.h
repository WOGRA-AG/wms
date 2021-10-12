#ifndef CDBCOMMANDUPDATECONTAINER_H
#define CDBCOMMANDUPDATECONTAINER_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandUpdateContainer : public CdbAbstractCommandTransactional
{
private:
    CdmObjectContainer* m_rpObjectContainer;
   qint64 m_lSessionId;

   qint64 DeleteObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects,qint64 p_lSessionId);
   qint64 UpdateObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects,qint64 p_lSessionId);
   qint64 UpdateRights(CdmObjectContainer *&p_pContainer);
public:
    CdbCommandUpdateContainer(CdmObjectContainer*& p_pContainer,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATECONTAINER_H
