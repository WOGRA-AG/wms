#ifndef CDBCOMMANDUPDATEUSER_H
#define CDBCOMMANDUPDATEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandUpdateUser : public CftlAbstractTransactionalCommand
{
private:
    CumUser* m_rpUser;

    void UpdateSchemeUri();
public:
    CftlCommandUpdateUser(CumUser* p_pUser,
                          CftlDataAccess* p_pDataAccess);

    virtual ~CftlCommandUpdateUser();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDUPDATEUSER_H
