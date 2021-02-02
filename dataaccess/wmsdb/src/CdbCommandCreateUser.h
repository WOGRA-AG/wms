#ifndef CDBCOMMANDCREATEUSER_H
#define CDBCOMMANDCREATEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandCreateUser : public CdbAbstractCommandTransactional
{
private:
    CumUser* m_rpUser;

    int InsertInAccessorTable();
    int InsertInUserTable(int p_iAccessorId);
    void InsertInAccessorSchemeTable(int p_iAccessorId);
public:
    CdbCommandCreateUser(CumUser* p_pUser,
                         CdbDataAccess* p_ppDataAccess);
    virtual ~CdbCommandCreateUser();

protected:
    virtual bool CheckValid();
    virtual int Execute();

};

#endif // CXDBCOMMANDCREATEUSER_H
