/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CdbQueryEnhancedNew.cpp
 ** Started Implementation: 2010/11/11
 ** Description:
 **
 ** This class implements the sql access for enhanced queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <qsqlquery.h>

#include "CwmsUtilities.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQueryElement.h"
#include "CdmDataAccessHelper.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"

// Own Includes
#include "CdbQuery.h"
#include "CdbDataStructureHelper.h"
#include "CdbDataAccess.h"
#include "CdbQueryElement.h"
#include "CdbQueryEnhancedNew.h"

#define RESULT_MEMBER_PLACEHOLDER "$RESULT_MEMBERS"
#define MEMBER_CONDITION_PLACEHOLDER "$MEMBER_CONDITION"
#define TABLE_NAME_PLACEHOLDER "$TABLE_NAME"
#define SUB_SELECT_NAME "$SUBSELECT_NAME"
#define OBJREF_TABLE_PREFIX "ref"
#define OBJECT_PREFIX "obj"
#define OBJECT_QUERY_PLACHOLDER "$OBJ"
#define WHERE_OBJREF_CONDITION_PLACEHOLDER "$WHERE"

static int MaxObjectIdComplexity = 5;

CdbQueryEnhancedNew::CdbQueryEnhancedNew(CdmQueryEnhanced* p_pCdmQueryEnhanced,
                                         CdbDataAccess* p_pCdbDataAccess)
    : m_rpCdmQuery(p_pCdmQueryEnhanced),
      m_rpCdbDataAccess(p_pCdbDataAccess),
      m_iKeynameCount(0),
      m_qmKeynames(),
      m_qmKeynamesSave(),
      m_qmTypesResults(),
      m_qmmObjectRefMembers()
{
}

CdbQueryEnhancedNew::~CdbQueryEnhancedNew()
{
}

long CdbQueryEnhancedNew::Execute()
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        QString qstrSql = GenerateSql();

        if (!qstrSql.isEmpty())
        {
            INFO(qstrSql);
            lRet = ExecuteQuery(qstrSql);
        }
        else
        {
            lRet = CdmLogging::eDmFalse;
        }
    }

    return lRet;
}

QString CdbQueryEnhancedNew::GenerateSql()
{
    QString qstrSql;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        QString qstrObjectIdQuery;
        CdbQuery cCdbQuery(m_rpCdbDataAccess, m_rpCdmQuery);
        qstrObjectIdQuery = cCdbQuery.GenerateQuerySql();
        QVector<QString> qvResultElements = m_rpCdmQuery->GetResultElements();

        if (!qstrObjectIdQuery.isEmpty() && m_rpCdmQuery->HasResultElements())
        {
            qstrSql = GenerateCompleteSql(qvResultElements, qstrObjectIdQuery);
        }
        else if (!qstrObjectIdQuery.isEmpty())
        {
            qstrSql = qstrObjectIdQuery;
        }
        else
        {
            ERR("Could not generate SQL Query!");
        }
    }

    return qstrSql;
}

long CdbQueryEnhancedNew::ExecuteQuery(QString p_qstrSql)
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;
    QSqlQuery cQSqlQuery;

    if (!p_qstrSql.isEmpty())
    {
//        QTime qStart = QTime::currentTime();
        lRet = m_rpCdbDataAccess->ExecuteQuery(p_qstrSql, cQSqlQuery);
//        QTime qDbExecuted = QTime::currentTime();
//        QTime qResultFilled;

        if(lRet > 0)
        {
            if(cQSqlQuery.first())
            {
                int iRowCount = 0;
                int iColumnCount = m_rpCdmQuery->GetColumnCount();
                do
                {
                    if (m_rpCdmQuery->ContainsGrouping() && iColumnCount == 1) // only one result means there is no objectid in result
                    {
                        QVariant qVariant = cQSqlQuery.value(0);
                        QString qstrTemp = qVariant.toString();
                        CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, 0, qVariant, -1, -1);
                    }
                    else
                    {
                        QVariant qvObjectId = cQSqlQuery.value(iColumnCount);
                        long lObjectId = cQSqlQuery.value(iColumnCount).toInt();
                        long lContainerId = cQSqlQuery.value(iColumnCount + 1).toInt();

                        for (int iCounter = 0; iCounter < iColumnCount; ++iCounter)
                        {
                            QVariant qVariant = cQSqlQuery.value(iCounter);
                            CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, iCounter, qVariant, lObjectId, lContainerId);
                        }

                        ++iRowCount;
                    }
                }
                while(cQSqlQuery.next());
            }
        }

//        qResultFilled = QTime::currentTime();

//        int mSecsDurationOnDb = qStart.msecsTo(qDbExecuted);
//        int mSecsDurationResultFilling = qDbExecuted.msecsTo(qResultFilled);
//        int mSecsDurationComplete = qStart.msecsTo(qResultFilled);

//        ERR("Query Execution Info:;Query Execution Duration:;" +
//             QString::number(mSecsDurationOnDb) +
//             ";FillData Duration:;" + QString::number(mSecsDurationResultFilling) +
//             ";Complete Duration:;" + QString::number(mSecsDurationComplete) +
//             ";Query:;" + p_qstrSql);
    }
    else
    {
        lRet = 2;
    }

    return lRet;
}

QString CdbQueryEnhancedNew::GenerateCompleteSql(QVector<QString> &p_qvKeynames,
                                                 QString &p_qstrObjectIdSql)
{
    QString qstrSql;
    BuildMemberMap(p_qvKeynames);
    QMap<QString, QString> qmSubQueries = BuildSubQueries(p_qstrObjectIdSql);
    qstrSql = ConcatenateQueries(p_qvKeynames, qmSubQueries, p_qstrObjectIdSql);
    return qstrSql;
}

QString CdbQueryEnhancedNew::ConcatenateQueries(QVector<QString> &p_qvKeynames,
                                                QMap<QString, QString> &p_qmSubQueries,
                                                QString &p_qstrObjectIdSql)
{
    QString qstrSql = CreateHead(p_qvKeynames);
    QString qstrObjectKey = OBJECT_PREFIX;
    qstrSql += "(" + p_qstrObjectIdSql +") " + qstrObjectKey;
    QMapIterator<QString, QString> qmIt(p_qmSubQueries);

    while (qmIt.hasNext())
    {
        qmIt.next();
        QString qstrSubQuery = qmIt.value();
        QString qstrSqlPart = " left join ";
        qstrSqlPart +=  qstrSubQuery + " on " + qmIt.key() + ".objectid = " + qstrObjectKey + ".objectid";
        qstrSql += qstrSqlPart;
    }

    AddGroupByToSql(qstrSql);
    AddOrderByToSql(qstrSql);
    return qstrSql;
}


void CdbQueryEnhancedNew::AddOrderByToSql(QString &qstrSql)
{
    const QStringList qstrlOrderBy = m_rpCdmQuery->GetOrderBy();
    bool bFirst = true;

    for (int iPos = 0; iPos < qstrlOrderBy.size(); ++iPos)
    {
        QString qstrKeyname = qstrlOrderBy[iPos];
        QString qstrOrderBy = m_qmKeynamesSave[qstrKeyname];

        if (!qstrOrderBy.isEmpty())
        {
            if (bFirst)
            {
                qstrSql += " order by " + qstrOrderBy;
                bFirst = false;
            }
            else
            {
                qstrSql += ", " + qstrOrderBy;
            }

            if (m_rpCdmQuery->GetOrderMode())
            {
                qstrSql += " asc";
            }
            else
            {
                qstrSql += " desc";
            }
        }
        else
        {
            ERR("Order by \"" + qstrKeyname + "\" couldn't be translated to sql");
        }
    }
}

void CdbQueryEnhancedNew::AddGroupByToSql(QString &qstrSql)
{
    const QList<QString> qlGroupBy = m_rpCdmQuery->GetGroupByElements();
    bool bFirst = true;

    for (int iPos = 0; iPos < qlGroupBy.size(); ++iPos)
    {
        QString qstrKeyname = qlGroupBy[iPos];
        QString qstrGroupBy = m_qmKeynamesSave[qstrKeyname];

        if (!qstrGroupBy.isEmpty())
        {
            if (bFirst)
            {
                qstrSql += " group by " + qstrGroupBy;
                bFirst = false;
            }
            else
            {
                qstrSql += ", " + qstrGroupBy;
            }
        }
        else
        {
            ERR("Group by \"" + qstrKeyname + "\" couldn't be translated to sql");
        }
    }
}

QString CdbQueryEnhancedNew::CreateHead(QVector<QString> &p_qvKeynames)
{
    QString qstrHead = "select ";

    for (int i = 0; i < p_qvKeynames.size(); ++i)
    {
        QString qstrKeyname = p_qvKeynames.at(i);
        QString qstrTemplate = GetSQlFunction(i);
        QString qstrKeynameSave = m_qmKeynamesSave.value(qstrKeyname);
        if (!qstrTemplate.contains(RESULT_MEMBER_PLACEHOLDER))
        {
            qstrHead += qstrTemplate + ", ";
        }
        else if (!qstrKeynameSave.isEmpty())
        {
            qstrHead += qstrTemplate.replace(RESULT_MEMBER_PLACEHOLDER, qstrKeynameSave);
            qstrHead += ", ";
        }
        else
        {
            ERR("Failed to select " + qstrKeyname);
        }
    }

    qstrHead += OBJECT_PREFIX ".objectid, " OBJECT_PREFIX ".objectlistid FROM ";
    return qstrHead;
}

void CdbQueryEnhancedNew::BuildMemberMap(QVector<QString> &p_qvKeynames)
{
    QVector<QString> qvOrderBy = m_rpCdmQuery->GetOrderBy().toVector();
    QVector<QString> qvGroupBy = m_rpCdmQuery->GetGroupByElements().toVector();

    BuildTypeAndReferenceList(p_qvKeynames);
    if (!qvOrderBy.isEmpty())
    {
        BuildTypeAndReferenceList(qvOrderBy);
    }
    if (!qvGroupBy.isEmpty())
    {
        BuildTypeAndReferenceList(qvGroupBy);
    }
}

void CdbQueryEnhancedNew::BuildTypeAndReferenceList(QVector<QString> &p_qvKeynames)
{
    for (int i = 0; i < p_qvKeynames.size(); ++i)
    {
        QString qstrKeyname = p_qvKeynames[i];
        if (!qstrKeyname.contains("."))
        {
            BuildType(qstrKeyname);
        }
        else
        {
            BuildReference(qstrKeyname);
        }
    }
}

void CdbQueryEnhancedNew::BuildType(QString p_qstrKeyname)
{
    const CdmClass* pCdmClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pCdmClass))
    {
        const CdmMember* pMember = pCdmClass->FindMember(p_qstrKeyname);

        if (p_qstrKeyname.toLower() != "count" && CHKPTR(pMember))
        {
            EdmValueType eType = pMember->GetValueType();

            if (eType == eDmValueUser ||
                    eType == eDmValueUserGroup ||
                    eType == eDmValueEnum)
            {
                eType = eDmValueInt;
            }
            else if (eType == eDmValueListInt ||
                     eType == eDmValueListDouble ||
                     eType == eDmValueListString ||
                     eType == eDmValueDictStringInt ||
                     eType == eDmValueDictStringString ||
                     eType == eDmValueDictStringDouble ||
                     eType == eDmValueDictIntInt ||
                     eType == eDmValueDictIntString ||
                     eType == eDmValueDictIntDouble)
            {
                eType = eDmValueCharacterDocument;
            }

            if (m_qmTypesResults.contains(eType))
            {
                QList<const CdmMember*>& qlMembers = m_qmTypesResults[eType];

                if (!qlMembers.contains(pMember))
                {
                    qlMembers.append(pMember);
                }
            }
            else
            {
                QList<const CdmMember*> qlMembers;
                qlMembers.append(pMember);
                m_qmTypesResults[eType] = qlMembers;
            }
        }
    }
}

void CdbQueryEnhancedNew::BuildReference(QString p_qstrKeyname)
{
    const CdmClass* pCdmClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pCdmClass))
    {
        QLinkedList<const CdmMember*> p_qllReferencedMembers;
        QStringList qstrlMemberChain = p_qstrKeyname.split(".");
        for (int Count = 0; Count < qstrlMemberChain.size(); ++Count)
        {
            QString qstrMember = qstrlMemberChain.mid(0, Count+1).join(".");
            const CdmMember* pRefMember = pCdmClass->FindMember(qstrMember);
            if (pRefMember)
            {
                p_qllReferencedMembers.append(pRefMember);
            }
            else
            {
                p_qllReferencedMembers.clear();
                ERR("Object Ref Member not found in class structure: " + qstrMember + "\nFull Keyname: " + p_qstrKeyname);
                break;
            }
        }

        if (!p_qllReferencedMembers.isEmpty())
        {
            bool bFound = false;
            const CdmMember* pSearchMember = p_qllReferencedMembers.takeLast();
            int iDepth = p_qllReferencedMembers.size();

            QMutableMapIterator<int, QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>>>
                    qmmIt(m_qmmObjectRefMembers);
            while (qmmIt.hasNext())
            {
                qmmIt.next();
                if (qmmIt.key() != iDepth)
                {
                    continue;
                }
                if (p_qllReferencedMembers == qmmIt.value().first)
                {
                    if (!qmmIt.value().second.contains(pSearchMember))
                    {
                        qmmIt.value().second.append(pSearchMember);
                    }
                    bFound = true;
                    break;
                }
            }

            if (!bFound)
            {
                QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>> qPair;
                qPair.first = p_qllReferencedMembers;
                QList<const CdmMember*> qlMembers;
                qlMembers.append(pSearchMember);
                qPair.second = qlMembers;
                m_qmmObjectRefMembers.insert(iDepth, qPair);
            }
        }
    }
}

QMap<QString, QString> CdbQueryEnhancedNew::BuildSubQueries(QString &p_qstrIdQuery)
{
    QMap<QString, QString> qmSubQueries;
    QMapIterator<EdmValueType, QList<const CdmMember*>> it(m_qmTypesResults);

    while (it.hasNext())
    {
        it.next();
        if (it.key() != eDmValueFormula)
        {
            QString qstrSubSelect = GetPartialQueryTemplate();
            QString qstrTable = CdbDataStructureHelper::GetTableName(it.key());
            qstrSubSelect = qstrSubSelect.replace(TABLE_NAME_PLACEHOLDER, qstrTable);
            QList<const CdmMember*> qlMembers = it.value();
            QString qstrResultMembers = BuildResultMembers(qlMembers);
            qstrSubSelect = qstrSubSelect.replace(RESULT_MEMBER_PLACEHOLDER, qstrResultMembers);
            QString qstrConditionMembers = BuildConditionMembers(qlMembers);
            qstrSubSelect = qstrSubSelect.replace(MEMBER_CONDITION_PLACEHOLDER, qstrConditionMembers);
            QString qstrSubSelectName = qstrTable + "_SEL";
            qstrSubSelect = qstrSubSelect.replace(SUB_SELECT_NAME, qstrSubSelectName);
            qmSubQueries.insert(qstrSubSelectName, qstrSubSelect);
        }
    }

    QMapIterator<QString, QString> subRefIt(BuildObjectRefSubQueries(p_qstrIdQuery));
    while (subRefIt.hasNext())
    {
        subRefIt.next();
        qmSubQueries.insert(subRefIt.key(), subRefIt.value());
    }

    return qmSubQueries;
}

QMap<QString, QString> CdbQueryEnhancedNew::BuildObjectRefSubQueries(QString &p_qstrIdQuery, bool p_bNoJoins)
{
    QMap<QString, QString> qmSubRefQueries;
    bool bIdQuery = true;
    CdmQueryElement* pQueryElement = m_rpCdmQuery->GetQueryElement();
    if (pQueryElement && pQueryElement->GetComplexity() > MaxObjectIdComplexity)
    {
        bIdQuery = false;
    }
    if (p_qstrIdQuery.isEmpty())
    {
        bIdQuery = false;
    }

    QString qstrMemberidAndObjectTemplate = QString("%1.memberid = %2 and "
                                                   "%1.objectid = %3.val and "
                                                   "%1.objectlistid = %3.orefobjectlist");
    QString qstrObjectTemplate = QString("%1.objectid = %2.val and "
                                         "%1.objectlistid = %2.orefobjectlist");

    QMapIterator<int, QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>>>
            qmitPairs(m_qmmObjectRefMembers);
    while (qmitPairs.hasNext())
    {
        qmitPairs.next();
        QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>> qPair = qmitPairs.value();
        QLinkedList<const CdmMember*> qlReferences = qPair.first;
        QList<const CdmMember*> qlMembers = qPair.second;
        if (qlReferences.isEmpty() || qlMembers.isEmpty())
        {
            continue;
        }

        bool bFirstTable = true;
        int iTablesPos = 0;
        QString qstrTables;
        QStringList qstrlReferenceTables;
        QString qstrWhereConditions;
        QString qstrResults;
        QString qstrFullReferenceKeyName;

        QLinkedListIterator<const CdmMember*> qlIt(qlReferences);
        while (qlIt.hasNext())
        {
            const CdmMember* pRefMember = qlIt.next();

            QString qstrCurrentTable = OBJREF_TABLE_PREFIX + QString::number(iTablesPos);
            QString qstrTable = CdbDataStructureHelper::GetTableName(pRefMember->GetValueType()) + " " + qstrCurrentTable;
            QString qstrKeyname = pRefMember->GetKeyname();
            long lMemberId = pRefMember->GetId();

            /* append delimiters to incrementelly built QStrings,
             * build Where Condition,
             * join Tables,
             * add the IdQuery if necessary
             * and select the objectid and objectlist of the first table
             */
            if (!bFirstTable)
            {
                qstrWhereConditions += " and ";
                qstrFullReferenceKeyName += ".";

                if (p_bNoJoins)
                {
                    qstrTables += ", " + qstrTable;

                    qstrWhereConditions += qstrMemberidAndObjectTemplate
                            .arg(qstrCurrentTable)
                            .arg(lMemberId)
                            .arg(qstrlReferenceTables.last());
                }
                else
                {
                    QString qstrJoin = qstrObjectTemplate
                            .arg(qstrCurrentTable)
                            .arg(qstrlReferenceTables.last());

                    qstrWhereConditions += qstrCurrentTable + ".memberid = " + QString::number(lMemberId);
                    qstrTables += " INNER JOIN " + qstrTable + " ON (" + qstrJoin + ")";
                }
            }
            else if (bIdQuery)
            {
                if (p_bNoJoins)
                {
                    qstrWhereConditions += QString("%1.memberid = %2 and "
                                        "%1.objectid = %3.objectid and "
                                        "%1.objectlistid = %3.objectlistid")
                            .arg(qstrCurrentTable)
                            .arg(lMemberId)
                            .arg(OBJECT_PREFIX);
                    qstrTables = "(" + p_qstrIdQuery + ") " OBJECT_PREFIX ", " + qstrTable;
                }
                else
                {
                    QString qstrJoin = QString("%1.objectid = %2.objectid and "
                                               "%1.objectlistid = %2.objectlistid")
                            .arg(qstrCurrentTable)
                            .arg(OBJECT_PREFIX);

                    qstrWhereConditions += qstrCurrentTable + ".memberid = " + QString::number(lMemberId);
                    qstrTables = "(" + p_qstrIdQuery + ") " OBJECT_PREFIX " INNER JOIN " + qstrTable + " ON (" + qstrJoin + ")";
                }
                qstrResults += OBJECT_PREFIX ".objectid, " OBJECT_PREFIX ".objectlistid";
            }
            else
            {
                qstrWhereConditions += qstrCurrentTable + ".memberid = " + QString::number(lMemberId);
                qstrTables = qstrTable;
                qstrResults += qstrCurrentTable + ".objectid, " + qstrCurrentTable + ".objectlistid";
            }

            qstrFullReferenceKeyName += qstrKeyname;

            // update TableList and bFirstTable
            qstrlReferenceTables.append(qstrCurrentTable);

            if (bFirstTable)
            {
                bFirstTable = false;
            }

            ++iTablesPos;
        }

        QMultiMap<QString, long> qmmValueTableMemberIds;

        for (int iPos = 0; iPos < qlMembers.size(); ++iPos)
        {
            const CdmMember* pRefMember = qlMembers.at(iPos);

            QString qstrTable = CdbDataStructureHelper::GetTableName(pRefMember->GetValueType());
            QString qstrKeyname = pRefMember->GetKeyname();
            long lMemberId = pRefMember->GetId();

            if (bFirstTable)
            {
                qstrTables = qstrTable;
                qstrResults = qstrTable + ".objectid, " + qstrTable + ".objectlistid";
                bFirstTable = false;
            }
            else if (!qmmValueTableMemberIds.contains(qstrTable))
            {
                if (p_bNoJoins)
                {
                    qstrTables += ", " + qstrTable;

                    qstrWhereConditions += " and " + qstrObjectTemplate
                            .arg(qstrTable)
                            .arg(qstrlReferenceTables.last());
                }
                else
                {
                    qstrTables += " LEFT JOIN " + qstrTable + " ON (" + qstrObjectTemplate
                            .arg(qstrTable)
                            .arg(qstrlReferenceTables.last()) + ")";
                }
            }

            qmmValueTableMemberIds.insert(qstrTable, lMemberId);

            QString qstrValueName = qstrFullReferenceKeyName + "." + qstrKeyname;
            qstrValueName = MakeKeynameSave(qstrValueName);
            m_qmKeynamesSave.insert(qstrFullReferenceKeyName + "." + qstrKeyname, qstrValueName);
            QString qstrResultMember = QString("min(CASE WHEN %1.objectid = %2.val and "
                                               "%1.objectlistid = %2.orefobjectlist and "
                                               "%1.memberid = %3 "
                                               "THEN %1.val else null end) "
                                               "AS %4")
                    .arg(qstrTable)
                    .arg(qstrlReferenceTables.last())
                    .arg(lMemberId)
                    .arg(qstrValueName);

            qstrResults += "," + qstrResultMember;
        }

        QListIterator<QString> qlKeyIterator = QListIterator<QString>(qmmValueTableMemberIds.uniqueKeys());
        while (qlKeyIterator.hasNext())
        {
            if (!qstrWhereConditions.isEmpty())
            {
                qstrWhereConditions += " and ";
            }
            QString qstrValueTable = qlKeyIterator.next();
            /*QStringList qlKeynames(qmmValueTableKeynames.values(qstrValueTable));
            for (int i = 0; i < qlKeynames.size(); ++i)
            {
                qlKeynames[i] = "'" + qlKeynames[i] + "'";
            }*/
            QStringList qstrlMemberIds;
            QListIterator<long> qlIt(qmmValueTableMemberIds.values(qstrValueTable));
            while (qlIt.hasNext())
            {
                long lMemberId = qlIt.next();
                qstrlMemberIds.append(QString::number(lMemberId));
            }
            qstrWhereConditions += qstrValueTable + ".memberid IN (" + qstrlMemberIds.join(',') + ")";
        }

        QString qstrSubSelectName = MakeKeynameSave("OBJREF_" + qstrFullReferenceKeyName);

        QString qstrSubSelect = GetPartialObjRefQueryTemplate();
        qstrSubSelect = qstrSubSelect.replace(TABLE_NAME_PLACEHOLDER, qstrTables);
        qstrSubSelect = qstrSubSelect.replace(WHERE_OBJREF_CONDITION_PLACEHOLDER, qstrWhereConditions);
        qstrSubSelect = qstrSubSelect.replace(RESULT_MEMBER_PLACEHOLDER, qstrResults);
        qstrSubSelect = qstrSubSelect.replace(SUB_SELECT_NAME, qstrSubSelectName);

        qmSubRefQueries.insert(qstrSubSelectName, qstrSubSelect);
    }

    return qmSubRefQueries;
}

QMap<QString, QString> CdbQueryEnhancedNew::BuildObjectRefSubQueriesPerDepth(QString &p_qstrIdQuery, bool p_bNoJoins)
{
    QMap<QString, QString> qmSubRefQueries;
    bool bIdQuery = true;
    CdmQueryElement* pQueryElement = m_rpCdmQuery->GetQueryElement();
    if (pQueryElement && pQueryElement->GetComplexity() > MaxObjectIdComplexity)
    {
        bIdQuery = false;
    }
    if (p_qstrIdQuery.isEmpty())
    {
        bIdQuery = false;
    }

    QString qstrObjectIdTemplate = QString("%1.objectid = %2.objectid and "
                                           "%1.objectlistid = %2.objectlistid");
    QString qstrObjectTemplate = QString("%1.objectid = %2.val and "
                                         "%1.objectlistid = %2.orefobjectlist");
    QListIterator<int> depthIterator(m_qmmObjectRefMembers.uniqueKeys());
    while(depthIterator.hasNext())
    {
        int iDepth = depthIterator.next();
        bool bFirstTable = true;
        QString qstrTables;
        QStringList qstrlReferenceTables;
        QStringList qstrlAddedValueTables;
        QString qstrWhereConditions;
        QString qstrResults;

        // Add <iDepth> ObjectRef Tables to the from clause
        for (int iPos = 0; iPos < iDepth; ++iPos)
        {
            QString qstrCurrentTable = OBJREF_TABLE_PREFIX + QString::number(iPos);
            QString qstrTable = CdbDataStructureHelper::GetTableName(eDmValueObjectRef) + " " + qstrCurrentTable;
            qstrlReferenceTables.append(qstrCurrentTable);

            /* append delimiters to incrementelly built QStrings,
             * build Where Condition,
             * join Tables,
             * add the IdQuery if necessary
             * and select the objectid and objectlist of the first table
             */
            if (!bFirstTable)
            {
                qstrWhereConditions += " and ";

                if (p_bNoJoins)
                {
                    qstrTables += ", " + qstrTable;

                    qstrWhereConditions += qstrObjectTemplate
                            .arg(qstrCurrentTable)
                            .arg(qstrlReferenceTables.last());
                }
                else
                {
                    QString qstrJoin = qstrObjectTemplate
                            .arg(qstrCurrentTable)
                            .arg(qstrlReferenceTables.last());

                    qstrTables += " INNER JOIN " + qstrTable + " ON (" + qstrJoin + ")";
                }
            }
            else if (bIdQuery)
            {
                if (p_bNoJoins)
                {
                    qstrWhereConditions = qstrObjectIdTemplate
                            .arg(qstrCurrentTable)
                            .arg(OBJECT_PREFIX);
                    qstrTables = "(" + p_qstrIdQuery + ") " OBJECT_PREFIX ", " + qstrTable;
                }
                else
                {
                    QString qstrJoin = qstrObjectIdTemplate
                            .arg(qstrCurrentTable)
                            .arg(OBJECT_PREFIX);

                    qstrTables = "(" + p_qstrIdQuery + ") " OBJECT_PREFIX " INNER JOIN " + qstrTable + " ON (" + qstrJoin + ")";
                }
                qstrResults = OBJECT_PREFIX ".objectid, " OBJECT_PREFIX ".objectlistid";
            }
            else
            {
                qstrTables = qstrTable;
                qstrResults = qstrCurrentTable + ".objectid, " + qstrCurrentTable + ".objectlistid";
            }

            // update bFirstTable
            if (bFirstTable)
            {
                bFirstTable = false;
            }
        }

        // Iterator over every ReferencePath of given depth
        QListIterator<QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>>> pairIterator(m_qmmObjectRefMembers.values(iDepth));
        while (pairIterator.hasNext())
        {
            QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>> qPair = pairIterator.next();
            QLinkedList<const CdmMember*> qllReferences = qPair.first;
            QList<const CdmMember*> qlMembers = qPair.second;
            if (qllReferences.size() != iDepth || qlMembers.isEmpty())
            {
                continue;
            }

            QLinkedListIterator<const CdmMember*> refIterator(qllReferences);
            bool bFirstReference = true;
            int iTablePos = 0;
            QString qstrFullReferenceKeyName;
            QString qstrReferenceWhereCondition;

            while (refIterator.hasNext())
            {
                const CdmMember* pRefMember = refIterator.next();

                QString qstrCurrentTable = qstrlReferenceTables.at(iTablePos);
                QString qstrKeyname = pRefMember->GetKeyname();
                long lMemberId = pRefMember->GetId();

                if (bFirstReference)
                {
                    bFirstReference = false;
                }
                else
                {
                    qstrFullReferenceKeyName += ".";
                    qstrReferenceWhereCondition += " and ";
                }

                qstrFullReferenceKeyName += qstrKeyname;
                qstrReferenceWhereCondition += QString("%1.memberid = %2")
                        .arg(qstrCurrentTable)
                        .arg(lMemberId);

                ++iTablePos;
            }

            if (qstrWhereConditions.isEmpty())
            {
                qstrWhereConditions = qstrReferenceWhereCondition;
            }
            else
            {
                qstrWhereConditions += " or " + qstrReferenceWhereCondition;
            }

            QMultiMap<QString, long> qmmLocalValueTableMemberIds;

            for (int iPos = 0; iPos < qlMembers.size(); ++iPos)
            {
                const CdmMember* pRefMember = qlMembers.at(iPos);

                QString qstrTable = CdbDataStructureHelper::GetTableName(pRefMember->GetValueType());
                QString qstrKeyname = pRefMember->GetKeyname();
                long lMemberId = pRefMember->GetId();

                if (bFirstTable)
                {
                    qstrTables = qstrTable;
                    qstrResults = qstrTable + ".objectid, " + qstrTable + ".objectlistid";
                    bFirstTable = false;
                }
                else if (!qstrlAddedValueTables.contains(qstrTable))
                {
                    if (p_bNoJoins)
                    {
                        qstrTables += ", " + qstrTable;

                        qstrWhereConditions += " and " + qstrObjectTemplate
                                .arg(qstrTable)
                                .arg(qstrlReferenceTables.last());
                    }
                    else
                    {
                        qstrTables += " LEFT JOIN " + qstrTable + " ON (" + qstrObjectTemplate
                                .arg(qstrTable)
                                .arg(qstrlReferenceTables.last()) + ")";
                    }
                }

                qstrlAddedValueTables.append(qstrTable);
                qmmLocalValueTableMemberIds.insert(qstrTable, lMemberId);

                QString qstrValueName = qstrFullReferenceKeyName + "." + qstrKeyname;
                qstrValueName = MakeKeynameSave(qstrValueName);
                m_qmKeynamesSave.insert(qstrFullReferenceKeyName + "." + qstrKeyname, qstrValueName);
                QString qstrResultMember = QString("min(CASE WHEN %1.objectid = %2.val and "
                                                   "%1.objectlistid = %2.orefobjectlist and "
                                                   "%3 and "
                                                   "%1.memberid = %4 "
                                                   "THEN %1.val else null end)"
                                                   " AS %5")
                        .arg(qstrTable)
                        .arg(qstrlReferenceTables.last())
                        .arg(qstrReferenceWhereCondition)
                        .arg(lMemberId)
                        .arg(qstrValueName);

                qstrResults += ", " + qstrResultMember;
            }

            QListIterator<QString> qlKeyIterator = QListIterator<QString>(qmmLocalValueTableMemberIds.uniqueKeys());
            while (qlKeyIterator.hasNext())
            {
                if (!qstrWhereConditions.isEmpty())
                {
                    qstrWhereConditions += " and ";
                }
                QString qstrValueTable = qlKeyIterator.next();
                QStringList qstrlMemberIds;
                QListIterator<long> qlIt(qmmLocalValueTableMemberIds.values(qstrValueTable));
                while (qlIt.hasNext())
                {
                    long lMemberId = qlIt.next();
                    qstrlMemberIds.append(QString::number(lMemberId));
                }
                qstrWhereConditions += qstrValueTable + ".memberid IN (" + qstrlMemberIds.join(',') + ")";
            }
        }

        QString qstrSubSelectName = MakeKeynameSave("OBJREF_DEPTH_" + QString::number(iDepth) + "_SEL");

        QString qstrSubSelect = GetPartialObjRefQueryTemplate();
        qstrSubSelect = qstrSubSelect.replace(TABLE_NAME_PLACEHOLDER, qstrTables);
        qstrSubSelect = qstrSubSelect.replace(WHERE_OBJREF_CONDITION_PLACEHOLDER, qstrWhereConditions);
        qstrSubSelect = qstrSubSelect.replace(RESULT_MEMBER_PLACEHOLDER, qstrResults);
        qstrSubSelect = qstrSubSelect.replace(SUB_SELECT_NAME, qstrSubSelectName);

        qmSubRefQueries.insert(qstrSubSelectName, qstrSubSelect);
    }

    return qmSubRefQueries;
}

QString CdbQueryEnhancedNew::BuildResultMembers(QList<const CdmMember*> &p_qlMembers)
{
    QString qstrResult;
    bool bFirst = true;

    for (int counter = 0; counter < p_qlMembers.count(); ++counter)
    {
        const CdmMember* pMember = p_qlMembers[counter];

        if (CHKPTR(pMember))
        {
            if (!bFirst)
            {
                qstrResult += ", ";
            }
            else
            {
                bFirst = false;
            }

            QString qstrKeyname = MakeKeynameSave(pMember->GetKeyname());
            m_qmKeynamesSave.insert(pMember->GetKeyname(), qstrKeyname);

            QString qstrColumnName = "val";
            if(pMember->GetValueType() == eDmValueBinaryDocument)
            {
                qstrColumnName = "Filename";
            }

            qstrResult += QString("min(CASE WHEN memberid = %1 THEN %2 else null end) AS %3")
                    .arg(pMember->GetId())
                    .arg(qstrColumnName)
                    .arg(qstrKeyname);
        }
    }


    return qstrResult;
}

QString CdbQueryEnhancedNew::BuildConditionMembers( QList<const CdmMember*> &p_qlMembers)
{
    QString qstrResult;
    bool bFirst = true;

    for (int counter = 0; counter < p_qlMembers.count(); ++counter)
    {
        if (!bFirst)
        {
            qstrResult += ", ";
        }
        else
        {
            bFirst = false;
        }

        qstrResult += QString::number(p_qlMembers[counter]->GetId());
    }

    return qstrResult;
}

QString CdbQueryEnhancedNew::GetPartialQueryTemplate()
{
    CdmObjectContainer *pCont = m_rpCdmQuery->GetContainer();
    if(pCont)
    {
        return "(SELECT objectid, objectlistid, " RESULT_MEMBER_PLACEHOLDER  " FROM " TABLE_NAME_PLACEHOLDER
                " where memberid in (" MEMBER_CONDITION_PLACEHOLDER ") and objectlistid = " + QString::number(pCont->GetId()) + " group by objectid, objectlistid) " SUB_SELECT_NAME;
    }
    else
    {
        return "(SELECT objectid, objectlistid, " RESULT_MEMBER_PLACEHOLDER  " FROM " TABLE_NAME_PLACEHOLDER
                " where memberid in (" MEMBER_CONDITION_PLACEHOLDER ") group by objectid, objectlistid) " SUB_SELECT_NAME;
    }
}

QString CdbQueryEnhancedNew::GetPartialObjRefQueryTemplate()
{
    return "(SELECT " RESULT_MEMBER_PLACEHOLDER " FROM " TABLE_NAME_PLACEHOLDER
            " where " WHERE_OBJREF_CONDITION_PLACEHOLDER " group by objectid, objectlistid) " SUB_SELECT_NAME;
}

QString CdbQueryEnhancedNew::MakeKeynameSave(QString p_qstrKeyname)
{
    return CwmsUtilities::MakeKeynameSave(p_qstrKeyname, m_qmKeynames, m_iKeynameCount);
}

QString CdbQueryEnhancedNew::GetSQlFunction(int pos)
{
    QString qstrRet;
    CdmQueryResultElement* pCdmResultElement = m_rpCdmQuery->GetResultElement(pos);

    if (pCdmResultElement)
    {
        qstrRet = CdbDataStructureHelper::GetDataFieldName();

        switch (pCdmResultElement->GetMode())
        {
        case eDmQueryResultElementModeSum:
            qstrRet = "sum(" RESULT_MEMBER_PLACEHOLDER ")";
            break;
        case eDmQueryResultElementModeAvg:
            qstrRet = "avg(" RESULT_MEMBER_PLACEHOLDER ")";
            break;
        case eDmQueryResultElementModeMax:
            qstrRet = "max(" RESULT_MEMBER_PLACEHOLDER ")";
            break;
        case eDmQueryResultElementModeMin:
            qstrRet = "min(" RESULT_MEMBER_PLACEHOLDER ")";
            break;
        case eDmQueryResultElementModeCount:
            qstrRet = "count(*)";
            break;
        default: // no grouping mode
            qstrRet = RESULT_MEMBER_PLACEHOLDER;
            break;
        }
    }
    else // not found expecting that is it a reference value.
    {
        qstrRet = "a.val";
    }

    return qstrRet;
}
