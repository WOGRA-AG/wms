#ifndef CWNCOMMANDUPDATECONTAINER_H
#define CWNCOMMANDUPDATECONTAINER_H

#include "CwnCommandBase.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

class CwnCommandUpdateContainer : public CwnCommandBase
{
private:
    CdmObjectContainer* m_rpObjectContainer;
   qint64 m_lSessionId;
    QString payload;

   qint64 DeleteObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects,qint64 p_lSessionId);
   qint64 UpdateObjects(CdmObjectContainer *p_pContainer, QList<CdmObject *> &p_rqlObjects,qint64 p_lSessionId);
    void UpdateRights(CdmObjectContainer *&p_pContainer);

public:
    CwnCommandUpdateContainer(CdmObjectContainer*& p_pContainer,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateContainer();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};


#endif // CWNCOMMANDUPDATECONTAINER_H
