#ifndef CDBCOMMANDLOCKMETHOD_H
#define CDBCOMMANDLOCKMETHOD_H

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandLockMethod : public CdbAbstractCommandTransactional
{
private:
    long m_lSessionId;
    long m_lMethodId;
    bool m_bResult;


public:
    CdbCommandLockMethod(long p_lMethodId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLockMethod();

    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDLOCKMETHOD_H
