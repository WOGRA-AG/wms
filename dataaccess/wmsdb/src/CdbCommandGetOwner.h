#ifndef CDBCOMMANDGETOWNER_H
#define CDBCOMMANDGETOWNER_H

#include "CdbAbstractCommand.h"

class CdbCommandGetOwner : public CdbAbstractCommand
{
private:
    long m_lContainerId;
    long m_lObjectId;
    long m_lOwnerContainerId;
    long m_lOwnerObjectId;

    long FindContainerOwner();
    long FindObjectOwner();
public:
    CdbCommandGetOwner(long p_lContainerId, long p_lObjectId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetOwner();

    long GetOwnerObjectId();
    long GetOwnerContainerId();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOWNER_H
