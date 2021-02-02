#ifndef CWNCOMMANDCREATEUSER_H
#define CWNCOMMANDCREATEUSER_H

#include "CwnCommandBase.h"

#include <QString>
#include "wmsneo4j.h"

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class WMSNEO4J_API CwnCommandCreateUser: public CwnCommandBase
{
public:
    CwnCommandCreateUser(CwnDataAccess* m_rpDataAccess, QString p_qstrIdentKey);
    virtual ~CwnCommandCreateUser();


    void setActive(bool active);
    void setAdmin(bool admin);
    void setEmail(QString email);
    void setFirstname(QString firstname);
    void setLastname(QString lastname);
    void setLogin(QString login);
    void setPass(QString pass);

    bool getActive();
    bool getAdmin();
    QString getEmail();
    QString getFirstname();
    QString getLastname();
    QString getLogin();
    QString getPass();

    QString createQuery();
    QString queryCausedError;

private:

    bool active;
    bool admin;
    QString email;
    QString firstname;
    QString lastname;
    QString login;
    QString pass;
    QString m_qstrIdentKey;


protected:
        void interpretAnswer(QVariant& Ret);
        virtual int Execute();
        virtual bool CheckValid();

};

#endif // CWNCOMMANDCREATEUSER_H
