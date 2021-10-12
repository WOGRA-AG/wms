#include "CftlCommandGetSchemeList.h"

CftlCommandGetSchemeList::CftlCommandGetSchemeList(CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess)
{
}

CftlCommandGetSchemeList::~CftlCommandGetSchemeList()
{

}

QList<QString> CftlCommandGetSchemeList::GetSchemes() const
{
    return m_qllSchemes;
}

bool CftlCommandGetSchemeList::CheckValid()
{
    return true;
}

int CftlCommandGetSchemeList::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    m_qllSchemes.clear();
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("Select SchemeName from WMS_SCHEME");

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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

