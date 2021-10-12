// System and QT Includes
#include <QString>
#include <qfile.h>
#include <QList>
#include <qvariant.h>
#include <QSqlQuery>

#include "CwmsUtilities.h"
#include "CwmsCleanupMacros.h"

// own Includes
#include "CdmQuery.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmQueryElement.h"
#include "CdmDataAccessHelper.h"

// WMS Includes
#include "CdbDataAccess.h"
#include "CdbDataStructureHelper.h"
#include "CdbQueryElement.h"
#include "CdbQuery.h"



CdbQueryElement::CdbQueryElement(CdbDataAccess* p_pCdbDataAccess,
                                 CdmQueryElement* p_pCdmQueryElement)
    : m_rpCdbDataAccess(p_pCdbDataAccess),
      m_rpCdmQueryElement(p_pCdmQueryElement)

{
    if(CHKPTR(m_rpCdmQueryElement) && CHKPTR(m_rpCdbDataAccess))
    {
        QList<CdmQueryElement*> qvlQueryElements;
        m_rpCdmQueryElement->GetChildList(qvlQueryElements);
        CreateChilds(qvlQueryElements);
    }
}

CdbQueryElement::~CdbQueryElement()
{
    CLEANUP_LINKEDLIST_PTR(CdbQueryElement, m_qvlChilds);
}

qint64 CdbQueryElement::Execute(QMap<qint64,qint64> &p_rqvlResultList)
{
    int lRet = CdmLogging::eDmUnknownDBQueryError;
    lRet = ExecuteValue(p_rqvlResultList);

    return lRet;
}

qint64 CdbQueryElement::ExecuteValue(QMap<qint64,qint64> &p_rqvlResults)
{
   qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

    if (m_rpCdmQueryElement->GetCompareKeyname().toUpper() == "OBJECT_ID" &&
            m_rpCdmQueryElement->GetValueType() == eDmValueObjectRef)
    {
        if (m_rpCdmQueryElement->GetSubQuery() != nullptr)
        {
            ERR("Subqueries not allowed with OBJECT_ID condition.");
            return EC(eDmInvalidSelectStatement);
        }

        CdmQuery* pQuery = m_rpCdmQueryElement->GetQuery();

        if (CHKPTR(pQuery))
        {
           qint64 containerId = pQuery->GetContainerId();

            if (containerId > 0)
            {
                if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeEqual)
                {
                    p_rqvlResults.insert(m_rpCdmQueryElement->GetValue().toInt(), containerId);
                    lRet = EC(eDmOk);
                }
                else if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn)
                {
                    QList<QVariant>::iterator qlIt = m_rpCdmQueryElement->GetList().begin();
                    QList<QVariant>::iterator qlItEnd = m_rpCdmQueryElement->GetList().end();

                    for (; qlIt  != qlItEnd; ++qlIt)
                    {
                        p_rqvlResults.insert((*qlIt).toInt(), containerId);
                    }

                    lRet = EC(eDmOk);
                }
                else
                {
                    ERR("For Object_ID only '='' or 'IN' as operator is allowed");
                }
            }
            else
            {
                ERR("Request works only on containers.");
            }
        }
    }
    else
    {
        QString qstrQuery = GenerateQuery();

        QSqlQuery cQSqlQuery;

        if (!qstrQuery.isEmpty())
        {
            lRet = m_rpCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

            if(lRet > 0)
            {
                if(cQSqlQuery.first())
                {
                    do // reading each objectid
                    {
                        int iObjectId = cQSqlQuery.value(0).toInt();
                        int iContainerId = cQSqlQuery.value(1).toInt();

                        if(!p_rqvlResults.contains(iObjectId))
                        {
                            p_rqvlResults[iObjectId] = iContainerId;
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
    }

    return lRet;
}

QString CdbQueryElement::GenerateQuery()
{
    QString qstrQuery;

    switch(m_rpCdmQueryElement->GetQueryElementType())
    {
    case eDmQueryElementTypeAnd:
        qstrQuery = GenerateAndQuery();
        break;
    case eDmQueryElementTypeOr:
        qstrQuery = GenerateOrQuery();
        break;
    case eDmQueryElementTypeCompare:
        qstrQuery = GenerateValueQuery();
        break;
    default:
        ERR("Default in switch called, this enum does not exist here!!");
        break;
    }

    return qstrQuery;
}

void CdbQueryElement::CreateChilds(QList<CdmQueryElement*> &p_qvlChilds)
{
    QList<CdmQueryElement*>::iterator qvlIt    = p_qvlChilds.begin();
    QList<CdmQueryElement*>::iterator qvlItEnd = p_qvlChilds.end();

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        CdmQueryElement* pCdmQueryElement = (*qvlIt);

        if(CHKPTR(pCdmQueryElement))
        {
            CdbQueryElement* pCdbQueryElement = new CdbQueryElement(m_rpCdbDataAccess, pCdmQueryElement);
            m_qvlChilds.append(pCdbQueryElement);
        }
    }
}

QString CdbQueryElement::GenerateAndQuery()
{
    QString qstrQuery;
    qstrQuery = "Select o1.ObjectId as objectid, o1.objectlistid as objectlistid from WMS_DM_OBJECT o1";

    if (m_qvlChilds.count() > 0)
    {
        int iCounter = 1;


        QList<CdbQueryElement*>::iterator qvlIt = m_qvlChilds.begin();
        QList<CdbQueryElement*>::iterator qvlItEnd = m_qvlChilds.end();

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            qstrQuery += " inner join ";

            CdbQueryElement* pCdbQueryElement = (*qvlIt);

            if(CHKPTR(pCdbQueryElement))
            {
                QString qstrPartialQuery = pCdbQueryElement->GenerateQuery();

                if (!qstrPartialQuery.isEmpty())
                {
                    qstrQuery += " (" + qstrPartialQuery + ") o" + QString::number(++iCounter);
                }
                else
                {
                    qstrQuery = "";
                    break;
                }
            }

            qstrQuery += " on o1.objectid = o" + QString::number(iCounter) + ".objectid";
        }
    }

    return qstrQuery;
}

QString CdbQueryElement::GenerateOrQuery()
{
    QString qstrQuery;

    if (m_qvlChilds.count() > 0)
    {
        QList<CdbQueryElement*>::iterator qvlIt = m_qvlChilds.begin();
        QList<CdbQueryElement*>::iterator qvlItEnd = m_qvlChilds.end();
        bool bFirst = true;

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            if (!bFirst)
            {
                qstrQuery += "union ";
            }

            qstrQuery += "Select o1.ObjectId as objectid, o1.objectlistid as objectlistid from WMS_DM_OBJECT o1 inner join ";

            CdbQueryElement* pCdbQueryElement = (*qvlIt);

            if(CHKPTR(pCdbQueryElement))
            {
                QString qstrPartialQuery = pCdbQueryElement->GenerateQuery();

                if (!qstrPartialQuery.isEmpty())
                {
                    qstrQuery += "(" + qstrPartialQuery + ") o2 ";
                }
                else
                {
                    qstrQuery = "";
                    break;
                }
            }

            qstrQuery += "on o1.objectid = o2.objectid ";
            bFirst = false;
        }
    }

    return qstrQuery;
}

QString CdbQueryElement::GenerateValueQuery()
{
    QString qstrQuery;
    CdmQuery* pCdmQuery = m_rpCdmQueryElement->GetQuery();

    if(pCdmQuery)
    {
        if (m_rpCdmQueryElement->GetCompareKeyname().toUpper() == "OBJECT_ID" &&
                m_rpCdmQueryElement->GetValueType() == eDmValueObjectRef)
        {
            if (m_rpCdmQueryElement->GetSubQuery() != nullptr)
            {
                ERR("Subqueries not allowed with OBJECT_ID condition.");
                return "";
            }

            CdmQuery* pQuery = m_rpCdmQueryElement->GetQuery();

            if (CHKPTR(pQuery))
            {
               qint64 containerId = pQuery->GetContainerId();

                if (containerId > 0)
                {
                    if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeEqual)
                    {
                        qstrQuery = "select distinct objectid, objectlistid from WMS_DM_OBJECT where Objectid = " + m_rpCdmQueryElement->GetValue().toString();
                    }
                    else if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn)
                    {

                        QList<QVariant>::iterator qlIt = m_rpCdmQueryElement->GetList().begin();
                        QList<QVariant>::iterator qlItEnd = m_rpCdmQueryElement->GetList().end();
                        qstrQuery = "(";
                        bool bFirst = true;

                        for (; qlIt  != qlItEnd; ++qlIt)
                        {
                            if (!bFirst)
                            {
                                qstrQuery += ", ";
                            }
                            else
                            {
                                bFirst = false;
                            }

                            qstrQuery += (*qlIt).toString();
                        }

                        qstrQuery += ")";
                        qstrQuery = "select objectid, objectlistid from WMS_DM_OBJECT where Objectid in " + qstrQuery;
                    }
                    else
                    {
                        ERR("For Object_ID only '='' or 'IN' as operator is allowed");
                    }
                }
                else
                {
                    ERR("Request works only on containers.");
                }
            }
        }
        else
        {
            QString qstrTableName = GetTableName();
            QString qstrCompareValue = GetCompareValueAsString();
            QString qstrCompareSign = GetCompareSign();
            QString qstrCompareKeyname = CdbDataStructureHelper::GetFirstMember(m_rpCdmQueryElement->GetCompareKeyname());
            QString qstrValueDataField = GetDataFieldName(); // contains d.DataFieldName
            const CdmClass* pClass = pCdmQuery->GetClass();

            if (!qstrTableName.isEmpty() && !qstrCompareValue.isEmpty() && qstrCompareValue != "()")
            {
                // optimized query without subqueries
                qstrQuery = QString("select distinct a.objectid as objectid, a.objectlistid as objectlistid from ");

                // Add Subquery as Derived Table if necessary
                if ((m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn ||
                     m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeNotIn)
                        && qstrCompareValue.contains("select")
                        && qstrCompareValue.contains("from"))
                {
                    qstrQuery += "(" + qstrCompareValue + ") b, ";

                    if (m_rpCdmQueryElement->IsSubQueryEnhanced())
                    {
                        qstrCompareValue = "b.value";
                    }
                    else
                    {
                        qstrCompareValue = "b.objectid";
                    }

                    qstrCompareSign = "=";
                }

                qstrQuery += qstrTableName + " a";

                // Based on Objectlist
                if (pCdmQuery->GetContainerId() > 0)
                {
                    qstrQuery += " where ";
                    qstrQuery += QString("a.objectlistid = %1")
                            .arg(pCdmQuery->GetContainerId());

                }
                // Based in Class expected only one objectlist in this class or used in subqueries
                else if (pClass)
                {
                    QList<qint64> qllClasses = pClass->GetDerivedClasses();
                    qllClasses.append(pClass->GetId());

                    QString qstrClasses = "(";
                    bool bFirst = true;

                    for (int pos = 0; pos < qllClasses.size(); ++pos)
                    {
                        if (!bFirst)
                        {
                            qstrClasses += ", ";
                        }
                        else
                        {
                            bFirst = false;
                        }

                        qstrClasses += QString::number(qllClasses.at(pos));
                    }

                    qstrClasses += ")";

                    qstrQuery += " inner join WMS_DM_OBJECTLIST objlist ON objlist.objectlistid = a.objectlistId "
                                 " where objlist.classId in " + qstrClasses;
                }
                else if (pCdmQuery->GetClassId() > 0)
                {
                    qstrQuery += " inner join WMS_DM_OBJECTLIST objlist ON objlist.objectlistid = a.objectlistId "
                                 " where objlist.classId = " + QString::number(pCdmQuery->GetClassId());
                }
                else
                {
                    ERR("Query Incomplete. No container or class set");
                }

                const CdmMember* pMember = nullptr;

                if (pClass && (pMember = pClass->FindMember(qstrCompareKeyname)))
                {
                    qstrQuery += QString(" and a.memberid = %1")
                            .arg(pMember->GetId());
                }
                else
                {
                    qstrQuery += QString(" and a.keyname = '%1'")
                            .arg(CwmsUtilities::MaskString(qstrCompareKeyname));
                }
                qstrQuery += QString(" and %1 %2 %3")
                        .arg(qstrValueDataField)
                        .arg(qstrCompareSign)
                        .arg(qstrCompareValue);
            }
            else
            {
                ERR("Tablename or comparevalue is empty!");
                qstrQuery = "";
            }
        }
    }

    return qstrQuery;
}

QString CdbQueryElement::GetDataFieldName()
{
    QString qstrRet;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        // the default
        if (!m_rpCdmQueryElement->IsThisCompare())
        {
            qstrRet = "a.";
            EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();
            qstrRet += CdbDataStructureHelper::GetDataFieldName();

            if (eDmValueType == eDmValueString || eDmValueType == eDmValueCharacterDocument)
            {
                qstrRet = "upper(" + qstrRet + ")";
            }
        }
        else
        {
            qstrRet = "a.objectId";
        }
    }

    return qstrRet;
}

QString CdbQueryElement::GetCompareSign()
{
    return m_rpCdmQueryElement->GetCompareTypeAsString();
}

QString CdbQueryElement::GetTableName()
{
    QString qstrTableName;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        if (!m_rpCdmQueryElement->IsThisCompare())
        {
            EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();
            qstrTableName = CdbDataStructureHelper::GetTableName(eDmValueType);
        }
        else
        {
            qstrTableName = "WMS_DM_OBJECT";
        }
    }

    return qstrTableName;
}

QString CdbQueryElement::GetTableIdName()
{
    QString qstrTableIdName;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        if (!m_rpCdmQueryElement->IsThisCompare())
        {
            qstrTableIdName = CdbDataStructureHelper::GetTableIdName();
        }
        else
        {
            qstrTableIdName = "OBJECTID";
        }
    }

    return qstrTableIdName;
}

QString CdbQueryElement::GetCompareValueAsString()
{
    QString qstrValue;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();

        if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn ||
                m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeNotIn)
        {
            qstrValue = GetListCompareValueAsString();
        }
        else if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeNull ||
                 m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeNotNull)
        {
            QVariant qVariant = m_rpCdmQueryElement->GetValue();
            if (!qVariant.isNull() && qVariant.toString().toUpper() != "NULL")
            {
                WARNING("\"IS NULL\" - Condition shouldn't contain a value");
            }
            qstrValue = "NULL";
        }
        else
        {
            QVariant qVariant = m_rpCdmQueryElement->GetValue();

            if (qVariant.isValid())
            {
                switch(eDmValueType)
                {
                case eDmValueObjectRef:
                case eDmValueCounter:
                case eDmValueInt:
                case eDmValueLong:
                case eDmValueContainerRef:
                case eDmValueUser:
                case eDmValueUserGroup:
                case eDmValueEnum:
                    qstrValue = QString::number(qVariant.toInt());
                    break;
                case eDmValueBool:
                    qstrValue = CwmsUtilities::ConvertBoolToString(qVariant.toBool());
                    break;
                case eDmValueFloat:
                case eDmValueDouble:
                    qstrValue = QString::number(qVariant.toDouble());
                    break;
                case eDmValueString:
                case eDmValueCharacterDocument:
                    qstrValue = qVariant.toString();

                    /*if (qstrValue.contains("-"))
                    {
                        qstrValue = qstrValue.replace("-", "_");
                        m_rpCdmQueryElement->SetCompareType(eDmQueryCompareTypeLike);
                    }

                    if (qstrValue.contains("ß"))
                    {
                        qstrValue = qstrValue.replace("ß", "_");
                        m_rpCdmQueryElement->SetCompareType(eDmQueryCompareTypeLike);
                    }*/

                    if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeLike &&
                            !qstrValue.isEmpty() && !qstrValue.contains("%"))
                    {
                        qstrValue = "'" + CwmsUtilities::MaskStringForChanges(qstrValue.toUpper()) + "%'";
                    }
                    else
                    {
                        qstrValue = "'" + CwmsUtilities::MaskStringForChanges(qstrValue.toUpper()) + "'";
                    }
                    break;
                case eDmValueDateTime:
                    qstrValue = CwmsUtilities::ChangeDateToString(qVariant.toDateTime());
                    break;
                case eDmValueDate:
                    qstrValue = CwmsUtilities::ChangeDateToString(qVariant.toDate());
                    break;
                case eDmValueTime:
                    qstrValue = "'" + qVariant.toTime().toString(Qt::ISODate) + "'";
                    break;
                    // for this values queries are not possible
                case eDmValueBinaryDocument:
                case eDmValueListInt:
                case eDmValueListDouble:
                case eDmValueListString:
                case eDmValueDictStringInt:
                case eDmValueDictStringString:
                case eDmValueDictStringDouble:
                case eDmValueDictIntInt:
                case eDmValueDictIntString:
                case eDmValueDictIntDouble:
                default:
                    ERR("Invalid Type for Comparision choosen ID: " + QString::number(eDmValueType));
                    qstrValue = "Invalid Value";
                    break;
                }
            }
        }
    }

    return qstrValue;
}

QString CdbQueryElement::GetListCompareValueAsString()
{
    QString qstrValueList;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();

        if ((eDmValueType == eDmValueLong ||
             eDmValueType == eDmValueInt ||
             eDmValueType == eDmValueObjectRef ||
             eDmValueType == eDmValueCounter ||
             eDmValueType == eDmValueUserGroup ||
             eDmValueType == eDmValueEnum)
                && m_rpCdmQueryElement->HasSubQuery())
        {
            CdmQuery* pCdmQuery = m_rpCdmQueryElement->GetSubQuery();
            CdbQuery cCdbQuery(m_rpCdbDataAccess, pCdmQuery);
            qstrValueList = "(" + cCdbQuery.GenerateSql() + ")";
        }
        else
        {
            qstrValueList = ExtractCompareEntriesFromList();
        }
    }

    return qstrValueList;
}

QString CdbQueryElement::ExtractCompareEntriesFromList()
{
    QString qstrValueList;
    QList<QVariant> qvlSubList;
    qvlSubList += m_rpCdmQueryElement->GetList();

    if (qvlSubList.size() > 0)
    {
        QList<QVariant>::Iterator qvlIt;
        qstrValueList = "(";
        bool bFirst = true;

        for (qvlIt = qvlSubList.begin(); qvlIt != qvlSubList.end(); ++qvlIt)
        {
            if (!bFirst)
            {
                qstrValueList += ", ";
            }
            else
            {
                bFirst = false;
            }

            qstrValueList += (*qvlIt).toString();
        }

        qstrValueList += ")";
    }
    else
    {
        qstrValueList = "(0)";
    }

    return qstrValueList;
}
