#ifndef CDBCOMMANDCLEANUPDB_H
#define CDBCOMMANDCLEANUPDB_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandCleanupDB : public CftlAbstractTransactionalCommand
{
public:
    CftlCommandCleanupDB(CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCleanupDB();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCLEANUPDB_H
