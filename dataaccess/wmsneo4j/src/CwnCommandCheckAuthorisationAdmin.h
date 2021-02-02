#ifndef CWNCOMMANDCHECKAUTHORISATIONADMIN_H
#define CWNCOMMANDCHECKAUTHORISATIONADMIN_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandCheckAuthorisationAdmin : public CwnCommandBase
{
public:

    CwnCommandCheckAuthorisationAdmin(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandCheckAuthorisationAdmin();

    void setLogin(QString login);
    QString getLogin();

    void setPassw(QString passw);
    QString getPassw();

    bool getAdmin();

    QString createQuery();
    QString queryCausedError;

private:
    bool admin;
    QString login;
    QString passw;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCHECKAUTHORISATIONADMIN_H



