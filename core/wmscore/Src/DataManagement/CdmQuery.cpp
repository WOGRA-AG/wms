/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qdom.h>
#include <QModelIndex>
#include <QLinkedList>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsTimeMeassurement.h"
#include "CdmScheme.h"
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


/** +-=---------------------------------------------------------Mi 10. Nov 18:43:42 2010----------*
 * @method  CdmQuery::CdmQuery                               // public                            *
 * @return                                                   //                                   *
 * @comment The Default constructor.                                                              *
 *----------------last changed: --------------------------------Mi 10. Nov 18:43:42 2010----------*/
CdmQuery::CdmQuery(QObject* parent)
: QObject(parent),
  m_qmResultElements(),
  m_qlResultElementsPos(),
  m_qvAddedSequence(),
  m_bForceEnhanced(false),
  m_pRoot(nullptr),
  m_rpResultLastResultObject(nullptr),
  m_bIsObjectNeededInResult(true),
  m_pCdmQueryElement(nullptr),
  m_bLocal(false),
  m_qstrScheme(),
  m_lContainerId(0),
  m_rpCdmClass(nullptr),
  m_lClassId(0),
  m_iResultStart(0),
  m_iMaxResults(0),
  m_qlGroupBy(),
  m_qstrlOrderBy(),
  m_bOrderAsc(true),
  m_bExecuted(false),
  m_bValid(true)
{
    m_pRoot = new CdmQueryResultObject(-1, -1, nullptr, this);
}

/** +-=---------------------------------------------------------Sa 20. Aug 10:51:08 2005----------*
 * @method  CdmQuery::CdmQuery                               // public                            *
 * @return                                                   //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment The constructor of the query. this query searches for object specified in the         *
 *          query element.                                                                        *
 *----------------last changed: --------------------------------Sa 20. Aug 10:51:08 2005----------*/
CdmQuery::CdmQuery(CdmObjectContainer* p_pContainer, QObject* parent)
: CdmQuery(parent)
{
    SetContainer(p_pContainer);
}

/** +-=---------------------------------------------------------So 11. Nov 10:40:53 2007----------*
 * @method  CdmQuery::CdmQuery                               // public                            *
 * @return                                                   //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment The Default constructor.                                                              *
 *----------------last changed: Wolfgang Graßhof----------------So 11. Nov 10:40:53 2007----------*/
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

/** +-=---------------------------------------------------------Sa 20. Aug 12:48:29 2005----------*
 * @method  CdmQuery::~CdmQuery                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmQuery                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:48:29 2005----------*/
CdmQuery::~CdmQuery(  )
{
    ClearAll();
    DELPTR(m_pRoot)
}

void CdmQuery::SetVariant(QVariantMap &p_rqvHash)
{
    ClearAll();

    m_lClassId = p_rqvHash.value("ClassId", 0).toInt();
    m_lContainerId = p_rqvHash.value("ObjectListId", 0).toInt();
    m_bExecuted = p_rqvHash.value("Executed", false).toBool();
    m_bLocal = p_rqvHash.value("Local", false).toBool();
    m_bOrderAsc = p_rqvHash.value("OrderAsc", true).toBool();
    m_qstrScheme = p_rqvHash.value("Database").toString();
    m_qstrlOrderBy = p_rqvHash.value("OrderBy").toStringList();
    m_iResultStart = p_rqvHash.value("ResultStart", 0).toInt();
    m_iMaxResults = p_rqvHash.value("MaxResults", 0).toInt();
    m_bValid = p_rqvHash.value("Valid", true).toBool();
    m_qlGroupBy = p_rqvHash.value("GroupBy").toStringList();
    m_bIsObjectNeededInResult = p_rqvHash.value("IsObjectNeededInResult", true).toBool();
    m_bIsObjectNeededInResult = p_rqvHash.value("ForceEnhanced", false).toBool();

    if (m_lClassId > 0)
    {
        if (m_qstrScheme.isEmpty())
        {
            SetClassId(m_lClassId);
        }
        else
        {
            SetClassId(m_lClassId, m_qstrScheme);
        }
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
    qvHash.insert("Database", m_qstrScheme);
    qvHash.insert("Local", m_bLocal);
    qvHash.insert("Executed", m_bExecuted);
    qvHash.insert("ResultStart", m_iResultStart);
    qvHash.insert("MaxResults", m_iMaxResults);
    qvHash.insert("Valid", m_bValid);
    qvHash.insert("GroupBy", QStringList(m_qlGroupBy));
    qvHash.insert("IsObjectNeededInResult", m_bIsObjectNeededInResult);
    qvHash.insert("ForceEnhanced", m_bForceEnhanced);

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

void CdmQuery::SetLocalSearch()
{
    m_bLocal = true;
}

void CdmQuery::SetSchemeSearch()
{
    m_bLocal = false;
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

/** +-=---------------------------------------------------------Di 20. Nov 10:55:12 2012----------*
 * @method  CdmQuery::Execute                                // public, slots                     *
 * @return  int                                              //                                   *
 * @comment This method call executes the query and fills the result list with correct            *
 *          results.                                                                              *
 *----------------last changed: --------------------------------Di 20. Nov 10:55:12 2012----------*/
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

/** +-=---------------------------------------------------------Di 20. Nov 10:55:00 2012----------*
 * @method  CdmQuery::Clear                                  // public, slots                     *
 * @return  void                                             //                                   *
 * @comment Clears the child elements of the query.                                               *
 *----------------last changed: --------------------------------Di 20. Nov 10:55:00 2012----------*/
void CdmQuery::ClearAll()
{
    ClearResults();
    DeleteResultElements();
    DeleteQueryElement();

    m_bIsObjectNeededInResult = true;
    m_bLocal = false;
    m_qstrScheme.clear();
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
                            AddResultElement(pCdmMember->GetKeyname());
                            ++iMemberCount;
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
        //if (!m_qmResultElements.contains(p_qstrKeyname))
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

void CdmQuery::SetScheme(QString p_qstrDatabase)
{
    m_qstrScheme = p_qstrDatabase;
}

QString CdmQuery::GetScheme() const
{
    return m_qstrScheme;
}

/** +-=---------------------------------------------------------Di 20. Nov 10:59:04 2012----------*
 * @method  CdmQuery::SetQueryElement                        // public                            *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElement              // change of ownership!!!!!!!!       *
 * @comment This method sets a query element in the query. The query element will be deleted      *
 *----------------last changed: --------------------------------Di 20. Nov 10:59:04 2012----------*/
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
    if (IsEnhancedQuery())
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
    else
    {
        if (p_eSortOrder == Qt::AscendingOrder)
        {
            m_bOrderAsc = true;
        }
        else
        {
            m_bOrderAsc = false;
        }
    }
}

void CdmQuery::SetOrderBy(QStringList &p_qstrOrderBy, bool p_bAsc)
{
    m_qstrlOrderBy = p_qstrOrderBy;
    m_bOrderAsc = p_bAsc;
}

void CdmQuery::AddOrderBy(QString p_qstrOrderBy, bool p_bAsc)
{
    m_qstrlOrderBy.clear();
    m_qstrlOrderBy.append(p_qstrOrderBy);
    m_bOrderAsc = p_bAsc;
}

QStringList CdmQuery::GetOrderBy() const
{
    return m_qstrlOrderBy;
}

/** +-=---------------------------------------------------------So 10. Feb 10:05:04 2013----------*
 * @method  CdmQuery::GetOrderMode                           // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment returns the order mode true = Asc, false = Desc.                                      *
 *----------------last changed: --------------------------------So 10. Feb 10:05:04 2013----------*/
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

        CdmScheme* pCdmDatabase = p_pContainer->GetScheme();

        if (CHKPTR(pCdmDatabase))
        {
            SetScheme(pCdmDatabase->GetSchemeName());
        }
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

/** +-=---------------------------------------------------------Di 20. Nov 10:58:36 2012----------*
 * @method  CdmQuery::SetContainerId                         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrDatabase                           //                                   *
 * @comment This method sets the ObjectList ID if no pointer of the objectlist is                 *
 *          availlable.                                                                           *
 *----------------last changed: --------------------------------Di 20. Nov 10:58:36 2012----------*/
void CdmQuery::SetContainerId(long p_lId, QString p_qstrDatabase)
{
    SetContainerId(p_lId);

    if (GetContainer())
    {
        SetScheme(p_qstrDatabase);
    }
}

void CdmQuery::SetContainerId(long p_lId)
{
    m_lContainerId = p_lId;

    SetContainer(GetContainer());
}

long CdmQuery::GetContainerId() const
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

/** +-=---------------------------------------------------------Di 20. Nov 10:56:19 2012----------*
 * @method  CdmQuery::SetClassId                             // public, slots                     *
 * @return  void                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrDatabase                           //                                   *
 * @comment This method sets the ObjectList ID if no pointer of the objectlist is                 *
 *          availlable.                                                                           *
 *----------------last changed: --------------------------------Di 20. Nov 10:56:19 2012----------*/
void CdmQuery::SetClassId(long p_lId, QString p_qstrDatabase)
{
    m_rpCdmClass = nullptr;
    m_lClassId = p_lId;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_qstrDatabase);

        if (CHKPTR(pCdmClassManager))
        {
            m_rpCdmClass = pCdmClassManager->FindClassById(m_lClassId);
        }
    }
}

void CdmQuery::SetClassId(long p_lId)
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

long CdmQuery::GetClassId() const
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

    if (IsEnhancedQuery())
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
    return (m_bForceEnhanced || HasResultElements());
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
        long lObjectId = qvResult["ObjectId"].toInt();
        long lContainerId = qvResult["ObjectListId"].toInt();
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

    if (IsEnhancedQuery())
    {
        if (0 <= p_iSection && p_iSection < GetColumnCount())
        {
            qstrName = m_qvAddedSequence.at(p_iSection);
        }
    }
    else
    {
        qstrName = "Object Data";
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
        if (IsEnhancedQuery())
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

long CdmQuery::GetObjectIdAt(int p_iPos) const
{
    long lObjectId = 0;

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

long CdmQuery::GetObjectListIdAt(int p_iPos) const
{
    long lContainerId = 0;

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

long CdmQuery::GetContainerIdAt(int p_iRow) const
{
    return GetObjectListIdAt(p_iRow);
}

int CdmQuery::GetRowPosOfObjectInResultTree(long p_lObjectId) const
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

bool CdmQuery::IsObjectInResultTree(long p_lObjectId) const
{
    return ContainsResultObject(p_lObjectId);
}

bool CdmQuery::ContainsResultObject(long p_lObjectId) const
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

const QLinkedList<long> CdmQuery::GetResultList() const
{
   QLinkedList<long> qllResult;

   for (int iPos = 0; iPos < GetResultCount(); ++iPos)
   {
       long lObjectId = GetObjectIdAt(iPos);
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

int CdmQuery::CountQueryiedChildren(long p_lParentId) const
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

QList<CdmObject*> CdmQuery::GetChildList(long lParentId) const
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

long CdmQuery::GetParentObjectId(const QModelIndex &p_rqIndex) const
{
    long lRet = -1;

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

CdmObject* CdmQuery::GetChildAt(long p_lParentId, int p_iRow)
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

long CdmQuery::GetPositionObjectId(long p_lParentId, int p_iPosition)
{
    long lRet = -1;
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

void CdmQuery::AddResult(long p_lObjectId, long p_lContainerId)
{
    CdmQueryResultObject * pResult = CdmQueryResultObject::FindOrCreateResultObject(p_lObjectId, p_lContainerId, m_pRoot, this);

    if (!pResult)
    {
        ERR("Couldn't Add Result ObjectId:" + QString::number(p_lObjectId))
    }
}

void CdmQuery::AddResultToColumn(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId)
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
        //pResult = CdmQueryResultObject::FindOrCreateResultObject(p_lObjectId, p_lContainerId, m_pRoot, this);
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

void CdmQuery::SetResultInternal(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId)
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

/** +-=---------------------------------------------------------Sa 20. Aug 10:52:10 2005----------*
 * @method  CdmQuery::XmlImport                              // public, static                    *
 * @return  CdmQuery*                                        //                                   *
 * @param   QString p_qstrXmlSource                          //                                   *
 * @comment This static method reads an xml string and creates from it the xml query object.      *
 *----------------last changed: --------------------------------Sa 20. Aug 10:52:10 2005----------*/
CdmQuery* CdmQuery::XmlImport(QString p_qstrXmlSource)
{
    CdmQuery* pCdmQuery = nullptr;

    BODY_TRY
    QDomDocument qDomDocument;
    QString qstrError;
    int iLine = 0;
    int iColumn = 0;

    qDomDocument.setContent(p_qstrXmlSource, false, &qstrError, &iLine, &iColumn);

    if (qstrError.isEmpty())
    {
       QDomElement qdeRoot = qDomDocument.documentElement();

       if (qdeRoot.tagName() == QStringLiteral("WMS_QUERY_ML"))
       {
           pCdmQuery = new CdmQuery();

           // Database
           pCdmQuery->SetScheme(qdeRoot.attribute(QStringLiteral("Database")));

           // ObjectListId
           pCdmQuery->SetContainerId(qdeRoot.attribute(QStringLiteral("ObjectListId")).toInt(), pCdmQuery->GetScheme());

           // Local
           bool bLocal = CdmModelElement::ChangeStringToBool(qdeRoot.attribute(QStringLiteral("Local")));

           if (bLocal)
           {
               pCdmQuery->SetLocalSearch();
           }

           // now it is time to read the query elements
           QDomNode qDomNode = qdeRoot.firstChild();

           if (!qDomNode.isNull())
           {
               QDomElement qDomElement = qDomNode.toElement(); // try to convert the node to an element.

               if (!qDomElement.isNull() && (qDomElement.tagName() == QStringLiteral("Query Elements")))
               {
                   CdmQueryElement* pCdmQueryElement = new CdmQueryElement(pCdmQuery, qDomElement);
                   pCdmQuery->SetQueryElement(pCdmQueryElement);
               }
           }
           else
           {
               ERR("Query Elements are missing, how to use this query???")
           }
       }
       else
       {
           ERR("Wrong Routeelement tagname!!!")
       }
    }
    else
    {
        ERR("Error happened while try to read XML String.\n"
            "Error Message: " + qstrError + "\n" +
            "Line Number: " + QString::number(iLine) + "\n" +
            "Column: " + QString::number(iColumn) + "\n")
    }
    BODY_CATCH

   return pCdmQuery;
}

void CdmQuery::IndexOutOfRangeError(int p_iPos, int p_iResultCount) const
{
    BODY_TRY
    ERR("Index out of range. Index: " + QString::number(p_iPos) + ", Range: " + QString::number(p_iResultCount))
    BODY_CATCH
}
