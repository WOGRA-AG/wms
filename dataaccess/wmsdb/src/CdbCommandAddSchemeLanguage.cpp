#include "CdbCommandAddSchemeLanguage.h"

CdbCommandAddSchemeLanguage::CdbCommandAddSchemeLanguage(qint64 p_lSchemeId,
                                                         QString p_qstrLanguage,
                                                         CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_qstrLanguage(p_qstrLanguage)
{
}


CdbCommandAddSchemeLanguage::~CdbCommandAddSchemeLanguage()
{

}

bool CdbCommandAddSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && !m_qstrLanguage.isEmpty());
}

int CdbCommandAddSchemeLanguage::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQuery;
    QString qstrQuery;

    qstrQuery = QString("insert into WMS_LANGUAGE (DatabaseId, Name) values(%1, '%2')")
                       .arg(m_lSchemeId)
                       .arg(CwmsUtilities::MaskStringForChanges(m_qstrLanguage));

    if(ExecuteQuery(qstrQuery, cQuery) > 0)
    {
      qstrQuery = QString("select LanguageId from WMS_LANGUAGE where DatabaseId = %1 and Name = '%2'")
         .arg(m_lSchemeId)
         .arg(CwmsUtilities::MaskStringForChanges(m_qstrLanguage));

      if(ExecuteQuery(qstrQuery, cQuery) > 0)
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
