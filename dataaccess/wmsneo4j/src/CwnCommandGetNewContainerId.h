#ifndef CWNGETNEWCONTAINERID_H
#define CWNGETNEWCONTAINERID_H

// Own Includes
#include "CwnCommandBase.h"

class CwnCommandGetNewContainerId : public CwnCommandBase
{
private:
   qint64 m_lClassId;
   qint64 m_lSessionId;

public:
    CwnCommandGetNewContainerId(qint64 p_lClassId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetNewContainerId();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    bool CheckValid();

};

#endif // CWNGETNEWCONTAINERID_H
