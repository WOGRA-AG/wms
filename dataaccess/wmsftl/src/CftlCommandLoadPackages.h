#ifndef CDBCOMMANDLOADPACKAGES_H
#define CDBCOMMANDLOADPACKAGES_H

// Own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;
class CdmPackage;
class CdmClassManager;

class CftlCommandLoadPackages : public CftlAbstractCommand
{
private:
    CdmClassManager* m_rpClassManager;
    bool ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages);
    void ResolvePackages(QList<CdmPackage *> &p_rqlUnresolvedPackages);

public:
    CftlCommandLoadPackages(CdmClassManager* p_pClassManager, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLoadPackages();

protected:
    virtual int Execute();
    bool CheckValid();

};

#endif // CDBCOMMANDLOADPACKAGES_H
