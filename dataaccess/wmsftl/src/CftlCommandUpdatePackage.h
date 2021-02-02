#ifndef CDBCOMMANDUPDATEPACKAGE_H
#define CDBCOMMANDUPDATEPACKAGE_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;
class CdmPackage;

class CftlCommandUpdatePackage : public CftlAbstractTransactionalCommand
{
private:
    CdmPackage* m_pPackage;

public:
    CftlCommandUpdatePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess);
    ~CftlCommandUpdatePackage();

protected:
    int Execute();
    virtual bool CheckValid();

};

#endif // CDBCOMMANDUPDATEPACKAGE_H
