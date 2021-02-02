#ifndef CDBCOMMANDDELETEOBJECT_H
#define CDBCOMMANDDELETEOBJECT_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandDeleteObject : public CdbAbstractCommandTransactional
{
private:
    long m_lObjectId;
    long m_lSessionId;

public:
    CdbCommandDeleteObject(long p_lObjectId, long p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETEOBJECT_H
