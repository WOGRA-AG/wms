#ifndef CWNCOMMANDLOCKMETHOD_H
#define CWNCOMMANDLOCKMETHOD_H

#include "CwnCommandBase.h"

class CwnCommandLockMethod : public CwnCommandBase
{

private:
    long m_lSessionId;
    long m_lMethodId;
    QString createQuery();

public:
     CwnCommandLockMethod(long p_lSessionId, long p_lMethodId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandLockMethod();
     QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDLOCKMETHOD_H
