#ifndef CWICOMMANDADDLANGUAGE_H
#define CWICOMMANDADDLANGUAGE_H

#include "CwiAbstractCommand.h"

class CdmScheme;


class CwiCommandAddLanguage : public CwiAbstractCommand
{
private:
    CwmscomData *m_rpData;
    CdmScheme *m_rpDatabase;
public:
    CwiCommandAddLanguage(CwmscomData *p_pData, CdmScheme* p_pDatabase);
    virtual ~CwiCommandAddLanguage();
    virtual void Execute();
};

#endif // CWICOMMANDADDLANGUAGE_H
