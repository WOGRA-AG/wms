#include "CwnCommandGetCounterValue.h"

#include "CdmValueCounter.h"
#include "CdmObject.h"

#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetCounterValue::CwnCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_rpCdmCounter(p_pCdmCounter),
      m_lObjectListId(0),
      m_lValueId(0)
{

}

CwnCommandGetCounterValue::CwnCommandGetCounterValue(qint64 p_lObjectListId,qint64 p_lValueId, QString p_qstrKeyname, CwnDataAccess *p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_rpCdmCounter(nullptr),
      m_lObjectListId(p_lObjectListId),
      m_lValueId(p_lValueId),
      m_qstrKeyname(p_qstrKeyname)
{

}

CwnCommandGetCounterValue::~CwnCommandGetCounterValue()
{
}

bool CwnCommandGetCounterValue::CheckValid()
{
    return (CHKPTR(m_rpCdmCounter) || (m_lObjectListId >0 && m_lValueId >0 && !m_qstrKeyname.isEmpty()));
}

int CwnCommandGetCounterValue::Execute()
{
    if (m_rpCdmCounter)
    {
        const CdmObject* pCdmObject = m_rpCdmCounter->GetObject();

        if (CHKPTR(pCdmObject))
        {
          qint64 lObjectListId = pCdmObject->GetObjectContainerId();
           ((CdmValueLong*)m_rpCdmCounter)->SetValue(GetCounterValue(lObjectListId,
                                                                    m_rpCdmCounter->GetId(),
                                                                    m_rpCdmCounter->GetKeyname()));
        }
    }
    else
    {
        GetCounterValue(m_lObjectListId,
                        m_lValueId,
                        m_qstrKeyname);
    }

    return EC(eDmOk);
}


qint64 CwnCommandGetCounterValue::GetCounterValue(qint64 p_lObjectListId,
                                            qint64 p_lValueId,
                                             QString p_qstrKeyname)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QString qstrQuery;


   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:COUNTER:WMS_VALUE)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' RETURN max(v.val)+1")
                       .arg(p_lObjectListId)
                       .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname));

   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswer(Ret);
  qint64 lValue = Ret.toInt();
   lRet = Ret.toInt();

   QTime qtCurrent = QTime::currentTime();
   int iTimeStamp = qtCurrent.msec() * qtCurrent.second() * qtCurrent.minute() * qtCurrent.hour();

   qstrQuery = QString("MATCH (v:COUNTER:WMS_VALUE) WHERE id(v)=%3 SET v.val=%1, v.timestamp = %2")
                          .arg(lValue)
                          .arg(iTimeStamp)
                          .arg(p_lValueId);

   payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   interpretAnswer(Ret);

   if(lRet> 0)
   {
        lRet = MakeCounterValueUnique(static_cast<int>(lValue),
                                       static_cast<int>(iTimeStamp),
                                       p_qstrKeyname,
                                       static_cast<int>(p_lObjectListId),
                                       static_cast<int>(p_lValueId));
   }
   return lRet;
}


int CwnCommandGetCounterValue::MakeCounterValueUnique(int p_iCounter,
                                              int p_iTimeStamp,
                                              QString p_qstrKeyname,
                                              int p_lObjectId,
                                              int p_iValueId)
{
   int iRet = CdmLogging::eDmUnknownClassAccessError;
   QString qstrQuery;
   int iSuccess = 0;

   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:COUNTER:WMS_VALUE)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' AND v.val = %3 "
                       "RETURN COUNT(v)")
                   .arg(p_lObjectId)
                   .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname))
                   .arg(p_iCounter);


   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswer(Ret);

   iSuccess = Ret.toInt();

   if(iSuccess > 0)
   {
     qint64 lValue = iSuccess;
      if (lValue == 1)
      {
        iRet = p_iCounter;
      }
      else if (lValue > 1)
      {
        iRet = IncreaseCounterValue(p_iCounter,
                                    p_iTimeStamp,
                                    p_qstrKeyname,
                                    p_lObjectId,
                                    p_iValueId);
      }
   }
   return iRet;
}


int CwnCommandGetCounterValue::IncreaseCounterValue(int p_iCounter,
                                            int p_iTimeStamp,
                                            QString p_qstrKeyname,
                                            int p_lObjectId,
                                            int p_iValueId)
{
   int iRet = p_iCounter;

   if (CheckIncreaseCounterNeeded(p_iCounter,
                                  p_iTimeStamp,
                                  p_qstrKeyname,
                                  p_lObjectId,
                                  p_iValueId))
   {
      iRet = GetCounterValue(p_lObjectId, p_iValueId, p_qstrKeyname);
   }

   return iRet;
}

bool CwnCommandGetCounterValue::CheckIncreaseCounterNeeded(int p_iCounter,
                                                   int p_iTimeStamp,
                                                   QString p_qstrKeyname,
                                                   int p_lObjectId,
                                                   int)
{
   bool bRet = false;
   QString qstrQuery;
   int iSuccess = 0;


   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:COUNTER:WMS_VALUE)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' AND v.val = %3 "
                       "RETURN min(v.timestamp)")
      .arg(p_lObjectId)
      .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname))
      .arg(p_iCounter);

   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswer(Ret);

   iSuccess = Ret.toInt();

   if(iSuccess > 0)
   {
     qint64 lValue = iSuccess;

      if (lValue != p_iTimeStamp)
      {
        bRet = true;
      }
   }

   return bRet;
}

void CwnCommandGetCounterValue::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());
    this->answer=nullptr;

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            Ret = row->at(0);
        }
        else
            Ret=0;
    }

}
