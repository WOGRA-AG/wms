#ifndef CDBCOMMANDADDSCHEMELANGUAGE_H
#define CDBCOMMANDADDSCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

class CftlCommandAddSchemeLanguage : public CftlAbstractTransactionalCommand
{
private:
    long m_lSchemeId;
    QString m_qstrLanguage;
public:
    CftlCommandAddSchemeLanguage(long p_lSchemeId, QString p_qstrLanguage, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandAddSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDADDSCHEMELANGUAGE_H
