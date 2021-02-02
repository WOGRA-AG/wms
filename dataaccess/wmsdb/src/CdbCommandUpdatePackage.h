#ifndef CDBCOMMANDUPDATEPACKAGE_H
#define CDBCOMMANDUPDATEPACKAGE_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;
class CdmPackage;

class CdbCommandUpdatePackage : public CdbAbstractCommandTransactional
{
private:
    CdmPackage* m_pPackage;

public:
    CdbCommandUpdatePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess);
    ~CdbCommandUpdatePackage();

protected:
    int Execute();
    virtual bool CheckValid();

};

#endif // CDBCOMMANDUPDATEPACKAGE_H
