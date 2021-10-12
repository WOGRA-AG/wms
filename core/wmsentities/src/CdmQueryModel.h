#ifndef CDMQUERYMODEL_H
#define CDMQUERYMODEL_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QPointer>
#include <QTimer>

// WMS Manager Includes
#include "CdmQuery.h"
#include "CdmContainerAdaptor.h"

// Own Includes
#include "IwmsViewProxy.h"
#include "basetools.h"

#include "IdmHandleDisplayData.h"

// Forwards
class QTimer;
class CdmObjectContainer;
class CdmEnhancedQueryProxy;


// Enumerations

/* 
 * This class implements the proxy for tableviews of enhanced queries
 */
class BASETOOLS_API CdmQueryModel : public QAbstractItemModel, public CdmContainerAdaptor
{
    Q_OBJECT

private:
    QTimer m_qtTimer;
    int m_iRowToInsert;
    int m_iRowToRemove;
    QMap<QString,QString> m_qmDisplayHeader;
    QMap<int, IwmsViewProxy*> m_qmViewProxy;

    IdmHandleDisplayData *m_pIdmDisplayHandler;



public:
    CdmQueryModel(QObject* p)
        : QAbstractItemModel(p),
          m_iRowToInsert(0),
          m_iRowToRemove(0),
          m_pCdmQuery(nullptr){}
    CdmQueryModel();
    virtual ~CdmQueryModel( );

    QModelIndex parent(const QModelIndex & index) const;
    QList<CdmObject *> GetObjects(QAbstractItemView *p_pqItemView);
    void SetInitialDisplayHandler(IdmHandleDisplayData *pDisplayHandler);
    QString GetDisplayString(QString p_qstrMember, QVariant p_qvValue) const;

public slots:
    int rowCount() const;
    int rowCount(const QModelIndex & p_rParent) const;
    int columnCount() const;
    virtual int columnCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex & p_qmIndex, int p_iRole = Qt::DisplayRole) const;
    CdmObject* GetObject(QAbstractItemView* p_pqItemView);
    CdmObject* GetObject(const QModelIndex & p_qmIndex);
    virtual QVariant headerData(int p_iSection,
                                Qt::Orientation p_iOrientation,
                                int p_iRole = Qt::DisplayRole) const;
    bool hasChildren(const QModelIndex & parent = QModelIndex()) const;
    QModelIndex index(int p_iRow, int p_iColumn, const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(int p_iRow, QString p_qstrColumnName, int p_iRole = Qt::DisplayRole) const;
    virtual QVariant data(int p_iRow, int p_iColumn, int p_iRole = Qt::DisplayRole) const;
    const CdmClass* GetClass();
    void AddColumn( QString p_qstrKeyname);
    void ClearColumns( );
    void AddViewProxy(int p_iColumn, IwmsViewProxy* p_pProxy);
    virtual QHash<int, QByteArray> roleNames() const;
    void AddAllMembers();
    CdmObject *GetObject(const int p_iRow);
    void Execute(CdmQuery* p_pCdmQuery);
    void Execute(QString p_qstrQuery);
    virtual void Execute();
    virtual CdmQuery* GetQuery();
    void SetProxy(CdmEnhancedQueryProxy *p_pProxy);
    void SetContainer(CdmObjectContainer* p_pList);
    CdmObjectContainer* GetContainer();
    virtual void SetContainer(QString p_qstrObjectListKeyname);
    void AddDisplayHeader(QString p_qstrKeyname, QString p_qstrDisplayString);

    void Clear();
protected:
    virtual void sort(int p_iColumn, Qt::SortOrder p_eSortOrder);
    virtual void ObjectCommitedEvent(qint64 p_lObjectId);
    CdmQuery* m_pCdmQuery;

protected slots:
    void UpdateSlot( );

private slots:
    void ExecuteQuery();

private:
    QModelIndexList getSelection(QAbstractItemView* p_pqItemView, QModelIndex p_Index);


    const CdmMember *FindMemberByKeyname(QString p_qstrKeyname) const;
signals:
    void UpdateSignal();
};

#endif //
