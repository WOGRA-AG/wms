#ifndef CWNCOMMANDEXISTUSER_H
#define CWNCOMMANDEXISTUSER_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandExistUser : public CwnCommandBase
{
public:
    CwnCommandExistUser(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandExistUser();

    void setLogin(QString login);
    QString getLogin();

    QString createQuery();
    QString queryCausedError;

private:
    QString login;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDEXISTUSER_H
