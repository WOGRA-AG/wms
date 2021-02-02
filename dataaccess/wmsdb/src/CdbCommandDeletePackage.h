#ifndef CDBCOMMANDDELETEPACKAGE_H
#define CDBCOMMANDDELETEPACKAGE_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;
class CdmPackage;

class CdbCommandDeletePackage : public CdbAbstractCommandTransactional
{
private:
    CdmPackage* m_pPackage;

    void DeletePackageChildren(QList<CdmPackage *> &p_rqlChildren);
public:
    CdbCommandDeletePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeletePackage();

protected:
    virtual bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDDELETEPACKAGE_H
