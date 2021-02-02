
#include "CdmMessageManager.h"
#include "CdmLogging.h"


#include "CwmsScriptableModel.h"

CwmsScriptableModel::CwmsScriptableModel()
{
    setObjectName("Model");
}

CwmsScriptableModel::~CwmsScriptableModel()
{
}

void CwmsScriptableModel::CopyHeaderData(QAbstractItemModel &p_rModel, Qt::Orientation orientation, QMap<int,QString>& qmHeader, int count)
{
    setHeaderCount(qmHeader, count);
    for(int iCounter = 0; iCounter < count; ++iCounter)
    {
        QString qstrHeader = p_rModel.headerData(iCounter, orientation).toString();
        insertHeader(qmHeader, iCounter, qstrHeader);
    }
}

void CwmsScriptableModel::CopyFromItemModel(QAbstractItemModel &p_rModel, int p_iDisplayType)
{
    m_qmData.clear();
    int iRowCount    = p_rModel.rowCount();
    int iColumnCount = p_rModel.columnCount();

    CopyHeaderData(p_rModel, Qt::Vertical, m_qstrlRowHeaders, iRowCount);
    CopyHeaderData(p_rModel, Qt::Horizontal, m_qstrlColumnHeaders, iColumnCount);

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
        for (int iRowCounter = rowCount(); iRowCounter < iRowCount; ++iRowCounter)
        {
            for(int iColumnCounter = 0; iColumnCounter < iColumnCount; ++iColumnCounter)
            {
                QModelIndex qIndex = p_rModel.index(iRowCounter - iOriginalRowCount, iColumnCounter);
                QVariant qValue = p_rModel.data(qIndex, p_iDisplayType);
                addValue(iRowCounter, iColumnCounter, p_iDisplayType, qValue);
            }
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

void CwmsScriptableModel::addValue(int p_iRow, int p_iColumn, int p_iDisplayType, QVariant &p_rValue)
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

void CwmsScriptableModel::insertColumnHeader(int iPos, QString &p_qstrHeader)
{
    insertHeader(m_qstrlColumnHeaders, iPos, p_qstrHeader);
}

void CwmsScriptableModel::insertRowHeader(int iPos, QString &p_qstrHeader)
{
    insertHeader(m_qstrlRowHeaders, iPos, p_qstrHeader);
}

void CwmsScriptableModel::insertHeader(QMap<int,QString>& qmHeader, int iPos, QString &p_qstrHeader)
{
    m_qstrlRowHeaders[iPos] = p_qstrHeader;
}

QString CwmsScriptableModel::rowHeader(int p_iPos)
{
    QString qstrHeader;

    if (m_qstrlRowHeaders.contains(p_iPos))
    {
        qstrHeader = m_qstrlRowHeaders[p_iPos];
    }


    return qstrHeader;
}

bool CwmsScriptableModel::existRowHeader(int p_iPos)
{
    bool bRet = true;

    if (m_qstrlRowHeaders.contains(p_iPos))
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
    return m_qstrlRowHeaders.count();
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
                pModel->setItemData(qIndex, qmDisplayTypeMap);
            }
        }
    }

    return pModel;
}
