#ifndef CWICOMMANDREGISTERCOMPANY_H
#define CWICOMMANDREGISTERCOMPANY_H

#include "IwiCommand.h"

// Forwards
class CumUser;
class CdmScheme;

class CwiCommandRegisterCompany : public IwiCommand
{
private:
    CwmscomData *m_rpData;

    void AddUserToScheme(CumUser *p_pUser, CdmScheme *p_pScheme);
public:
    CwiCommandRegisterCompany(CwmscomData *p_pData);
    virtual ~CwiCommandRegisterCompany();
    virtual void Execute();
};

#endif // CWICOMMANDREGISTERCOMPANY_H
