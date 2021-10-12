#ifndef CWNCOMMANDLOCKMETHOD_H
#define CWNCOMMANDLOCKMETHOD_H

#include "CwnCommandBase.h"

class CwnCommandLockMethod : public CwnCommandBase
{

private:
   qint64 m_lSessionId;
   qint64 m_lMethodId;
    QString createQuery();

public:
     CwnCommandLockMethod(qint64 p_lSessionId,qint64 p_lMethodId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandLockMethod();
     QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDLOCKMETHOD_H
