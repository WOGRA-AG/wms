#ifndef CWNCOMMANDCHECKSESSIONTIMEOUT_H
#define CWNCOMMANDCHECKSESSIONTIMEOUT_H

// System and Qt Includes

// WMS Includes

// own Includes
#include "CwnCommandBase.h"

// Forwards
class CwnDataAccess;

class CwnCommandCheckSessionTimeout : public CwnCommandBase
{
private:
    int m_iTimeout; // minutes
public:
    CwnCommandCheckSessionTimeout(int p_iTimeout, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandCheckSessionTimeout();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDCHECKSESSIONTIMEOUT_H
