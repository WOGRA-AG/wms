// System and QT Includes
#include <QString>
#include <QVariant>
#include <QDomDocument>
#include <QList>

// WMS Commons Includes

// own Includes
#include "CdmModelElement.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmQueryBuilder.h"



CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery)
: m_lChildQuerys(),
  m_eDmQueryElementType(eDmQueryElementTypeNone),
  m_qVariant(),
  m_eDmCompareType(eDmQueryCompareTypeNone),
  m_qstrCompareKeyname(),
  m_rpCdmQuery(p_pCdmQuery),
  m_rpCdmSubQuery(nullptr),
  m_qvlInOrNotInList(),
  m_eDmValueCompare(eDmValueNone),
  m_bAutomaticSubqueryCreation(false),
  m_pParent(nullptr)
{
   // nothing todo
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery,
                                 EdmQueryElementType p_eDmQueryElementType)
: CdmQueryElement(p_pCdmQuery)
{
    SetQueryElementType(p_eDmQueryElementType);
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery,
                                 EdmQueryElementType p_eDmQueryElementType,
                                 EdmQueryCompareType p_eDmQueryCompareType)
: CdmQueryElement(p_pCdmQuery)
{
    SetQueryElementType(p_eDmQueryElementType);
    SetCompareType(p_eDmQueryCompareType);
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery,
                                 EdmQueryElementType p_eDmQueryElementType,
                                 EdmQueryCompareType p_eDmQueryCompareType,
                                 QVariant p_qVariant,
                                 QString p_qstrKeyname)
: CdmQueryElement(p_pCdmQuery)
{
    SetQueryElementType(p_eDmQueryElementType);
    SetCompareType(p_eDmQueryCompareType);
    SetComparisonValue(p_qstrKeyname, p_qVariant);
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery, QString p_qstrCondition)
: CdmQueryElement(p_pCdmQuery)
{
    ParseCondition(p_qstrCondition);
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery, QDomElement &p_rqDomElement)
: CdmQueryElement(p_pCdmQuery)
{
   XmlImport(p_rqDomElement);
}

CdmQueryElement::CdmQueryElement(CdmQuery* p_pCdmQuery, QVariantMap &p_rqvHash)
: CdmQueryElement(p_pCdmQuery)
{
    m_eDmQueryElementType = EdmQueryElementType(p_rqvHash["ElementType"].toInt());
    m_qVariant = p_rqvHash["Value"];
    m_eDmCompareType = EdmQueryCompareType(p_rqvHash["CompareType"].toInt());
    m_qstrCompareKeyname = p_rqvHash["Keyname"].toString();

    m_eDmValueCompare = EdmValueType(p_rqvHash["ValueType"].toInt());
    m_bAutomaticSubqueryCreation = p_rqvHash["AutomaticSubQueryCreation"].toBool();

    if (p_rqvHash.contains("SubQuery"))
    {
        QVariantMap qvHash = p_rqvHash["SubQuery"].toMap();
        m_rpCdmSubQuery = new CdmQuery(qvHash);
    }

    QList<QVariant> qllInOrNotInList = p_rqvHash["InOrNotIn"].toList();

    for (int iPos = 0; iPos < qllInOrNotInList.size(); ++iPos)
    {
        m_qvlInOrNotInList.append(qllInOrNotInList[iPos]);
    }

    QList<QVariant> qllChildQueries = p_rqvHash["ChildQueries"].toList();

    for (int iPos = 0; iPos < qllChildQueries.size(); ++iPos)
    {
        QVariantMap qvChild = qllChildQueries[iPos].toMap();
        CdmQueryElement* pElement = new CdmQueryElement(p_pCdmQuery, qvChild);
        m_lChildQuerys.append(pElement);
    }
}

CdmQueryElement::~CdmQueryElement()
{
    if (m_bAutomaticSubqueryCreation)
    {
        DELPTR(m_rpCdmSubQuery);
    }
}

QVariant CdmQueryElement::GetVariant() const
{
    QVariantMap qvHash;

    qvHash.insert("CompareType", m_eDmCompareType);
    qvHash.insert("ElementType", m_eDmQueryElementType);
    qvHash.insert("ValueType", m_eDmValueCompare);
    qvHash.insert("Value", m_qVariant);
    qvHash.insert("Keyname", m_qstrCompareKeyname);
    qvHash.insert("AutomaticSubQueryCreation", m_bAutomaticSubqueryCreation);

    if (m_rpCdmSubQuery)
    {
        qvHash.insert("SubQuery", m_rpCdmSubQuery->GetVariant());
    }

    QList<QVariant>::const_iterator qllIt = m_qvlInOrNotInList.begin();
    QList<QVariant>::const_iterator qllItEnd = m_qvlInOrNotInList.end();
    QList<QVariant> qlInOrNotInList;

    for (; qllIt != qllItEnd; ++qllIt)
    {
        qlInOrNotInList.append(*qllIt);
    }

    qvHash.insert("InOrNotIn", qlInOrNotInList);

    QList<CdmQueryElement*>::const_iterator qllQueryIt = m_lChildQuerys.begin();
    QList<CdmQueryElement*>::const_iterator qllQueryItEnd = m_lChildQuerys.end();
    QList<QVariant> qlChildQueries;

    for (; qllQueryIt != qllQueryItEnd; ++qllQueryIt)
    {
        qlChildQueries.append((*qllQueryIt)->GetVariant());
    }

    qvHash.insert("ChildQueries", qlChildQueries);

    return qvHash;
}

void CdmQueryElement::SetParent(CdmQueryElement* p_pParent)
{
    m_pParent = p_pParent;
}

CdmQueryElement* CdmQueryElement::GetParent() const
{
    return m_pParent;
}

bool CdmQueryElement::HasParent() const
{
    return (m_pParent != nullptr);
}

CdmQuery* CdmQueryElement::GetQuery() const
{
    return m_rpCdmQuery;
}

EdmQueryCompareType CdmQueryElement::GetCompareType() const
{
    return m_eDmCompareType;
}

void CdmQueryElement::SetCompareType(EdmQueryCompareType p_eDmQueryCompareType)
{
    m_eDmCompareType = p_eDmQueryCompareType;
}

EdmQueryElementType CdmQueryElement::GetQueryElementType() const
{
    return m_eDmQueryElementType;
}

void CdmQueryElement::SetQueryElementType(EdmQueryElementType p_eDmQueryElementType)
{
    m_eDmQueryElementType = p_eDmQueryElementType;
}

void CdmQueryElement::GetChildList(QList<CdmQueryElement*> &p_rqvlChilds) const
{
    if(!m_lChildQuerys.isEmpty())
    {
        p_rqvlChilds = m_lChildQuerys;
    }
}

void CdmQueryElement::SetVariant(QVariant p_pqVariant)
{
    SetValue(p_pqVariant);
}

void CdmQueryElement::SetValue(QVariant p_pqVariant)
{
    m_qVariant = p_pqVariant;
}

QVariant CdmQueryElement::GetValue() const
{
    return m_qVariant;
}

void CdmQueryElement::SetKeyname(QString p_qstrKeyname)
{
    m_qstrCompareKeyname = p_qstrKeyname;
}

QString CdmQueryElement::GetCompareKeyname() const
{
    return m_qstrCompareKeyname;
}

void CdmQueryElement::AddChild(CdmQueryElement* p_pCdmQueryElement)
{
    if(CHKPTR(p_pCdmQueryElement))
    {
        p_pCdmQueryElement->SetParent(this);
        m_lChildQuerys.append(p_pCdmQueryElement);
    }
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname, QVariant p_qvValue)
{
    if (p_qvValue.isValid() && p_qvValue.canConvert(QMetaType::QVariantList))
    {
        QSequentialIterable qvIt = p_qvValue.value<QSequentialIterable>();
        m_qVariant = QVariant();
        m_qvlInOrNotInList.clear();

        for (const QVariant &qVariant : qvIt)
        {
            m_qvlInOrNotInList.append(qVariant);
        }
    }
    else
    {
        m_qVariant = p_qvValue;
    }
    m_qstrCompareKeyname = p_qstrKeyname;
    FindValue();
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname, bool p_bValue)
{
    SetComparisonValue(p_qstrKeyname, QVariant(p_bValue));
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname, int p_iValue)
{
    SetComparisonValue(p_qstrKeyname, QVariant(p_iValue));
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname,qint64 p_lValue)
{
    SetComparisonValue(p_qstrKeyname, QVariant(static_cast<qlonglong>(p_lValue)));
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname, float p_fValue)
{
    SetComparisonValue(p_qstrKeyname, QVariant(p_fValue));
}

void CdmQueryElement::SetComparisonValue(QString p_qstrKeyname, QList<QVariant> p_qvlList)
{
    m_qVariant = QVariant();
    m_qvlInOrNotInList = p_qvlList;
    m_qstrCompareKeyname = p_qstrKeyname;
    FindValue();
}

bool CdmQueryElement::IsValueMember() const
{
    bool bRet = false;

    if (GetQuery())
    {
        const CdmClass* pCdmClass = GetQuery()->GetClass();

        if (!pCdmClass && GetQuery()->GetClassId() > 0)
        {
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

            if(CHKPTR(pCdmManager))
            {
                CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

                if(CHKPTR(pCdmClassManager))
                {
                    pCdmClass = pCdmClassManager->FindClassById(m_rpCdmQuery->GetClassId());
                }
            }
        }

        if (CHKPTR(pCdmClass))
        {
            if (pCdmClass->FindMember(GetValue().toString()))
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

void CdmQueryElement::FindValue()
{
    FindValue(m_qstrCompareKeyname);
}

bool CdmQueryElement::FindValue(QString p_qstrKeyname)
{
    bool bFound = false;

    if (p_qstrKeyname.toUpper() == "THIS")
    {
        m_eDmValueCompare = eDmValueObjectRef;
        return true;
    }

    if (CHKPTR(GetQuery()))
    {
        const CdmClass* pCdmClass = GetQuery()->GetClass();

        if (!pCdmClass && GetQuery()->GetClassId() > 0)
        {
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

            if(CHKPTR(pCdmManager))
            {
                CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

                if(CHKPTR(pCdmClassManager))
                {
                    pCdmClass = pCdmClassManager->FindClassById(GetQuery()->GetClassId());
                }
            }
        }

        if (pCdmClass)
        {
            if (!GetCompareKeyname().contains("."))
            {
                const CdmMember* pCdmMember = pCdmClass->FindMember(p_qstrKeyname);

                if (pCdmMember)
                {
                    m_eDmValueCompare = pCdmMember->GetValueType();
                    bFound = true;
                }
                else
                {
                    if (p_qstrKeyname.toUpper() == "OBJECT_ID")
                    {
                        m_eDmValueCompare = eDmValueObjectRef;
                        bFound = true;
                    }
                    else
                    {
                        ERR("Where clause member not found keyname: " + p_qstrKeyname);
                        GetQuery()->m_bValid = false;
                    }
                }
            }
            else
            {
                INFO("Looking if it is a dot seperated keyname!");
                int iPos = p_qstrKeyname.indexOf('.');

                if (iPos != -1)
                {
                    QString qstrKeyname = GetCompareKeyname().mid(0, iPos);

                    const CdmMember* pCdmMember = pCdmClass->FindMember(qstrKeyname);

                    if(CHKPTR(pCdmMember))
                    {
                        bFound = true;
                        m_eDmValueCompare = pCdmMember->GetValueType();

                        if (m_eDmValueCompare == eDmValueObjectRef ||
                                m_eDmValueCompare == eDmValueContainerRef)
                        {
                            QString qstrSubMember = p_qstrKeyname.mid(iPos + 1,
                                                                      p_qstrKeyname.length() - iPos - 1);
                            p_qstrKeyname = qstrKeyname;
                            CreateSubQueryFromMember(pCdmMember, qstrSubMember);
                        }
                        else
                        {
                            ERR("The Member has an invalidtype for referencing to other classes!");
                        }
                    }
                }
                else
                {
                    ERR("Invalid Keyname used!!!");
                }
            }
        }
        else
        {
            ERR("Invalid ClassId in Query. Check container or class in From clause.");
        }
    }

    return bFound;
}

void CdmQueryElement::CreateSubQueryFromMember(const CdmMember* p_pCdmMember,
                                               QString p_qstrSubMemberName)
{
    if (CHKPTR(p_pCdmMember) && !p_qstrSubMemberName.isEmpty())
    {
       qint64 lClassId = p_pCdmMember->GetClassReference();

        CdmClassManager* pCdmClassManager = p_pCdmMember->GetClassManager();

        if (CHKPTR(pCdmClassManager))
        {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(lClassId);

            if (CHKPTR(pCdmClass))
            {
                // First step create the subquery for the IN element with class instett of objectlist
                m_bAutomaticSubqueryCreation = true;
                m_rpCdmSubQuery = new CdmQuery(pCdmClass);

                //  change of ownership in the constructor m_qVariant set to nullptr is enough
                CdmQueryElement* pCdmQueryElement = new CdmQueryElement(m_rpCdmSubQuery,
                                                                        eDmQueryElementTypeCompare,
                                                                        m_eDmCompareType,
                                                                        m_qVariant,
                                                                        p_qstrSubMemberName);

                m_rpCdmSubQuery->ResetQueryElement(pCdmQueryElement);

                // second step change the current queryelement to an IN element
                m_eDmCompareType = eDmQueryCompareTypeIn;
                // must not be deleted because there is a change of ownership in the constructor above
                m_qVariant = QVariant();
            }
        }
    }
}

void CdmQueryElement::SetSubQuery(QString p_qstrKeyname, CdmQuery* p_pCdmQuery)
{
    if (!p_qstrKeyname.isEmpty() && CHKPTR(p_pCdmQuery))
    {
        m_eDmCompareType = eDmQueryCompareTypeIn;
        m_rpCdmSubQuery = p_pCdmQuery;
        m_rpCdmSubQuery->SetSubQuery(true);
        m_qstrCompareKeyname = p_qstrKeyname;
        FindValue();
    }
}

CdmQuery* CdmQueryElement::GetSubQuery() const
{
    return m_rpCdmSubQuery;
}

QList<QVariant>& CdmQueryElement::GetList()
{
    return m_qvlInOrNotInList;
}

EdmValueType CdmQueryElement::GetValueType() const
{
    return m_eDmValueCompare;
}

int CdmQueryElement::GetComplexity() const
{
    int iRet = 1;

    if (GetQueryElementType() != eDmQueryElementTypeCompare)
    {
        QList<CdmQueryElement*>::ConstIterator qvlIt;

        for(qvlIt = m_lChildQuerys.begin(); qvlIt != m_lChildQuerys.end(); ++qvlIt)
        {
            iRet += (*qvlIt)->GetComplexity();
        }
    }
    else
    {
        iRet += GetCompareKeyname().count('.') * 3;
    }

    return iRet;
}

bool CdmQueryElement::IsThisCompare() const
{
    return (GetCompareKeyname().toUpper() == "THIS");
}

bool CdmQueryElement::HasSubQuery() const
{
    bool bRet = false;

    if (m_rpCdmSubQuery)
    {
        bRet = true;
    }

    return bRet;
}

bool CdmQueryElement::IsSubQueryEnhanced() const
{
    bool bRet = false;

    if (m_rpCdmSubQuery && m_rpCdmSubQuery->HasResultElements())
    {
        bRet = true;
    }

    return bRet;
}

void CdmQueryElement::ParseCondition(QString p_qstrCondition)
{
    p_qstrCondition = p_qstrCondition.trimmed();

    if (p_qstrCondition.startsWith("AND", Qt::CaseInsensitive))
    {
        SetQueryElementType(eDmQueryElementTypeAnd);
    }
    else if (p_qstrCondition.startsWith("OR", Qt::CaseInsensitive))
    {
        SetQueryElementType(eDmQueryElementTypeOr);
    }
    else
    {
        SetQueryElementType(eDmQueryElementTypeCompare);
    }

    switch (GetQueryElementType())
    {
    case eDmQueryElementTypeAnd:
    case eDmQueryElementTypeOr:
        ParseChildConditions(p_qstrCondition);
        break;
    case eDmQueryElementTypeCompare:
        ParseCompareCondition(p_qstrCondition);
        break;
    case eDmQueryElementTypeNone:
        ERR("Elementtype not set");
        break;
    default:
        ERR("Unknown Elementtype");
    }
}

void CdmQueryElement::ParseChildConditions(QString p_qstrCondition)
{
    int iStartPos = p_qstrCondition.indexOf("(");
    int iEndPos = p_qstrCondition.lastIndexOf(")");

    if (iStartPos > 0 && iEndPos > 0 && iEndPos > iStartPos)
    {
        QString qstrCondition = p_qstrCondition.mid(iStartPos + 1, iEndPos - iStartPos - 1);
        QStringList qstrlConditions = qstrCondition.split(",", QString::SkipEmptyParts);

        if (qstrlConditions.isEmpty())
        {
            qstrlConditions.append(qstrCondition);
        }

        for (int iCounter = 0; iCounter < qstrlConditions.size(); ++iCounter)
        {
            QString qstrChildCondition = qstrlConditions[iCounter];
            qstrChildCondition = qstrChildCondition.trimmed();
            CdmQueryElement* pCdmQueryElement = new CdmQueryElement(GetQuery(), qstrChildCondition);
            AddChild(pCdmQueryElement);
        }
    }
    else
    {
        ERR("Error while parsing where condition. Do not find braces in correct sequence.\n" + p_qstrCondition);
    }
}

void CdmQueryElement::ParseCompareCondition(QString p_qstrCondition)
{
    p_qstrCondition = p_qstrCondition.simplified();
    int iCompareElementPos = FindCompareElement(p_qstrCondition);

    if (iCompareElementPos > 0)
    {
        QString qstrFirstCompareItem = p_qstrCondition.mid(0, iCompareElementPos);
        qstrFirstCompareItem = qstrFirstCompareItem.trimmed();
        int iSecondCompareItemPos = iCompareElementPos + GetCompareElementLength();
        QString qstrSecondCompareItem;

        if (iSecondCompareItemPos > iCompareElementPos)
        {
            qstrSecondCompareItem = p_qstrCondition.mid(iSecondCompareItemPos, p_qstrCondition.length() - iSecondCompareItemPos);
            qstrSecondCompareItem = qstrSecondCompareItem.trimmed();
        }
        else
        {
            ERR("Error occurred!");
        }

        if (!qstrFirstCompareItem.isEmpty() && !qstrSecondCompareItem.isEmpty())
        {
            if (GetCompareType() != eDmQueryCompareTypeIn &&
                    GetCompareType() != eDmQueryCompareTypeNotIn)
            {
                AnalyzeCompare(qstrFirstCompareItem, qstrSecondCompareItem);
            }
            else // special handling if in and not in
            {
                SetInNotInValuesForComparision(qstrFirstCompareItem, qstrSecondCompareItem);
            }
        }
        else
        {
            ERR("One or Two compare elements are missing!");
        }
    }
    else
    {
        ERR("No compare element found!");
    }
}

int CdmQueryElement::FindCompareElement(QString p_qstrCompareElement)
{
    int iPos = 0;

    if (p_qstrCompareElement.contains("<>", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeNotEqual);
        iPos = p_qstrCompareElement.indexOf("<>", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("<=", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeSmallerEqual);
        iPos = p_qstrCompareElement.indexOf("<=", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains(">=", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeLargerEqual);
        iPos = p_qstrCompareElement.indexOf(">=", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("=", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeEqual);
        iPos = p_qstrCompareElement.indexOf("=", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("<", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeSmaller);
        iPos = p_qstrCompareElement.indexOf("<", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains(">", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeLarger);
        iPos = p_qstrCompareElement.indexOf(">", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("NOT LIKE", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeNotLike);
        iPos = p_qstrCompareElement.indexOf("NOT LIKE", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("LIKE", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeLike);
        iPos = p_qstrCompareElement.indexOf("LIKE", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("NOT IN", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeNotIn);
        iPos = p_qstrCompareElement.indexOf("NOT IN", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("IN", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeIn);
        iPos = p_qstrCompareElement.indexOf("IN", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("IS NOT", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeNotNull);
        iPos = p_qstrCompareElement.indexOf("IS NOT", Qt::CaseInsensitive);
    }
    else if (p_qstrCompareElement.contains("IS", Qt::CaseInsensitive))
    {
        SetCompareType(eDmQueryCompareTypeNull);
        iPos = p_qstrCompareElement.indexOf("IS", Qt::CaseInsensitive);
    }
    else
    {
        SetCompareType(eDmQueryCompareTypeNone);
    }

    return iPos;
}

int CdmQueryElement::GetCompareElementLength()
{
    int iLength = 0;

    if (GetCompareType() == eDmQueryCompareTypeNone)
    {
        ERR("Compare type is not defined");
        iLength = -1;
    }
    else
    {
        iLength = GetCompareTypeAsString().size();
    }

    return iLength;
}

void CdmQueryElement::SetInNotInValuesForComparision(QString p_qstrFirst, QString p_qstrSecond)
{
    SetKeyname(p_qstrFirst);
    FindValue();

    int iStartPos = p_qstrSecond.indexOf("(");
    int iEndPos = p_qstrSecond.lastIndexOf(")");

    if (iStartPos >= 0 && iEndPos > 0 && iEndPos > iStartPos)
    {
        QString qstrContent = p_qstrSecond.mid (iStartPos + 1, iEndPos - iStartPos - 1);
        qstrContent = qstrContent.simplified();

        if (qstrContent.startsWith("select", Qt::CaseInsensitive))
        {
            m_rpCdmSubQuery = CdmQueryBuilder::BuildQuery(qstrContent);
            m_bAutomaticSubqueryCreation = true;
        }
        else
        {
            QStringList qstrlItems = qstrContent.split(",");

            if (qstrlItems.count() == 0)
            {
                qstrlItems.append(qstrContent);
            }

            for (int iCounter = 0;
                 iCounter < qstrlItems.size();
                 ++iCounter)
            {
                QString qstrItem = qstrlItems[iCounter];
                qstrItem = qstrItem.trimmed();
                m_qvlInOrNotInList.append(qstrItem);
            }
        }
    }
}

const CdmMember* CdmQueryElement::GetMember(QString p_qstrKeyname)
{
     const CdmClass* pCdmClass = nullptr;
    if (GetQuery())
    {
        CdmObjectContainer* pContainer = GetQuery()->GetContainer();

        if (pContainer)
        {
            pCdmClass = pContainer->GetClass();
        }
        else
        {
            pCdmClass = GetQuery()->GetClass();
        }

        if (CHKPTR(pCdmClass))
        {
            return pCdmClass->FindMember(p_qstrKeyname);
        }
    }

    return nullptr;
}

void CdmQueryElement::AnalyzeCompare(QString p_qstrFirst, QString p_qstrSecond)
{
    const CdmMember* pCdmMember = GetMember(p_qstrFirst);

    if (!pCdmMember)
    {
        pCdmMember = GetMember(p_qstrSecond);
    }

    if (pCdmMember)
    {
        SetKeyname(p_qstrFirst);
        SetValue(p_qstrSecond);
        m_eDmValueCompare = pCdmMember->GetValueType();
    }
    else
    {
        ERR("No Member in condition");
    }
}

QString CdmQueryElement::GetConditionAsString() const
{
    QString qstrRet;

    if (GetParent() == nullptr)
    {
        qstrRet = "where ";
    }

    if (GetQueryElementType() == eDmQueryElementTypeCompare)
    {
        qstrRet += GetCompareKeyname() + " " + GetCompareTypeAsString() + " ";

        switch(GetCompareType())
        {
        case eDmQueryCompareTypeIn:
        case eDmQueryCompareTypeNotIn:
        {
            if (HasSubQuery())
            {
                qstrRet += "(" + CdmQueryBuilder::BuildString(GetSubQuery()) + ")";
            }
            else
            {
                QStringList qstrlInValues;
                QListIterator<QVariant> qllIt(m_qvlInOrNotInList);
                while (qllIt.hasNext())
                {
                    qstrlInValues.append(qllIt.next().toString());
                }
                qstrRet += "(" + qstrlInValues.join(",") + ")";
            }
            break;
        }
        case eDmQueryCompareTypeNull:
        case eDmQueryCompareTypeNotNull:
            qstrRet += "NULL";
            break;
        default:
            if (GetValueType() == eDmValueString ||
                    GetValueType() == eDmValueCharacterDocument)
            {
                qstrRet += "\"" + GetValue().toString() + "\"";
            }
            else
            {
                qstrRet += GetValue().toString();
            }
            break;
        }
    }
    else
    {
        if (GetQueryElementType() == eDmQueryElementTypeAnd)
        {
            qstrRet += "and(";
        }
        else
        {
            qstrRet += "or(";
        }

        QList<CdmQueryElement*>::ConstIterator qvlIt;
        bool bFirst = true;

        for(qvlIt = m_lChildQuerys.begin(); qvlIt != m_lChildQuerys.end(); ++qvlIt)
        {
            if (bFirst)
            {
                bFirst = false;
            }
            else
            {
                qstrRet += ", ";
            }

            CdmQueryElement* pCdmQueryElement = (*qvlIt);

            if (CHKPTR(pCdmQueryElement))
            {
                qstrRet += pCdmQueryElement->GetConditionAsString();
            }
        }

        qstrRet += ")";
    }

    return qstrRet;
}

QString CdmQueryElement::GetCompareTypeAsString() const
{
    return CompareTypeToString(GetCompareType());
}

QString CdmQueryElement::CompareTypeToString(EdmQueryCompareType p_eDmQueryCompareType)
{
    QString qstrRet;

    switch(p_eDmQueryCompareType)
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
    case eDmQueryCompareTypeNotLike:
        qstrRet = "NOT LIKE";
        break;
    case eDmQueryCompareTypeIn:
        qstrRet = "IN";
        break;
    case eDmQueryCompareTypeNotIn:
        qstrRet = "NOT IN";
        break;
    case eDmQueryCompareTypeNull:
        qstrRet = "IS";
        break;
    case eDmQueryCompareTypeNotNull:
        qstrRet = "IS NOT";
        break;
    default:
        ERR("Unknown compare sign!!!");
        qstrRet = "?";
        break;
    };

    return qstrRet;
}

void CdmQueryElement::XmlExport(QDomDocument& p_rqdDomDocument, QDomElement& p_rqdeElement) const
{
    QString qstrElementType;

   if(eDmQueryElementTypeAnd == m_eDmQueryElementType)
   {
      qstrElementType = "AND";
   }
   else if(eDmQueryElementTypeOr == m_eDmQueryElementType)
   {
      qstrElementType = "OR";
   }
   else if(eDmQueryElementTypeCompare == m_eDmQueryElementType)
   {
      qstrElementType = "COMPARE";
   }
   else
   {
      ERR( "Invalid ENUM Type." );
   }

   p_rqdeElement.setAttribute("ElementType", qstrElementType);


   if(eDmQueryElementTypeCompare == m_eDmQueryElementType)
   {
      QString qstrCompareType;

      switch(m_eDmCompareType)
      {
      case eDmQueryCompareTypeEqual:
         qstrCompareType = "==";
         break;
      case eDmQueryCompareTypeNotEqual:
         qstrCompareType = "!=";
         break;
      case eDmQueryCompareTypeSmaller:
         qstrCompareType = "<";
         break;
      case eDmQueryCompareTypeSmallerEqual:
         qstrCompareType = "<=";
         break;
      case eDmQueryCompareTypeLarger:
         qstrCompareType = ">";
         break;
      case eDmQueryCompareTypeLargerEqual:
         qstrCompareType = ">=";
         break;
      case eDmQueryCompareTypeLike:
         qstrCompareType = "LIKE";
         break;
      case eDmQueryCompareTypeIn:
         qstrCompareType = "IN";
         break;
      case eDmQueryCompareTypeNotIn:
         qstrCompareType = "NOT IN";
         break;
      default:
         qstrCompareType = "Invalid CompareType";
         ERR("No valid Comparetype");
         break;
      }

      p_rqdeElement.setAttribute("Compare Type", qstrCompareType);
      p_rqdeElement.setAttribute("ValueType", QString::number(m_eDmValueCompare));
      p_rqdeElement.setAttribute("Keyname", m_qstrCompareKeyname);
      p_rqdeElement.setAttribute("Value", m_qVariant.toString());
   }
   else
   {
      QList<CdmQueryElement*>::const_iterator qvlIt = m_lChildQuerys.begin();
      QList<CdmQueryElement*>::const_iterator qvlItEnd = m_lChildQuerys.end();

      for(; qvlIt != qvlItEnd; ++qvlIt)
      {
         CdmQueryElement* pCdmQueryElement = (*qvlIt);

         if(CHKPTR(pCdmQueryElement))
         {
            QDomElement qdeElement = p_rqdDomDocument.createElement("Child Query");
            p_rqdeElement.appendChild(qdeElement);
            pCdmQueryElement->XmlExport(p_rqdDomDocument, qdeElement);
         }
      }
   }
}

void CdmQueryElement::XmlImport(QDomElement& p_rqDomElement)
{
   QString qstrElementType = p_rqDomElement.attribute("ElementType","");

   if(qstrElementType == "COMPARE")
   {
      m_eDmQueryElementType = eDmQueryElementTypeCompare;
      QString qstrCompareType = p_rqDomElement.attribute("Compare Type","");

      if(qstrCompareType == "==")
      {
         m_eDmCompareType = eDmQueryCompareTypeEqual;
      }
      else if (qstrCompareType == "!=")
      {
         m_eDmCompareType = eDmQueryCompareTypeNotEqual;
      }
      else if (qstrCompareType == "<=")
      {
         m_eDmCompareType = eDmQueryCompareTypeSmallerEqual;
      }
      else if (qstrCompareType == ">=")
      {
         m_eDmCompareType = eDmQueryCompareTypeLargerEqual;
      }
      else if (qstrCompareType == ">")
      {
         m_eDmCompareType = eDmQueryCompareTypeLarger;
      }
      else if (qstrCompareType == "<")
      {
         m_eDmCompareType = eDmQueryCompareTypeSmaller;
      }
      else if (qstrCompareType == "LIKE")
      {
         m_eDmCompareType = eDmQueryCompareTypeLike;
      }
      else if (qstrCompareType == "IN")
      {
         m_eDmCompareType = eDmQueryCompareTypeIn;
      }
      else if (qstrCompareType == "NOT IN")
      {
         m_eDmCompareType = eDmQueryCompareTypeNotIn;
      }
      else
      {
         ERR("Invalid Comparetype: " + qstrCompareType);
      }

      m_eDmValueCompare = (EdmValueType)p_rqDomElement.attribute("Compare Type","").toInt();
      m_qstrCompareKeyname = p_rqDomElement.attribute("Keyname","");
      QString qstrValue = p_rqDomElement.attribute("Value","");
      m_qVariant = qstrValue;
   }
   else if(qstrElementType == "AND")
   {
      m_eDmQueryElementType = eDmQueryElementTypeAnd;
      XmlImportChilds(p_rqDomElement);
   }
   else if(qstrElementType == "OR")
   {
      m_eDmQueryElementType = eDmQueryElementTypeOr;
      XmlImportChilds(p_rqDomElement);
   }
   else
   {
      ERR("Wrong Elementtype: " + qstrElementType);
   }
}

void CdmQueryElement::XmlImportChilds(  QDomElement& p_rqDomElement )
{
   QDomNode qDomNode = p_rqDomElement.firstChild();
   while(!qDomNode.isNull())
   {
      QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

      if(!qDomElement.isNull() && qDomElement.tagName() == "Child Query")
      {
         CdmQueryElement* pCdmQueryElement = new CdmQueryElement(m_rpCdmQuery, qDomElement);
         m_lChildQuerys.append(pCdmQueryElement);
      }

      qDomNode = qDomNode.nextSibling();
   }
}
