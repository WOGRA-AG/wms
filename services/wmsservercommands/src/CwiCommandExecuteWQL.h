#ifndef CWICOMMANDEXECUTEWQL_H
#define CWICOMMANDEXECUTEWQL_H

#include "CwiAbstractCommand.h"

class CwiCommandExecuteWQL : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandExecuteWQL(CwmscomData* p_pData);
    virtual ~CwiCommandExecuteWQL();
    virtual void Execute();
};

#endif // CWICOMMANDEXECUTEWQL_H
