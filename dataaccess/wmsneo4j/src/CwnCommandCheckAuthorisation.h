#ifndef CWNCOMMANDCHECKAUTHORISATION_H
#define CWNCOMMANDCHECKAUTHORISATION_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandCheckAuthorisation : public CwnCommandBase
{
public:

    CwnCommandCheckAuthorisation(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandCheckAuthorisation();

    void setLogin(QString login);
    QString getLogin();

    void setPassw(QString passw);
    QString getPassw();

    QString createQuery();
    QString queryCausedError;

private:
    QString login;
    QString passw;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCHECKAUTHORISATION_H



