#ifndef CWICOMMANDREGISTERUSER_H
#define CWICOMMANDREGISTERUSER_H

// own Includes
#include "IwiCommand.h"

// Forwards
class CumUser;

class CwiCommandRegisterUser : public IwiCommand
{
private:
    CumUser* m_pUser;
    CwmscomData *m_rpData;
public:
    CwiCommandRegisterUser(CwmscomData *p_pData);
    virtual ~CwiCommandRegisterUser();
    virtual void Execute();
    CumUser *GetUser();
};

#endif // CWICOMMANDREGISTERUSER_H
