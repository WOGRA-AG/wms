#ifndef CWMSSCRIPTABLEMODEL_H
#define CWMSSCRIPTABLEMODEL_H

#include <QMap>
#include <QStandardItemModel>


#include "basetools.h"


class BASETOOLS_API CwmsScriptableModel : public QObject
{
private:
    QMap<int, QMap<int,QMap<int,QVariant>>> m_qmData;
    QMap<int,QString> m_qstrlRowHeaders;
    QMap<int,QString> m_qstrlColumnHeaders;
    bool checkRowColumn(int p_iRow, int p_iColumn);
    void fillHeader(QStandardItemModel* pModel, QMap<int,QString>& p_qmHeader, Qt::Orientation p_iRowColumnType);

    void getDisplayTypeMap(int p_iRow, int p_iColumn, QMap<int, QVariant> &qmDisplayTypeMap);
    void insertHeader(QMap<int, QString> &qmHeader, int iPos, QString &p_qstrHeader);
    void CopyHeaderData(QAbstractItemModel &p_rModel, Qt::Orientation orientation, QMap<int,QString>& qmHeader, int count);

    void setHeaderCount(QMap<int, QString> &pmHeader, int p_iCount);
public:
    CwmsScriptableModel();
    ~CwmsScriptableModel();

public slots:
    void CopyFromItemModel(QAbstractItemModel& p_rModel, int p_iDisplayType);
    QVariant getValue(int p_iRow, int p_iColumn, int p_iDisplayType);
    void addValue(int p_iRow, int p_iColumn, int p_iDisplayType, QVariant& p_rValue);
    void insertColumnHeader(int iPos, QString& p_qstrHeader);
    void insertRowHeader(int iPos, QString& p_qstrHeader);
    QString rowHeader(int p_iPos);
    QString columnHeader(int p_iPos);
    int rowCount();
    int columnCount();
    QStandardItemModel* generateItemModel();
    bool existRowHeader(int p_iPos);
    bool existColumnHeader(int p_iPos);
    void setRowCount(int p_iCount);
    void setColumnCount(int p_iCount);
    void appendFromItemModel(QAbstractItemModel &p_rModel, int p_iDisplayType);
};

#endif // CWMSSCRIPTABLEMODEL_H
