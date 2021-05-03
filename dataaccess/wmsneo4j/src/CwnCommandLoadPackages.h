#ifndef CWNCOMMANDLOADPACKAGES_H
#define CWNCOMMANDLOADPACKAGES_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>
#include <QList>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;
class CdmClassManager;

class CwnCommandLoadPackages : public CwnCommandBase
{

public:
    CwnCommandLoadPackages(CdmClassManager* p_pClassManager, CwnDataAccess* p_pDataAccess, QString schema);
    CdmClassManager* m_rpClassManager;
    QString schema;
    CdmPackage* packagetemp;

    bool ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages);
    void ResolvePackages(QList<CdmPackage *> &p_rqlUnresolvedPackages);

    virtual ~CwnCommandLoadPackages();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOADPACKAGES_H
