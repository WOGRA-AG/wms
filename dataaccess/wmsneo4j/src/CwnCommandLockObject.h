#ifndef CWNCOMMANDLOCKOBJECT_H
#define CWNCOMMANDLOCKOBJECT_H

#include "CwnCommandBase.h"

class CwnCommandLockObject : public CwnCommandBase
{

private:
    long m_lSessionId;
    long m_lObjectId;
    QString createQuery();

public:
     CwnCommandLockObject(long p_lSessionId, long p_lObjectId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandLockObject();
     QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDLOCKOBJECT_H
