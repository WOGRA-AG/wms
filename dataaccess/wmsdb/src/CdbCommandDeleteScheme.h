#ifndef CDBCOMMANDDELETESCHEME_H
#define CDBCOMMANDDELETESCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandDeleteScheme : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrSchemeName;

    long GetSchemeId();
    void DeleteLanguages(long p_lSchemeId);
public:
    CdbCommandDeleteScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETESCHEME_H
