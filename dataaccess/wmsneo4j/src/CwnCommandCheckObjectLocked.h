#ifndef CWNCOMMANDOBJECTLOCKED_H
#define CWNCOMMANDOBJECTLOCKED_H

#include "CwnCommandBase.h"

class CwnCommandCheckObjectLocked : public CwnCommandBase
{

private:
   qint64 m_lObjectId;
   qint64 m_lSessionId;

public:
    CwnCommandCheckObjectLocked(qint64 p_lObjectId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckObjectLocked();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDOBJECTLOCKED_H
