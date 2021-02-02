#include "CdbCommandGetObjectReferences.h"

CdbCommandGetObjectReferences::CdbCommandGetObjectReferences(long p_lContainerId, long p_lObjectId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lContainerId(p_lContainerId),
  m_lObjectId(p_lObjectId)
{
}


CdbCommandGetObjectReferences::~CdbCommandGetObjectReferences()
{

}

bool CdbCommandGetObjectReferences::CheckValid()
{
    return (m_lContainerId > 0 && m_lObjectId > 0);
}

int CdbCommandGetObjectReferences::Execute()
{
    QString qstrSql = QString ("select objectlistid, objectid from V_VALUE_OBJECTREFERENCE where Val = %1 and orefobjectlist = %2")
       .arg(m_lObjectId)
       .arg(m_lContainerId);

    QSqlQuery cQSqlQuery;
    long lRet = GetDataAccess()->ExecuteQuery(qstrSql, cQSqlQuery);

    if(lRet > 0)
    {
       cQSqlQuery.first();

       while(cQSqlQuery.isValid())
       {
          long lObjectListId = cQSqlQuery.value(0).toInt();
          long lObjectId = cQSqlQuery.value(1).toInt();
          m_qmReferences.insert(lObjectId, lObjectListId);
          cQSqlQuery.next();
       }
    }

    return lRet;
}

QMap<long,long> CdbCommandGetObjectReferences::GetResult()
{
    return m_qmReferences;
}
