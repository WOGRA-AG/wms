#ifndef CWNCOMMANDDELETEUSER_H
#define CWNCOMMANDDELETEUSER_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

// Forwards
class CwnUserManager;
class CumUser;
class CwnConfiguration;

class CwnCommandDeleteUser : public CwnCommandBase
{
public:
    CwnCommandDeleteUser(CwnDataAccess* m_rpDataAccess);
    CwnCommandDeleteUser(long p_lUserId, CwnDataAccess *p_pDataAccess);

    virtual ~CwnCommandDeleteUser();

    void setLogin(QString login);
    QString getLogin();

    QString createQuery();
    QString queryCausedError;

private:
    QString login;
    long m_iUserId;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDDELETEUSER_H
