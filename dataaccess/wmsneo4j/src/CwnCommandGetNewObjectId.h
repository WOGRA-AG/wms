#ifndef CWNCOMMANDGETNEWOBJECTID_H
#define CWNCOMMANDGETNEWOBJECTID_H

// Own Includes
#include "CwnCommandBase.h"

class CwnCommandGetNewObjectId : public CwnCommandBase
{

private:
   qint64 m_lContainerId;
   qint64 m_lSessionId;

public:
    CwnCommandGetNewObjectId(qint64 p_lContainerId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewObjectId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();

};

#endif // CWNCOMMANDGETNEWOBJECTID_H
