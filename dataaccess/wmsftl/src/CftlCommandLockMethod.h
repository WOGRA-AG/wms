#ifndef CDBCOMMANDLOCKMETHOD_H
#define CDBCOMMANDLOCKMETHOD_H

// own Includes
#include "CftlAbstractTransactionalCommand.h"

class CftlCommandLockMethod : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lMethodId;
    bool m_bResult;


public:
    CftlCommandLockMethod(qint64 p_lMethodId, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandLockMethod();

    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDLOCKMETHOD_H
