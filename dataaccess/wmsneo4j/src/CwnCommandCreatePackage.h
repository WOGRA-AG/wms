#ifndef CWNCOMMANDCREATEPACKAGE_H
#define CWNCOMMANDCREATEPACKAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"
#include "CwnHelper.h"

// Forwards
class CwnDataAccess;
class CdmPackage;

class CwnCommandCreatePackage : public CwnCommandBase
{
private:
    CdmPackage* m_pPackage;
public:
    CwnCommandCreatePackage(CdmPackage* p_pPackage, CwnDataAccess* p_pDataAccess);
    ~CwnCommandCreatePackage();
    QString createQuery();
    QString queryCausedError;
protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCREATEPACKAGE_H

