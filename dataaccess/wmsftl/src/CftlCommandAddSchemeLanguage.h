#ifndef CDBCOMMANDADDSCHEMELANGUAGE_H
#define CDBCOMMANDADDSCHEMELANGUAGE_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

class CftlCommandAddSchemeLanguage : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lSchemeId;
    QString m_qstrLanguage;
public:
    CftlCommandAddSchemeLanguage(qint64 p_lSchemeId, QString p_qstrLanguage, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandAddSchemeLanguage();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDADDSCHEMELANGUAGE_H
