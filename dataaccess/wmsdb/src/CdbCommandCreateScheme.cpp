// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CdbCommandCreateScheme.h"

CdbCommandCreateScheme::CdbCommandCreateScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName),
      m_pScheme(nullptr)
{
}


CdbCommandCreateScheme::~CdbCommandCreateScheme()
{

}

bool CdbCommandCreateScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty());
}

int CdbCommandCreateScheme::Execute()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("Insert into WMS_DATABASE (DataBaseName, Version) values('%1', 1)")
                       .arg(CwmsUtilities::MaskStringForChanges(m_qstrSchemeName));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {

      qstrQuery = QString("Select DatabaseId, DatabaseName, Version from WMS_DATABASE where DataBaseName = '%1'")
                     .arg(CwmsUtilities::MaskString(m_qstrSchemeName));


      if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            // Value in col 0 is DataBaseId
            // Value in col 1 is DataBaseName
            // Value in col 2 is Version

            long lDBId = cQSqlQuery.value(0).toInt();
            int iVersion = cQSqlQuery.value(2).toInt();

            // this is just for test if the correct one was found
            QString qstrKeyname = cQSqlQuery.value(1).toString();

            m_pScheme = new CdmScheme(lDBId, qstrKeyname, iVersion);

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

CdmScheme* CdbCommandCreateScheme::GetResult()
{
    return m_pScheme;
}
