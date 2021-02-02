#ifndef CWIABSTRACTCOMMAND_H
#define CWIABSTRACTCOMMAND_H

#include "IwiCommand.h"


class CwmscomDataResult;

class CwiAbstractCommand : public IwiCommand
{
public:
    CwiAbstractCommand();
    virtual ~CwiAbstractCommand();

protected:
    CwmscomDataResult *GetResultContainer(CwmscomData *p_pData, int p_iReturnCode, QString p_qstrMessage, EwmscomMessageServerity p_eSeverity);
};

#endif // CWIABSTRACTCOMMAND_H
