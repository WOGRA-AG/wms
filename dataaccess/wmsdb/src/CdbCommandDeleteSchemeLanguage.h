#ifndef CDCOMMANDDELETESCHEMELANGUAGE_H
#define CDCOMMANDDELETESCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandDeleteSchemeLanguage : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lSchemeId;
   qint64 m_lLanguage;

public:
    CdbCommandDeleteSchemeLanguage(qint64 p_lSchemeId, int p_lLanguage, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDCOMMANDDELETESCHEMELANGUAGE_H
