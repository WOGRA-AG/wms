#include "CdbCommandDeleteClass.h"

CdbCommandDeleteClass::CdbCommandDeleteClass(qint64 p_lClassId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lClassId(p_lClassId)
{
}


CdbCommandDeleteClass::~CdbCommandDeleteClass()
{
}


bool CdbCommandDeleteClass::CheckValid()
{
    return (m_lClassId >0);
}

int CdbCommandDeleteClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // query for reading new id
    qstrQuery = QString("delete from WMS_CLASS where ClassID = %1")
                      .arg(m_lClassId);

    // Deleting class itselves
    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       iRet = EC(eDmOk);
    }
    else
    {
       iRet = EC(eDmInvalidDeleteStatement);
       ERR("The Class could not be deleted (Error in Query)!!!");
    }

    return iRet;
}
