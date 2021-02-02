#include "CdmValueBinaryDocument.h"

#include "CdbCommandReadBinaryDocument.h"

CdbCommandReadBinaryDocument::CdbCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_rpCdmBinaryDocument(p_pCdmBinaryDocument)
{
}

CdbCommandReadBinaryDocument::~CdbCommandReadBinaryDocument()
{

}

bool CdbCommandReadBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpCdmBinaryDocument);
}

int CdbCommandReadBinaryDocument::Execute()
{
   int iRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   // query for reading new id
   qstrQuery = QString("select Val, Filename, Type from WMS_VALUE_BINARYDOCUMENT where BinaryDocumentId = %1")
                     .arg(m_rpCdmBinaryDocument->GetId());

   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         QString qString64 = cQSqlQuery.value(0).toString();
         QString qstrFilename = cQSqlQuery.value(1).toString();
         QString qstrFiletype = cQSqlQuery.value(2).toString();
         m_rpCdmBinaryDocument->SetFilenameAndTypeWithoutModifyingValue(qstrFilename, qstrFiletype);
         m_qByteArray = QByteArray::fromBase64(qString64.toLocal8Bit());
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(eDmNotUniqueQueryResult);
         ERR("No BinDoc found!!!");
      }
   }

    return iRet;
}

QByteArray CdbCommandReadBinaryDocument::GetByteArray()
{
    return m_qByteArray;
}
