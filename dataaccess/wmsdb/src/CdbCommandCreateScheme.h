#ifndef CDBCOMMANDCREATESCHEME_H
#define CDBCOMMANDCREATESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;
class CdmScheme;

class CdbCommandCreateScheme : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrSchemeName;
    CdmScheme* m_pScheme;

public:
    CdbCommandCreateScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCreateScheme();

    CdmScheme *GetResult();
protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCREATESCHEME_H
