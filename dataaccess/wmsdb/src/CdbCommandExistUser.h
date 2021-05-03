#ifndef CDBCOMMANDEXISTUSER_H
#define CDBCOMMANDEXISTUSER_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CdbDataAccess;

class CdbCommandExistUser : public CdbAbstractCommand
{
private:
    QString m_qstrLogin;

public:
    CdbCommandExistUser(QString p_qstrLogin, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandExistUser();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDEXISTUSER_H
