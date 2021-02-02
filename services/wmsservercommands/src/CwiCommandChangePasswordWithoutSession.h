#ifndef CWICOMMANDCHANGEPASSWORDWITHOUTSESSION_H
#define CWICOMMANDCHANGEPASSWORDWITHOUTSESSION_H

#include "CwiAbstractCommand.h"


class CwiCommandChangePasswordWithoutSession : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;
public:
    CwiCommandChangePasswordWithoutSession(CwmscomData* p_pData);
    virtual ~CwiCommandChangePasswordWithoutSession();
    virtual void Execute();
};

#endif // CWICOMMANDCHANGEPASSWORDWITHOUTSESSION_H
