// System and QT Includes
#include <QVector>
#include <QByteArray>
#include <QApplication>

// Own Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryResultObject.h"
#include "CdmQueryBuilder.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmEnhancedQueryProxy.h"
#include "CdmQueryModel.h"

// defines
#define EXECUTIONTIMEOUT 500

CdmQueryModel::CdmQueryModel()
    : QAbstractItemModel(nullptr),
      m_iRowToInsert(0),
      m_iRowToRemove(0),
      m_pIdmDisplayHandler(nullptr),
      m_pCdmQuery(nullptr)
{
    m_pCdmQuery = new CdmQueryEnhanced(this);
}

CdmQueryModel::~CdmQueryModel()
{
    DELPTR(m_pCdmQuery)
}

int CdmQueryModel::rowCount() const
{
    int iRet = 0;

    if (m_pCdmQuery)
    {
        iRet = m_pCdmQuery->GetResultCount();
    }

    return iRet;
}

int CdmQueryModel::rowCount(const QModelIndex & p_rParent) const
{
    int iRet = 0;

    if (!p_rParent.isValid())
    {
        iRet = rowCount();
    }
    else if (p_rParent.column() > 0)
    {
        iRet = 0;
    }
    else
    {
        if (m_pCdmQuery)
        {
            CdmObjectContainer* pCdmObjectContainer = m_pCdmQuery->GetContainer();

            if (pCdmObjectContainer && pCdmObjectContainer->IsTree())
            {
                CdmQueryResultObject* pParent = static_cast<CdmQueryResultObject*>(p_rParent.internalPointer());

                if (pParent)
                {
                    iRet = pParent->GetRowCount();
                }
            }
        }
    }

    return iRet;
}

int CdmQueryModel::columnCount() const
{
    int iRet = 0;

    if (m_pCdmQuery)
    {
        iRet = m_pCdmQuery->GetColumnCount();
    }

    return iRet;
}

int CdmQueryModel::columnCount(const QModelIndex &) const
{
    return columnCount();
}

void CdmQueryModel::AddColumn(QString p_qstrKeyname)
{
    if (m_pCdmQuery)
    {
        m_pCdmQuery->AddResultElement(p_qstrKeyname);
    }
}

void CdmQueryModel::ClearColumns()
{
    if (m_pCdmQuery)
    {
        m_pCdmQuery->DeleteResultElements();
    }
}

void CdmQueryModel::Clear()
{
    if (m_pCdmQuery)
    {
        DELPTR(m_pCdmQuery);
    }
}

QVariant CdmQueryModel::data(const QModelIndex & p_qmIndex, int p_iRole) const
{
    QVariant qVariant;
    int iColumn = p_qmIndex.column();

    if (m_pCdmQuery)
    {
        if (m_qmViewProxy.contains(iColumn))
        {
            qVariant = m_pCdmQuery->GetResultAt(p_qmIndex);
            IwmsViewProxy* pProxy = m_qmViewProxy[iColumn];

            if (CHKPTR(pProxy))
            {
                qVariant = pProxy->data(p_iRole, qVariant);
            }
        }
        else
        {
            if (p_iRole > Qt::UserRole)
            {
                int columnIAbsdx = p_iRole - Qt::UserRole - 1;

                if (columnIAbsdx >= columnCount()) // the displaystring is requested
                {
                    qVariant = m_pCdmQuery->GetResultAsStringAt(p_qmIndex.row());
                }
                else
                {
                    QModelIndex modelIndex = this->index(p_qmIndex.row(), columnIAbsdx);
                    qVariant = data(modelIndex, Qt::DisplayRole);
                    qVariant = m_pCdmQuery->GetDisplayString(m_pCdmQuery->GetKeynameAt(columnIAbsdx), qVariant);
                }
            }
            else if (p_iRole == Qt::DisplayRole)
            {
                if(m_pIdmDisplayHandler)
                {
                    qVariant = m_pIdmDisplayHandler->data(p_qmIndex, p_iRole);
                }
                else
                {
                    qVariant = m_pCdmQuery->GetResultAt(p_qmIndex);
                    qVariant = m_pCdmQuery->GetDisplayString(m_pCdmQuery->GetKeynameAt(iColumn), qVariant);
                }
            }
            else if (p_iRole == Qt::TextAlignmentRole)
            {
                qVariant = m_pCdmQuery->GetColumnAlignment(m_pCdmQuery->GetKeynameAt(iColumn));
            }
            else if (p_iRole == Qt::ToolTipRole)
            {
                qVariant = m_pCdmQuery->GetColumnTooltip(m_pCdmQuery->GetKeynameAt(iColumn));
            }
            else if (p_iRole == Qt::StatusTipRole)
            {
                qVariant = m_pCdmQuery->GetColumnTooltip(m_pCdmQuery->GetKeynameAt(iColumn));
            }
            else if (p_iRole == Qt::FontRole)
            {
                if(m_pIdmDisplayHandler)
                {
                    qVariant = m_pIdmDisplayHandler->data(p_qmIndex, p_iRole);
                }
            }
            else if (p_iRole == Qt::BackgroundRole)
            {
                if(m_pIdmDisplayHandler)
                {
                    qVariant = m_pIdmDisplayHandler->data(p_qmIndex, p_iRole);
                }
            }
            else if (p_iRole == Qt::ForegroundRole)
            {
                if(m_pIdmDisplayHandler)
                {
                    qVariant = m_pIdmDisplayHandler->data(p_qmIndex, p_iRole);
                }
            }
        }
    }

    return qVariant;
}

QVariant CdmQueryModel::data(int p_iRow, int p_iColumn, int p_iRole) const
{
    Q_UNUSED(p_iRole)
    QVariant qVariant;

    BODY_TRY
    if (CHKPTR(m_pCdmQuery))
    {
        qVariant = m_pCdmQuery->GetResultAt(p_iColumn, p_iRow);
    }
    BODY_CATCH

    return qVariant;
}

QVariant CdmQueryModel::data(int p_iRow, QString p_qstrColumnName, int p_iRole) const
{
    Q_UNUSED(p_iRole)
    QVariant qVariant;

    BODY_TRY
    if (CHKPTR(m_pCdmQuery))
    {
        CdmQueryResultElement* pResultElement = m_pCdmQuery->GetResultElement(p_qstrColumnName);

        if (CHKPTR(pResultElement))
        {
            qVariant = pResultElement->GetResultAt(p_iRow);
        }
    }
    BODY_CATCH

    return qVariant;
}

CdmObject* CdmQueryModel::GetObject(QAbstractItemView* p_pqItemView)
{
    CdmObject* pCdmObject = nullptr;

    BODY_TRY
    if (CHKPTR(p_pqItemView))
    {
        QModelIndexList qmiList = getSelection(p_pqItemView, p_pqItemView->rootIndex());

        if (qmiList.size() > 0)
        {
            pCdmObject = GetObject(qmiList[0]);
        }
    }
    BODY_CATCH

    return pCdmObject;
}

QList<CdmObject*> CdmQueryModel::GetObjects(QAbstractItemView* p_pqItemView)
{
    QList<CdmObject*> qllObjects;

    BODY_TRY
    if (CHKPTR(p_pqItemView))
    {
        QModelIndexList qmiList = getSelection(p_pqItemView, p_pqItemView->rootIndex());

        if (qmiList.size() > 0)
        {
            for (int iPos = 0; iPos < qmiList.count(); iPos++)
            {
                CdmObject *pObject = GetObject(qmiList[iPos]);

                if (CHKPTR(pObject))
                {
                    qllObjects.append(pObject);
                }
            }
        }
    }
    BODY_CATCH

    return qllObjects;
}

QModelIndexList CdmQueryModel::getSelection(QAbstractItemView* p_pqItemView, QModelIndex p_Index)
{
    QModelIndexList list;

    BODY_TRY
    if (CHKPTR(p_pqItemView))
    {
        QItemSelectionModel* pQItemSelectionModel = p_pqItemView->selectionModel();

        if (CHKPTR(pQItemSelectionModel))
        {
            for (int row = 0; row < rowCount(p_Index); ++row)
            {
                QModelIndex idx = index(row, 0, p_Index);

                if (rowCount(idx) > 0)
                {
                    list += getSelection(p_pqItemView, idx);
                }

                if (pQItemSelectionModel->isSelected(idx))
                {
                    list.push_back(idx);
                }
            }
        }
    }
    BODY_CATCH

    return list;
}

CdmObject* CdmQueryModel::GetObject(const QModelIndex & p_qmIndex)
{
    CdmObject* pCdmObject = nullptr;

    BODY_TRY
   qint64 lObjectId = 0;

    if (m_pCdmQuery && m_pCdmQuery->IsObjectListTree())
    {
        if (p_qmIndex.isValid())
        {
            CdmQueryResultObject* pResult = static_cast<CdmQueryResultObject*>(p_qmIndex.internalPointer());

            if (CHKPTR(pResult))
            {
                lObjectId = pResult->GetObjectId();

                CdmObjectContainer* pContainer = m_pCdmQuery->GetContainer();

                if (CHKPTR(pContainer))
                {
                    pCdmObject = pContainer->FindObjectById(lObjectId);
                }
            }
        }
    }
    else
    {
        int iRow = p_qmIndex.row();

        if (iRow >= 0)
        {
            pCdmObject = GetObject(iRow);
        }
        else
        {
            WARNING("Invalid row index using index 0 if possible")

            if (m_pCdmQuery && m_pCdmQuery->GetResultCount() > 0) // statement avoids error message when creating the first object in a container
            {
                // to keep legacy code (maybe) working ?!
                pCdmObject = GetObject(0);
            }
        }
    }
    BODY_CATCH

    return pCdmObject;
}

CdmObject* CdmQueryModel::GetObject(const int p_iRow)
{
    if (m_pCdmQuery)
    {
        return m_pCdmQuery->GetObjectAt(p_iRow);
    }
    else
    {
        return nullptr;
    }
}

QVariant CdmQueryModel::headerData(int p_iSection, Qt::Orientation p_iOrientation, int p_iRole) const
{
    QVariant qVariant;

    if (m_pCdmQuery != nullptr)
    {
        if (p_iRole == Qt::DisplayRole)
        {
            if (p_iOrientation == Qt::Horizontal)
            {
                QString qstrKeyname = m_pCdmQuery->GetKeynameAt(p_iSection);

                if (m_qmDisplayHeader.contains(qstrKeyname))
                {
                    qVariant = m_qmDisplayHeader[qstrKeyname];
                }
                else
                {
                    const CdmClass* pCdmClass = m_pCdmQuery->GetClass();

                    if (!pCdmClass)
                    {
                        CdmObjectContainer* pContainer = m_pCdmQuery->GetContainer();

                        if (pContainer)
                        {
                            pCdmClass = pContainer->GetClass();
                        }
                    }

                    if (pCdmClass)
                    {
                        const CdmMember* pCdmMember = pCdmClass->FindMember(qstrKeyname);

                        if (pCdmMember)
                        {
                            qVariant = pCdmMember->GetCaption();
                        }
                        else
                        {
                            qVariant = qstrKeyname;
                        }
                    }
                    else
                    {
                        qVariant = qstrKeyname;
                    }
                }
            }
            else
            {
                qVariant = QString::number(p_iSection);
            }
        }
    }
    return qVariant;
}

void CdmQueryModel::AddDisplayHeader(QString p_qstrKeyname, QString p_qstrDisplayString)
{
    m_qmDisplayHeader.insert(p_qstrKeyname, p_qstrDisplayString);
}

void CdmQueryModel::Execute(QString p_qstrQuery)
{
    CdmQuery* pCdmQuery = CdmQueryBuilder::BuildQuery(p_qstrQuery);

    if (pCdmQuery != nullptr)
    {
        pCdmQuery->setParent(this);
        Execute(pCdmQuery);
    }
    else
    {
        //ERR("No enhanced query. Can not be executed in query model.");
    }
}

void CdmQueryModel::Execute(QString p_qstrQuery, int p_iLimit)
{
    CdmQuery* pCdmQuery = CdmQueryBuilder::BuildQuery(p_qstrQuery);

    if (pCdmQuery != nullptr)
    {
        pCdmQuery->setParent(this);
        if (p_iLimit > 0)
        {
            pCdmQuery->SetLimitResultCount(p_iLimit);
        }

        Execute(pCdmQuery);
    }
    else
    {
        //ERR("No enhanced query. Can not be executed in query model.");
    }
}

void CdmQueryModel::Execute(CdmQuery* p_pCdmQuery)
{
    if (CHKPTR(p_pCdmQuery) && (p_pCdmQuery != m_pCdmQuery))
    {
        if (m_pCdmQuery)
        {
            DELPTR(m_pCdmQuery)
        }

        m_pCdmQuery = p_pCdmQuery;
        SetContainer(m_pCdmQuery->GetContainer());
    }

    Execute();
}

void CdmQueryModel::Execute()
{
    if (CHKPTR(m_pCdmQuery) && (m_pCdmQuery->GetClass() || m_pCdmQuery->GetContainer()))
    {
        beginResetModel();
        m_pCdmQuery->ClearResults();

//        if (m_pCdmQuery->GetLimitResultCount() == 0)
//        {
//            m_pCdmQuery->SetLimitResultCount(5000);
//        }

        if (m_pCdmQuery->GetContainer())
        {
            SetContainer(m_pCdmQuery->GetContainer());
        }

        m_pCdmQuery->Execute();
        endResetModel();
    }

    disconnect(&m_qtTimer, SIGNAL(timeout()),
            this, SLOT(ExecuteQuery()));

    m_qtTimer.stop();
    connect(&m_qtTimer, SIGNAL(timeout()),
            this, SLOT(ExecuteQuery()));

    emit UpdateSignal();
}

void CdmQueryModel::UpdateSlot()
{
    BODY_TRY
    if (!m_qtTimer.isActive())
    {
        m_qtTimer.setSingleShot(true);
        m_qtTimer.start(EXECUTIONTIMEOUT);
    }
    BODY_CATCH
}

void CdmQueryModel::ExecuteQuery()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    Execute();

    QModelIndex qmiUpperLeft = index(0,0);
    QModelIndex qmiLowerRight = index(columnCount() - 1, rowCount() -1);

    emit dataChanged(qmiUpperLeft, qmiLowerRight);
    QApplication::restoreOverrideCursor();
}

QHash<int, QByteArray> CdmQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    if (CHKPTR(m_pCdmQuery))
    {
        QVector<QString> qvResultElements = m_pCdmQuery->GetResultElements();

        for (int iPos = 0; iPos < qvResultElements.count(); ++iPos)
        {
            roles[Qt::UserRole + 1 + iPos] = qvResultElements[iPos].toUtf8();
        }

        roles[Qt::UserRole + 1 + qvResultElements.count()] = QString("DisplayString").toUtf8();
    }

    return roles;
}

void CdmQueryModel::sort(int p_iColumn, Qt::SortOrder p_eSortOrder)
{
    if (m_pCdmQuery)
    {
        QString qstrKeyname;
        auto pResultElement = m_pCdmQuery->GetResultElement(p_iColumn);
        bool bAsc = (p_eSortOrder == Qt::AscendingOrder);

        if (pResultElement)
        {
            qstrKeyname = pResultElement->GetKeyname();
        }

        if (!qstrKeyname.isEmpty() && (!m_pCdmQuery->GetOrderBy().contains(qstrKeyname) || bAsc != m_pCdmQuery->GetOrderMode()))
        {
            m_pCdmQuery->SetSorting(p_iColumn, p_eSortOrder);
            UpdateSlot();
        }
    }
}

CdmQuery* CdmQueryModel::GetQuery()
{
    return m_pCdmQuery;
}

void CdmQueryModel::SetProxy(CdmEnhancedQueryProxy* p_pProxy)
{
    if (p_pProxy && m_pCdmQuery)
    {
        p_pProxy->CreateQuery(m_pCdmQuery->GetContainer());
        Execute(p_pProxy->GetQuery());
    }
}

void CdmQueryModel::SetContainer(CdmObjectContainer* p_pList)
{
    if (p_pList != nullptr)
    {
        CdmContainerAdaptor::SetContainer(p_pList);

        if (CHKPTR(m_pCdmQuery))
        {
            m_pCdmQuery->SetContainer(p_pList);
        }
    }
}

void CdmQueryModel::SetContainer(QString p_qstrObjectListKeyname)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager =
                pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());

        if(CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = nullptr;
            pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrObjectListKeyname);
            SetContainer(pContainer);
        }
    }
}

CdmObjectContainer* CdmQueryModel::GetContainer()
{
    CdmObjectContainer* pList = nullptr;

    if (CHKPTR(m_pCdmQuery))
    {
        pList = m_pCdmQuery->GetContainer();
    }

    return pList;
}

void CdmQueryModel::AddViewProxy(int p_iColumn, IwmsViewProxy* p_pProxy)
{
    BODY_TRY
    if (CHKPTR(p_pProxy))
    {
        if (m_qmViewProxy.contains(p_iColumn))
        {
            if (m_qmViewProxy[p_iColumn] != p_pProxy)
            {
                IwmsViewProxy* pProxy = m_qmViewProxy[p_iColumn];

                if (pProxy)
                {
                    DELPTR(pProxy)
                }

                m_qmViewProxy.remove(p_iColumn);
            }
        }

        m_qmViewProxy.insert(p_iColumn, p_pProxy);
    }
    BODY_CATCH
}

const CdmClass* CdmQueryModel::GetClass()
{
    return GetContainer()->GetClass();
}

QModelIndex CdmQueryModel::parent(const QModelIndex & index) const
{
    QModelIndex qRet;

    if (index.isValid())
    {
        // this is the parent
        CdmQueryResultObject* pResult = static_cast<CdmQueryResultObject*>(index.internalPointer());

        if (pResult && (m_pCdmQuery == nullptr || pResult->GetParent() != m_pCdmQuery->GetRootElement()))
        {
            int iRow = pResult->GetRow();

            if (iRow >= 0)
            {
                qRet = createIndex(iRow, 0, pResult->GetParent());
            }
        }
    }

    return qRet;
}

bool CdmQueryModel::hasChildren(const QModelIndex & parent) const
{
    bool bRet = false;

    if (rowCount(parent) > 0)
    {
        bRet = true;
    }

    return bRet;
}

void CdmQueryModel::ObjectCommitedEvent(qint64)
{
    UpdateSlot();
}


QModelIndex CdmQueryModel::index(int p_iRow, int p_iColumn, const QModelIndex & parent) const
{
    QModelIndex qmIndex;

    if (hasIndex(p_iRow, p_iColumn, parent) && m_pCdmQuery)
    {
        CdmQueryResultObject* pParent = nullptr;

        if (!parent.isValid())
        {
            pParent = m_pCdmQuery->GetRootElement();
        }
        else
        {
            pParent = static_cast<CdmQueryResultObject*>(parent.internalPointer());
        }

        if (pParent)
        {
            // add the object as internal pointer
            CdmQueryResultObject* pObject = pParent->GetChildAtRow(p_iRow);
            qmIndex = createIndex(p_iRow, p_iColumn, pObject);
        }
        else if (m_pCdmQuery->HasResultElements() == false)
        {
            qmIndex = createIndex(p_iRow, p_iColumn);
        }
    }

    return qmIndex;
}

void CdmQueryModel::AddAllMembers()
{
    GetQuery()->AddAllMembers();
}

void CdmQueryModel::SetInitialDisplayHandler(IdmHandleDisplayData *pDisplayHandler)
{
    m_pIdmDisplayHandler = pDisplayHandler;
}

QString CdmQueryModel::GetDisplayString(QString p_qstrMember, QVariant p_qvValue) const
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

const CdmMember* CdmQueryModel::FindMemberByKeyname(QString p_qstrKeyname) const
{
    const CdmMember* pCdmMember = nullptr;

    if (m_pCdmQuery)
    {
        CdmObjectContainer* pContainer = m_pCdmQuery->GetContainer();
        const CdmClass* pCdmClass = nullptr;

        if (pContainer)
        {
            pCdmClass = pContainer->GetClass();
        }
        else
        {
            pCdmClass = m_pCdmQuery->GetClass();
        }

        if (CHKPTR(pCdmClass))
        {
            pCdmMember = pCdmClass->FindMember(p_qstrKeyname);
        }
    }

    return pCdmMember;
}

