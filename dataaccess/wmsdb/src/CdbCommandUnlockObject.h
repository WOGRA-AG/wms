#ifndef CDBCOMMANDUNLOCKOBJECT_H
#define CDBCOMMANDUNLOCKOBJECT_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandUnlockObject : public CdbAbstractCommandTransactional
{
private:
        long m_lSessionId;
        long m_lObjectId;
public:
    CdbCommandUnlockObject(long p_lSessionId, long p_lObjectId,CdbDataAccess* p_pDataAccess);
    ~CdbCommandUnlockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUNLOCKOBJECT_H
