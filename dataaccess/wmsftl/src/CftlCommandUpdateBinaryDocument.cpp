#include <QSqlError>
#include <QFileInfo>

// WMS Includes
#include "CdmMember.h"
#include "CdmValueBinaryDocument.h"
#include "CdmObject.h"

#include "CftlCommandUpdateBinaryDocument.h"

CftlCommandUpdateBinaryDocument::CftlCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpValue(p_pValue)
{
}

CftlCommandUpdateBinaryDocument::~CftlCommandUpdateBinaryDocument()
{

}

bool CftlCommandUpdateBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpValue);
}

int CftlCommandUpdateBinaryDocument::Execute()
{
    int iRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    const CdmObject* pObject = m_rpValue->GetObject();
    const CdmMember* pMember = m_rpValue->GetMember();

    if (CHKPTR(pObject) && CHKPTR(pMember))
    {
        QString qstrTableName = GetClassTableNameFromObject(pObject);
        QString qstrFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString() + FTL_BIN_DOC_CONTENT_SUFFIX;


        // query for reading new id
        QString qstrQuery = QString("update %1 set %2 = ? where %3 = ?")
                .arg(qstrTableName)
                .arg(qstrFieldName)
                .arg(FTL_OBJECT_ID_FIELD_NAME);

        cQSqlQuery.prepare((qstrQuery));
        cQSqlQuery.addBindValue(m_rpValue->GetByteArray());
        cQSqlQuery.addBindValue((int)pObject->GetId());

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            iRet = EC(eDmOk);
         }
         else
         {
            iRet = EC(eDmInvalidInsertStatement);
            // must be ok because the other values won't be saved and it is probabply a sizing problem
            ERR("Insert of Binary Document failed");
            ERR("Insert Query Error: "+ cQSqlQuery.lastError().text());
         }
    }

    return iRet;
}

