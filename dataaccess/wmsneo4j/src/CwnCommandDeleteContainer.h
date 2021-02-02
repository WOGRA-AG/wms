#ifndef CWNCOMMANDDELETEOBJECTCONTAINER_H
#define CWNCOMMANDDELETEOBJECTCONTAINER_H

// Own Includes
#include "CwnCommandBase.h"


class CwnCommandDeleteContainer : public CwnCommandBase
{
private:
    long m_lContainerId;

public:
    CwnCommandDeleteContainer(long p_lContainerId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteContainer();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEOBJECTCONTAINER_H
