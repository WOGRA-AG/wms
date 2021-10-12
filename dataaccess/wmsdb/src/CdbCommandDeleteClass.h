#ifndef CDBCOMMANDDELETECLASS_H
#define CDBCOMMANDDELETECLASS_H

#include "CdbAbstractCommandTransactional.h"

class CdbCommandDeleteClass : public CdbAbstractCommandTransactional
{
private:
   qint64 m_lClassId;

public:
    CdbCommandDeleteClass(qint64 p_lClassId, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandDeleteClass();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETECLASS_H
