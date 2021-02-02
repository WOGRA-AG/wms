#ifndef CWICOMMANDUPDATEBINARYDOCUMENT_H
#define CWICOMMANDUPDATEBINARYDOCUMENT_H

#include "CwiAbstractCommand.h"

class CwiCommandUpdateBinaryDocument : public CwiAbstractCommand
{

private:
    CwmscomData* m_rpData;

public:
    CwiCommandUpdateBinaryDocument(CwmscomData* p_pData);
    virtual ~CwiCommandUpdateBinaryDocument();
    virtual void Execute();
};

#endif // CWICOMMANDUPDATEBINARYDOCUMENT_H
