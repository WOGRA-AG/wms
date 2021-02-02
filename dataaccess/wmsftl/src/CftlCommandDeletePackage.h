#ifndef CDBCOMMANDDELETEPACKAGE_H
#define CDBCOMMANDDELETEPACKAGE_H

// Own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;
class CdmPackage;

class CftlCommandDeletePackage : public CftlAbstractTransactionalCommand
{
private:
    CdmPackage* m_pPackage;

    void DeletePackageChildren(QList<CdmPackage *> &p_rqlChildren);
public:
    CftlCommandDeletePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeletePackage();

protected:
    virtual bool CheckValid();
    int Execute();

};

#endif // CDBCOMMANDDELETEPACKAGE_H
