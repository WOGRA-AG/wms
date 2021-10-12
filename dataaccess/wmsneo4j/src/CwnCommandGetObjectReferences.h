#ifndef CWNCOMMANDGETOBJECTREFERENCES_H
#define CWNCOMMANDGETOBJECTREFERENCES_H

#include "CwnCommandBase.h"

class CwnCommandGetObjectReferences : public CwnCommandBase
{
private:
   qint64 m_lContainerId;
   qint64 m_lObjectId;
    QMap<qint64,qint64> m_qmReferences;
    QString createQuery();

public:
    CwnCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetObjectReferences();

    QMap<qint64,qint64> GetResult();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant &Ret);
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETOBJECTREFERENCES_H
