// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CdbCommandUpdateScheme.h"

CdbCommandUpdateScheme::CdbCommandUpdateScheme(CdmScheme* p_pScheme, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_rpScheme(p_pScheme)
{
}


CdbCommandUpdateScheme::~CdbCommandUpdateScheme()
{

}

bool CdbCommandUpdateScheme::CheckValid()
{
    return (m_rpScheme != nullptr);
}

int CdbCommandUpdateScheme::Execute()
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   qstrQuery = QString("Update WMS_DATABASE set Version = %1, DatabaseName = '%2' "
                       "where DatabaseId = %3")
      .arg(m_rpScheme->GetVersion())
      .arg(CwmsUtilities::MaskStringForChanges(m_rpScheme->GetSchemeName()))
      .arg(m_rpScheme->GetId());

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      lRet = GetDataAccess()->SaveRights(m_rpScheme->GetRights(),
                                         m_rpScheme->GetId(),
                                         "WMS_DATABASE_RIGHTS",
                                         "DatabaseId");
   }
   else
   {
      lRet = EC(eDmInvalidUpdateStatement);
   }

   return lRet;
}
