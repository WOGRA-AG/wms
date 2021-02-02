#ifndef CDBCOMMANDDELETEUSER_H
#define CDBCOMMANDDELETEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandDeleteUser : public CftlAbstractTransactionalCommand
{
private:
    QString m_qstrLogin;
    int m_iUserId;

    int DeleteUserById();
    int DeleteUserByLogin();
public:
    CftlCommandDeleteUser(long p_lUserId, CftlDataAccess* p_pDataAccess);
    CftlCommandDeleteUser(QString p_qstrLogin, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteUser();

protected:
    virtual bool CheckValid();
    virtual int Execute();
};

#endif // CDBCOMMANDDELETEUSER_H
