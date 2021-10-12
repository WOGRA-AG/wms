#ifndef CDBCOMMANDGETOWNER_H
#define CDBCOMMANDGETOWNER_H

#include "CftlAbstractCommand.h"

class CftlCommandGetOwner : public CftlAbstractCommand
{
private:
    const CdmObjectContainer* m_rpContainer;
    const CdmObject* m_rpObject;
   qint64 m_lOwnerObjectId;
   qint64 m_lOwnerContainerId;
   qint64 FindContainerOwner();
   qint64 FindObjectOwner();
public:
    CftlCommandGetOwner(const CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    CftlCommandGetOwner(const CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetOwner();

   qint64 GetOwnerObjectId();
   qint64 GetOwnerContainerId();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOWNER_H
