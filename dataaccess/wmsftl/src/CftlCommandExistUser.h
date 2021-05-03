#ifndef CDBCOMMANDEXISTUSER_H
#define CDBCOMMANDEXISTUSER_H

// System and Qt Includes
#include <QList>
// WMS Includes

// own Includes
#include "CftlAbstractCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandExistUser : public CftlAbstractCommand
{
private:
    QString m_qstrLogin;

public:
    CftlCommandExistUser(QString p_qstrLogin, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandExistUser();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDEXISTUSER_H
