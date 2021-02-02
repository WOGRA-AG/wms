#ifndef CWNCOMMANDDELETECLASSCONTAINER_H
#define CWNCOMMANDDELETECLASSCONTAINER_H

// Own Includes
#include "CwnCommandBase.h"


class CwnCommandDeleteClass : public CwnCommandBase
{
private:
    long m_lClassId;

public:
    CwnCommandDeleteClass(long p_lContainerId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteClass();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETECLASSCONTAINER_H
