#ifndef CWNCOMMANDDELETESCHEMELANGUAGE_H
#define CWNCOMMANDDELETESCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

class CwnCommandDeleteSchemeLanguage : public CwnCommandBase
{
private:
    long m_lSchemeId;
    long m_lLanguage;

public:
    CwnCommandDeleteSchemeLanguage(long p_lSchemeId, int p_lLanguage, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandDeleteSchemeLanguage();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual bool CheckValid();
    int Execute();
};

#endif // CWNCOMMANDDELETESCHEMELANGUAGE_H
