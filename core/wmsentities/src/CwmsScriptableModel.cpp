#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include "CdmMessageManager.h"
#include "CdmLogging.h"

#include "CsaQuery.h"
#include "CwmsScriptableModel.h"

CwmsScriptableModel::CwmsScriptableModel()
{
    setObjectName("Model");
}

CwmsScriptableModel::~CwmsScriptableModel()
{
}

void CwmsScriptableModel::copyFromQuery(QObject* p_pQuery)
{
    CsaQuery* pQuery = dynamic_cast<CsaQuery*>(p_pQuery);

    if (CHKPTR(pQuery))
    {
        m_qmData.clear();
        int iRowCount    = pQuery->getResultCount();
        int iColumnCount = pQuery->getColumnCount();

        copyHeaderData(pQuery, m_qstrlColumnHeaders, iColumnCount);

        for (int iRowCounter = 0; iRowCounter < iRowCount; ++iRowCounter)
        {
            for(int iColumnCounter = 0; iColumnCounter < iColumnCount; ++iColumnCounter)
            {
                QVariant qValue = pQuery->getResultAt(iColumnCounter, iRowCounter);
                addValue(iRowCounter, iColumnCounter, Qt::DisplayRole, qValue);
            }
        }
    }
}

void CwmsScriptableModel::appendFromQuery(QObject* p_pQuery)
{
    CsaQuery* pQuery = dynamic_cast<CsaQuery*>(p_pQuery);

    if (CHKPTR(pQuery))
    {
        int iOriginalRowCount = rowCount();
        int iRowCount    = pQuery->getResultCount() + iOriginalRowCount;
        int iColumnCount = pQuery->getColumnCount();
        setRowCount(iRowCount);

        if (iColumnCount == columnCount())
        {
            int iCurrentRow = 0;
            for (int iRowCounter = rowCount(); iRowCounter < iRowCount; ++iRowCounter)
            {
                for(int iColumnCounter = 0; iColumnCounter < iColumnCount; ++iColumnCounter)
                {
                    QVariant qValue = pQuery->getResultAt(iColumnCounter, iCurrentRow);
                    addValue(iRowCounter, iColumnCounter, Qt::DisplayRole, qValue);
                }

                ++iCurrentRow;
            }
        }
        else
        {
            CdmMessageManager::critical("Fehler im Modell", "Die Spaltenanzahl entspricht nicht dem Originalmodell");
        }
    }
}

void CwmsScriptableModel::copyHeaderData(CsaQuery* pQuery, QMap<int,QString>& qmHeader, int count)
{
    setHeaderCount(qmHeader, count);
    for(int iCounter = 0; iCounter < count; ++iCounter)
    {
        QString qstrHeader = pQuery->getKeynameAt(iCounter);
        insertHeader(qmHeader, iCounter, qstrHeader);
    }
}

void CwmsScriptableModel::copyHeaderData(QAbstractItemModel &p_rModel, Qt::Orientation orientation, QMap<int,QString>& qmHeader, int count)
{
    setHeaderCount(qmHeader, count);
    for(int iCounter = 0; iCounter < count; ++iCounter)
    {
        QString qstrHeader = p_rModel.headerData(iCounter, orientation).toString();
        insertHeader(qmHeader, iCounter, qstrHeader);
    }
}

void CwmsScriptableModel::copyFromItemModel(QAbstractItemModel &p_rModel, int p_iDisplayType)
{
    m_qmData.clear();
    int iRowCount    = p_rModel.rowCount();
    int iColumnCount = p_rModel.columnCount();

    copyHeaderData(p_rModel, Qt::Vertical, m_qstrlRowHeaders, iRowCount);
    copyHeaderData(p_rModel, Qt::Horizontal, m_qstrlColumnHeaders, iColumnCount);

    for (int iRowCounter = 0; iRowCounter < iRowCount; ++iRowCounter)
    {
        for(int iColumnCounter = 0; iColumnCounter < iColumnCount; ++iColumnCounter)
        {
            QModelIndex qIndex = p_rModel.index(iRowCounter, iColumnCounter);
            QVariant qValue = p_rModel.data(qIndex, p_iDisplayType);
            addValue(iRowCounter, iColumnCounter, p_iDisplayType, qValue);
        }
    }
}

void CwmsScriptableModel::appendFromItemModel(QAbstractItemModel &p_rModel, int p_iDisplayType)
{
    int iOriginalRowCount = rowCount();
    int iRowCount    = p_rModel.rowCount() + iOriginalRowCount;
    int iColumnCount = p_rModel.columnCount();

    setRowCount(iRowCount);

    if (iColumnCount == columnCount())
    {
        int iCurrentRow = 0;
        for (int iRowCounter = rowCount(); iRowCounter < iRowCount; ++iRowCounter)
        {
            for(int iColumnCounter = 0; iColumnCounter < iColumnCount; ++iColumnCounter)
            {
                QModelIndex qIndex = p_rModel.index(iCurrentRow, iColumnCounter);
                QVariant qValue = p_rModel.data(qIndex, p_iDisplayType);
                addValue(iRowCounter, iColumnCounter, p_iDisplayType, qValue);
            }

            ++iCurrentRow;
        }
    }
    else
    {
        CdmMessageManager::critical("Fehler im Modell", "Die Spaltenanzahl entspricht nicht dem Originalmodell");
    }
}

QVariant CwmsScriptableModel::getValue(int p_iRow, int p_iColumn, int p_iDisplayType)
{
    QVariant qValue;

    if (checkRowColumn(p_iRow, p_iColumn))
    {
        QMap<int, QMap<int, QVariant>> qmRow;
        QMap<int, QVariant> qmData;

        if (m_qmData.contains(p_iRow))
        {
            qmRow = m_qmData[p_iRow];

            if (qmRow.contains(p_iColumn))
            {
                qmData = qmRow[p_iColumn];

                if (qmData.contains(p_iDisplayType))
                {
                    qValue = qmData[p_iDisplayType];
                }
            }
        }
    }

    return qValue;
}

void CwmsScriptableModel::getDisplayTypeMap(int p_iRow, int p_iColumn, QMap<int,QVariant>& qmDisplayTypeMap)
{

    if (checkRowColumn(p_iRow, p_iColumn))
    {
        QMap<int, QMap<int, QVariant>> qmRow;
        QMap<int, QVariant> qmData;

        if (m_qmData.contains(p_iRow))
        {
            qmRow = m_qmData[p_iRow];

            if (qmRow.contains(p_iColumn))
            {
                qmDisplayTypeMap = qmRow[p_iColumn];
            }
        }
    }
}

void CwmsScriptableModel::addValue(int p_iRow, int p_iColumn, int p_iDisplayType, QVariant p_rValue)
{
    if (checkRowColumn(p_iRow, p_iColumn))
    {
        bool bOk = true;
        double dValue = p_rValue.toDouble(&bOk);
        if (bOk)
        {
            QLocale loc;
            p_rValue = loc.toString(dValue, 'f', 2);
        }

        QMap<int, QMap<int, QVariant>> qmRow;
        QMap<int, QVariant> qmData;

        if (m_qmData.contains(p_iRow))
        {
            qmRow = m_qmData[p_iRow];

            if (qmRow.contains(p_iColumn))
            {
                qmData = qmRow[p_iColumn];
                qmData.insert(p_iDisplayType, p_rValue);
                qmRow.insert(p_iColumn, qmData);
                m_qmData.insert(p_iRow, qmRow);
            }
            else
            {
                qmData.insert(p_iDisplayType, p_rValue);
                qmRow.insert(p_iColumn, qmData);
                m_qmData.insert(p_iRow, qmRow);
            }
        }
        else
        {
            qmData.insert(p_iDisplayType, p_rValue);
            qmRow.insert(p_iColumn, qmData);
            m_qmData.insert(p_iRow, qmRow);
        }
    }
}

bool CwmsScriptableModel::checkRowColumn(int p_iRow, int p_iColumn)
{
    bool bRet = true;

    if (!existRowHeader(p_iRow))
    {
        bRet = false;
        CdmMessageManager::critical("Fehler im Modell", "Zeile wurde nicht angelegt");
    }

    if (!existColumnHeader(p_iColumn))
    {
        bRet = false;
        CdmMessageManager::critical("Fehler im Modell", "Spalte wurde nicht angelegt");
    }

    return bRet;
}

void CwmsScriptableModel::insertColumnHeader(int iPos, QString p_qstrHeader)
{
    insertHeader(m_qstrlColumnHeaders, iPos, p_qstrHeader);
}

void CwmsScriptableModel::insertRowHeader(int iPos, QString p_qstrHeader)
{
    insertHeader(m_qstrlRowHeaders, iPos, p_qstrHeader);
}

void CwmsScriptableModel::insertHeader(QMap<int,QString>& qmHeader, int iPos, QString &p_qstrHeader)
{
    qmHeader[iPos] = p_qstrHeader;
}

QString CwmsScriptableModel::rowHeader(int p_iPos)
{
    QString qstrHeader;

    if (m_qstrlRowHeaders.contains(p_iPos))
    {
        qstrHeader = m_qstrlRowHeaders[p_iPos];
    }
    else
    {
        qstrHeader = QString::number(p_iPos);
    }


    return qstrHeader;
}

bool CwmsScriptableModel::existRowHeader(int p_iPos)
{
    bool bRet = true;

    if (m_qmData.contains(p_iPos))
    {
         bRet = true;
    }

    return bRet;
}

bool CwmsScriptableModel::existColumnHeader(int p_iPos)
{
    bool bRet = true;

    if (m_qstrlColumnHeaders.contains(p_iPos))
    {
         bRet = true;
    }

    return bRet;
}


QString CwmsScriptableModel::columnHeader(int p_iPos)
{
    QString qstrHeader;

    if (m_qstrlColumnHeaders.contains(p_iPos))
    {
        qstrHeader = m_qstrlColumnHeaders[p_iPos];
    }

    return qstrHeader;
}

void CwmsScriptableModel::setRowCount(int p_iCount)
{
    setHeaderCount(m_qstrlRowHeaders, p_iCount);

}

void CwmsScriptableModel::setHeaderCount(QMap<int,QString>& pmHeader, int p_iCount)
{
    pmHeader.clear();

    for (int counter = 0; counter < p_iCount; ++counter)
    {
        pmHeader[counter] = QString::number(counter);
    }
}


void CwmsScriptableModel::setColumnCount(int p_iCount)
{
    setHeaderCount(m_qstrlColumnHeaders, p_iCount);
}

int CwmsScriptableModel::rowCount()
{
    return m_qmData.count();
}

int CwmsScriptableModel::columnCount()
{
    return m_qstrlColumnHeaders.count();
}

void CwmsScriptableModel::fillHeader(QStandardItemModel* pModel, QMap<int,QString>& p_qmHeader, Qt::Orientation p_iRowColumnType)
{
    QMapIterator<int,QString> qmIt(p_qmHeader);

    while(qmIt.hasNext())
    {
        qmIt.next();
        pModel->setHeaderData(qmIt.key(), p_iRowColumnType, qmIt.value());
    }
}

QStandardItemModel *CwmsScriptableModel::generateItemModel()
{
    QStandardItemModel* pModel = nullptr;

    if (checkRowColumn(0,0))
    {
        pModel = new QStandardItemModel(rowCount(),columnCount());
        fillHeader(pModel, m_qstrlRowHeaders, Qt::Vertical);
        fillHeader(pModel, m_qstrlColumnHeaders, Qt::Horizontal);

        for (int iRowCounter = 0; iRowCounter < rowCount(); ++iRowCounter)
        {
            for (int iColumnCounter = 0; iColumnCounter < columnCount(); ++iColumnCounter)
            {
                QMap<int,QVariant> qmDisplayTypeMap;
                getDisplayTypeMap(iRowCounter,iColumnCounter, qmDisplayTypeMap);
                QModelIndex qIndex = pModel->index(iRowCounter, iColumnCounter);
                bool bSuccess = pModel->setItemData(qIndex, qmDisplayTypeMap);

                if (bSuccess)
                {
                    qmDisplayTypeMap = pModel->itemData(qIndex);
                }
            }
        }
    }

    return pModel;
}

//QChart* CwmsScriptableModel::generateLineChart()
//{
//    QChart* chart = new QChart();
//    chart->legend()->hide();
//    //chart->addSeries(series); // todo
//    chart->createDefaultAxes();
//    chart->setTitle("Simple line chart example");

//    return chart;
//}

