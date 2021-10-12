#ifndef CDBCOMMANDDELETEUSER_H
#define CDBCOMMANDDELETEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandDeleteUser : public CdbAbstractCommandTransactional
{
private:
    QString m_qstrLogin;
    int m_iUserId;

    int DeleteUserById();
    int DeleteUserByLogin();
public:
    CdbCommandDeleteUser(qint64 p_lUserId, CdbDataAccess* p_pDataAccess);
    CdbCommandDeleteUser(QString p_qstrLogin, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteUser();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDDELETEUSER_H
