#ifndef CDCOMMANDDELETESCHEMELANGUAGE_H
#define CDCOMMANDDELETESCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandDeleteSchemeLanguage : public CdbAbstractCommandTransactional
{
private:
    long m_lSchemeId;
    long m_lLanguage;

public:
    CdbCommandDeleteSchemeLanguage(long p_lSchemeId, int p_lLanguage, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDCOMMANDDELETESCHEMELANGUAGE_H
