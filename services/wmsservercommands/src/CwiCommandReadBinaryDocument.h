#ifndef CWICOMMANDREADBINARYDOCUMENT_H
#define CWICOMMANDREADBINARYDOCUMENT_H

#include "CwiAbstractCommand.h"

class CwiCommandReadBinaryDocument : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandReadBinaryDocument(CwmscomData* p_pData);
    virtual ~CwiCommandReadBinaryDocument();
    virtual void Execute();
};

#endif // CWICOMMANDREADBINARYDOCUMENT_H
