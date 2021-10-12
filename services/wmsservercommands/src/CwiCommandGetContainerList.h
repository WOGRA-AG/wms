#ifndef CWICOMMANDGETCONTAINERLIST_H
#define CWICOMMANDGETCONTAINERLIST_H

#include "CwiAbstractCommand.h"

class CwiCommandGetContainerList : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;
   qint64 m_rlDbId;
public:
    CwiCommandGetContainerList(CwmscomData* p_pData,qint64 p_lDbId);
    virtual ~CwiCommandGetContainerList();
    virtual void Execute();
};

#endif // CWICOMMANDGETCONTAINERLIST_H
