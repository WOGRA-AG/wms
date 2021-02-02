#ifndef CWNCOMMANDFINDUSERBYEMAIL_H
#define CWNCOMMANDFINDUSERBYEMAIL_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandFindUserByEmail : public CwnCommandBase
{
public:
    CwnCommandFindUserByEmail(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandFindUserByEmail();

    void setEmail(QString email);
    QString getEmail();

    QString createQuery();
    CumUser *getResult();
    QString queryCausedError;

private:
    QString email;
    CumUser* result;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFINDUSERBYEMAIL_H

