#ifndef CDBCOMMANDLOCKMETHOD_H
#define CDBCOMMANDLOCKMETHOD_H

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandLockMethod : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lSessionId;
   qint64 m_lMethodId;
    bool m_bResult;


public:
    CdbCommandLockMethod(qint64 p_lMethodId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandLockMethod();

    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDLOCKMETHOD_H
