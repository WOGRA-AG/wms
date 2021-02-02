#ifndef CWNCOMMANDDELETEPACKAGE_H
#define CWNCOMMANDDELETEPACKAGE_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CdmPackage;
class CwnConfiguration;

class CwnCommandDeletePackage : public CwnCommandBase
{
public:
    CwnCommandDeletePackage(CdmPackage* p_pPackage, CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandDeletePackage();

    QString createQuery();
    QString queryCausedError;
private:
    CdmPackage* m_pPackage;
    void DeletePackageChildren(QList<CdmPackage *> &p_rqlChildren);

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEPACKAGE_H
