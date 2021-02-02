#ifndef CWNCOMMANDUPDATEPACKAGE_H
#define CWNCOMMANDUPDATEPACKAGE_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

class CdmPackage;

class CwnCommandUpdatePackage : public CwnCommandBase
{
private:
    CdmPackage* m_pPackage = NULL;
    bool notSupported = false;

public:
    CwnCommandUpdatePackage(CdmPackage* p_pPackage, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdatePackage();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDUPDATEPACKAGE_H
