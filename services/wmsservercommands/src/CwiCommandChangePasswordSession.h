#ifndef CWICOMMANDCHANGEPASSWORDSESSION_H
#define CWICOMMANDCHANGEPASSWORDSESSION_H

#include "CwiAbstractCommand.h"

class CwiCommandChangePasswordSession : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandChangePasswordSession(CwmscomData* p_pData);
    virtual ~CwiCommandChangePasswordSession();
    virtual void Execute();
};

#endif // CWICOMMANDCHANGEPASSWORDSESSION_H
