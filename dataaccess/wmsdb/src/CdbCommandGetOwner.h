#ifndef CDBCOMMANDGETOWNER_H
#define CDBCOMMANDGETOWNER_H

#include "CdbAbstractCommand.h"

class CdbCommandGetOwner : public CdbAbstractCommand
{
private:
   qint64 m_lContainerId;
   qint64 m_lObjectId;
   qint64 m_lOwnerContainerId;
   qint64 m_lOwnerObjectId;

   qint64 FindContainerOwner();
   qint64 FindObjectOwner();
public:
    CdbCommandGetOwner(qint64 p_lContainerId,qint64 p_lObjectId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandGetOwner();

   qint64 GetOwnerObjectId();
   qint64 GetOwnerContainerId();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOWNER_H
