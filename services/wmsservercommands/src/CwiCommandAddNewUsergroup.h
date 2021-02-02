#ifndef CWICOMMANDADDNEWUSERGROUP_H
#define CWICOMMANDADDNEWUSERGROUP_H

#include "CwiAbstractCommand.h"


class CwiCommandAddNewUsergroup : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandAddNewUsergroup(CwmscomData *p_pData);
    virtual ~CwiCommandAddNewUsergroup();
    virtual void Execute();
};

#endif // CWICOMMANDADDNEWUSERGROUP_H
