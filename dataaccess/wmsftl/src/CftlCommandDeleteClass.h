#ifndef CDBCOMMANDDELETECLASS_H
#define CDBCOMMANDDELETECLASS_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandDeleteClass : public CftlAbstractTransactionalCommand
{
private:
    long m_lClassId;

    long DropClassTable();
    
public:
    CftlCommandDeleteClass(long p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteClass();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETECLASS_H
