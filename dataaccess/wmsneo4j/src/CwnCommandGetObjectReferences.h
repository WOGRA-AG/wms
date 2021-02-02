#ifndef CWNCOMMANDGETOBJECTREFERENCES_H
#define CWNCOMMANDGETOBJECTREFERENCES_H

#include "CwnCommandBase.h"

class CwnCommandGetObjectReferences : public CwnCommandBase
{
private:
    long m_lContainerId;
    long m_lObjectId;
    QMap<long, long> m_qmReferences;
    QString createQuery();

public:
    CwnCommandGetObjectReferences(long p_lContainerId, long p_lObjectId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetObjectReferences();

    QMap<long, long> GetResult();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant &Ret);
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETOBJECTREFERENCES_H
