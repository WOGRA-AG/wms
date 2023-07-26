// System and QT Includes
#include <qdom.h>
#include <QModelIndex>
#include <QList>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CdmLogging.h"

// own Includes
#include "CdmModelElement.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmQueryElement.h"
#include "CdmQueryResultElement.h"
#include "CdmQueryResultObject.h"
#include "CdmQuery.h"

static int HIGHCOMPLEXITY = 14;




CdmQuery::CdmQuery(QObject* parent)
: QObject(parent),
  m_qmResultElements(),
  m_qlResultElementsPos(),
  m_qvAddedSequence(),
  m_pRoot(nullptr),
  m_rpResultLastResultObject(nullptr),
  m_bIsObjectNeededInResult(true),
  m_pCdmQueryElement(nullptr),
  m_lContainerId(0),
  m_rpCdmClass(nullptr),
  m_lClassId(0),
  m_iResultStart(0),
  m_iMaxResults(0),
  m_iExecutionMode(-1),
  m_qlGroupBy(),
  m_qstrlOrderBy(),
  m_bOrderAsc(true),
  m_bExecuted(false),
  m_bValid(true),
  m_bCaseInsensitiveSearch(false)
{
    m_pRoot = new CdmQueryResultObject(-1, -1, nullptr, this);
}

CdmQuery::CdmQuery(CdmObjectContainer* p_pContainer, QObject* parent)
: CdmQuery(parent)
{
    SetContainer(p_pContainer);
}

CdmQuery::CdmQuery(CdmClass* p_pCdmClass, QObject* parent)
: CdmQuery(parent)
{
    SetClass(p_pCdmClass);
}

CdmQuery::CdmQuery(QVariantMap &p_rqvHash, QObject* parent)
: CdmQuery(parent)
{
   SetVariant(p_rqvHash);
}

CdmQuery::CdmQuery(const CdmQuery &p_rQuery, QObject* parent)
: CdmQuery(parent)
{
   QVariantMap qvHash = p_rQuery.GetVariant().toMap();
   SetVariant(qvHash);
}

CdmQuery::~CdmQuery()
{
    ClearAll();
    DELPTR(m_pRoot)
}

// support depends on DBAccess implementation
// the DB Access to read the execution mode
void CdmQuery::SetExecutionMode(int p_iMode)
{
    m_iExecutionMode = p_iMode;
}

int CdmQuery::GetExecutionMode()
{
    return m_iExecutionMode;
}

void CdmQuery::SetVariant(QVariantMap &p_rqvHash)
{
    ClearAll();

    m_lClassId = p_rqvHash.value("ClassId", 0).toInt();
    m_lContainerId = p_rqvHash.value("ObjectListId", 0).toInt();
    m_bExecuted = p_rqvHash.value("Executed", false).toBool();
    m_bOrderAsc = p_rqvHash.value("OrderAsc", true).toBool();
    m_qstrlOrderBy = p_rqvHash.value("OrderBy").toStringList();
    m_iResultStart = p_rqvHash.value("ResultStart", 0).toInt();
    m_iMaxResults = p_rqvHash.value("MaxResults", 0).toInt();
    m_bValid = p_rqvHash.value("Valid", true).toBool();
    m_qlGroupBy = p_rqvHash.value("GroupBy").toStringList();
    m_bIsObjectNeededInResult = p_rqvHash.value("IsObjectNeededInResult", true).toBool();
    m_bIsObjectNeededInResult = p_rqvHash.value("ForceEnhanced", false).toBool();

    if (m_lClassId > 0)
    {
        SetClassId(m_lClassId);
    }

    if (p_rqvHash.contains("RootElement"))
    {
        QVariantMap qvh = p_rqvHash.value("RootElement").toMap();
        m_pCdmQueryElement = new CdmQueryElement(this, qvh);
    }

    if (p_rqvHash.contains("ResultObject") && CHKPTR(m_pRoot))
    {
        QVariantMap qmResultObject = p_rqvHash.value("ResultObject").toMap();
        m_pRoot->SetVariant(qmResultObject);
    }

    if (p_rqvHash.contains("ResultElements"))
    {
        QVariantMap qvResultElements = p_rqvHash.value("ResultElements").toMap();

        QVariantMap::Iterator qvIt;
        for (qvIt = qvResultElements.begin(); qvIt != qvResultElements.end(); ++qvIt)
        {
            QString qstrKey = qvIt.key();
            QVariantMap qvHash = qvIt.value().toMap();
            CdmQueryResultElement* pCdmElement = new CdmQueryResultElement(qvHash, this);
            m_qmResultElements.insert(qstrKey, pCdmElement);
            m_qlResultElementsPos.append(pCdmElement);
        }
    }

    if (p_rqvHash.contains("Sequence"))
    {
        QList<QVariant> qlSequence = p_rqvHash.value("Sequence").toList();

        for (int iPos = 0; iPos < qlSequence.size(); ++iPos)
        {
            m_qvAddedSequence.append(qlSequence.at(iPos).toString());
        }
    }
}

QVariant CdmQuery::GetVariant() const
{
    QVariantMap qvHash;
    qvHash.insert("OrderBy", m_qstrlOrderBy);
    qvHash.insert("OrderAsc", m_bOrderAsc);
    qvHash.insert("Executed", m_bExecuted);
    qvHash.insert("ResultStart", m_iResultStart);
    qvHash.insert("MaxResults", m_iMaxResults);
    qvHash.insert("Valid", m_bValid);
    qvHash.insert("GroupBy", QStringList(m_qlGroupBy));
    qvHash.insert("IsObjectNeededInResult", m_bIsObjectNeededInResult);

    if (m_lContainerId > 0)
    {
        qvHash.insert("ObjectListId", static_cast<int>(m_lContainerId));
    }

    if (m_rpCdmClass)
    {
        qvHash.insert("ClassId", static_cast<int>(m_rpCdmClass->GetId()));
    }
    else if (m_lClassId > 0)
    {
        qvHash.insert("ClassId", static_cast<int>(m_lClassId));
    }

    if (m_pCdmQueryElement)
    {
        qvHash.insert("RootElement", m_pCdmQueryElement->GetVariant());
    }

    if (CHKPTR(m_pRoot))
    {
        qvHash.insert("ResultObject", m_pRoot->GetVariant());
    }

    QVariantMap qvhResultElements;
    QMap<QString, CdmQueryResultElement*>::ConstIterator qmIt;

    for (qmIt = m_qmResultElements.begin(); qmIt != m_qmResultElements.end(); ++qmIt)
    {
        QString qstrKeyname = qmIt.key();
        CdmQueryResultElement* pResultElement = qmIt.value();
        qvhResultElements.insert(qstrKeyname, pResultElement->GetVariant());
    }

    qvHash.insert("ResultElements", qvhResultElements);

    QList<QVariant> qlSequence;
    QVector<QString>::ConstIterator qvIt;

    for (qvIt = m_qvAddedSequence.begin(); qvIt != m_qvAddedSequence.end(); ++qvIt)
    {
        qlSequence.append(*qvIt);
    }

    qvHash.insert("Sequence", qlSequence);
    return qvHash;
}

void CdmQuery::SetSubQuery(bool p_bSubQuery)
{
    m_bIsObjectNeededInResult = !p_bSubQuery;
}

void CdmQuery::SetObjectNeededInResult(bool p_bObjectNeededInResult)
{
    m_bIsObjectNeededInResult = p_bObjectNeededInResult;
}

bool CdmQuery::IsObjectNeededInResult() const
{
    return m_bIsObjectNeededInResult && !ContainsGrouping();
}

int CdmQuery::EvaluateComplexity() const
{
    int iRet = 0;

    if (m_pCdmQueryElement)
    {
        iRet = m_pCdmQueryElement->GetComplexity();
    }
    else
    {
        iRet = 1; // select over all objectids in objectlist (very simple).
    }

    for (int i = 0; i < m_qvAddedSequence.size(); ++i)
    {
        iRet += 1 + m_qvAddedSequence.at(i).count('.') * 3;
    }

    return iRet;
}

int CdmQuery::Execute()
{
    int iRet = EC(eDmWqlError);

    if (GetColumnCount() == 0)
    {
        INFO("Query has no select fields. Selecting *.")
        AddAllMembers();
    }

    if (IsValid())
    {
        m_bExecuted = true;
        iRet = ExecuteDb();
    }

    return iRet;
}

void CdmQuery::Clear()
{
    ClearResults();
    DeleteQueryElement();
    m_iResultStart = 0;
    m_iMaxResults = 0;
    m_qlGroupBy.clear();
    m_qstrlOrderBy.clear();
    m_bOrderAsc = true;
}

void CdmQuery::ClearAll()
{
    ClearResults();
    DeleteResultElements();
    DeleteQueryElement();

    m_bIsObjectNeededInResult = true;
    m_lContainerId = 0;
    m_rpCdmClass = nullptr;
    m_lClassId = 0;
    m_iResultStart = 0;
    m_iMaxResults = 0;
    m_qlGroupBy.clear();
    m_qstrlOrderBy.clear();
    m_bOrderAsc = true;
    m_bExecuted = false;
    m_bValid = true;
}

void CdmQuery::AddAllMembers()
{
    const CdmClass* pCdmClass = GetClass();

    if (pCdmClass)
    {
        QVector<QString> qvSequence = pCdmClass->GetMemberSequence();
        int iMemberCount = 0;

        for (int iCounter = 0; iCounter < qvSequence.size(); ++iCounter)
        {
            if (iMemberCount >= MAX_MEMBER_COUNT)
            {
                INFO("Max member count for Query exceeded canceling procedure")
                break;
            }

            QString qstrMember = qvSequence.at(iCounter);
            const CdmMember* pCdmMember = pCdmClass->FindMember(qstrMember);

            if (pCdmMember)
            {
                if (pCdmMember->GetAccessMode() != eDmMemberAccessPrivate)
                {
                    const CdmClassGroup* pCdmGroup = pCdmMember->GetGroup();

                    if (pCdmGroup)
                    {
                        CdmRights &cRights = (const_cast<CdmClassGroup*>(pCdmGroup))->GetRights();
                        if (!cRights.HasCurrentUserReadAccess())
                        {
                            continue;
                        }
                    }

                    CdmRights &cRights = (const_cast<CdmMember*>(pCdmMember))->GetRights();

                    if (cRights.HasCurrentUserReadAccess())
                    {
                        if (pCdmMember->IsDisplayMember())
                        {
                            if (pCdmMember->GetValueType() == eDmValueObjectRef)
                            {
                                auto pClassRef = pCdmMember->GetClassReferencePtr();

                                if (pClassRef)
                                {
                                    auto qstrCaptionMember = pClassRef->GetCaptionMemberKeyname();

                                    if (!qstrCaptionMember.isEmpty())
                                    {
                                        QString qstrMember = pCdmMember->GetKeyname()+ "." + qstrCaptionMember;
                                        AddResultElement(qstrMember);
                                        ++iMemberCount;
                                    }
                                }
                            }
                            else
                            {
                                AddResultElement(pCdmMember->GetKeyname());
                                ++iMemberCount;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        ERR("Class or Objectcontainer for Query not found")
        m_bValid = false;
    }
}

void CdmQuery::AddResultElement(QString p_qstrKeyname)
{
    if (p_qstrKeyname.contains("("))
    {
        int iStartPos = p_qstrKeyname.indexOf("(");
        int iEndPos = p_qstrKeyname.indexOf(")");

        if (iStartPos > 0 && iEndPos > 0 && iEndPos > iStartPos)
        {
            QString qstrMode = p_qstrKeyname.mid(0, iStartPos);
            QString qstrValue = p_qstrKeyname.mid(iStartPos + 1, iEndPos - iStartPos - 1);
            EdmQueryResultElementMode eMode = ReadModeFromString(qstrMode);
            AddResultElement(qstrValue, eMode);
        }
    }
    else
    {
        AddResultElement(p_qstrKeyname, eDmQueryResultElementModeNone);
    }
}

void CdmQuery::AddResultElement(QString p_qstrKeyname, EdmQueryResultElementMode p_eDmMode)
{
    if (p_qstrKeyname == QStringLiteral("*"))
    {
        AddAllMembers();
    }
    else if (p_qstrKeyname.contains("&&"))
    {
        QStringList qstrlKeynames = p_qstrKeyname.split("&&");

        for (int iPos = 0; iPos < qstrlKeynames.size(); ++iPos)
        {
            QString qstrKeyname = qstrlKeynames.at(iPos);
            qstrKeyname = qstrKeyname.simplified();
            AddResultElement(qstrKeyname, p_eDmMode);
        }
    }
    else
    {
        const CdmClass* pClass = GetClass();

        if (pClass)
        {
            if (p_eDmMode == eDmQueryResultElementModeCount || pClass->FindMember(p_qstrKeyname))
            {
                CdmQueryResultElement* pCdmResultElement = new CdmQueryResultElement(p_qstrKeyname,
                                                                                     p_eDmMode,
                                                                                     this);
                m_qmResultElements.insert(p_qstrKeyname, pCdmResultElement);
                m_qlResultElementsPos.append(pCdmResultElement);
                m_qvAddedSequence.append(p_qstrKeyname);
            }
            else
            {
                ERR("Invalid member-keyname in query with keyname: " + p_qstrKeyname)
            }
        }
        else
        {
            ERR("Class or objectcontainer for query not found")
            m_bValid = false;
        }
    }
}

int CdmQuery::FindResultElement(QString p_qstrKeyname) const
{
    int iRet = -1;

    if (m_qvAddedSequence.contains(p_qstrKeyname))
    {
        for (int iPos = 0; iPos < m_qvAddedSequence.size(); ++iPos)
        {
            if (m_qvAddedSequence.at(iPos) == p_qstrKeyname)
            {
                iRet = iPos;
                break;
            }
        }
    }

    return iRet;
}

CdmQueryResultElement* CdmQuery::GetResultElement(int p_iPos) const
{
    CdmQueryResultElement* pRet = nullptr;

    if (0 <= p_iPos && p_iPos < m_qlResultElementsPos.size())
    {
        pRet = m_qlResultElementsPos[p_iPos];
    }

    return pRet;
}

CdmQueryResultElement* CdmQuery::GetResultElement(QString &p_qstrKeyname) const
{
    CdmQueryResultElement* pRet = nullptr;

    if (m_qmResultElements.contains(p_qstrKeyname))
    {
        pRet = m_qmResultElements[p_qstrKeyname];
    }

    return pRet;
}

QVector<QString> CdmQuery::GetResultElements() const
{
    return m_qvAddedSequence;
}

bool CdmQuery::IsSimpleCountQUery() const
{
    return (m_qvAddedSequence.count() == 1 && m_qvAddedSequence[0].toLower() == "count");
}

void CdmQuery::DeleteResultElements()
{
    QMap<QString, CdmQueryResultElement*>::Iterator qmIt;

    for (qmIt = m_qmResultElements.begin(); qmIt != m_qmResultElements.end(); ++qmIt)
    {
        DELPTR(qmIt.value())
    }

    m_qmResultElements.clear();
    m_qlResultElementsPos.clear();
    m_qvAddedSequence.clear();
}

void CdmQuery::SetQueryElement(CdmQueryElement* p_pCdmQueryElement)
{
    m_pCdmQueryElement = p_pCdmQueryElement;
}

void CdmQuery::ResetQueryElement(CdmQueryElement* p_pCdmQueryElement)
{
    DeleteQueryElement();
    SetQueryElement(p_pCdmQueryElement);
}

CdmQueryElement* CdmQuery::GetQueryElement() const
{
    return m_pCdmQueryElement;
}

void CdmQuery::DeleteQueryElement()
{
    DELPTR(m_pCdmQueryElement)
}

void CdmQuery::AddGroupByElement(QString p_qstrElement)
{
    bool bCheck = true;
    const CdmClass* pClass = GetClass();

    if (pClass)
    {
        bCheck = (pClass->FindMember(p_qstrElement) != nullptr);
    }

    if (bCheck)
    {
        m_qlGroupBy.append(p_qstrElement);
    }
}

QList<QString> CdmQuery::GetGroupByElements() const
{
    return m_qlGroupBy;
}

void CdmQuery::SetResultStart(int p_iStart)
{
    m_iResultStart = p_iStart;
}

int CdmQuery::GetResultStart() const
{
    return m_iResultStart;
}

void CdmQuery::SetLimitResultCount(int p_iMaxResults)
{
    m_iMaxResults = p_iMaxResults;
}

int CdmQuery::GetLimitResultCount() const
{
    return m_iMaxResults;
}

void CdmQuery::SetSorting(int p_iColumn, Qt::SortOrder p_eSortOrder)
{
    if (HasResultElements())
    {
        if (0 <= p_iColumn && p_iColumn < GetColumnCount())
        {
            QString qstrOrder = GetKeynameAt(p_iColumn);

            if (p_eSortOrder == Qt::AscendingOrder)
            {
                AddOrderBy(qstrOrder, true);
            }
            else
            {
                AddOrderBy(qstrOrder, false);
            }
        }
    }
}

void CdmQuery::ResetOrderBy()
{
     m_qstrlOrderBy.clear();
}

void CdmQuery::SetOrderBy(QStringList &p_qstrOrderBy, bool p_bAsc)
{
    ResetOrderBy();
    m_qstrlOrderBy = p_qstrOrderBy;
    m_bOrderAsc = p_bAsc;
}

void CdmQuery::AddOrderBy(QString p_qstrOrderBy, bool p_bAsc)
{
    ResetOrderBy();
    m_qstrlOrderBy.append(p_qstrOrderBy);
    m_bOrderAsc = p_bAsc;
}

QStringList CdmQuery::GetOrderBy() const
{
    return m_qstrlOrderBy;
}

bool CdmQuery::GetOrderMode() const
{
    return m_bOrderAsc;
}

void CdmQuery::SetContainer(QString p_qstrKeyname)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmObjectContainer* pContainer = nullptr;
        pContainer = pCdmManager->GetObjectContainerEmpty(p_qstrKeyname);

        if (pContainer)
        {
            SetContainer(pContainer);
        }
        else
        {
            m_bValid = false;
            ERR("Unknow Container for Query " +  p_qstrKeyname)
        }
    }
}

void CdmQuery::SetContainer(CdmObjectContainer* p_pContainer)
{
    if (p_pContainer)
    {
        m_lContainerId = p_pContainer->GetId();
        m_rpCdmClass = p_pContainer->GetClass();
        m_lClassId = p_pContainer->GetClassId();
    }
    else
    {
        m_lContainerId = 0;
        m_rpCdmClass = nullptr;
        m_lClassId = 0;
    }
}

CdmObjectContainer* CdmQuery::GetContainer() const
{
    CdmObjectContainer* pContainer = nullptr;

    if (m_lContainerId != 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (pCdmManager)
        {
            CdmContainerManager* pCdmOLManager = pCdmManager->GetContainerManager();

            if (pCdmOLManager)
            {
                pContainer = pCdmOLManager->FindEmptyContainerById(m_lContainerId);
            }
        }
    }

    return pContainer;
}

void CdmQuery::SetContainerId(qint64 p_lId)
{
    m_lContainerId = p_lId;

    SetContainer(GetContainer());
}

qint64 CdmQuery::GetContainerId() const
{
    return m_lContainerId;
}

void CdmQuery::SetClass(CdmClass* p_pClass)
{
    m_rpCdmClass = p_pClass;
    m_lClassId = 0;

    if (CHKPTR(p_pClass))
    {
        m_lClassId = p_pClass->GetId();
    }
}

const CdmClass* CdmQuery::GetClass() const
{
    return m_rpCdmClass;
}

void CdmQuery::SetClassId(qint64 p_lId)
{
    m_rpCdmClass = nullptr;
    m_lClassId = p_lId;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pCdmClassManager))
        {
            m_rpCdmClass = pCdmClassManager->FindClassById(m_lClassId);
        }
    }
}

qint64 CdmQuery::GetClassId() const
{
    return m_lClassId;
}

bool CdmQuery::ContainsGrouping() const
{
    bool bRet = false;
    QMap<QString, CdmQueryResultElement*>::ConstIterator qmIt;

    for (qmIt = m_qmResultElements.begin(); qmIt != m_qmResultElements.end(); ++qmIt)
    {
        CdmQueryResultElement* pCdmElement = qmIt.value();

        if (CHKPTR(pCdmElement))
        {
            if (pCdmElement->GetMode() != eDmQueryResultElementModeNone)
            {
                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

bool CdmQuery::IsHighComplexQuery() const
{
    bool bRet = false;

    if (EvaluateComplexity() >= HIGHCOMPLEXITY)
    {
        bRet = true;
    }

    return bRet;
}

bool CdmQuery::IsValid() const
{
    bool bRet = m_bValid;

    if (bRet)
    {
        CdmObjectContainer* pContainer = GetContainer();

        if (!pContainer)
        {
            const CdmClass* pClass = GetClass();

            if (!pClass)
            {
                bRet = false;
                INFO("Query has neither a Container nor a Class.")
            }
        }
    }
    else
    {
        ERR("Query has an invalid flag.")
    }

    return bRet;
}

int CdmQuery::GetColumnCount() const
{
    int iColumns = 0;

    if (HasResultElements())
    {
        iColumns = m_qvAddedSequence.size();
    }
    else
    {
        iColumns = 1;
    }

    return iColumns;
}

bool CdmQuery::IsObjectListTree() const
{
    bool bRet = false;

    CdmObjectContainer* pContainer = GetContainer();

    if (pContainer)
    {
        bRet = pContainer->IsTree();
    }

    return bRet;
}

bool CdmQuery::IsEnhancedQuery() const
{
    return HasResultElements();
}

bool CdmQuery::HasResultElements() const
{
    bool bRet = false;

    if (m_qmResultElements.size() > 0)
    {
        bRet = true;
    }

    return bRet;
}

CdmQueryResultObject* CdmQuery::GetRootElement() const
{
    return m_pRoot;
}

CdmQueryResultObject* CdmQuery::GetChildAtRow(int p_iRow) const
{
    CdmQueryResultObject* pResult = nullptr;

    if (CHKPTR(m_pRoot))
    {
        pResult = m_pRoot->GetChildAtRow(p_iRow);
    }

    return pResult;
}

void CdmQuery::SetResults(QList<QVariant> &p_rqlResults)
{
    for (int iPos = 0; iPos < p_rqlResults.size(); ++iPos)
    {
        QVariantMap qvResult = p_rqlResults[iPos].toMap();
       qint64 lObjectId = qvResult["ObjectId"].toInt();
       qint64 lContainerId = qvResult["ObjectListId"].toInt();
        AddResult(lObjectId, lContainerId);
    }
}

void CdmQuery::ClearResults()
{
    if (m_pRoot)
    {
        m_pRoot->ClearResults();
    }
    m_rpResultLastResultObject = nullptr;

    QMap<QString, CdmQueryResultElement*>::Iterator qmIt;

    for (qmIt = m_qmResultElements.begin(); qmIt != m_qmResultElements.end(); ++qmIt)
    {
        CdmQueryResultElement* pResult = qmIt.value();

        if (pResult)
        {
            pResult->ClearResults();
        }
    }
}

QString CdmQuery::GetKeynameAt(int p_iSection) const
{
    QString qstrName;

    if (HasResultElements())
    {
        if (0 <= p_iSection && p_iSection < GetColumnCount())
        {
            qstrName = m_qvAddedSequence.at(p_iSection);
        }
    }
    else
    {
        qstrName = OBJECT_DATA;
    }

    return qstrName;
}

QVariant CdmQuery::GetResultAt(int p_iColumn, int p_iRow) const
{
    QVariant qvResult;

    if (CHKPTR(m_pRoot))
    {
        qvResult = m_pRoot->GetResult(p_iRow, p_iColumn);
    }

    return qvResult;
}

QString CdmQuery::GetResultAsDisplayStringAt(int p_iColumn, int p_iRow) const
{
    QString qvResult;

    if (CHKPTR(m_pRoot))
    {
        qvResult = GetDisplayString(GetKeynameAt(p_iColumn), m_pRoot->GetResult(p_iRow, p_iColumn));
    }

    return qvResult;
}

QVariant CdmQuery::GetResultAt(QString p_qstrKeyname, int p_iPos) const
{
    QVariant qVariant(QVariant::Int);

    if (m_qvAddedSequence.contains(p_qstrKeyname) || m_qmResultElements.contains(p_qstrKeyname))
    {
        if (CHKPTR(m_pRoot))
        {
            int iColumn = m_qvAddedSequence.indexOf(p_qstrKeyname);
            qVariant = m_pRoot->GetResult(p_iPos, iColumn);
        }
    }
    else if (p_qstrKeyname.startsWith("object.")) // a direct value of the object is called
    {
        p_qstrKeyname = p_qstrKeyname.mid(QString("object.").size());
        CdmQueryResultObject* pResult = GetChildAtRow(p_iPos);

        if (pResult)
        {
            CdmObject* pObject = pResult->GetObject();

            if (pObject)
            {
                qVariant = pObject->GetVariant(p_qstrKeyname);
            }
        }
    }

    return qVariant;
}

QVariant CdmQuery::GetResultAt(const QModelIndex &p_Index) const
{
    QVariant qVariant;

    try
    {
        if (p_Index.isValid())
        {
            if (IsObjectListTree())
            {
                CdmQueryResultObject* pResult = static_cast<CdmQueryResultObject*>(p_Index.internalPointer());

                if (pResult)
                {
                    qVariant = pResult->GetResultAt(p_Index.column());
                }
            }
            else
            {
                qVariant = GetResultAt(p_Index.column(), p_Index.row());
            }
        }
    }
    catch(...)
    {
        ERR("Something went wrong here")
        qVariant = QVariant();
    }

    return qVariant;
}

QString CdmQuery::GetResultAsStringAt(int p_iRow) const
{
    QString qstrRet;

    CdmQueryResultObject* pResult = GetChildAtRow(p_iRow);

    if (pResult)
    {
        if (HasResultElements())
        {
            qstrRet = pResult->GetResultAsString();
        }
        else
        {
            qstrRet = "Object: " + QString::number(pResult->GetObjectId()) + ", Container: " + QString::number(pResult->GetContainerId());
        }
    }

    return qstrRet;
}

qint64 CdmQuery::GetObjectIdAt(int p_iPos) const
{
   qint64 lObjectId = 0;

    BODY_TRY
    if ((0 <= p_iPos) && (p_iPos < GetResultCount()))
    {
        CdmQueryResultObject* pResult = GetChildAtRow(p_iPos);

        if (pResult)
        {
            lObjectId = pResult->GetObjectId();
        }
    }
    else
    {
        IndexOutOfRangeError(p_iPos, GetResultCount());
    }
    BODY_CATCH

    return lObjectId;
}

CdmObject* CdmQuery::GetFirstResultObject() const
{
    CdmObject* pObject = nullptr;

    BODY_TRY
    if (GetResultCount() > 0)
    {
        pObject = GetObjectAt(0);
    }
    BODY_CATCH

    return pObject;
}

CdmObject* CdmQuery::GetObjectAt(int p_iPos) const
{
    return GetResultObjectAt(p_iPos);
}

CdmObject* CdmQuery::GetResultObjectAt(int p_iPos) const
{
    CdmObject* pObject = nullptr;

    BODY_TRY
    if ((0 <= p_iPos) && (p_iPos < GetResultCount()))
    {
        CdmQueryResultObject* pResult = GetChildAtRow(p_iPos);

        if (pResult)
        {
            pObject = pResult->GetObject();
        }
    }
    else
    {
        IndexOutOfRangeError(p_iPos, GetResultCount());
    }
    BODY_CATCH

    return pObject;
}

qint64 CdmQuery::GetObjectListIdAt(int p_iPos) const
{
   qint64 lContainerId = 0;

    BODY_TRY
    if ((0 <= p_iPos) && (p_iPos < GetResultCount()))
    {
        CdmQueryResultObject* pResult = GetChildAtRow(p_iPos);

        if (pResult)
        {
            lContainerId = pResult->GetContainerId();
        }
    }
    else
    {
        IndexOutOfRangeError(p_iPos, GetResultCount());
    }
    BODY_CATCH

    return lContainerId;
}

qint64 CdmQuery::GetContainerIdAt(int p_iRow) const
{
    return GetObjectListIdAt(p_iRow);
}

int CdmQuery::GetRowPosOfObjectInResultTree(qint64 p_lObjectId) const
{
    int iRet = -1;

    BODY_TRY
    if (CHKPTR(m_pRoot))
    {
        CdmQueryResultObject* pResult = m_pRoot->GetChild(p_lObjectId);

        if (pResult)
        {
            iRet = pResult->GetRow();
        }
    }
    BODY_CATCH

    return iRet;
}

bool CdmQuery::IsObjectInResultTree(qint64 p_lObjectId) const
{
    return ContainsResultObject(p_lObjectId);
}

bool CdmQuery::ContainsResultObject(qint64 p_lObjectId) const
{
    bool bRet = false;

    if (CHKPTR(m_pRoot) && m_pRoot->GetChild(p_lObjectId))
    {
        bRet = true;
    }

    return bRet;
}

bool CdmQuery::ContainsResultObject(CdmObject* p_pObject) const
{
    bool bRet = false;

    if (CHKPTR(p_pObject))
    {
        bRet = ContainsResultObject(p_pObject->GetId());
    }

    return bRet;
}

QVariant CdmQuery::GetResultElementsAsVariant() const
{
    QVariantList qvlResults;

    for (int iPos = 0; iPos < GetResultCount(); ++iPos)
    {
        CdmQueryResultObject* pResult = GetChildAtRow(iPos);

        if (pResult)
        {
            qvlResults.append(pResult->GetResultAsVariant());
        }
    }

    return qvlResults;
}

QVariant CdmQuery::GetResultsAsVariant() const
{
   QVariantList qvlResults;

   for (int i = 0; i < GetResultCount(); ++i)
   {
       CdmQueryResultObject* pResult = GetChildAtRow(i);

       if (pResult)
       {
           qvlResults.append(
                       CdmLocatedElement::CreateUri(WMS_OBJECT,
                                                    QString::number(pResult->GetObjectId()),
                                                    QString::number(pResult->GetContainerId())));
       }
   }

   return qvlResults;
}

QString CdmQuery::GetResultAsString() const
{
    QString qstrResult;

    for (int iCounter = 0; iCounter < GetResultCount(); ++iCounter)
    {
        qstrResult += GetResultAsStringAt(iCounter) + "\n";
    }

    return qstrResult;
}

const QList<qint64> CdmQuery::GetResultList() const
{
   QList<qint64> qllResult;

   for (int iPos = 0; iPos < GetResultCount(); ++iPos)
   {
      qint64 lObjectId = GetObjectIdAt(iPos);
       qllResult.append(lObjectId);
   }

   return qllResult;
}

QVariant CdmQuery::GetFirstResultList(QString p_qstrKeyname) const
{
    QVector<QVariant> qllResults;
    GetResultElementList(p_qstrKeyname, qllResults);
    QVariant qVariant;

    if (qllResults.begin() != qllResults.end())
    {
        qVariant = *qllResults.begin();
    }

    return qVariant;
}

void CdmQuery::GetResultElementList(QString p_qstrKeyname, QVector<QVariant> &p_rqllResults) const
{
    if (m_qmResultElements.contains(p_qstrKeyname))
    {
        CdmQueryResultElement* pCdmResultElement = m_qmResultElements.value(p_qstrKeyname);
        p_rqllResults = pCdmResultElement->GetResults();
    }
}

int CdmQuery::CountQueryiedChildren(qint64 p_lParentId) const
{
    int iRet = 0;

    if (CHKPTR(m_pRoot))
    {
        CdmQueryResultObject* pResult = m_pRoot->GetChild(p_lParentId);

        if (pResult)
        {
            iRet = pResult->GetRowCount();
        }
    }

    return iRet;
}

QList<CdmObject*> CdmQuery::GetChildList(qint64 lParentId) const
{
    QList<CdmObject*> qlObjects;

    if (IsObjectListTree() && CHKPTR(m_pRoot))
    {
        CdmQueryResultObject* pResult = m_pRoot->GetChild(lParentId);

        if (pResult)
        {
            qlObjects = pResult->GetChildList();
        }
    }

    return qlObjects;
}

qint64 CdmQuery::GetParentObjectId(const QModelIndex &p_rqIndex) const
{
   qint64 lRet = -1;

    if (p_rqIndex.isValid())
    {
        // this is the parent
        CdmQueryResultObject* pResult = static_cast<CdmQueryResultObject*>(p_rqIndex.internalPointer());

        if (pResult)
        {
            lRet = pResult->GetObjectParentId();
        }
    }

    return lRet;
}

CdmObject* CdmQuery::GetChildAt(qint64 p_lParentId, int p_iRow)
{
    CdmObject* pCdmOject = nullptr;

    if (CHKPTR(m_pRoot))
    {
        CdmQueryResultObject* pResult = m_pRoot->GetChildAtRow(p_iRow, p_lParentId);

        if (pResult)
        {
            pCdmOject = pResult->GetObject();
        }
    }

    return pCdmOject;
}

qint64 CdmQuery::GetPositionObjectId(qint64 p_lParentId, int p_iPosition)
{
   qint64 lRet = -1;
    CdmQueryResultObject* pParent = nullptr;

    if (p_lParentId <= 0)
    {
        pParent = m_pRoot;
    }
    else if (CHKPTR(m_pRoot))
    {
        pParent = m_pRoot->GetChild(p_lParentId);
    }

    if (CHKPTR(pParent))
    {
        CdmQueryResultObject* pObject = pParent->GetChildAtRow(p_iPosition);

        if (CHKPTR(pObject))
        {
            lRet = pObject->GetObjectId();
        }
    }

    return lRet;
}

int CdmQuery::GetResultCount() const
{
    int iRet = 0;

    if (CHKPTR(m_pRoot))
    {
        iRet = m_pRoot->GetRowCount();
    }

    return iRet;
}

int CdmQuery::ExecuteDb()
{
    int iRet = CdmLogging::eDmUnknownQueryError;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
       IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

       if (CHKPTR(pIdmDataAccess))
       {
           if (m_rpCdmClass || GetContainer())
           {
               iRet = pIdmDataAccess->ExecuteQuery(this);
           }
           else
           {
               ERR("No container and no class defined as query source. Query could not be executed!")
           }
       }
       else
       {
          iRet = EC(eDmInvalidPtr);
       }
    }
    else
    {
        iRet = EC(eDmInvalidPtr);
    }

    return iRet;
}

bool CdmQuery::IsExecuted() const
{
    return m_bExecuted;
}

EdmQueryResultElementMode CdmQuery::ReadModeFromString(QString p_qstrMode)
{
    EdmQueryResultElementMode eMode = eDmQueryResultElementModeNone;
    p_qstrMode = p_qstrMode.trimmed();

    if (p_qstrMode.toUpper() == "SUM")
    {
        eMode = eDmQueryResultElementModeSum;
    }
    else if (p_qstrMode.toUpper() == "AVG")
    {
        eMode = eDmQueryResultElementModeAvg;
    }
    else if (p_qstrMode.toUpper() == "MIN")
    {
        eMode = eDmQueryResultElementModeMin;
    }
    else if (p_qstrMode.toUpper() == "MAX")
    {
        eMode = eDmQueryResultElementModeMax;
    }

    return eMode;
}

void CdmQuery::AddResult(qint64 p_lObjectId,qint64 p_lContainerId)
{
    CdmQueryResultObject * pResult = CdmQueryResultObject::FindOrCreateResultObject(p_lObjectId, p_lContainerId, m_pRoot, this);

    if (!pResult)
    {
        ERR("Couldn't Add Result ObjectId:" + QString::number(p_lObjectId))
    }
}

void CdmQuery::AddResultToColumn(int p_iColumn, QVariant p_qvValue,qint64 p_lObjectId,qint64 p_lContainerId)
{
    CdmQueryResultObject* pResult = nullptr;

    if (m_rpResultLastResultObject != nullptr &&
        m_rpResultLastResultObject->GetObjectId() == p_lObjectId &&
        m_rpResultLastResultObject->GetContainerId() == p_lContainerId)
    {
        pResult = m_rpResultLastResultObject;
    }
    else
    {
        pResult = CdmQueryResultObject::FindOrCreateResultObject(p_lObjectId, p_lContainerId, m_pRoot, this);
        m_rpResultLastResultObject = pResult;
    }

    if (pResult && p_qvValue.isValid())
    {
        pResult->AddResult(p_iColumn, p_qvValue);
        QString qstrKeyname = GetKeynameAt(p_iColumn);

        if (m_qmResultElements.contains(qstrKeyname))
        {
            CdmQueryResultElement* pResultElement = m_qmResultElements[qstrKeyname];
            pResultElement->AddResult(p_qvValue);
        }
    }
    else
    {
        ERR("Couldn't Add Result (" + p_qvValue.toString() + ")"
            " to ObjectId " + QString::number(p_lObjectId) +
            " in Column" + QString::number(p_iColumn))
    }
}

void CdmQuery::AddResultToColumnInRow(int p_iColumn, int p_iRow, QVariant& p_rqvValue)
{
    BODY_TRY
    CdmQueryResultObject* pResult = nullptr;

    if ((m_rpResultLastResultObject != nullptr) && (m_rpResultLastResultObject->GetRow() == p_iRow))
    {
        pResult = m_rpResultLastResultObject;
    }
    else
    {
        GetChildAtRow(p_iRow);

        if (!pResult)
        {
            pResult = CdmQueryResultObject::CreateResultObject(this, m_pRoot, -1, -1, -1);
        }
        m_rpResultLastResultObject = pResult;
    }

    if (pResult && p_rqvValue.isValid())
    {
        pResult->AddResult(p_iColumn, p_rqvValue);
        QString qstrKeyname = GetKeynameAt(p_iColumn);

        if (m_qmResultElements.contains(qstrKeyname))
        {
            CdmQueryResultElement* pResultElement = m_qmResultElements[qstrKeyname];
            pResultElement->AddResult(p_rqvValue);
        }
    }
    else
    {
        ERR("Couldn't Add Result (" + p_rqvValue.toString() + ")"
            " to Row " + QString::number(p_iRow))
    }
    BODY_CATCH
}

void CdmQuery::SetResultInternal(int p_iColumn, QVariant p_qvValue,qint64 p_lObjectId,qint64 p_lContainerId)
{
    AddResultToColumn(p_iColumn, p_qvValue, p_lObjectId, p_lContainerId);
}

bool CdmQuery::IsWql(QString qstrWql)
{
    QString qstrString = qstrWql.simplified().toLower();
    bool bSelect = qstrString.contains(QStringLiteral("select"));
    bool bWhitespace = qstrString.contains(' ');
    bool bFrom = qstrString.contains(QStringLiteral("from"));

    return (bSelect && bWhitespace && bFrom);
}

void CdmQuery::IndexOutOfRangeError(int p_iPos, int p_iResultCount) const
{
    BODY_TRY
    ERR("Index out of range. Index: " + QString::number(p_iPos) + ", Range: " + QString::number(p_iResultCount))
    BODY_CATCH
}

QString CdmQuery::GetDisplayString(QString p_qstrMember, QVariant p_qvValue) const
{
    QString qstrRet;
    const CdmMember* pCdmMember = FindMemberByKeyname(p_qstrMember);

    if (pCdmMember)
    {
        qstrRet = pCdmMember->ConvertValueToDisplayString(p_qvValue);
    }
    else
    {
        qstrRet = p_qvValue.toString();
    }

    return qstrRet;
}

QVariant CdmQuery::GetColumnAlignment(QString p_qstrKeyname) const
{
    QVariant qVariant;
    const CdmMember* pCdmMember = FindMemberByKeyname(p_qstrKeyname);

    if (pCdmMember)
    {
        qVariant = pCdmMember->GetMemberAlignment();
    }
    else
    {
        qVariant = int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return qVariant;
}

QVariant CdmQuery::GetColumnTooltip(QString p_qstrKeyname) const
{
    QVariant qVariant;
    const CdmMember* pCdmMember = FindMemberByKeyname(p_qstrKeyname);

    if (pCdmMember)
    {
        qVariant = pCdmMember->GetComment();
    }

    return qVariant;
}

QString CdmQuery::GetDatabaseCommand() const
{
    return m_qstrDatabaseCommand;
}

void CdmQuery::AddDatabaseCommand(QString p_qstrCommand)
{
    if (!m_qstrDatabaseCommand.isEmpty())
    {
        m_qstrDatabaseCommand += "\n\n";
    }

    m_qstrDatabaseCommand += p_qstrCommand;
}

bool CdmQuery::IsAggregationQuery() const
{
    if (HasResultElements())
    {
        QMap<QString, CdmQueryResultElement*>::ConstIterator qmIt;

        for (qmIt = m_qmResultElements.begin(); qmIt != m_qmResultElements.end(); ++qmIt)
        {
            CdmQueryResultElement* pResultElement = qmIt.value();

            if (CHKPTR(pResultElement) && pResultElement->GetMode() != eDmQueryResultElementModeNone)
            {
                return true;
            }
        }
    }

    return false;
}

const CdmMember* CdmQuery::FindMemberByKeyname(QString p_qstrKeyname) const
{
    const CdmMember* pCdmMember = nullptr;

    CdmObjectContainer* pContainer = GetContainer();
    const CdmClass* pCdmClass = nullptr;

    if (pContainer)
    {
        pCdmClass = pContainer->GetClass();
    }
    else
    {
        pCdmClass = GetClass();
    }

    if (CHKPTR(pCdmClass))
    {
        pCdmMember = pCdmClass->FindMember(p_qstrKeyname);
    }

    return pCdmMember;
}

bool CdmQuery::IsQueryCaseInsensitive()
{
    return m_bCaseInsensitiveSearch;
}

void CdmQuery::SetQueryCaseInsensitive(bool bInsensitive)
{
    m_bCaseInsensitiveSearch = bInsensitive;
}
