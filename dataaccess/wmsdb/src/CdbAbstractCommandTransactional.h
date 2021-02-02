#ifndef CDBABSTRACTCOMMANDTRANSACTIONAL_H
#define CDBABSTRACTCOMMANDTRANSACTIONAL_H

#include "CdbAbstractCommand.h"

class CdbAbstractCommandTransactional : public CdbAbstractCommand
{
public:
    CdbAbstractCommandTransactional(CdbDataAccess* p_pDataAccess);
    virtual ~CdbAbstractCommandTransactional();
    virtual int Run();
};

#endif // CDBABSTRACTCOMMANDTRANSACTIONAL_H
