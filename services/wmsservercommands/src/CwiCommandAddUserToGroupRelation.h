#ifndef CWICOMMANDADDUSERTOGROUPRELATION_H
#define CWICOMMANDADDUSERTOGROUPRELATION_H

#include "CwiAbstractCommand.h"

class CwiCommandAddUserToGroupRelation : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandAddUserToGroupRelation(CwmscomData *p_pData);
    virtual ~CwiCommandAddUserToGroupRelation();
    virtual void Execute();
};

#endif // CWICOMMANDADDUSERTOGROUPRELATION_H
