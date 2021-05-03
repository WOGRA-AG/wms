/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QSqlQuery>
#include <QList>
#include <QQueue>
#include <qvariant.h>

#include "CwmsTimeMeassurement.h"

// own Includes
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQueryElement.h"
#include "CdmQueryEnhanced.h"
#include "CdmDataAccessHelper.h"

// WMS ODBC Includes
#include "CftlObjectAccess.h"
#include "CftlDialect.h"
#include "CftlInterface.h"
#include "CftlDataAccess.h"
#include "CftlCommandQueryEnhanced.h"
#include "CftlCommandQueryElement.h"
#include "CftlHelper.h"
#include "CftlCommandQuery.h"


CftlCommandQuery::CftlCommandQuery(CftlDataAccess* p_pCftlDataAccess, CdmQuery* p_pCdmQuery)
    : m_rpCftlDataAccess(p_pCftlDataAccess),
      m_rpCdmQuery(p_pCdmQuery)
{

}

CftlCommandQuery::~CftlCommandQuery()
{
    QMapIterator<const CdmMember*, CftlJoinData*> qmIt(m_qmLeftJoins);

    while (qmIt.hasNext())
    {
        qmIt.next();
        CftlJoinData* pJoinData = qmIt.value();
        DELPTR(pJoinData);
    }
}

long CftlCommandQuery::Execute(CftlDataAccess* p_pCftlDataAccess, CdmQuery* p_pCdmQuery)
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;
    CftlCommandQuery cQuery(p_pCftlDataAccess, p_pCdmQuery);
    lRet = cQuery.ExecuteQuery();
    return lRet;
}

long CftlCommandQuery::ExecuteQuery()
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;

    if(CHKPTR(m_rpCftlDataAccess) &&
       CHKPTR(m_rpCdmQuery))
    {
        lRet = ExecuteQueryP();
    }

    return lRet;
}

long CftlCommandQuery::ExecuteQueryP()
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;
    QString qstrSql = GenerateSql();
    QSqlQuery cQSqlQuery;
    int iColumnCount = 0;
    CdmQueryEnhanced* pQuery = nullptr;

    if (m_rpCdmQuery->HasResultElements())
    {
        pQuery = dynamic_cast<CdmQueryEnhanced*>(m_rpCdmQuery);

        if (CHKPTR(pQuery))
        {
            iColumnCount = pQuery->GetColumnCount();
        }
    }

    if (!qstrSql.isEmpty())
    {
        lRet = m_rpCftlDataAccess->ExecuteQuery(qstrSql, cQSqlQuery);

        if(lRet > 0)
        {
            if(cQSqlQuery.first())
            {
                do // reading each objectid
                {
                    int iPos = 0;
                    int iObjectId = -1;
                    int iContainerId = -1;

                    if (IsObjectNeededInResult())
                    {
                        iObjectId = cQSqlQuery.value(iPos++).toInt();
                        iContainerId = cQSqlQuery.value(iPos++).toInt();
                        CdmDataAccessHelper::AddQueryResult(m_rpCdmQuery, iObjectId, iContainerId);
                    }

                    if (iColumnCount > 0)
                    {
                        for (int iMemberPos = 0; iMemberPos < iColumnCount; ++iMemberPos)
                        {
                            QVariant qvValue = cQSqlQuery.value(iPos);
                            CdmDataAccessHelper::SetQueryEnhancedResult(pQuery, iMemberPos, qvValue, iObjectId, iContainerId);
                            iPos++;
                        }
                    }
                }
                while(cQSqlQuery.next());
            }
        }
    }
    else
    {
        lRet = EC(eDmOk);
    }

    return lRet;
}

bool CftlCommandQuery::IsObjectNeededInResult()
{
    if (m_rpCdmQuery->HasResultElements())
    {
        CdmQueryEnhanced* pQuery = dynamic_cast<CdmQueryEnhanced*>(m_rpCdmQuery);

        if (pQuery)
        {
            return pQuery->IsObjectNeededInResult();
        }
    }

    return true;
}

QString CftlCommandQuery::GenerateContainerQuery()
{
    QString qstrRet;
    CdmObjectContainer* pContainer = m_rpCdmQuery->GetContainer();

    if (CHKPTR(pContainer))
    {
        const CdmClass* pClass = pContainer->GetClass();

        if (CHKPTR(pClass))
        {
            QString qstrClassTable = CftlHelper::GetClassTableName(pClass);

            if (IsObjectNeededInResult())
            {
                qstrRet = QString("select o1.%1, o1.%2 from %3 o1 %4 where o1.%5 = %6")
                        .arg(FTL_OBJECT_ID_FIELD_NAME)
                        .arg(FTL_CONTAINER_ID_FIELD_NAME)
                        .arg(qstrClassTable)
                        .arg(GetJoinsAsString())
                        .arg(FTL_CONTAINER_ID_FIELD_NAME)
                        .arg(pContainer->GetId());
            }
            else
            {
                qstrRet = QString("select from %1 o1 %2 where o1.%3 = %4")
                        .arg(qstrClassTable)
                        .arg(GetJoinsAsString())
                        .arg(FTL_CONTAINER_ID_FIELD_NAME)
                        .arg(pContainer->GetId());
            }
        }
    }

    return qstrRet;
}

QString CftlCommandQuery::GenerateClassQuery()
{
    QString qstrRet;
    const CdmClass* pClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pClass))
    {
        QString qstrClassTable = CftlHelper::GetClassTableName(pClass);

        if (IsObjectNeededInResult())
        {
            qstrRet = QString("select o1.%1, o1.%2 from %3 o1 %4")
                    .arg(FTL_OBJECT_ID_FIELD_NAME)
                    .arg(FTL_CONTAINER_ID_FIELD_NAME)
                    .arg(qstrClassTable)
                    .arg(GetJoinsAsString());
        }
        else
        {
            qstrRet = QString("select from %1 o1 %2")
                    .arg(qstrClassTable)
                    .arg(GetJoinsAsString());
        }
    }

    return qstrRet;
}

void CftlCommandQuery::AddOrderByToQuery(QString& qstrRet)
{
    if (!m_rpCdmQuery->GetOrderBy().isEmpty())
    {
       const CdmClass* pClass = CftlHelper::GetClassFromQuery(m_rpCdmQuery);

        if (CHKPTR(pClass))
        {
            bool bFirst = true;
            QStringList qstrlOrderBy = m_rpCdmQuery->GetOrderBy();

            for (int iPos = 0; iPos < qstrlOrderBy.count(); ++iPos)
            {
                const CdmMember* pMember = pClass->FindMember(m_rpCdmQuery->GetOrderBy()[iPos]);

                if (CHKPTR(pMember))
                {
                    QString qstrFieldName = CftlHelper::GetMemberFieldName(pMember);

                    if (!qstrFieldName.isEmpty())
                    {
                        if (bFirst)
                        {
                            bFirst = false;
                            qstrRet += " order by ";
                        }
                        else
                        {
                            qstrRet += ", ";
                        }

                        qstrRet += qstrFieldName;
                    }
                }
            }


            if (m_rpCdmQuery->GetOrderMode()) // ASC
            {
                qstrRet += " asc";
            }
            else
            {
                qstrRet += " desc";
            }
        }
    }
}

void CftlCommandQuery::AddLimitToQuery(QString& qstrRet)
{
    if (GetDialect()->IsSupportingLimit())
    {
        if (m_rpCdmQuery->GetLimitResultCount() > 0)
        {
            qstrRet += " " + GetDialect()->GetLimitKeyname() + " " + QString::number(m_rpCdmQuery->GetLimitResultCount());

            if (m_rpCdmQuery->GetResultStart() > 0)
            {
                qstrRet += " " + GetDialect()->GetOffsetKeyname() + " " + QString::number(m_rpCdmQuery->GetResultStart());
            }
        }
    }
}

QString CftlCommandQuery::GenerateSql()
{
    QString qstrRet;
    QString qstrSelectMembers;

    if(CHKPTR(m_rpCftlDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        CdmQueryElement* pCdmQueryElement = m_rpCdmQuery->GetQueryElement();

        if (m_rpCdmQuery->HasResultElements())
        {
            qstrSelectMembers += AddSelectMembers();
        }

        if(IsQueryElementValid(pCdmQueryElement))
        {
            QScopedPointer<CftlCommandQueryElement> pCftlQueryElement(new CftlCommandQueryElement(m_rpCftlDataAccess, pCdmQueryElement, this));
            qstrRet = pCftlQueryElement->GenerateQuery();
        }
        else
        {
            if (m_rpCdmQuery->GetContainerId() > 0)
            {
                qstrRet = GenerateContainerQuery();
            }
            else if (m_rpCdmQuery->GetClassId() > 0)
            {
                qstrRet = GenerateClassQuery();
            }
            else
            {
                ERR("Unknown Target no container and no class selected.")
            }
        }

        AddOrderByToQuery(qstrRet);
        AddLimitToQuery(qstrRet);

        if (!qstrSelectMembers.isEmpty())
        {
            int iInsertPos = qstrRet.indexOf(" from ");
            if (iInsertPos > 0)
            {
                if (IsObjectNeededInResult())
                {
                    qstrRet = qstrRet.insert(iInsertPos, ", " + qstrSelectMembers);
                }
                else
                {
                    qstrRet = qstrRet.insert(iInsertPos, " " + qstrSelectMembers);
                }
            }
        }
    }

    return qstrRet;
}

QString CftlCommandQuery::AddSelectMembers()
{
    QString qstrRet;

    if (m_rpCdmQuery->HasResultElements())
    {
        CdmQueryEnhanced* pQuery = dynamic_cast<CdmQueryEnhanced*>(m_rpCdmQuery);

        if (CHKPTR(pQuery))
        {
            QVector<QString> qvResultElements = pQuery->GetResultElements();
            const CdmClass* pClass = pQuery->GetClass();

            if (CHKPTR(pClass))
            {
                bool bFirst = true;
                for (int iPos = 0; iPos < qvResultElements.count(); ++iPos)
                {
                    if (bFirst)
                    {
                        bFirst = false;
                    }
                    else
                    {
                        qstrRet += ", ";
                    }
                    QString qstrElement = qvResultElements[iPos];

                    if (!qstrElement.contains(".")) // Simple case no references
                    {
                        QString qstrFieldName = GetMemberFieldName(qstrElement, pQuery);
                        qstrRet += qstrFieldName;
                    }
                    else // references, we have to join
                    {
                        QString qstrFieldName = GetReferenceMemberFieldName(qstrElement, pQuery);
                        qstrRet += qstrFieldName;
                    }

                }
            }
        }

    }

    return qstrRet;
}

bool CftlCommandQuery::IsQueryElementValid(CdmQueryElement* p_pElement)
{
    bool bRet = false;

    if (p_pElement)
    {
        if (p_pElement->GetQueryElementType() == eDmQueryElementTypeCompare)
        {
            bRet = true;
        }
        else
        {
            QList<CdmQueryElement*> qllChilds;
            p_pElement->GetChildList(qllChilds);

            if (qllChilds.count() > 0)
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

QString CftlCommandQuery::AddOrUpdateLeftJoin(const CdmMember* p_pMember,
                                              QString &p_qstrJoin,
                                              QString &p_qstrCompareKeyname)
{
    QString qstrJoinName;

    if (!ContainsLeftJoin(p_pMember))
    {
        qstrJoinName = "refjoin" + QString::number(m_qmLeftJoins.count());
        QString qstrBaseRefMember = CftlHelper::GetBaseMemberFieldName(p_pMember);
        CftlJoinData* pJoinData = new CftlJoinData(p_qstrJoin, qstrJoinName, qstrBaseRefMember);
        pJoinData->AddJoinMember(p_qstrCompareKeyname);
        m_qmLeftJoins.insert(p_pMember,
                                     pJoinData);
    }
    else
    {
        CftlJoinData* pJoinData = GetJoinData(p_pMember);
        if (CHKPTR(pJoinData))
        {
            pJoinData->AddJoinMember(p_qstrCompareKeyname);
            qstrJoinName = pJoinData->GetJoinName();
        }
    }

    return qstrJoinName;
}

QString CftlCommandQuery::AddOrUpdateLeftJoin(const CdmMember* p_pMember, QString &p_qstrJoin,
                                              QString &p_qstrCompareKeyname, QString &p_qstrJoinPartner)
{
    QString qstrJoinName;

    if (!ContainsLeftJoin(p_pMember))
    {
        qstrJoinName = "refjoin" + QString::number(m_qmLeftJoins.count());
        QString qstrBaseRefMember = CftlHelper::GetBaseMemberFieldName(p_pMember);
        CftlJoinData* pJoinData = new CftlJoinData(p_qstrJoin, qstrJoinName, qstrBaseRefMember, p_qstrJoinPartner);
        pJoinData->AddJoinMember(p_qstrCompareKeyname);
        m_qmLeftJoins.insert(p_pMember,
                                     pJoinData);
    }
    else
    {
        CftlJoinData* pJoinData = GetJoinData(p_pMember);
        if (CHKPTR(pJoinData))
        {
            pJoinData->AddJoinMember(p_qstrCompareKeyname);
            qstrJoinName = pJoinData->GetJoinName();
        }
    }

    return qstrJoinName;
}

bool CftlCommandQuery::ContainsLeftJoin(const CdmMember* p_pMember)
{
    return m_qmLeftJoins.contains(p_pMember);
}

CftlJoinData* CftlCommandQuery::GetJoinData(const CdmMember* p_pMember)
{
    CftlJoinData* pJoinData = nullptr;

    if (ContainsLeftJoin(p_pMember))
    {
        pJoinData = m_qmLeftJoins[p_pMember];
    }

    return pJoinData;
}

QString CftlCommandQuery::GetJoinName(const CdmMember* p_pMember)
{
    QString qstrJoinName;

    CftlJoinData* pJoinData = GetJoinData(p_pMember);

    if (pJoinData)
    {
        qstrJoinName = pJoinData->GetJoinName();
    }

    return qstrJoinName;
}

QString CftlCommandQuery::GetJoinsAsString()
{
    QString qstrJoins;

    QQueue<CftlJoinData*> qQueue;
    QMultiMap<QString, CftlJoinData*> qmDelayed;

    QMap<const CdmMember*, CftlJoinData*>::iterator qmIt;
    for (qmIt = m_qmLeftJoins.begin(); qmIt != m_qmLeftJoins.end(); ++qmIt)
    {
        CftlJoinData* pJoinData = qmIt.value();

        if (pJoinData)
        {
            if (pJoinData->HasJoinPartner())
            {
                qmDelayed.insert(pJoinData->GetJoinPartner(), pJoinData);
            }
            else
            {
                qQueue.enqueue(pJoinData);
            }
        }
    }

    while (!qQueue.isEmpty())
    {
        CftlJoinData* pJoinData = qQueue.dequeue();

        if (pJoinData)
        {
            qstrJoins += pJoinData->GenerateJoin() + " ";

            QString qstrJoinName = pJoinData->GetJoinName();

            qQueue.append(qmDelayed.values(qstrJoinName));
            qmDelayed.remove(qstrJoinName);
        }
    }

    if (qmDelayed.size() > 0)
    {
        WARNING("Couldn't add " + QString::number(qmDelayed.size()) + " Joins due to missing Parent Joins");
    }

    return qstrJoins;
}

QString CftlCommandQuery::GetMemberFieldName(QString p_qstrKeyname, CdmQueryEnhanced* pQuery)
{
   QString qstrRet;

   CdmQueryResultElement* pCdmResultElement = pQuery->GetResultElement(p_qstrKeyname);
   const CdmClass* pClass = pQuery->GetClass();

   if (CHKPTR(pClass) && pCdmResultElement)
   {
       const CdmMember* pMember = pClass->FindMember(p_qstrKeyname);

       if (pMember)
       {
           QString qstrFieldName = CftlHelper::GetMemberFieldName(pMember);
           qstrRet += "o1." + qstrFieldName;
       }
       else
       {
           ERR("Unknown Member in query. Member: " + p_qstrKeyname);
       }

       AddFunctionToSelectMember(pCdmResultElement, qstrRet);
   }
   else // not found expecting that is it a reference value.
   {
      ERR("ResultElement not found in Query: " + p_qstrKeyname);
   }

   return qstrRet;
}

void CftlCommandQuery::AddFunctionToSelectMember(CdmQueryResultElement* pCdmResultElement, QString& qstrRet)
{
    switch (pCdmResultElement->GetMode())
    {
    case eDmQueryResultElementModeSum:
       qstrRet = "sum(" + qstrRet + ")";
       break;
    case eDmQueryResultElementModeAvg:
       qstrRet = "avg(" + qstrRet + ")";
       break;
    case eDmQueryResultElementModeMax:
       qstrRet = "max(" + qstrRet + ")";
       break;
    case eDmQueryResultElementModeMin:
       qstrRet = "min(" + qstrRet + ")";
       break;
    case eDmQueryResultElementModeCount:
        qstrRet = "count(*)";
        break;
    default: // no grouping mode
       break;
    }
}

QString CftlCommandQuery::GetReferenceMemberFieldName(QString p_qstrKeyname, CdmQueryEnhanced* pQuery)
{
   QString qstrRet;

   CdmQueryResultElement* pCdmResultElement = pQuery->GetResultElement(p_qstrKeyname);
   const CdmClass* pClass = pQuery->GetClass();

   if (CHKPTR(pClass) && pCdmResultElement)
   {
       QStringList qstrl_Members = p_qstrKeyname.split(".");

       const CdmMember* pMember = pClass->FindMember(qstrl_Members.at(0));
       QString qstrJoinPartner = "o1";
       const CdmMember* prevMember = nullptr;

       if (CHKPTR(pMember))
       {
           prevMember = pMember;
           pMember = nullptr;

           for (int iPos = 1; iPos < qstrl_Members.size(); ++iPos)
           {
               QString qstrMemberName = qstrl_Members.mid(0, iPos+1).join(".");
               pMember = pClass->FindMember(qstrMemberName);

               if (CHKPTR(pMember))
               {
                   QString qstrJoin = CftlHelper::GetUnionOfSubclasses(pMember->GetClass());
                   QString qstrRefName = CftlHelper::GetMemberFieldName(pMember);

                   qstrJoinPartner = AddOrUpdateLeftJoin(prevMember, qstrJoin, qstrRefName, qstrJoinPartner);
                   prevMember = pMember;
               }
               else
               {
                   qstrJoinPartner.clear();
                   prevMember = nullptr;
                   break;
               }
           }

           if (pMember && !qstrJoinPartner.isEmpty())
           {
               QString qstrRefName = CftlHelper::GetMemberFieldName(pMember);
               qstrRet = qstrJoinPartner + "." + qstrRefName;
           }
           else
           {
               ERR("Unknown Member in query. Reference Chain: " + p_qstrKeyname);
           }
       }

       AddFunctionToSelectMember(pCdmResultElement, qstrRet);
   }
   else // not found expecting that is it a reference value.
   {
      ERR("ResultElement not found in Query: " + p_qstrKeyname);
   }

   return qstrRet;
}

CftlDialect *CftlCommandQuery::GetDialect()
{
    CftlInterface* pInterface = GetInterface();

    if (CHKPTR(pInterface))
    {
        return pInterface->GetDialect();
    }

    return nullptr;
}

CftlInterface *CftlCommandQuery::GetInterface()
{
    CftlInterface* pInterface = nullptr;

    if (CHKPTR(m_rpCftlDataAccess))
    {
        pInterface = m_rpCftlDataAccess->GetFtlInterface();
    }

    return pInterface;
}
