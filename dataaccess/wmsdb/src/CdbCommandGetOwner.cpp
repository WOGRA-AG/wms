#include "CdbCommandGetOwner.h"

CdbCommandGetOwner::CdbCommandGetOwner(qint64 p_lContainerId,qint64 p_lObjectId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_lObjectId(p_lObjectId),
      m_lOwnerContainerId(0),
      m_lOwnerObjectId(0)
{
}

CdbCommandGetOwner::~CdbCommandGetOwner()
{

}

bool CdbCommandGetOwner::CheckValid()
{
    return (m_lContainerId > 0);
}

int CdbCommandGetOwner::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (m_lObjectId > 0)
    {
        lRet = FindObjectOwner();
    }
    else
    {
        lRet = FindContainerOwner();
    }

    return lRet;
}

qint64 CdbCommandGetOwner::GetOwnerObjectId()
{
    return m_lOwnerObjectId;
}

qint64 CdbCommandGetOwner::GetOwnerContainerId()
{
    return m_lOwnerContainerId;
}
qint64 CdbCommandGetOwner::FindObjectOwner()
{
    QString qstrSql = QString ("select objectlistid, objectid from V_VALUE_OBJECTREFERENCE where Val = %1 and orefobjectlist = %2 and Owner = true")
                               .arg(m_lObjectId)
                               .arg(m_lContainerId);

    QSqlQuery cQSqlQuery;
   qint64 lRet = GetDataAccess()->ExecuteQuery(qstrSql, cQSqlQuery);

    if(lRet > 0)
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          m_lOwnerContainerId = cQSqlQuery.value(0).toInt();
          m_lOwnerObjectId = cQSqlQuery.value(1).toInt();
       }
       else
       {
          lRet = FindContainerOwner();
       }
    }

    return lRet;
}

qint64 CdbCommandGetOwner::FindContainerOwner()
{
    QString qstrSql = QString ("select objectlistid, objectid from V_VALUE_OBJECTLISTREFERENCE where Val = %1 and Owner = true")
       .arg(m_lContainerId);

    QSqlQuery cQSqlQuery;
   qint64 lRet = GetDataAccess()->ExecuteQuery(qstrSql, cQSqlQuery);

    if(lRet > 0)
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          m_lOwnerContainerId = cQSqlQuery.value(0).toInt();
          m_lOwnerObjectId = cQSqlQuery.value(1).toInt();
       }
    }

    return lRet;
}
