#ifndef CDBCOMMANDEXISTSCHEME_H
#define CDBCOMMANDEXISTSCHEME_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandExistScheme : public CftlAbstractCommand
{
private:
    QString m_qstrSchemeName;

public:
    CftlCommandExistScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandExistScheme();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDEXISTSCHEME_H
