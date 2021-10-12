#ifndef CDBCOMMANDUNLOCKMETHOD_H
#define CDBCOMMANDUNLOCKMETHOD_H

// own Includes
#include "CdbAbstractCommandTransactional.h"

class CdbCommandUnlockMethod : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lSessionId;
   qint64 m_lMethodId;
    bool m_bResult;


public:
    CdbCommandUnlockMethod(qint64 p_lMethodId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUnlockMethod();
    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDUNLOCKMETHOD_H
