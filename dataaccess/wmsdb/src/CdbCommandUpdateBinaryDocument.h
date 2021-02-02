#ifndef CDBCOMMANDUPDATEBINARYDOCUMENT_H
#define CDBCOMMANDUPDATEBINARYDOCUMENT_H

#include "CdbAbstractCommandTransactional.h"

// Forwards
class CdmValueBinaryDocument;

class CdbCommandUpdateBinaryDocument : public CdbAbstractCommandTransactional
{
private:
    CdmValueBinaryDocument* m_rpValue;
    QString ShortFilename(QString p_qstrFilename);
public:
    CdbCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandUpdateBinaryDocument();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDUPDATEBINARYDOCUMENT_H
