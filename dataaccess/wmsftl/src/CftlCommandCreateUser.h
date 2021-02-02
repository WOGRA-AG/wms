#ifndef CDBCOMMANDCREATEUSER_H
#define CDBCOMMANDCREATEUSER_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandCreateUser : public CftlAbstractTransactionalCommand
{
private:
    CumUser* m_rpUser;
    int InsertInUserTable(int p_iAccessorId);
    void InsertInAccessorSchemeTable(int p_iAccessorId);
public:
    CftlCommandCreateUser(CumUser* p_pUser,
                         CftlDataAccess* p_ppDataAccess);
    virtual ~CftlCommandCreateUser();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();

};

#endif // CXDBCOMMANDCREATEUSER_H
