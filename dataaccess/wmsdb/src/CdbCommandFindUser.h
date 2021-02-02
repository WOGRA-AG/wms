#ifndef CDBCOMMANDFINDUSER_H
#define CDBCOMMANDFINDUSER_H

// own Includes
#include "CdbAbstractCommand.h"

// Forwards
class CumUser;

class CdbCommandFindUser : public CdbAbstractCommand
{
private:
    long m_lUserId;
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
    int FindUserByIdentityKey();

    QString GetSelectPartOfQuery();
    int SetResult(QSqlQuery &p_rQuery);
    QString GenerateJoin();
    bool CheckPassword(QSqlQuery& cQSqlQuery);

public:
    CdbCommandFindUser(long p_lUserId, CdbDataAccess* p_pDataAccess);
    CdbCommandFindUser(QString p_qstrValue, bool p_bEmail, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess);
    CdbCommandFindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri,  CdbDataAccess *p_pDataAccess);
    CdbCommandFindUser(QString p_qstrIdentKey, QString p_qstrSchemeUri, CdbDataAccess *p_pDataAccess);

    virtual ~CdbCommandFindUser();
    CumUser* GetResult();
protected:
    bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDFINDUSER_H
