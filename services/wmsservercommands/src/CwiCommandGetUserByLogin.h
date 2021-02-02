#ifndef CWICOMMANDGETUSERBYLOGIN_H
#define CWICOMMANDGETUSERBYLOGIN_H

#include <QMutex>

#include "CwiAbstractCommand.h"


class CwiCommandGetUserByLogin : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetUserByLogin(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserByLogin();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERBYLOGIN_H
