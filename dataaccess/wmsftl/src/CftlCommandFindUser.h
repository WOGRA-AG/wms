#ifndef CDBCOMMANDFINDUSER_H
#define CDBCOMMANDFINDUSER_H

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CumUser;

class CftlCommandFindUser : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lUserId;
    QString m_qstrLogin;
    QString m_qstrPassword;
    QString m_qstrEmail;
    QString m_qstrIdentKey;
    QString m_qstrSchemeUri;
    CumUser* m_rpUser;

    int FindUserById();
    int FindUserByLogin();
    int FindUserByEmail();
    int FindUserByLoginAndPassword();
    void EncryptAllPasswords();

    void CreateUserObjectFromQuery(QSqlQuery &p_rQuery);
    QString CreateSelectPart();
    QString GenerateJoin();

public:
    CftlCommandFindUser(qint64 p_lUserId, CftlDataAccess* p_pDataAccess);
    CftlCommandFindUser(QString p_qstrValue, bool p_bEmail, QString p_qstrSchemeUri, CftlDataAccess* p_pDataAccess);
    CftlCommandFindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess);
    CftlCommandFindUser(QString p_qstrIdentKey, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess);
    virtual ~CftlCommandFindUser();
    CumUser* GetResult();

protected:
    bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();
protected slots:
    int FindUserByIdentityKey();
};

#endif // CDBCOMMANDFINDUSER_H
