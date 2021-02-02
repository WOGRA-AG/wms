#ifndef CWNGETNEWCONTAINERID_H
#define CWNGETNEWCONTAINERID_H

// Own Includes
#include "CwnCommandBase.h"

class CwnCommandGetNewContainerId : public CwnCommandBase
{
private:
    long m_lClassId;
    long m_lSessionId;

public:
    CwnCommandGetNewContainerId(long p_lClassId, long p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewContainerId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();

};

#endif // CWNGETNEWCONTAINERID_H
