#ifndef CWICOMMANDGETUSERBYIDENTITYKEY_H
#define CWICOMMANDGETUSERBYIDENTITYKEY_H

#include "CwiAbstractCommand.h"


class CwiCommandGetUserByIdentityKey : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetUserByIdentityKey(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserByIdentityKey();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERBYIDENTITYKEY_H
