#ifndef CDBCOMMANDLOGOUT_H
#define CDBCOMMANDLOGOUT_H

#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbUserManager;
class CumUser;

class CdbCommandLogout : public CdbAbstractCommandTransactional
{
private:
    long m_lSessionId;
public:
    CdbCommandLogout(long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLogout();

protected:
    virtual int Execute();
    virtual bool CheckValid();
    virtual bool NeedsActiveSession();

};

#endif // CDBCOMMANDLOGOUT_H
