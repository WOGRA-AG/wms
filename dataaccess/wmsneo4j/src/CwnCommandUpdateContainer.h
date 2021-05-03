#ifndef CWNCOMMANDUPDATECONTAINER_H
#define CWNCOMMANDUPDATECONTAINER_H

#include "CwnCommandBase.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

class CwnCommandUpdateContainer : public CwnCommandBase
{
private:
    CdmObjectContainer* m_rpObjectContainer;
    long m_lSessionId;
    QString payload;

    long DeleteObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects, long p_lSessionId);
    long UpdateObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects, long p_lSessionId);
    void UpdateRights(CdmObjectContainer *&p_pContainer);

public:
    CwnCommandUpdateContainer(CdmObjectContainer*& p_pContainer, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateContainer();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};


#endif // CWNCOMMANDUPDATECONTAINER_H
