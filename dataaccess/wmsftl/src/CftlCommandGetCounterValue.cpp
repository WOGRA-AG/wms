
// WMS Includes
#include "CdmValueCounter.h"
#include "CdmObject.h"
#include "CdmMember.h"

// Own Includes
#include "CftlCommandGetCounterValue.h"

// DEFINES
#define MAX_RECURSION 5

CftlCommandGetCounterValue::CftlCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpCdmCounter(p_pCdmCounter),
      m_iRecursionCount(0)
{
}

CftlCommandGetCounterValue::CftlCommandGetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue, CftlDataAccess *p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_rpCdmCounter(dynamic_cast<CdmValueCounter*>(p_pValue)),
      m_iRecursionCount(0)

{
    Q_UNUSED(p_pContainer);
}

CftlCommandGetCounterValue::~CftlCommandGetCounterValue()
{
}

bool CftlCommandGetCounterValue::CheckValid()
{
    return (CHKPTR(m_rpCdmCounter));
}

int CftlCommandGetCounterValue::Execute()
{
    if (m_rpCdmCounter)
    {
        const CdmObject* pCdmObject = m_rpCdmCounter->GetObject();

        if (CHKPTR(pCdmObject))
        {
            ((CdmValueLong*)m_rpCdmCounter)->SetValue(GetCounterValue(pCdmObject));
        }

    }

    return EC(eDmOk);
}

long CftlCommandGetCounterValue::GetCounterValue(const CdmObject* p_pObject)
{
    ++m_iRecursionCount;
    long lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pObject))
    {
        QString qstrTableName = GetClassTableNameFromObject(p_pObject);

        if (!qstrTableName.isEmpty())
        {
            const CdmMember* pMember = m_rpCdmCounter->GetMember();

            if (CHKPTR(pMember))
            {
                QString qstrFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();
                QSqlQuery cQSqlQuery(GetSqlDatabase());
                QString qstrQuery = QString("select MAX(%1) + 1 from %2 where %3 = ?")
                        .arg(qstrFieldName)
                        .arg(qstrTableName)
                        .arg(FTL_CONTAINER_ID_FIELD_NAME);
                cQSqlQuery.prepare(qstrQuery);
                cQSqlQuery.addBindValue((int)p_pObject->GetObjectContainerId());

                if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                {
                    long lValue = 0;
                    cQSqlQuery.first();

                    if(cQSqlQuery.isValid())
                    {
                        lValue = cQSqlQuery.value(0).toInt();
                    }

                    QSqlQuery cQuery(GetSqlDatabase());

                    QDateTime qdCurrent = QDateTime::currentDateTime();
                    QString qstrQuery = QString("update %1 set %2 = ?, %3 = ? where %4 = ?")
                            .arg(qstrTableName)
                            .arg(qstrFieldName)
                            .arg(FTL_LAST_MODIFIED)
                            .arg(FTL_CONTAINER_ID_FIELD_NAME);
                    cQuery.prepare(qstrQuery);
                    cQuery.addBindValue((int)lValue);
                    cQuery.addBindValue(qdCurrent);
                    cQuery.addBindValue((int)p_pObject->GetObjectContainerId());

                    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
                    {
                        lRet = lValue;

                        lRet = MakeCounterValueUnique(lValue,
                                                      qdCurrent,
                                                      qstrTableName,
                                                      qstrFieldName,
                                                      p_pObject->GetObjectContainerId());
                    }
                }
            }
        }
    }

    return lRet;
}

int CftlCommandGetCounterValue::MakeCounterValueUnique(int p_iCounter,
                                                       QDateTime qdCurrentDateTime,
                                                       QString p_qstrTableName,
                                                       QString p_qstrFieldName,
                                                       long p_lContainerId)
{
    int iRet = 0;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery = QString("select COUNT(*) from %1 where %2 = ? and %3 = ?")
            .arg(p_qstrTableName)
            .arg(p_qstrFieldName)
            .arg(FTL_CONTAINER_ID_FIELD_NAME);
    cQSqlQuery.prepare(qstrQuery);
    cQSqlQuery.addBindValue(p_iCounter);
    cQSqlQuery.addBindValue((int)p_lContainerId);

    if(ExecuteQuery(cQSqlQuery))
    {
        long lValue = 0;
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            lValue = cQSqlQuery.value(0).toInt();

            if (lValue == 1)
            {
                iRet = p_iCounter;
            }
            else if (lValue > 1)
            {
                iRet = IncreaseCounterValue(p_iCounter,
                                            qdCurrentDateTime,
                                            p_qstrTableName,
                                            p_qstrFieldName,
                                            p_lContainerId);
            }
        }
    }


    return iRet;
}

int CftlCommandGetCounterValue::IncreaseCounterValue(int p_iCounter,
                                                     QDateTime qdCurrentDateTime,
                                                     QString p_qstrTableName,
                                                     QString p_qstrFieldName,
                                                     long p_lContainerId)
{
    int iRet = p_iCounter;

    if (CheckIncreaseCounterNeeded(p_iCounter,
                                   qdCurrentDateTime,
                                   p_qstrTableName,
                                   p_qstrFieldName,
                                   p_lContainerId))
    {
        iRet = GetCounterValue(m_rpCdmCounter->GetObject());
    }

    return iRet;
}

bool CftlCommandGetCounterValue::CheckIncreaseCounterNeeded(int p_iCounter,
                                                            QDateTime qdCurrentDateTime,
                                                            QString p_qstrTableName,
                                                            QString p_qstrFieldName,
                                                            long p_lContainerId)
{
    if (m_iRecursionCount > MAX_RECURSION)
    {
        return false;
    }

    bool bRet = false;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery = QString("select MIN(%1) from %2 where %3 = ? and %4 = ?")
            .arg(FTL_LAST_MODIFIED)
            .arg(p_qstrTableName)
            .arg(p_qstrFieldName)
            .arg(FTL_CONTAINER_ID_FIELD_NAME);
    cQSqlQuery.prepare(qstrQuery);
    cQSqlQuery.addBindValue(p_iCounter);
    cQSqlQuery.addBindValue((int)p_lContainerId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            QDateTime qdtLastModified = cQSqlQuery.value(0).toDateTime();

            if (qdtLastModified != qdCurrentDateTime)
            {
                bRet = true;
            }
        }
    }

    return bRet;
}
