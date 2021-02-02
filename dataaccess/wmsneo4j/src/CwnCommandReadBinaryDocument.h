#ifndef DBCOMMANDREADBINARYDOCUMENT_H
#define DBCOMMANDREADBINARYDOCUMENT_H

#include "CwnCommandBase.h"
#include <QByteArray>


class CwnCommandReadBinaryDocument : public CwnCommandBase
{
private:
    CdmValueBinaryDocument* m_rpCdmBinaryDocument;
    QByteArray m_qByteArray;
    QString createQuery();

public:
    CwnCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandReadBinaryDocument();
    QByteArray GetByteArray();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // DBCOMMANDREADBINARYDOCUMENT_H
