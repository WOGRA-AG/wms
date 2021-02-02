#ifndef CWICOMMANDUPDATEUSER_H
#define CWICOMMANDUPDATEUSER_H

#include "CwiAbstractCommand.h"

class CwiCommandUpdateUser : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandUpdateUser(CwmscomData *p_pData);
    virtual ~CwiCommandUpdateUser();
    virtual void Execute();
};

#endif // CWICOMMANDUPDATEUSER_H
