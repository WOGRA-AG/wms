#ifndef CDBCOMMANDCHECKSESSIONTIMEOUT_H
#define CDBCOMMANDCHECKSESSIONTIMEOUT_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdbDataAccess;

class CdbCommandCheckSessionTimeout : public CdbAbstractCommandTransactional
{
private:
    int m_iTimeout; // minutes
public:
    CdbCommandCheckSessionTimeout(int p_iTimeout, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandCheckSessionTimeout();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKSESSIONTIMEOUT_H
