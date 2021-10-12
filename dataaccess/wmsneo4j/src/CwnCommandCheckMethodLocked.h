#ifndef CWNCOMMANDMETHODLOCKED_H
#define CWNCOMMANDMETHODLOCKED_H

#include "CwnCommandBase.h"

class CwnCommandCheckMethodLocked : public CwnCommandBase
{

private:
   qint64 m_lMethodId;
   qint64 m_lSessionId;

public:
    CwnCommandCheckMethodLocked(qint64 p_lMethodId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckMethodLocked();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDMETHODLOCKED_H
