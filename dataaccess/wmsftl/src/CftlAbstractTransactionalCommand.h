#ifndef CFTLAVSTRACTTRANSACTIONALCOMMAND_H
#define CFTLAVSTRACTTRANSACTIONALCOMMAND_H


#include "CftlAbstractCommand.h"

class CftlDataAccess;

class CftlAbstractTransactionalCommand : public CftlAbstractCommand
{
public:
    CftlAbstractTransactionalCommand(CftlDataAccess* p_pDataAccess);
    virtual ~CftlAbstractTransactionalCommand();
    virtual int Run();
};

#endif // CFTLAVSTRACTTRANSACTIONALCOMMAND_H
