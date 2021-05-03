#include "CdbCommandGetSchemeList.h"

CdbCommandGetSchemeList::CdbCommandGetSchemeList(CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess)
{
}

CdbCommandGetSchemeList::~CdbCommandGetSchemeList()
{

}

QList<QString> CdbCommandGetSchemeList::GetSchemes() const
{
    return m_qllSchemes;
}

bool CdbCommandGetSchemeList::CheckValid()
{
    return true;
}

int CdbCommandGetSchemeList::Execute()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    m_qllSchemes.clear();
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("Select DataBaseName from WMS_DATABASE");

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         do
         {
            QString qstrDatabaseName = cQSqlQuery.value(0).toString();
            m_qllSchemes.append(qstrDatabaseName);
         }
         while(cQSqlQuery.next());

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmNoDatabaseExists);
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

