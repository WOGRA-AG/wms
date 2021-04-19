#ifndef NOMINMAX
#define NOMINMAX
#endif

// System and QT Includes

// WMS Commons Includes
#include "CwmsTimeMeassurement.h"
#include "CwmsUtilities.h"

// own Includes
#include "CdmMessageManager.h"
#include "CdmSystemVariables.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryFactory.h"
#include "CdmQueryBuilder.h"


CdmQueryBuilder::CdmQueryBuilder(QString p_qstrQuery)
    : m_qstrQuery(p_qstrQuery),
      m_qmValueMap(),
      m_rpContainer(nullptr),
      bProcessed(false)
{
}

CdmQueryBuilder::CdmQueryBuilder(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
    : m_qstrQuery(p_qstrQuery),
      m_qmValueMap(),
      m_rpContainer(p_pContainer),
      bProcessed(false)
{
}

CdmQueryBuilder::~CdmQueryBuilder()
{
}

CdmQuery* CdmQueryBuilder::GenerateQuery()
{
    QString qstrQuery = GetFinalWql();
    return CdmQueryFactory::ParseString(qstrQuery, m_rpContainer);
}

QString CdmQueryBuilder::GetFinalWql()
{
    if (!bProcessed)
    {
        ExecutePreProcessor();
    }
    return m_qstrQuery;
}

void CdmQueryBuilder::ExecutePreProcessor()
{
    int iPosEnd = 0;
    int iPosStart = m_qstrQuery.indexOf("${", 0);

    while (iPosStart > 0)
    {
        iPosEnd = m_qstrQuery.indexOf("}", iPosStart);

        if (iPosEnd > 0)
        {
            QString qstrKey = m_qstrQuery.mid(iPosStart, iPosEnd - iPosStart + 1);
            QString qstrValue;

            if (m_qmValueMap.contains(qstrKey))
            {
                qstrValue = m_qmValueMap[qstrKey];
            }
            else if (CdmSystemVariables::IsSystemValue(qstrKey))
            {
                qstrValue = CdmSystemVariables::GetValueAsString(qstrKey);
            }
            else
            {
                qstrValue = CdmMessageManager::GetMessenger()->AskForInputText("Bitte geben Sie den Wert für \"" + qstrKey + "\" ein.");
            }

            m_qstrQuery.replace(qstrKey, qstrValue);
        }
        else
        {
            ERR(tr("Präprozessor Fehler Variable kann nicht gesetzt werden\nEin Variablenbeginn (\"${\") wurde definiert aber nicht abgeschlossen."));
            break;
        }

        iPosStart = m_qstrQuery.indexOf("${", iPosStart);
    }
}

void CdmQueryBuilder::AddValueEntry(QString p_qstrKey, QString p_qstrValue)
{
    if (!p_qstrKey.startsWith("${"))
    {
        p_qstrKey = "${" + p_qstrKey + "}";
    }

    m_qmValueMap.insert(p_qstrKey, p_qstrValue);
}

void CdmQueryBuilder::SetContainer(CdmObjectContainer* p_pContainer)
{
    m_rpContainer = p_pContainer;
}

QString CdmQueryBuilder::ReadRequestMembersFromQuery(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (CHKPTR(p_pCdmQuery))
    {
        QVector<QString> qvElements = p_pCdmQuery->GetResultElements();

        if (qvElements.count() > 0)
        {
            for (int iCounter = 0; iCounter < qvElements.count(); iCounter++)
            {
                qstrRet += qvElements[iCounter];

                if (iCounter < qvElements.count() - 1)
                {
                    qstrRet += ", ";
                }
            }
        }
    }

    return qstrRet;
}

QString CdmQueryBuilder::ReadObjectListKeyname(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (p_pCdmQuery)
    {
        CdmObjectContainer* pContainer = p_pCdmQuery->GetContainer();

        if (pContainer)
        {
            qstrRet = pContainer->GetKeyname();
        }
        else
        {
            const CdmClass* pClass = p_pCdmQuery->GetClass();

            if (pClass)
            {
                qstrRet = pClass->GetFullQualifiedName() + ".class";
            }
        }
    }

    return qstrRet;
}

CdmQuery* CdmQueryBuilder::BuildQuery(QString p_qstrQuery)
{
    CdmQueryBuilder cCdmBuilder(p_qstrQuery);
    CdmQuery* pCdmQuery = cCdmBuilder.GenerateQuery();
    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::BuildQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
{
    CdmQueryBuilder cCdmBuilder(p_qstrQuery, p_pContainer);
    CdmQuery* pCdmQuery = cCdmBuilder.GenerateQuery();
    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::ExecuteQuery(QString p_qstrQuery)
{
    CdmQuery* pCdmQuery = BuildQuery(p_qstrQuery);

    if (pCdmQuery)
    {
        if (pCdmQuery->Execute() < 0)
        {
            ERR("Query not successfull executed")
            DELPTR(pCdmQuery)
        }
    }
    else
    {
        ERR("Could not parse query.\n" + p_qstrQuery)
    }

    return pCdmQuery;
}

CdmQuery* CdmQueryBuilder::ExecuteQuery(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
{
    CdmQuery* pCdmQuery = BuildQuery(p_qstrQuery, p_pContainer);

    if (pCdmQuery)
    {
        if (pCdmQuery->Execute() < 0)
        {
            ERR("Query not successfull executed");
            DELPTR(pCdmQuery);
        }
    }
    else
    {
        ERR("Could not parse query.\n" + p_qstrQuery);
    }

    return pCdmQuery;
}

QString CdmQueryBuilder::BuildString(CdmQuery* p_pCdmQuery)
{
    QString qstrRet;

    if (CHKPTR(p_pCdmQuery))
    {
        qstrRet += "select ";

        if (p_pCdmQuery->HasResultElements())
        {
            qstrRet += ReadRequestMembersFromQuery(p_pCdmQuery);
        }

        qstrRet += " from " + ReadObjectListKeyname(p_pCdmQuery) + " ";

        CdmQueryElement* pCdmElement = p_pCdmQuery->GetQueryElement();

        if (pCdmElement)
        {
            QString qstrCond(pCdmElement->GetConditionAsString());

            if (false == qstrCond.contains(QStringLiteral("where")))
            {
                qstrRet += "where ";
            }

            qstrRet += pCdmElement->GetConditionAsString() + " ";
        }

        if (!p_pCdmQuery->GetOrderBy().isEmpty())
        {
            qstrRet += " order by " + p_pCdmQuery->GetOrderBy().join(", ");

            if (p_pCdmQuery->GetOrderMode())
            {
                qstrRet += " ASC";
            }
            else
            {
                qstrRet += " DESC";
            }
        }
    }

    qstrRet = qstrRet.trimmed();
    return qstrRet;
}
