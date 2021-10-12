#ifndef CWNCOMMANDCHECKOBJECTUSED_H
#define CWNCOMMANDCHECKOBJECTUSED_H

#include "CwnCommandBase.h"

class CwnCommandCheckObjectUsed : public CwnCommandBase
{
private:
   qint64 m_lObjectId;
   qint64 m_lContainerId;

public:
    CwnCommandCheckObjectUsed(qint64 p_lObjectId,qint64 p_lContainerId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckObjectUsed();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCHECKOBJECTUSED_H
