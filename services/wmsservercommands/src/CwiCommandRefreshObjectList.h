#ifndef CWICOMMANDREFRESHOBJECTLIST_H
#define CWICOMMANDREFRESHOBJECTLIST_H

#include "CwiAbstractCommand.h"


class CwiCommandRefreshObjectList : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;
   qint64 m_rlDbId;
   qint64 m_rObjectListId;
public:
    CwiCommandRefreshObjectList(CwmscomData* p_pData,qint64 p_lDbId,qint64 p_ObjectListId);
    virtual ~CwiCommandRefreshObjectList();
    virtual void Execute();
};

#endif // CWICOMMANDREFRESHOBJECTLIST_H
