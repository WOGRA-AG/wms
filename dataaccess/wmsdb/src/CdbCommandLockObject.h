#ifndef CDBCOMMANDLOCKOBJECT_H
#define CDBCOMMANDLOCKOBJECT_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandLockObject : public CdbAbstractCommandTransactional
{
private:
       qint64 m_lSessionId;
       qint64 m_lObjectId;
public:
    CdbCommandLockObject(qint64 p_lSessionId,qint64 p_lObjectId,CdbDataAccess* p_pDataAccess);
    ~CdbCommandLockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDLOCKOBJECT_H
