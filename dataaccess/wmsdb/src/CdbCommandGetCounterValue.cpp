#include "CdmValueCounter.h"
#include "CdmObject.h"

#include "CdbCommandGetCounterValue.h"

CdbCommandGetCounterValue::CdbCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_rpCdmCounter(p_pCdmCounter)
{
}

CdbCommandGetCounterValue::~CdbCommandGetCounterValue()
{
}

bool CdbCommandGetCounterValue::CheckValid()
{
    return (CHKPTR(m_rpCdmCounter));
}

int CdbCommandGetCounterValue::Execute()
{
    if (m_rpCdmCounter)
    {
        const CdmObject* pCdmObject = m_rpCdmCounter->GetDataObject();

        if (CHKPTR(pCdmObject))
        {
          qint64 lObjectListId = pCdmObject->GetObjectContainerId();
           ((CdmValueLong*)m_rpCdmCounter)->SetValue(GetCounterValue(lObjectListId,
                                                                    m_rpCdmCounter->GetMemberId()));
        }
    }

    return EC(eDmOk);
}

qint64 CdbCommandGetCounterValue::GetCounterValue(qint64 p_lObjectListId,
                                            qint64 p_lMemberId)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   qstrQuery = QString("select max(val) + 1 from V_VALUE_COUNTER where objectlistid = %1 and memberid = %2")
                        .arg(p_lObjectListId)
                        .arg(p_lMemberId);

   lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);


      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
         lRet = cQSqlQuery.value(0).toInt();

         if (lRet == 0)
         {
             lRet += 1;
         }
      }

   return lRet;
}
