#ifndef CWICOMMANDREFRESHOBJECTLIST_H
#define CWICOMMANDREFRESHOBJECTLIST_H

#include "CwiAbstractCommand.h"


class CwiCommandRefreshObjectList : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;
    long m_rlDbId;
    long m_rObjectListId;
public:
    CwiCommandRefreshObjectList(CwmscomData* p_pData, long p_lDbId, long p_ObjectListId);
    virtual ~CwiCommandRefreshObjectList();
    virtual void Execute();
};

#endif // CWICOMMANDREFRESHOBJECTLIST_H
