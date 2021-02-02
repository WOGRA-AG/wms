#ifndef CWSCOMMANDDELETECOMPANYREGISTRATION_H
#define CWSCOMMANDDELETECOMPANYREGISTRATION_H

#include "IwiCommand.h"

// Forwards
class CdmScheme;
class CwsServer;

class CwiCommandDeleteCompanyRegistration : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;

    void DeleteSchemeUsers(CdmScheme *p_pScheme);
    bool Validate();
public:
    CwiCommandDeleteCompanyRegistration(CwmscomData* p_pData);
    virtual ~CwiCommandDeleteCompanyRegistration();
    virtual void Execute();
};

#endif // CWSCOMMANDDELETECOMPANYREGISTRATION_H
