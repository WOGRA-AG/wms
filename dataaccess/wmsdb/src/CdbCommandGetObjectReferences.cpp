#include "CdbCommandGetObjectReferences.h"

CdbCommandGetObjectReferences::CdbCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CdbDataAccess* p_pDataAccess)
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
   qint64 lRet = GetDataAccess()->ExecuteQuery(qstrSql, cQSqlQuery);

    if(lRet > 0)
    {
       cQSqlQuery.first();

       while(cQSqlQuery.isValid())
       {
         qint64 lObjectListId = cQSqlQuery.value(0).toInt();
         qint64 lObjectId = cQSqlQuery.value(1).toInt();
          m_qmReferences.insert(lObjectId, lObjectListId);
          cQSqlQuery.next();
       }
    }

    return lRet;
}

QMap<qint64,qint64> CdbCommandGetObjectReferences::GetResult()
{
    return m_qmReferences;
}
