#include "CdmValueBinaryDocument.h"
#include "CdmMember.h"
#include "CdmObject.h"

#include "CftlCommandReadBinaryDocument.h"

CftlCommandReadBinaryDocument::CftlCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpCdmBinaryDocument(p_pCdmBinaryDocument)
{
}

CftlCommandReadBinaryDocument::~CftlCommandReadBinaryDocument()
{

}

QByteArray CftlCommandReadBinaryDocument::GetByteArray()
{
    return m_qByteArray;
}

bool CftlCommandReadBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpCdmBinaryDocument);
}

int CftlCommandReadBinaryDocument::Execute()
{
    int iRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    const CdmObject* pObject = m_rpCdmBinaryDocument->GetObject();
    const CdmMember* pMember = m_rpCdmBinaryDocument->GetMember();

    if (CHKPTR(pObject) && CHKPTR(pMember))
    {
        QString qstrTableName = GetClassTableNameFromObject(pObject);
        QString qstrFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString() + FTL_BIN_DOC_CONTENT_SUFFIX;


        // query for reading new id
        qstrQuery = QString("select %1 from %2 where %3 = ?")
                .arg(qstrFieldName)
                .arg(qstrTableName)
                .arg(FTL_OBJECT_ID_FIELD_NAME);

        cQSqlQuery.prepare((qstrQuery));
        cQSqlQuery.addBindValue((int)pObject->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
                QString qString64 = cQSqlQuery.value(0).toString();
                m_qByteArray = QByteArray::fromBase64(qString64.toLocal8Bit());
                iRet = EC(eDmOk);
            }
            else
            {
                iRet = EC(eDmNotUniqueQueryResult);
                ERR("No BinDoc found!!!");
            }
        }
    }

    return iRet;
}
