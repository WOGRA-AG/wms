#ifndef CWNCOMMANDGETNEWCLASSID_H
#define CWNCOMMANDGETNEWCLASSID_H

#include "CwnCommandBase.h"
#include <QVariant>
#include <QString>

class CwnCommandGetNewClassId : public CwnCommandBase
{
private:
   qint64 m_lSchemeId;
   qint64 m_lSessionId;

public:
    CwnCommandGetNewClassId(qint64 p_lSessionId,qint64 p_lSchemeId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewClassId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDGETNEWCLASSID_H
