#ifndef CDBCOMMANDLOADPACKAGES_H
#define CDBCOMMANDLOADPACKAGES_H

// Own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;
class CdmPackage;
class CdmClassManager;

class CdbCommandLoadPackages : public CdbAbstractCommand
{
private:
    CdmClassManager* m_rpClassManager;
    bool ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages);
    void ResolvePackages(QList<CdmPackage *> &p_rqlUnresolvedPackages);

public:
    CdbCommandLoadPackages(CdmClassManager* p_pClassManager, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLoadPackages();

protected:
    virtual int Execute();
    bool CheckValid();

};

#endif // CDBCOMMANDLOADPACKAGES_H
