#include "CftlCommandExistScheme.h"

CftlCommandExistScheme::CftlCommandExistScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName)
{
}

CftlCommandExistScheme::~CftlCommandExistScheme()
{
}

bool CftlCommandExistScheme::CheckValid()
{
    return !m_qstrSchemeName.isEmpty();
}

int CftlCommandExistScheme::Execute()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select SchemeId from WMS_SCHEME where SchemeName = ?");
    cQSqlQuery.addBindValue(m_qstrSchemeName);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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
