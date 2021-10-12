// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CftlCommandCreateScheme.h"

CftlCommandCreateScheme::CftlCommandCreateScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName),
      m_pScheme(nullptr)
{
}


CftlCommandCreateScheme::~CftlCommandCreateScheme()
{

}

bool CftlCommandCreateScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty());
}

int CftlCommandCreateScheme::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());


    cQSqlQuery.prepare("Insert into WMS_SCHEME (SchemeName, Version) values(?, 1)");
    cQSqlQuery.addBindValue(m_qstrSchemeName);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
          cQSqlQuery.prepare("Select SchemeId, Version from WMS_SCHEME where SchemeName = ?");
          cQSqlQuery.addBindValue(m_qstrSchemeName);



      if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
           qint64 lSchemeId = cQSqlQuery.value(0).toInt();
            int iVersion = cQSqlQuery.value(1).toInt();
            m_pScheme = new CdmScheme(lSchemeId, m_qstrSchemeName, iVersion);

            if(CHKPTR(m_pScheme))
            {
               lRet = EC(eDmOk);
            }
            else
            {
               lRet = EC(eDmMemoryAllocationError);
               ERR("Memory Allocation Error (could not initialize new object");
            }
         }
         else
         {
            lRet = EC(eDmInvalidSelectStatement);
            ERR("Db Creation not succeeded (SELECT COMMAND). Db Name: " + m_qstrSchemeName);
         }
      }
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
      ERR("Db Creation not succeeded (INSERT COMMAND). Db Name: " + m_qstrSchemeName);
    }

    return lRet;
}

CdmScheme* CftlCommandCreateScheme::GetResult()
{
    return m_pScheme;
}
