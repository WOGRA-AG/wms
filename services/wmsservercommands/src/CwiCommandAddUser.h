#ifndef CWICOMMANDADDUSER_H
#define CWICOMMANDADDUSER_H

#include "CwiAbstractCommand.h"

class CwiCommandAddUser : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandAddUser(CwmscomData* p_pData);
    virtual ~CwiCommandAddUser();
    virtual void Execute();
};

#endif // CWICOMMANDADDUSER_H
