#include "CdbCommandExistScheme.h"

CdbCommandExistScheme::CdbCommandExistScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName)
{
}

CdbCommandExistScheme::~CdbCommandExistScheme()
{

}

bool CdbCommandExistScheme::CheckValid()
{
    return !m_qstrSchemeName.isEmpty();
}

int CdbCommandExistScheme::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
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
