#include <QSqlError>
#include <QFileInfo>

// WMS Includes
#include "CdmValueBinaryDocument.h"

// Own Includes
#include "CdbCommandUpdateBinaryDocument.h"

CdbCommandUpdateBinaryDocument::CdbCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_rpValue(p_pValue)
{
}

CdbCommandUpdateBinaryDocument::~CdbCommandUpdateBinaryDocument()
{

}

bool CdbCommandUpdateBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpValue);
}

int CdbCommandUpdateBinaryDocument::Execute()
{
    int iRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    QString qcstrBase64 = m_rpValue->GetBase64();
    // if string is empty the bindoc content was deleted.


    // deleting old dataset
    qstrQuery = QString("delete from WMS_VALUE_BINARYDOCUMENT where BinaryDocumentId = %1")
            .arg(m_rpValue->GetId());

    if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        // adding new dataset
        int iValueId = (int)m_rpValue->GetId();
        QString qstrFileType = m_rpValue->GetFileType();
        QString qstrFilename = ShortFilename(m_rpValue->GetFilename());
        cQSqlQuery.prepare("insert into WMS_VALUE_BINARYDOCUMENT (BinaryDocumentId, Type, Filename, Val) "
                           "values(?, ?, ?, ?)");


        cQSqlQuery.bindValue(0, iValueId);
        if (!qcstrBase64.isEmpty())
        {
            cQSqlQuery.bindValue(1, qstrFileType);
            cQSqlQuery.bindValue(2, qstrFilename);
        }
        else
        {
            cQSqlQuery.bindValue(1, "");
            cQSqlQuery.bindValue(2, "");
        }

        cQSqlQuery.bindValue(3, qcstrBase64);

        if (cQSqlQuery.exec())
        {
            iRet = EC(eDmOk);
            m_rpValue->ResetNewModified();
        }
        else
        {
            iRet = EC(eDmInvalidInsertStatement);
            // must be ok because the other values won't be saved and it is probabply a sizing problem
            ERR("Insert of Binary Document failed");
            ERR("Executed Query: " + cQSqlQuery.executedQuery());
            ERR("Insert Query Error: "+ cQSqlQuery.lastError().text());
        }
    }

    return iRet;
}

QString CdbCommandUpdateBinaryDocument::ShortFilename(QString p_qstrFilename)
{
    QString qstrFilename;

    if (p_qstrFilename.length() > 32)
    {
        QFileInfo qfInfo(p_qstrFilename);
        QString qstrSuffix = qfInfo.completeSuffix();
        qstrFilename = qfInfo.baseName();
        qstrFilename = qstrFilename.left(31 - qstrSuffix.length());
        qstrFilename += "." + qstrSuffix;
    }
    else
    {
        qstrFilename = p_qstrFilename;
    }

    return qstrFilename;
}

