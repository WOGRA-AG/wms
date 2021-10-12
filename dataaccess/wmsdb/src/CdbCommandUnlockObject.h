#ifndef CDBCOMMANDUNLOCKOBJECT_H
#define CDBCOMMANDUNLOCKOBJECT_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandUnlockObject : public CdbAbstractCommandTransactional
{
private:
       qint64 m_lSessionId;
       qint64 m_lObjectId;
public:
    CdbCommandUnlockObject(qint64 p_lSessionId,qint64 p_lObjectId,CdbDataAccess* p_pDataAccess);
    ~CdbCommandUnlockObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUNLOCKOBJECT_H
