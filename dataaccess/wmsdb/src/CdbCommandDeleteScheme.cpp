// Own Includes
#include "CdbCommandCleanupDB.h"
#include "CdbCommandDeleteScheme.h"

CdbCommandDeleteScheme::CdbCommandDeleteScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName)
{
}


CdbCommandDeleteScheme::~CdbCommandDeleteScheme()
{

}

bool CdbCommandDeleteScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty());
}

int CdbCommandDeleteScheme::Execute()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    long lId = GetSchemeId();

    qstrQuery = QString("delete from WMS_DATABASE where DataBaseName = '%1'")
                        .arg(CwmsUtilities::MaskStringForChanges(m_qstrSchemeName));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       lRet = GetDataAccess()->DeleteRights(lId, "WMS_DATABASE_RIGHTS", "DatabaseId");
    }

    CdbCommandCleanupDB command(GetDataAccess());

    if (!SUCCESSFULL(command.Run()))
    {
       lRet = CdmLogging::eDmInvalidDeleteStatement;
    }

    return lRet;
}

void CdbCommandDeleteScheme::DeleteLanguages(long p_lSchemeId)
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_LANGUAGE where SchemeId = ?");
    cQSqlQuery.addBindValue((int)p_lSchemeId);

    if(!SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        ERR("Failed deleting Languages to Scheme!");
    }
}

long CdbCommandDeleteScheme::GetSchemeId()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("Select DatabaseId from WMS_DATABASE where DataBaseName = '%1'")
     .arg(CwmsUtilities::MaskStringForChanges(m_qstrSchemeName));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            lRet = cQSqlQuery.value(0).toInt();
        }
        else
        {
            lRet = EC(eDmFalse);
        }
    }
    else
    {
        lRet = EC(eDmInvalidSelectStatement);
    }

   return lRet;
}
