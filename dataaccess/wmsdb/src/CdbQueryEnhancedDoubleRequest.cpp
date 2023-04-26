// System and QT Includes
#include <qsqlquery.h>

#include "CwmsUtilities.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmDataAccessHelper.h"
#include "CdmClass.h"

// Own Includes
#include "CdbQuery.h"
#include "CdbDataStructureHelper.h"
#include "CdbDataAccess.h"
#include "CdbQueryEnhancedDoubleRequest.h"

#define RESULT_MEMBER_PLACEHOLDER "$RESULT_MEMBERS"
#define MEMBER_CONDITION_PLACEHOLDER "$MEMBER_CONDITION"
#define TABLE_NAME_PLACEHOLDER "$TABLE_NAME"
#define SUB_SELECT_NAME "$SUBSELECT_NAME"
#define OBJECT_IDS ":objectids"
#define OBJREF_TABLE_PREFIX "ref"
#define OBJECT_PREFIX "obj"
#define OBJECT_QUERY_PLACHOLDER "$OBJ"
#define WHERE_OBJREF_CONDITION_PLACEHOLDER "$WHERE"

CdbQueryEnhancedDoubleRequest::CdbQueryEnhancedDoubleRequest(CdmQueryEnhanced* p_pCdmQueryEnhanced,
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

CdbQueryEnhancedDoubleRequest::~CdbQueryEnhancedDoubleRequest()
{
}

qint64 CdbQueryEnhancedDoubleRequest::Execute()
{
    qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        QStringList qvlObjectIds;
        QString qstrSql = GenerateSql(qvlObjectIds);

        if (!qstrSql.isEmpty())
        {
            QString qstrObjIds = qvlObjectIds.join(",");
            qstrSql = qstrSql.replace(OBJECT_IDS, qstrObjIds);

            QSqlQuery cQSqlQuery(m_rpCdbDataAccess->GetDbInterface()->GetSqlDatabase());
            cQSqlQuery.prepare(qstrSql);

            if (!qstrSql.isEmpty())
            {
                m_rpCdmQuery->AddDatabaseCommand(qstrSql);
                lRet = ExecuteQuery(cQSqlQuery);
            }
            else
            {
                lRet = CdmLogging::eDmFalse;
            }
        }
        else
        {
            lRet = CdmLogging::eDmFalse;
        }
    }

    return lRet;
}

QString CdbQueryEnhancedDoubleRequest::GenerateSql(QStringList& qvlObjects)
{
    QString qstrSql;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        QVector<QString> qvResultElements = m_rpCdmQuery->GetResultElements();

        if (m_rpCdmQuery->HasResultElements())
        {
            ExecuteIdQuery(qvlObjects);

            if (!qvlObjects.isEmpty())
            {
                qstrSql = GenerateMemberSql(qvResultElements);
            }
        }
        else
        {
            CdbQuery cCdbQuery(m_rpCdbDataAccess, m_rpCdmQuery);
            qstrSql = cCdbQuery.GenerateQuerySql();
        }
    }

    return qstrSql;
}

void CdbQueryEnhancedDoubleRequest::ExecuteIdQuery(QStringList& qvlResults)
{

    QString qstrObjectIdQuery;
    CdbQuery cCdbQuery(m_rpCdbDataAccess, m_rpCdmQuery);
    qstrObjectIdQuery = cCdbQuery.GenerateQuerySql();
    m_rpCdmQuery->AddDatabaseCommand(qstrObjectIdQuery);

    QSqlQuery cQSqlQuery;

    if (!qstrObjectIdQuery.isEmpty())
    {
        qint64 lRet = m_rpCdbDataAccess->ExecuteQuery(qstrObjectIdQuery, cQSqlQuery);

        if(lRet > 0)
        {
            if(cQSqlQuery.first())
            {
                do
                {
                    qvlResults.append(cQSqlQuery.value(0).toString());
                }
                while(cQSqlQuery.next());
            }
        }
        else
        {
            ERR("ID Query failed! " + qstrObjectIdQuery);
        }
    }

}


qint64 CdbQueryEnhancedDoubleRequest::ExecuteQuery(QSqlQuery& cQSqlQuery)
{
    qint64 lRet = CdmLogging::eDmUnknownDBQueryError;
    lRet = m_rpCdbDataAccess->ExecuteQuery(cQSqlQuery);

    if(lRet > 0)
    {
        qint64 lObjectId = 0;
        qint64 lContainerId = 0;

        if(cQSqlQuery.first())
        {
            int iColumnCount = m_rpCdmQuery->GetColumnCount();
            do
            {
                if (m_rpCdmQuery->ContainsGrouping() && iColumnCount == 1) // only one result means there is no objectid in result
                {
                    QVariant qVariant = cQSqlQuery.value(0);
                    CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, 0, qVariant, -1, -1);
                }
                else
                {

                    if (!m_rpCdmQuery->IsAggregationQuery())
                    {
                        lObjectId = cQSqlQuery.value(iColumnCount).toInt();
                        lContainerId = cQSqlQuery.value(iColumnCount + 1).toInt();
                    }
                    else
                    {
                        lObjectId--;
                    }

                    for (int iCounter = 0; iCounter < iColumnCount; ++iCounter)
                    {
                        QVariant qVariant = cQSqlQuery.value(iCounter);
                        CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, iCounter, qVariant, lObjectId, lContainerId);
                    }
                }
            }
            while(cQSqlQuery.next());
        }
    }

    return lRet;
}

QString CdbQueryEnhancedDoubleRequest::GenerateMemberSql(QVector<QString> &p_qvKeynames)
{
    QString qstrSql;
    BuildMemberMap(p_qvKeynames);
    QMap<QString, QString> qmSubQueries = BuildSubQueries();
    qstrSql = ConcatenateQueries(p_qvKeynames, qmSubQueries);

    return qstrSql;
}

QString CdbQueryEnhancedDoubleRequest::ConcatenateQueries(QVector<QString> &p_qvKeynames,
                                                          QMap<QString, QString> &p_qmSubQueries)
{
    QString qstrSql = CreateHead(p_qvKeynames);

    if (!qstrSql.isEmpty())
    {
        QMapIterator<QString, QString> qmIt(p_qmSubQueries);
        QString qstrFirstKey;
        bool bFirst = true;

        while (qmIt.hasNext())
        {
            qmIt.next();
            QString qstrSqlPart;
            QString qstrSubQuery = qmIt.value();

            if (bFirst)
            {
                qstrFirstKey = qmIt.key();

                if (!m_rpCdmQuery->IsAggregationQuery())
                {
                    qstrSqlPart += QString(", %1.objectid, %1.objectlistid").arg(qstrFirstKey);
                }

                qstrSqlPart += " FROM ";

                if (!qstrSubQuery.startsWith("("))
                {
                    qstrSqlPart +=  "(";
                }

                qstrSqlPart += qstrSubQuery + " ";
            }
            else
            {
                qstrSqlPart = " left join ";
                if (!qstrSubQuery.startsWith("("))
                {
                    qstrSqlPart +=  "(";
                }
                qstrSqlPart +=  qstrSubQuery + " on " + qmIt.key() + ".objectid = " + qstrFirstKey + ".objectid";
            }

            qstrSql += qstrSqlPart;
            bFirst = false;
        }

        AddGroupByToSql(qstrSql);
        AddOrderByToSql(qstrSql);
    }
    return qstrSql;
}


void CdbQueryEnhancedDoubleRequest::AddOrderByToSql(QString &qstrSql)
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

void CdbQueryEnhancedDoubleRequest::AddGroupByToSql(QString &qstrSql)
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

QString CdbQueryEnhancedDoubleRequest::CreateHead(QVector<QString> &p_qvKeynames)
{
    QString qstrHead = "select ";

    for (int i = 0; i < p_qvKeynames.size(); ++i)
    {
        QString qstrKeyname = p_qvKeynames.at(i);
        QString qstrTemplate = GetSQlFunction(i);
        QString qstrKeynameSave = m_qmKeynamesSave.value(qstrKeyname);

        if (!qstrTemplate.contains(RESULT_MEMBER_PLACEHOLDER))
        {
            qstrHead += qstrTemplate;
        }
        else if (!qstrKeynameSave.isEmpty())
        {
            qstrHead += qstrTemplate.replace(RESULT_MEMBER_PLACEHOLDER, qstrKeynameSave);

        }
        else
        {
            ERR("Failed to select " + qstrKeyname);
            return "";
        }

        if (i+1 < p_qvKeynames.size())
        {
            qstrHead += ", ";
        }
    }

    return qstrHead;
}

void CdbQueryEnhancedDoubleRequest::BuildMemberMap(QVector<QString> &p_qvKeynames)
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

void CdbQueryEnhancedDoubleRequest::BuildTypeAndReferenceList(QVector<QString> &p_qvKeynames)
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

void CdbQueryEnhancedDoubleRequest::BuildType(QString p_qstrKeyname)
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

void CdbQueryEnhancedDoubleRequest::BuildReference(QString p_qstrKeyname)
{
    const CdmClass* pCdmClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pCdmClass))
    {
        QList<const CdmMember*> p_qllReferencedMembers;
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

            QMutableMapIterator<int, QPair<QList<const CdmMember*>, QList<const CdmMember*>>>
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
                QPair<QList<const CdmMember*>, QList<const CdmMember*>> qPair;
                qPair.first = p_qllReferencedMembers;
                QList<const CdmMember*> qlMembers;
                qlMembers.append(pSearchMember);
                qPair.second = qlMembers;
                m_qmmObjectRefMembers.insert(iDepth, qPair);
            }
        }
    }
}

QMap<QString, QString> CdbQueryEnhancedDoubleRequest::BuildSubQueries()
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

    QMapIterator<QString, QString> subRefIt(BuildObjectRefSubQueries());
    while (subRefIt.hasNext())
    {
        subRefIt.next();
        qmSubQueries.insert(subRefIt.key(), subRefIt.value());
    }

    return qmSubQueries;
}

QMap<QString, QString> CdbQueryEnhancedDoubleRequest::BuildObjectRefSubQueries(bool p_bNoJoins)
{
    QMap<QString, QString> qmSubRefQueries;
    //CdmQueryElement* pQueryElement = m_rpCdmQuery->GetQueryElement();

    QString qstrMemberidAndObjectTemplate = QString("%1.memberid = %2 and "
                                                   "%1.objectid = %3.val and "
                                                   "%1.objectlistid = %3.orefobjectlist");
    QString qstrObjectTemplate = QString("%1.objectid = %2.val and "
                                         "%1.objectlistid = %2.orefobjectlist");

    QMapIterator<int, QPair<QList<const CdmMember*>, QList<const CdmMember*>>>
            qmitPairs(m_qmmObjectRefMembers);
    while (qmitPairs.hasNext())
    {
        qmitPairs.next();
        QPair<QList<const CdmMember*>, QList<const CdmMember*>> qPair = qmitPairs.value();
        QList<const CdmMember*> qlReferences = qPair.first;
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

        QListIterator<const CdmMember*> qlIt(qlReferences);
        while (qlIt.hasNext())
        {
            const CdmMember* pRefMember = qlIt.next();

            QString qstrCurrentTable = OBJREF_TABLE_PREFIX + QString::number(iTablesPos);
            QString qstrTable = CdbDataStructureHelper::GetTableName(pRefMember->GetValueType()) + " " + qstrCurrentTable;
            QString qstrKeyname = pRefMember->GetKeyname();
            qint64 lMemberId = pRefMember->GetId();

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
            else
            {
                qstrWhereConditions += qstrCurrentTable + ".memberid = " + QString::number(lMemberId) + " and " + qstrCurrentTable + ".objectid in (" + OBJECT_IDS + ")";
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

        QMultiMap<QString,qint64> qmmValueTableMemberIds;

        for (int iPos = 0; iPos < qlMembers.size(); ++iPos)
        {
            const CdmMember* pRefMember = qlMembers.at(iPos);

            QString qstrTable = CdbDataStructureHelper::GetTableName(pRefMember->GetValueType());
            QString qstrKeyname = pRefMember->GetKeyname();
            qint64 lMemberId = pRefMember->GetId();

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
            QListIterator<qint64> qlIt(qmmValueTableMemberIds.values(qstrValueTable));
            while (qlIt.hasNext())
            {
                qint64 lMemberId = qlIt.next();
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


QString CdbQueryEnhancedDoubleRequest::BuildResultMembers(QList<const CdmMember*> &p_qlMembers)
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

QString CdbQueryEnhancedDoubleRequest::BuildConditionMembers( QList<const CdmMember*> &p_qlMembers)
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

QString CdbQueryEnhancedDoubleRequest::GetPartialQueryTemplate()
{
    QString qstrTemplate;

    qstrTemplate  = QString("SELECT objectid, objectlistid, %1 FROM %2 where memberid in (%3) and objectid in(%4) group by objectid, objectlistid) %5")
            .arg(RESULT_MEMBER_PLACEHOLDER)
            .arg(TABLE_NAME_PLACEHOLDER)
            .arg(MEMBER_CONDITION_PLACEHOLDER)
            .arg(OBJECT_IDS)
            .arg(SUB_SELECT_NAME);
    return qstrTemplate;
}

QString CdbQueryEnhancedDoubleRequest::GetPartialObjRefQueryTemplate()
{
    return "(SELECT " RESULT_MEMBER_PLACEHOLDER " FROM " TABLE_NAME_PLACEHOLDER
            " where " WHERE_OBJREF_CONDITION_PLACEHOLDER " group by objectid, objectlistid) " SUB_SELECT_NAME;
}

QString CdbQueryEnhancedDoubleRequest::MakeKeynameSave(QString p_qstrKeyname)
{
    return CwmsUtilities::MakeKeynameSave(p_qstrKeyname, m_qmKeynames, m_iKeynameCount);
}

QString CdbQueryEnhancedDoubleRequest::GetSQlFunction(int pos)
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
            m_qmKeynamesSave.insert("count", MakeKeynameSave(qstrRet));
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
