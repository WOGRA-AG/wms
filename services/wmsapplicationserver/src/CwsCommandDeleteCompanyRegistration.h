#ifndef CWSCOMMANDDELETECOMPANYREGISTRATION_H
#define CWSCOMMANDDELETECOMPANYREGISTRATION_H

#include "IwsServerCommand.h"

// Forwards
class CdmScheme;
class CwsServer;

class CwiCommandDeleteCompanyRegistration : public IwsServerCommand
{
private:
    CwsServer* m_rpCwsServer;

    void DeleteSchemeUsers(CdmScheme *p_pScheme);
public:
    CwiCommandDeleteCompanyRegistration(CwsServer* p_pServer);
    virtual ~CwiCommandDeleteCompanyRegistration();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDDELETECOMPANYREGISTRATION_H
