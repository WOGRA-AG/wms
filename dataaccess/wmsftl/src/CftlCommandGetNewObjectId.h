#ifndef CDBCOMMANDGETNEWOBJECTID_H
#define CDBCOMMANDGETNEWOBJECTID_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

//forwards
class CdmObjectContainer;

class CftlCommandGetNewObjectId : public CftlAbstractTransactionalCommand
{
private:
    const CdmObjectContainer* m_rpContainer;
public:
    CftlCommandGetNewObjectId(const CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetNewObjectId();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETNEWOBJECTID_H
