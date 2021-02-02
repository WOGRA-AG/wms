#ifndef CDBCOMMANDADDSCHEMELANGUAGE_H
#define CDBCOMMANDADDSCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandAddSchemeLanguage : public CdbAbstractCommandTransactional
{
private:
    long m_lSchemeId;
    QString m_qstrLanguage;
public:
    CdbCommandAddSchemeLanguage(long p_lSchemeId, QString p_qstrLanguage, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandAddSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDADDSCHEMELANGUAGE_H
