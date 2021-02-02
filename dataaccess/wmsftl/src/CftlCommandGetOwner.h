#ifndef CDBCOMMANDGETOWNER_H
#define CDBCOMMANDGETOWNER_H

#include "CftlAbstractCommand.h"

class CftlCommandGetOwner : public CftlAbstractCommand
{
private:
    const CdmObjectContainer* m_rpContainer;
    const CdmObject* m_rpObject;
    long m_lOwnerObjectId;
    long m_lOwnerContainerId;
    long FindContainerOwner();
    long FindObjectOwner();
public:
    CftlCommandGetOwner(const CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    CftlCommandGetOwner(const CdmObject* p_pObject, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetOwner();

    long GetOwnerObjectId();
    long GetOwnerContainerId();
protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETOWNER_H
