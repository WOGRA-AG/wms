#ifndef CDBCOMMANDUPDATEBINARYDOCUMENT_H
#define CDBCOMMANDUPDATEBINARYDOCUMENT_H

#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CdmValueBinaryDocument;

class CftlCommandUpdateBinaryDocument : public CftlAbstractTransactionalCommand
{
private:
    CdmValueBinaryDocument* m_rpValue;

public:
    CftlCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandUpdateBinaryDocument();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATEBINARYDOCUMENT_H
