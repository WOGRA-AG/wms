#ifndef DBCOMMANDREADBINARYDOCUMENT_H
#define DBCOMMANDREADBINARYDOCUMENT_H

#include "CdbAbstractCommand.h"

class CdbCommandReadBinaryDocument : public CdbAbstractCommand
{
private:
    CdmValueBinaryDocument* m_rpCdmBinaryDocument;
    QByteArray m_qByteArray;
public:
    CdbCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CdbDataAccess* p_pDataAccess);
    virtual ~CdbCommandReadBinaryDocument();

    QByteArray GetByteArray();
protected:
    bool CheckValid();
    int Execute();
};

#endif // DBCOMMANDREADBINARYDOCUMENT_H
