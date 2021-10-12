#include "CdbCommandDeleteSchemeLanguage.h"

CdbCommandDeleteSchemeLanguage::CdbCommandDeleteSchemeLanguage(qint64 p_lSchemeId, int p_lLanguage, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_lLanguage(p_lLanguage)
{
}


CdbCommandDeleteSchemeLanguage::~CdbCommandDeleteSchemeLanguage()
{
}

bool CdbCommandDeleteSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && m_lLanguage > 0);
}

int CdbCommandDeleteSchemeLanguage::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQuery;
    QString qstrQuery;

    qstrQuery = QString("delete from WMS_LANGUAGE where DatabaseId = %1 and LanguageId = %2")
       .arg(m_lSchemeId)
       .arg(m_lLanguage);

    if(ExecuteQuery(qstrQuery, cQuery) > 0)
    {
       lRet = EC(eDmOk);
    }
    else
    {
        lRet = EC(eDmInvalidDeleteStatement);
    }

    return lRet;
}
