#ifndef CWNCOMMANDCOUNTOBJECTSONDB_H
#define CWNCOMMANDCOUNTOBJECTSONDB_H

#include "CwnCommandBase.h"
#include "CdmObjectContainer.h"

class CwnCommandCountObjectsOnDb : public CwnCommandBase
{
private:
    CdmObjectContainer* m_rpContainer;

public:
    CwnCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCountObjectsOnDb();
    QString createQuery();
    QString queryCausedError;
protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCOUNTOBJECTSONDB_H


