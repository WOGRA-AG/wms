#ifndef CDBCOMMANDUNLOCKMETHOD_H
#define CDBCOMMANDUNLOCKMETHOD_H

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandUnlockMethod : public CdbAbstractCommandTransactional
{
private:
    long m_lSessionId;
    long m_lMethodId;
    bool m_bResult;


public:
    CdbCommandUnlockMethod(long p_lMethodId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUnlockMethod();
    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDUNLOCKMETHOD_H
