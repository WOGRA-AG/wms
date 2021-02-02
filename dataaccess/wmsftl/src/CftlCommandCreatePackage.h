#ifndef CDBCOMMANDCREATEPACKAGE_H
#define CDBCOMMANDCREATEPACKAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;
class CdmPackage;

class CftlCommandCreatePackage : public CftlAbstractTransactionalCommand
{
private:
    CdmPackage* m_pPackage;

public:
    CftlCommandCreatePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess);
    ~CftlCommandCreatePackage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCREATEPACKAGE_H
