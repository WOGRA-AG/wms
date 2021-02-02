#ifndef CDBCOMMANDCREATEPACKAGE_H
#define CDBCOMMANDCREATEPACKAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;
class CdmPackage;

class CdbCommandCreatePackage : public CdbAbstractCommandTransactional
{
private:
    CdmPackage* m_pPackage;

public:
    CdbCommandCreatePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess);
    ~CdbCommandCreatePackage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCREATEPACKAGE_H
