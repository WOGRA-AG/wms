#ifndef CWNCOMMANDLOCKOBJECT_H
#define CWNCOMMANDLOCKOBJECT_H

#include "CwnCommandBase.h"

class CwnCommandLockObject : public CwnCommandBase
{

private:
   qint64 m_lSessionId;
   qint64 m_lObjectId;
    QString createQuery();

public:
     CwnCommandLockObject(qint64 p_lSessionId,qint64 p_lObjectId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandLockObject();
     QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDLOCKOBJECT_H
