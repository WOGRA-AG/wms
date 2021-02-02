#ifndef CWICOMMANDGETUSERBYEMAIL_H
#define CWICOMMANDGETUSERBYEMAIL_H

#include "CwiAbstractCommand.h"


class CwiCommandGetUserByEmail : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetUserByEmail(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserByEmail();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERBYEMAIL_H
