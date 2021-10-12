#include "CftlCommandDeleteSchemeLanguage.h"

CftlCommandDeleteSchemeLanguage::CftlCommandDeleteSchemeLanguage(qint64 p_lSchemeId, int p_lLanguage, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_lLanguage(p_lLanguage)
{
}


CftlCommandDeleteSchemeLanguage::~CftlCommandDeleteSchemeLanguage()
{
}

bool CftlCommandDeleteSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && m_lLanguage > 0);
}

int CftlCommandDeleteSchemeLanguage::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQuery(GetSqlDatabase());

    cQuery.prepare("delete from WMS_LANGUAGE where SchemeId = %1 and LanguageId = %2");
    cQuery.addBindValue(m_lSchemeId);
    cQuery.addBindValue(m_lLanguage);

    if(ExecuteQuery(cQuery) > 0)
    {
       lRet = EC(eDmOk);
    }
    else
    {
        lRet = EC(eDmInvalidDeleteStatement);
    }

    return lRet;
}
