#ifndef IWMSMODEL_H
#define IWMSMODEL_H

#endif // IWMSMODEL_H



class IwmsModel
{
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
    void SetProxy(CdmProxyBase* p_pProxy);
    void SetContainer(CdmObjectContainer* p_pList);
    CdmObjectContainer* GetContainer();
    virtual void SetContainer(QString p_qstrObjectListKeyname);
    void AddDisplayHeader(QString p_qstrKeyname, QString p_qstrDisplayString);
};
