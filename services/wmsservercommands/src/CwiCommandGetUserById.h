#ifndef CWICOMMANDGETUSERBYID_H
#define CWICOMMANDGETUSERBYID_H

#include "CwiAbstractCommand.h"

class CwiCommandGetUserById : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandGetUserById(CwmscomData* p_pData);
    virtual ~CwiCommandGetUserById();
    virtual void Execute();
};

#endif // CWICOMMANDGETUSERBYID_H
