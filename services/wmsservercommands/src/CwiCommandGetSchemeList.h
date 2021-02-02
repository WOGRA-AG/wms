#ifndef CWICOMMANDGETSCHEMELIST_H
#define CWICOMMANDGETSCHEMELIST_H

#include "CwiAbstractCommand.h"

class CwiCommandGetSchemeList : public CwiAbstractCommand
{
private:
    CwmscomData *m_rpData;

public:
    CwiCommandGetSchemeList(CwmscomData* p_pData);
    virtual ~CwiCommandGetSchemeList();
    virtual void Execute();
};

#endif // CWICOMMANDGETSCHEMELIST_H
