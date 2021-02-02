#ifndef CwnCOMMANDUPDATEBINARYDOCUMENT_H
#define CwnCOMMANDUPDATEBINARYDOCUMENT_H

#include "CwnCommandBase.h"

// Forwards
class CdmValueBinaryDocument;

class CwnCommandUpdateBinaryDocument : public CwnCommandBase
{
private:
    CdmValueBinaryDocument* m_rpValue;
    QString ShortFilename(QString p_qstrFilename);
    QString createQuery();
public:
    CwnCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateBinaryDocument();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    bool CheckValid();
    int Execute();
};

#endif // CwnCOMMANDUPDATEBINARYDOCUMENT_H
