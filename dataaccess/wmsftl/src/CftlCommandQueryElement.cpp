/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <qstring.h>
#include <qfile.h>
#include <QList>
#include <qvariant.h>
#include <QSqlQuery>
#include <CdmObjectContainer.h>

#include "CwmsUtilities.h"

// own Includes
#include "CdmQuery.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmQueryElement.h"
#include "CdmDataAccessHelper.h"
#include "CdmClassManager.h"

// WMS Includes
#include "CftlHelper.h"
#include "CftlDialect.h"
#include "CftlDataStructureHelper.h"
#include "CftlCommandQueryElement.h"
#include "CftlCommandQuery.h"


CftlCommandQueryElement::CftlCommandQueryElement(CftlDataAccess* p_pCftlDataAccess,
                                                 CdmQueryElement* p_pCdmQueryElement,
                                                 CftlCommandQuery* p_rpQuery)
    : m_rpCftlDataAccess(p_pCftlDataAccess),
      m_rpCdmQueryElement(p_pCdmQueryElement),
      m_rpCtflQuery(p_rpQuery)

{
    if(CHKPTR(m_rpCdmQueryElement) &&
       CHKPTR(m_rpCftlDataAccess))
    {
        QList<CdmQueryElement*> qvlQueryElements;
        m_rpCdmQueryElement->GetChildList(qvlQueryElements);
        CreateChilds(qvlQueryElements);
    }
}

CftlCommandQueryElement::~CftlCommandQueryElement()
{
}

QString CftlCommandQueryElement::GenerateQuery()
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

void CftlCommandQueryElement::CreateChilds(QList<CdmQueryElement*>& p_qvlChilds)
{
    QList<CdmQueryElement*>::iterator qvlIt    = p_qvlChilds.begin();
    QList<CdmQueryElement*>::iterator qvlItEnd = p_qvlChilds.end();

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        CdmQueryElement* pCdmQueryElement = (*qvlIt);

        if(CHKPTR(pCdmQueryElement))
        {
            CftlCommandQueryElement* pCftlQueryElement
                    = new CftlCommandQueryElement(m_rpCftlDataAccess,
                                                  pCdmQueryElement,
                                                  m_rpCtflQuery);
            m_qvlChilds.append(pCftlQueryElement);
        }
    }
}

QString CftlCommandQueryElement::GenerateSelectPartOfQuery()
{
    QString qstrQuery;
    CdmQuery* pQuery = m_rpCdmQueryElement->GetQuery();

    if (CHKPTR(pQuery) && !m_rpCdmQueryElement->HasParent())
    {
        QString qstrClassTableName = CftlHelper::GetClassTableName(pQuery);

        if (!qstrClassTableName.isEmpty())
        {
            qstrQuery = QString ("Select o1.%1 as objectid, o1.%2 as objectlistid from %3 o1 %4 where ")
                    .arg(FTL_OBJECT_ID_FIELD_NAME)
                    .arg(FTL_CONTAINER_ID_FIELD_NAME)
                    .arg(qstrClassTableName)
                    .arg(m_rpCtflQuery->GetJoinsAsString());

            CdmObjectContainer* pContainer = pQuery->GetContainer();

            if (pContainer)
            {
                qstrQuery += QString("%1 = %2 and ")
                        .arg("o1." FTL_CONTAINER_ID_FIELD_NAME)
                        .arg(pContainer->GetId());
            }
        }
    }

    return qstrQuery;
}

void CftlCommandQueryElement::CollectChildConditions(QStringList& qstrlConditions)
{
    QList<CftlCommandQueryElement*>::iterator qvlIt = m_qvlChilds.begin();
    QList<CftlCommandQueryElement*>::iterator qvlItEnd = m_qvlChilds.end();

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        CftlCommandQueryElement* pCftlQueryElement = (*qvlIt);

        if(CHKPTR(pCftlQueryElement))
        {
            qstrlConditions.append(pCftlQueryElement->GenerateQuery());
        }
    }
}

void CftlCommandQueryElement::BuildWhereClauseQuery(QStringList& qstrlConditions, QString& qstrQuery, QString& p_qstrAndOr)
{
    bool first = true;
    qstrQuery += " (";

    for (int iPos = 0; iPos < qstrlConditions.count(); ++iPos)
    {
        if (!first)
        {
            qstrQuery += " " + p_qstrAndOr + " ";
        }
        else
        {
            first = false;
        }

        qstrQuery += qstrlConditions[iPos];
    }

    qstrQuery += ")";
}

QString CftlCommandQueryElement::GenerateAndOrQuery(QString p_qstrAndOr)
{
    QString qstrQuery;

    if (m_qvlChilds.count() > 0)
    {
        QStringList qstrlConditions;
        CollectChildConditions(qstrlConditions);
        BuildWhereClauseQuery(qstrlConditions, qstrQuery, p_qstrAndOr);
    }

    qstrQuery = GenerateSelectPartOfQuery() + " " + qstrQuery;
    return qstrQuery;
}

QString CftlCommandQueryElement::GenerateAndQuery()
{
    return GenerateAndOrQuery(SQL_AND);
}

QString CftlCommandQueryElement::GenerateOrQuery()
{
    return GenerateAndOrQuery(SQL_OR);
}

QString CftlCommandQueryElement::GenerateValueConditionObjectId()
{
    QString qstrQuery;

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
                    qstrQuery = QString ("%1 = %2")
                            .arg(FTL_OBJECT_ID_FIELD_NAME)
                            .arg(m_rpCdmQueryElement->GetValue().toString())
                            .arg(FTL_CONTAINER_ID_FIELD_NAME)
                            .arg(containerId);

                }
                else if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn)
                {
                    qstrQuery = QString ("%1 = %2 and %3 in(")
                            .arg(FTL_CONTAINER_ID_FIELD_NAME)
                            .arg(containerId)
                            .arg(FTL_OBJECT_ID_FIELD_NAME);

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
                }
                else
                {
                    ERR("For Object_ID only '='' or 'IN' as operator is allowed");
                }
            }
            else
            {
                if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeEqual)
                {
                    qstrQuery = QString ("%1 = %2")
                            .arg(FTL_OBJECT_ID_FIELD_NAME)
                            .arg(m_rpCdmQueryElement->GetValue().toString());

                }
                else if (m_rpCdmQueryElement->GetCompareType() == eDmQueryCompareTypeIn)
                {
                    qstrQuery = QString ("%1 in(")
                            .arg(FTL_OBJECT_ID_FIELD_NAME);

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
                }
                else
                {
                    ERR("For Object_ID only '='' or 'IN' as operator is allowed");
                }
            }
        }
    }
    else
    {
        QString qstrCompareValue = GetCompareValueAsString();
        QString qstrCompareSign = GetCompareSign();
        QString qstrCompareKeyname = GetCompareKeyname();

        if (IsCompareValueValid(qstrCompareValue) &&
            !qstrCompareKeyname.isEmpty())
        {
            qstrQuery = QString("%1 %2 %3")
                    .arg(qstrCompareKeyname)
                    .arg(qstrCompareSign)
                    .arg(qstrCompareValue);
        }
        else
        {
            ERR("Comparevalue or comparekeyname is Empty!");
            qstrQuery = "";
        }
    }

    return qstrQuery;
}

bool CftlCommandQueryElement::IsCompareValueValid(QString& p_qstrCompareValue)
{
    return (!p_qstrCompareValue.isEmpty() &&
            p_qstrCompareValue.simplified() != "()");
}

QString CftlCommandQueryElement::GenerateValueQuery()
{
    QString qstrQuery = GenerateValueConditionObjectId();
    qstrQuery = GenerateSelectPartOfQuery() + " " + qstrQuery;
    return qstrQuery;
}

QString CftlCommandQueryElement::GetCompareKeyname()
{
    QString qstrRet;

    if (CftlHelper::HasMultipleReferences(m_rpCdmQueryElement))
    {
        CdmClass* pClass = CftlHelper::GetClassOfMember(m_rpCdmQueryElement);

        if (CHKPTR(pClass))
        {
            QStringList qstrl_Members = m_rpCdmQueryElement->GetCompareKeyname().split(".");

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

                        qstrJoinPartner = m_rpCtflQuery->AddOrUpdateLeftJoin(prevMember, qstrJoin, qstrRefName, qstrJoinPartner);
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
                    ERR("Unknown Member in query. Member: " + m_rpCdmQueryElement->GetCompareKeyname());
                }
            }
        }
    }
    else if (m_rpCdmQueryElement->HasSubQuery())
    {
        qstrRet = QString("o1." FTL_OBJECT_ID_FIELD_NAME);
    }
    else
    {
        qstrRet = CftlHelper::GetClassMemberFieldNameFromQueryElement(m_rpCdmQueryElement);
    }

    return qstrRet;
}

QString CftlCommandQueryElement::GetCompareSign()
{
    QString qstrRet;
    CdmQueryElement* pElement = m_rpCdmQueryElement;

    if (CftlHelper::HasMultipleReferences(m_rpCdmQueryElement) && m_rpCdmQueryElement->HasSubQuery())
    {
        pElement = CftlHelper::GetLastQueryElementReference(pElement);
    }

    if (CHKPTR(pElement))
    {
        switch(pElement->GetCompareType())
        {
        case eDmQueryCompareTypeEqual:
            qstrRet = "=";
            break;
        case eDmQueryCompareTypeNotEqual:
            qstrRet = "<>";
            break;
        case eDmQueryCompareTypeSmaller:
            qstrRet = "<";
            break;
        case eDmQueryCompareTypeSmallerEqual:
            qstrRet = "<=";
            break;
        case eDmQueryCompareTypeLarger:
            qstrRet = ">";
            break;
        case eDmQueryCompareTypeLargerEqual:
            qstrRet = ">=";
            break;
        case eDmQueryCompareTypeLike:
            qstrRet = "LIKE";
            break;
        case eDmQueryCompareTypeIn:
            qstrRet = "IN";
            break;
        case eDmQueryCompareTypeNotIn:
            qstrRet = "NOT IN";
            break;
        default:
            ERR("Unknown compare sign!!!");
            qstrRet = "?";
            break;
        };
    }

    return qstrRet;
}

QString CftlCommandQueryElement::getComparisionValueFromQueryElement(EdmValueType p_eType)
{
    QString qstrValue;
    QVariant qVariant = m_rpCdmQueryElement->GetValue();

    if (!qVariant.isValid() && m_rpCdmQueryElement->HasSubQuery())
    {
        CdmQueryElement* pElement = CftlHelper::GetLastQueryElementReference(m_rpCdmQueryElement);

        if (CHKPTR(pElement))
        {
            qVariant = pElement->GetValue();
        }
    }

    if (qVariant.isValid())
    {
        switch(p_eType)
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
            if (m_rpCdmQueryElement->GetCompareType() != eDmQueryCompareTypeLike)
            {
                qstrValue = "'" + CwmsUtilities::MaskStringForChanges(qVariant.toString().toUpper()) + "'";
            }
            else
            {
                if(qVariant.toString().contains("%"))
                {
                    qstrValue = "'" + CwmsUtilities::MaskStringForChanges(qVariant.toString().toUpper()) + "'";
                }
                else
                {
                    qstrValue = "'" + CwmsUtilities::MaskStringForChanges(qVariant.toString().toUpper()) + "%'";
                }
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
            ERR("Invalid Type for Comparision choosen ID: " + QString::number(p_eType));
            qstrValue = "Invalid Value";
            break;
        }
    }

    return qstrValue;
}

QString CftlCommandQueryElement::GetCompareValueAsString()
{
    QString qstrValue;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();

        // read final member of reference
        if (CftlHelper::HasMultipleReferences(m_rpCdmQueryElement))
        {
            const CdmMember* pMember = CftlHelper::GetLastMemberOfQueryElementReference(m_rpCdmQueryElement);

            if (CHKPTR(pMember))
            {
                qstrValue = getComparisionValueFromQueryElement(pMember->GetValueType());
            }
            else
            {
                ERR("Member not found");
            }
        }
        else
        {
            if (m_rpCdmQueryElement->GetCompareType() != eDmQueryCompareTypeIn &&
                    m_rpCdmQueryElement->GetCompareType() != eDmQueryCompareTypeNotIn)
            {
                qstrValue = getComparisionValueFromQueryElement(eDmValueType);
            }
            else
            {
                qstrValue = GetListCompareValueAsString();
            }
        }
    }

    return qstrValue;
}

QString CftlCommandQueryElement::GetListCompareValueAsString()
{
    QString qstrValueList;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        EdmValueType eDmValueType = m_rpCdmQueryElement->GetValueType();

        if (eDmValueType == eDmValueLong ||
                eDmValueType == eDmValueInt ||
                eDmValueType == eDmValueObjectRef ||
                eDmValueType == eDmValueCounter ||
                eDmValueType == eDmValueUserGroup ||
                eDmValueType == eDmValueEnum)
        {
            qstrValueList = GetListCompareValueAsStringFromDecimals();
        }
        else
        {
            qstrValueList = ExtractCompareEntriesFromList();
        }
    }

    return qstrValueList;
}

QString CftlCommandQueryElement::GetListCompareValueAsStringFromDecimals()
{
    QString qstrValueList;
    CdmQuery* pCdmQuery = m_rpCdmQueryElement->GetSubQuery();

    if (pCdmQuery)
    {
        CftlCommandQuery cCftlQuery(m_rpCftlDataAccess, pCdmQuery);
        qstrValueList = "(" + cCftlQuery.GenerateSql() + ")";
    }
    else
    {
        qstrValueList = ExtractCompareEntriesFromList();
    }

    return qstrValueList;
}

QString CftlCommandQueryElement::ExtractCompareEntriesFromList()
{
    QString qstrValueList;
    QList<QVariant> qvlSubList;
    qvlSubList += m_rpCdmQueryElement->GetList();

    if (qvlSubList.count() > 0)
    {
        QList<QVariant>::iterator qvlIt    = qvlSubList.begin();
        QList<QVariant>::iterator qvlItEnd = qvlSubList.end();

        qstrValueList = "(";
        bool bFirst = true;

        for(; qvlIt != qvlItEnd; ++qvlIt)
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
    else if (qstrValueList.isEmpty())
    {
        qstrValueList = "(0)";
    }

    return qstrValueList;
}
