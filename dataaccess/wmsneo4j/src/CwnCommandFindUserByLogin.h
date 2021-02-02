#ifndef CWNCOMMANDFINDUSERBYLOGIN_H
#define CWNCOMMANDFINDUSERBYLOGIN_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandFindUserByLogin : public CwnCommandBase
{
public:
    CwnCommandFindUserByLogin(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandFindUserByLogin();

    void setLogin(QString login);
    QString getLogin();

    QString createQuery();
    CumUser *getResult();
    QString queryCausedError;

private:
    QString login;
    CumUser* result;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFINDUSERBYLOGIN_H
