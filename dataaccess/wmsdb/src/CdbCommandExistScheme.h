#ifndef CDBCOMMANDEXISTSCHEME_H
#define CDBCOMMANDEXISTSCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandExistScheme : public CdbAbstractCommand
{
private:
    QString m_qstrSchemeName;

public:
    CdbCommandExistScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandExistScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDEXISTSCHEME_H
