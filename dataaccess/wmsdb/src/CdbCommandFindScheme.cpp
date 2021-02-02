// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CdbCommandFindScheme.h"

CdbCommandFindScheme::CdbCommandFindScheme(QString p_qstrSchemeName, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_qstrSchemeName(p_qstrSchemeName),
  m_lSchemeId(0),
  m_pScheme(nullptr)
{
}

CdbCommandFindScheme::CdbCommandFindScheme(long p_lSchemeId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_pScheme(nullptr)
{
}

CdbCommandFindScheme::~CdbCommandFindScheme()
{

}

bool CdbCommandFindScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty() || m_lSchemeId > 0);
}

int CdbCommandFindScheme::Execute()
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   if (!m_qstrSchemeName.isEmpty())
   {
        qstrQuery = QString("Select DatabaseId, DatabaseName, Version from WMS_DATABASE where DataBaseName = '%1'")
          .arg(CwmsUtilities::MaskString(m_qstrSchemeName));
   }
   else
   {
       qstrQuery = QString("Select DatabaseId, DatabaseName, Version from WMS_DATABASE where DatabaseId = %1")
         .arg(m_lSchemeId);
   }

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {

         // Value in col 0 is DataBaseId
         // Value in col 1 is DataBaseName
         // Value in col 2 is Version

         long lDBId = cQSqlQuery.value(0).toInt();

         // this is just for test if the correct one was found
         QString qstrKeyname = cQSqlQuery.value(1).toString();
         int iVersion = cQSqlQuery.value(2).toInt();

         m_pScheme = new CdmScheme(lDBId, qstrKeyname, iVersion);

         if(CHKPTR(m_pScheme))
         {
            lRet = GetDataAccess()->LoadRights(m_pScheme->GetRights(),
                                               m_pScheme->GetId(),
                                               "WMS_DATABASE_RIGHTS",
                                               "DatabaseId");
            LoadLanguages();
         }
         else
         {
            lRet = EC(eDmMemoryAllocationError);
            ERR("Memory Allocation Error (could not initialize new object)");
         }
      }
      else
      {
         lRet = EC(eDmNotUniqueQueryResult);
         ERR("No Database found!!!");
      }
   }
   else
   {
      lRet = EC(eDmInvalidSelectStatement);
   }

    return lRet;

}

void CdbCommandFindScheme::LoadLanguages()
{
   if (CHKPTR(m_pScheme))
   {
      QSqlQuery cQuery;
      QString qstrQuery = QString("select LanguageId, Name from WMS_LANGUAGE where DatabaseId = %1")
         .arg(m_pScheme->GetId());

      if(ExecuteQuery(qstrQuery, cQuery) > 0)
      {
         cQuery.first();
         while(cQuery.isValid())
         {
            int iLanguageId = cQuery.value(0).toInt();
            QString qstrName = cQuery.value(1).toString();
            m_pScheme->AddLanguage(iLanguageId, qstrName);
            cQuery.next();
         }
      }
   }
}

CdmScheme* CdbCommandFindScheme::GetResult()
{
    return m_pScheme;
}
