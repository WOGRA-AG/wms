#ifndef CWNCOMMANDDELETEOBJECTCONTAINER_H
#define CWNCOMMANDDELETEOBJECTCONTAINER_H

// Own Includes
#include "CwnCommandBase.h"


class CwnCommandDeleteContainer : public CwnCommandBase
{
private:
   qint64 m_lContainerId;

public:
    CwnCommandDeleteContainer(qint64 p_lContainerId, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteContainer();
    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEOBJECTCONTAINER_H
