#ifndef CDBCOMMANDUPDATEUSER_H
#define CDBCOMMANDUPDATEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandUpdateUser : public CdbAbstractCommandTransactional
{
private:
    CumUser* m_rpUser;

    void UpdateSchemeUri();
public:
    CdbCommandUpdateUser(CumUser* p_pUser,
                         CdbDataAccess* p_pDataAccess);

    virtual ~CdbCommandUpdateUser();

protected:
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CDBCOMMANDUPDATEUSER_H
