#ifndef CDBCOMMANDDELETECLASS_H
#define CDBCOMMANDDELETECLASS_H

#include "CftlAbstractTransactionalCommand.h"

class CftlCommandDeleteClass : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lClassId;

   qint64 DropClassTable();
    
public:
    CftlCommandDeleteClass(qint64 p_lClassId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandDeleteClass();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDDELETECLASS_H
