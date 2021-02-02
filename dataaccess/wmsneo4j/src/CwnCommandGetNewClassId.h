#ifndef CWNCOMMANDGETNEWCLASSID_H
#define CWNCOMMANDGETNEWCLASSID_H

#include "CwnCommandBase.h"
#include <QVariant>
#include <QString>

class CwnCommandGetNewClassId : public CwnCommandBase
{
private:
    long m_lSchemeId;
    long m_lSessionId;

public:
    CwnCommandGetNewClassId(long p_lSessionId, long p_lSchemeId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewClassId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETNEWCLASSID_H
