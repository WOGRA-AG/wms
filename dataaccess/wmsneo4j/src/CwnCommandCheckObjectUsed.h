#ifndef CWNCOMMANDCHECKOBJECTUSED_H
#define CWNCOMMANDCHECKOBJECTUSED_H

#include "CwnCommandBase.h"

class CwnCommandCheckObjectUsed : public CwnCommandBase
{
private:
    long m_lObjectId;
    long m_lContainerId;

public:
    CwnCommandCheckObjectUsed(long p_lObjectId, long p_lContainerId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckObjectUsed();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCHECKOBJECTUSED_H
