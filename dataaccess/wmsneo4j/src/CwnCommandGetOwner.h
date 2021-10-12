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
   qint64 m_lContainerId;
   qint64 m_lObjectId;
   qint64 m_lOwnerContainerId;
   qint64 m_lOwnerObjectId;

public:
    CwnCommandGetOwner(qint64 p_lContainerId,qint64 p_lObjectId, CwnDataAccess *p_pDataAccess);
    virtual ~CwnCommandGetOwner();

    QString createQueryForFindObjectOwner();
    QString createQueryForFindContainerOwner();


   qint64 GetOwnerObjectId();
   qint64 GetOwnerContainerId();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant &Ret);
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDGETOWNER_H
