#ifndef CDCOMMANDDELETESCHEMELANGUAGE_H
#define CDCOMMANDDELETESCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

class CftlCommandDeleteSchemeLanguage : public CftlAbstractTransactionalCommand
{
private:
    long m_lSchemeId;
    long m_lLanguage;

public:
    CftlCommandDeleteSchemeLanguage(long p_lSchemeId, int p_lLanguage, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDCOMMANDDELETESCHEMELANGUAGE_H
