#ifndef CWICOMMANDREMOVEUSERTOGROUPRELATION_H
#define CWICOMMANDREMOVEUSERTOGROUPRELATION_H

#include "CwiAbstractCommand.h"

class CwiCommandRemoveUserToGroupRelation : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandRemoveUserToGroupRelation(CwmscomData *p_pData);
    virtual ~CwiCommandRemoveUserToGroupRelation();
    virtual void Execute();
};

#endif // CWICOMMANDREMOVEUSERTOGROUPRELATION_H
