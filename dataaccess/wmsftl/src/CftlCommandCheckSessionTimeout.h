#ifndef CDBCOMMANDCHECKSESSIONTIMEOUT_H
#define CDBCOMMANDCHECKSESSIONTIMEOUT_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CftlDataAccess;

class CftlCommandCheckSessionTimeout : public CftlAbstractTransactionalCommand
{
private:
    int m_iTimeout; // minutes
public:
    CftlCommandCheckSessionTimeout(int p_iTimeout, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandCheckSessionTimeout();

protected:
    virtual bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDCHECKSESSIONTIMEOUT_H
