#ifndef CDBCOMMANDLOCKOBJECT_H
#define CDBCOMMANDLOCKOBJECT_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandLockObject : public CdbAbstractCommandTransactional
{
private:
        long m_lSessionId;
        long m_lObjectId;
public:
    CdbCommandLockObject(long p_lSessionId, long p_lObjectId,CdbDataAccess* p_pDataAccess);
    ~CdbCommandLockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOCKOBJECT_H
