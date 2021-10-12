// WMS Includes
#include "CdmScheme.h"

// Own Includes
#include "CftlCommandUpdateScheme.h"

CftlCommandUpdateScheme::CftlCommandUpdateScheme(CdmScheme* p_pScheme, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpScheme(p_pScheme)
{
}


CftlCommandUpdateScheme::~CftlCommandUpdateScheme()
{

}

bool CftlCommandUpdateScheme::CheckValid()
{
    return (m_rpScheme != nullptr);
}

int CftlCommandUpdateScheme::Execute()
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   cQSqlQuery.prepare("Update WMS_SCHEME set Version = ?, SchemeName = ? where SchemeId = ?");
   cQSqlQuery.addBindValue(m_rpScheme->GetVersion());
   cQSqlQuery.addBindValue(m_rpScheme->GetSchemeName());
   cQSqlQuery.addBindValue(m_rpScheme->GetId());

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      lRet = GetDataAccess()->SaveRights(m_rpScheme->GetRights(),
                                         m_rpScheme->GetId(),
                                         "WMS_SCHEME_RIGHTS",
                                         "SchemeId");
   }
   else
   {
      lRet = EC(eDmInvalidUpdateStatement);
   }

   return lRet;
}
