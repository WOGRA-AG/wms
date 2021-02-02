#include "CftlCommandExistClass.h"

CftlCommandExistClass::CftlCommandExistClass(long p_lSchemeId, QString p_qstrKeyname, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_qstrKeyname(p_qstrKeyname),
  m_bResult(false)
{
}

CftlCommandExistClass::~CftlCommandExistClass()
{
}

bool CftlCommandExistClass::CheckValid()
{
    return (m_lSchemeId > 0 &&
            !m_qstrKeyname.isEmpty());
}

int CftlCommandExistClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    // query for reading new id
    cQSqlQuery.prepare("select ClassId from WMS_CLASS where Keyname = ? and SchemeId = ?");
    cQSqlQuery.addBindValue(m_qstrKeyname);
    cQSqlQuery.addBindValue((int)m_lSchemeId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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

bool CftlCommandExistClass::GetResult()
{
    return m_bResult;
}
