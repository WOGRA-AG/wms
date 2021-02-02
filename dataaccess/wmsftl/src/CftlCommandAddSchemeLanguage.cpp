#include "CftlCommandAddSchemeLanguage.h"

CftlCommandAddSchemeLanguage::CftlCommandAddSchemeLanguage(long p_lSchemeId,
                                                         QString p_qstrLanguage,
                                                         CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_qstrLanguage(p_qstrLanguage)
{
}


CftlCommandAddSchemeLanguage::~CftlCommandAddSchemeLanguage()
{

}

bool CftlCommandAddSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && !m_qstrLanguage.isEmpty());
}

int CftlCommandAddSchemeLanguage::Execute()
{
    long lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQuery(GetSqlDatabase());


    cQuery.prepare("insert into WMS_LANGUAGE (SchemeId, Name) values(?, ?)");
    cQuery.addBindValue((int)m_lSchemeId);
    cQuery.addBindValue(m_qstrLanguage);

    if(SUCCESSFULL(ExecuteQuery(cQuery)))
    {
        cQuery.prepare("select LanguageId from WMS_LANGUAGE where SchemeId = ? and Name = ?");
        cQuery.addBindValue((int)m_lSchemeId);
        cQuery.addBindValue(m_qstrLanguage);

      if(ExecuteQuery(cQuery) > 0)
      {
         cQuery.first();

         if(cQuery.isValid())
         {
            lRet = cQuery.value(0).toInt();
         }
      }
    }

    return lRet;
}
