#ifndef CDBCOMMANDUNLOCKMETHOD_H
#define CDBCOMMANDUNLOCKMETHOD_H

// own Includes
#include "CftlAbstractTransactionalCommand.h"

class CftlCommandUnlockMethod : public CftlAbstractTransactionalCommand
{
private:
   qint64 m_lMethodId;
    bool m_bResult;


public:
    CftlCommandUnlockMethod(qint64 p_lMethodId,CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUnlockMethod();
    bool GetResult();
protected:
    virtual int Execute();
    bool CheckValid();
};

#endif // CDBCOMMANDUNLOCKMETHOD_H
