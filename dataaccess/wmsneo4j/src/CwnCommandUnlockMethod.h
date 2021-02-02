#ifndef CWNCOMMANDUNLOCKMETHOD_H
#define CWNCOMMANDUNLOCKMETHOD_H

#include "CwnCommandBase.h"

class CwnCommandUnlockMethod : public CwnCommandBase
{

private:
    long m_lSessionId;
    long m_lMethodId;

public:
    CwnCommandUnlockMethod(long p_lSessionId, long p_lMethodId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandUnlockMethod();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDUNLOCKMETHOD_H
