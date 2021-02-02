#ifndef CWNCOMMANDUNLOCKOBJECT_H
#define CWNCOMMANDUNLOCKOBJECT_H

#include "CwnCommandBase.h"

class CwnCommandUnlockObject : public CwnCommandBase
{

private:
    long m_lSessionId;
    long m_lObjectId;

public:
    CwnCommandUnlockObject(long p_lSessionId, long p_lObjectId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandUnlockObject();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDUNLOCKOBJECT_H
