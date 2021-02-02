#ifndef CWNCOMMANDGETOWNER_H
#define CWNCOMMANDGETOWNER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnDataAccess;

class CwnCommandGetOwner : public CwnCommandBase
{

private:
    long m_lContainerId;
    long m_lObjectId;
    long m_lOwnerContainerId;
    long m_lOwnerObjectId;

public:
    CwnCommandGetOwner(long p_lContainerId, long p_lObjectId, CwnDataAccess *p_pDataAccess);
    virtual ~CwnCommandGetOwner();

    QString createQueryForFindObjectOwner();
    QString createQueryForFindContainerOwner();


    long GetOwnerObjectId();
    long GetOwnerContainerId();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant &Ret);
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETOWNER_H
