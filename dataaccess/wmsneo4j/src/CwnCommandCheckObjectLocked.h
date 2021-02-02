#ifndef CWNCOMMANDOBJECTLOCKED_H
#define CWNCOMMANDOBJECTLOCKED_H

#include "CwnCommandBase.h"

class CwnCommandCheckObjectLocked : public CwnCommandBase
{

private:
    long m_lObjectId;
    long m_lSessionId;

public:
    CwnCommandCheckObjectLocked(long p_lObjectId, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckObjectLocked();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDOBJECTLOCKED_H
