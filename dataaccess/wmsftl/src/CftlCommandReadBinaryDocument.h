#ifndef DBCOMMANDREADBINARYDOCUMENT_H
#define DBCOMMANDREADBINARYDOCUMENT_H

#include "CftlAbstractCommand.h"

class CftlCommandReadBinaryDocument : public CftlAbstractCommand
{
private:
    CdmValueBinaryDocument* m_rpCdmBinaryDocument;
    QByteArray m_qByteArray;
public:
    CftlCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandReadBinaryDocument();
    QByteArray GetByteArray();

protected:
    bool CheckValid();
    int Execute();
};

#endif // DBCOMMANDREADBINARYDOCUMENT_H
