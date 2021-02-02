#ifndef CDBCOMMANDCLEANUPDB_H
#define CDBCOMMANDCLEANUPDB_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandCleanupDB : public CdbAbstractCommandTransactional
{
public:
    CdbCommandCleanupDB(CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCleanupDB();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCLEANUPDB_H
