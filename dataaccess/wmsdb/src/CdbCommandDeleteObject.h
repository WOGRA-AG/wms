#ifndef CDBCOMMANDDELETEOBJECT_H
#define CDBCOMMANDDELETEOBJECT_H

// Own Includes
#include "CdbAbstractCommandTransactional.h"


class CdbCommandDeleteObject : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lObjectId;
   qint64 m_lSessionId;

public:
    CdbCommandDeleteObject(qint64 p_lObjectId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteObject();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETEOBJECT_H
