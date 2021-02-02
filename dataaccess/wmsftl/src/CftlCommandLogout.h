#ifndef CDBCOMMANDLOGOUT_H
#define CDBCOMMANDLOGOUT_H

#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlUserManager;
class CumUser;

class CftlCommandLogout : public CftlAbstractTransactionalCommand
{
public:
    CftlCommandLogout(CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLogout();

protected:
    virtual int Execute();
    virtual bool CheckValid();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDLOGOUT_H
