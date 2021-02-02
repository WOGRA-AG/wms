#ifndef CWNCOMMANDFINDUSER_H
#define CWNCOMMANDFINDUSER_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>


// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandFindUser : public CwnCommandBase
{
public:

    CwnCommandFindUser(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandFindUser();

    void setLogin(QString login);
    QString getLogin();

    void setPassw(QString passw);
    QString getPassw();

    void setUserId(long userid);
    long getUserId();

    void setUserEmail(QString useremail);
    QString getUserEmail();

    void setDecider(int decider_var);
    int getDecider();

    void setUserIdentKey(QString useridentkey);
    QString getUserIdentKey();

    QString createQuery();
    CumUser* getResult();
    QString queryCausedError;

private:
    int decider;
    long userid;
    QString useremail;
    QString login;
    QString passw;
    QString useridentkey;
    CumUser* result;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDFINDUSER_H
