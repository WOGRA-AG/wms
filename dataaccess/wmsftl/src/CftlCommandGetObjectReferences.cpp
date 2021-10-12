#include "CftlCommandGetObjectReferences.h"

CftlCommandGetObjectReferences::CftlCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lContainerId(p_lContainerId),
  m_lObjectId(p_lObjectId)
{
}


CftlCommandGetObjectReferences::~CftlCommandGetObjectReferences()
{

}

bool CftlCommandGetObjectReferences::CheckValid()
{
    return (m_lContainerId > 0 && m_lObjectId > 0);
}

int CftlCommandGetObjectReferences::Execute()
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("select Ref_Container_ID, Ref_Object_ID from WMS_DM_OBJECT_REFERENCE where ObjectId = ? and ContainerId = ?");
    cQSqlQuery.addBindValue(m_lObjectId);
    cQSqlQuery.addBindValue(m_lContainerId);

   qint64 lRet = ExecuteQuery(cQSqlQuery);

    if(SUCCESSFULL(lRet))
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

QMap<qint64,qint64> CftlCommandGetObjectReferences::GetResult()
{
    return m_qmReferences;
}
