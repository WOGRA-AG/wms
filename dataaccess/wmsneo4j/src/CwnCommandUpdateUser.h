#ifndef CWNCOMMANDUPDATEUSER_H
#define CWNCOMMANDUPDATEUSER_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandUpdateUser : public CwnCommandBase
{
public:
    CwnCommandUpdateUser(CwnDataAccess* m_rpDataAccess);
    virtual ~CwnCommandUpdateUser();

    void setUserId(long userid);
    long getUserId();

    void setFirstname(QString Surname);
    QString getFirstname();

    void setLastname(QString name);
    QString getLastname();

    void setLogin(QString login);
    QString getLogin();

    void setPassw(QString passw, bool p_bEncrypted);
    QString getPassw();

    void setEmail(QString email);
    QString getEmail();

    void setAdmin(bool admin);
    bool getAdmin();

    void setActive(bool active);
    bool getActive();

    QString createQuery();
    QString queryCausedError;

private:
    long userid;
    QString firstname;
    QString lastname;
    QString login;
    QString passw;
    QString email;
    bool admin;
    bool active;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDUPDATEUSER_H
