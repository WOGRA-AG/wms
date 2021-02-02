#ifndef CWICOMMANDGETLANGUAGES_H
#define CWICOMMANDGETLANGUAGES_H

#include "CwiAbstractCommand.h"

class CdmDataProvider;


class CwiCommandGetLanguages : public CwiAbstractCommand
{
private:
    CwmscomData *m_rpData;

public:
    CwiCommandGetLanguages(CwmscomData *p_pData);
    virtual ~CwiCommandGetLanguages();
    virtual void Execute();
};

#endif // CWICOMMANDGETLANGUAGES_H
