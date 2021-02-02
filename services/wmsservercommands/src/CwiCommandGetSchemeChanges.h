#ifndef CWICOMMANDGETSCHEMECHANGES_H
#define CWICOMMANDGETSCHEMECHANGES_H

#include "CwiAbstractCommand.h"

class CwiCommandGetSchemeChanges : public CwiAbstractCommand
{

private:
    CwmscomData *m_rpData;

public:
    CwiCommandGetSchemeChanges(CwmscomData* p_pData);
    virtual ~CwiCommandGetSchemeChanges();
    virtual void Execute();
};

#endif // CWICOMMANDGETSCHEMECHANGES_H
