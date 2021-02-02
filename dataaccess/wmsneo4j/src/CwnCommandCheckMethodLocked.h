#ifndef CWNCOMMANDMETHODLOCKED_H
#define CWNCOMMANDMETHODLOCKED_H

#include "CwnCommandBase.h"

class CwnCommandCheckMethodLocked : public CwnCommandBase
{

private:
    long m_lMethodId;
    long m_lSessionId;

public:
    CwnCommandCheckMethodLocked(long p_lMethodId, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckMethodLocked();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDMETHODLOCKED_H
