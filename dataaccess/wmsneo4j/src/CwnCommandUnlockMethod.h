#ifndef CWNCOMMANDUNLOCKMETHOD_H
#define CWNCOMMANDUNLOCKMETHOD_H

#include "CwnCommandBase.h"

class CwnCommandUnlockMethod : public CwnCommandBase
{

private:
   qint64 m_lSessionId;
   qint64 m_lMethodId;

public:
    CwnCommandUnlockMethod(qint64 p_lSessionId,qint64 p_lMethodId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandUnlockMethod();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDUNLOCKMETHOD_H
