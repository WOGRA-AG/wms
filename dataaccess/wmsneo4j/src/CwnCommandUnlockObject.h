#ifndef CWNCOMMANDUNLOCKOBJECT_H
#define CWNCOMMANDUNLOCKOBJECT_H

#include "CwnCommandBase.h"

class CwnCommandUnlockObject : public CwnCommandBase
{

private:
   qint64 m_lSessionId;
   qint64 m_lObjectId;

public:
    CwnCommandUnlockObject(qint64 p_lSessionId,qint64 p_lObjectId,CwnDataAccess* p_pDataAccess);
    ~CwnCommandUnlockObject();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDUNLOCKOBJECT_H
