#include "CdbCommandExistClass.h"

CdbCommandExistClass::CdbCommandExistClass(qint64 p_lSchemeId, QString p_qstrKeyname, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_qstrKeyname(p_qstrKeyname),
  m_bResult(false)
{
}

CdbCommandExistClass::~CdbCommandExistClass()
{
}

bool CdbCommandExistClass::CheckValid()
{
    return (m_lSchemeId > 0 &&
            !m_qstrKeyname.isEmpty());
}

int CdbCommandExistClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // query for reading new id
    qstrQuery = QString("select ClassId from WMS_CLASS where Keyname = '%1' and DatabaseId = %2")
                        .arg(CwmsUtilities::MaskString(m_qstrKeyname))
                        .arg(m_lSchemeId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       cQSqlQuery.first();
       if(cQSqlQuery.isValid())
       {
          m_bResult = true;
          iRet = EC(eDmTrue);
       }
       else
       {
          iRet = EC(eDmFalse);
          INFO("Class with Keyname " + m_qstrKeyname + " not found.");
       }
    }
    else
    {
       iRet = EC(eDmInvalidSelectStatement);
       ERR("Class Select pronounced an error.");
    }

    return iRet;
}

bool CdbCommandExistClass::GetResult()
{
    return m_bResult;
}
