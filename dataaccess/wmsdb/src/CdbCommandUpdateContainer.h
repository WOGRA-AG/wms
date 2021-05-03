#ifndef CDBCOMMANDUPDATECONTAINER_H
#define CDBCOMMANDUPDATECONTAINER_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandUpdateContainer : public CdbAbstractCommandTransactional
{
private:
    CdmObjectContainer* m_rpObjectContainer;
    long m_lSessionId;

    long DeleteObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects, long p_lSessionId);
    long UpdateObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects, long p_lSessionId);
    long UpdateRights(CdmObjectContainer *&p_pContainer);
public:
    CdbCommandUpdateContainer(CdmObjectContainer*& p_pContainer, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateContainer();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATECONTAINER_H
