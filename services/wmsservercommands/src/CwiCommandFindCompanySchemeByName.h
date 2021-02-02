#ifndef CWICOMMANDFINDCOMPANYSCHEMEBYNAME_H
#define CWICOMMANDFINDCOMPANYSCHEMEBYNAME_H

#include "IwiCommand.h"

// Forwards
class CdmScheme;
class CwsServer;

class CwiCommandFindCompanySchemeByName : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;

public:
    CwiCommandFindCompanySchemeByName(CwmscomData* p_pData);
    virtual ~CwiCommandFindCompanySchemeByName();
    virtual void Execute();
};

#endif // CWICOMMANDFINDCOMPANYBYSCHEMENAME_H
