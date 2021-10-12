// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CftlCommandFindScheme.h"

CftlCommandFindScheme::CftlCommandFindScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_qstrSchemeName(p_qstrSchemeName),
  m_lSchemeId(0),
  m_pScheme(nullptr)
{
}

CftlCommandFindScheme::CftlCommandFindScheme(qint64 p_lSchemeId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_pScheme(nullptr)
{
}


CftlCommandFindScheme::~CftlCommandFindScheme()
{

}

bool CftlCommandFindScheme::CheckValid()
{
    return !m_qstrSchemeName.isEmpty();
}

int CftlCommandFindScheme::Execute()
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   QString qstrQuery;

   if (!m_qstrSchemeName.isEmpty())
   {
       cQSqlQuery.prepare("Select SchemeId, SchemeName, Version from WMS_SCHEME where SchemeName = ?");
       cQSqlQuery.addBindValue(m_qstrSchemeName);
   }
   else
   {
       cQSqlQuery.prepare("Select SchemeId, SchmeName, Version from WMS_SCHEME where SchemeId = ?");
       cQSqlQuery.addBindValue(m_lSchemeId);
   }

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
        qint64 lSchemeId = cQSqlQuery.value(0).toInt();

         // this is just for test if the correct one was found
         QString qstrKeyname = cQSqlQuery.value(1).toString();
         int iVersion = cQSqlQuery.value(2).toInt();

         m_pScheme = new CdmScheme(lSchemeId, qstrKeyname, iVersion);

         if(CHKPTR(m_pScheme))
         {
            lRet = GetDataAccess()->LoadRights(m_pScheme->GetRights(),
                                               m_pScheme->GetId(),
                                               "WMS_SCHEME_RIGHTS",
                                               "SchemeId");
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

void CftlCommandFindScheme::LoadLanguages()
{
   if (CHKPTR(m_pScheme))
   {
      QSqlQuery cQuery(GetSqlDatabase());
      cQuery.prepare("select LanguageId, Name from WMS_LANGUAGE where SchemeId = ?");
      cQuery.addBindValue(m_pScheme->GetId());

      if(SUCCESSFULL(ExecuteQuery(cQuery)))
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

CdmScheme* CftlCommandFindScheme::GetResult()
{
    return m_pScheme;
}
