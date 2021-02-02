#ifndef CWNCOMMANDDELETEOBJECT_H
#define CWNCOMMANDDELETEOBJECT_H

// Own Includes
#include "CwnCommandBase.h"


class CwnCommandDeleteObject : public CwnCommandBase
{
private:
    long m_lObjectId;
    long m_lSessionId;

public:
    CwnCommandDeleteObject(long p_lObjectId, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteObject();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEOBJECT_H
