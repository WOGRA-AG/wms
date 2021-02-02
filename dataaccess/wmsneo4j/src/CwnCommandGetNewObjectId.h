#ifndef CWNCOMMANDGETNEWOBJECTID_H
#define CWNCOMMANDGETNEWOBJECTID_H

// Own Includes
#include "CwnCommandBase.h"

class CwnCommandGetNewObjectId : public CwnCommandBase
{

private:
    long m_lContainerId;
    long m_lSessionId;

public:
    CwnCommandGetNewObjectId(long p_lContainerId, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewObjectId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();

};

#endif // CWNCOMMANDGETNEWOBJECTID_H
