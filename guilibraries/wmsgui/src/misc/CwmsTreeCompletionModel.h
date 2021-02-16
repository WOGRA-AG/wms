#ifndef CWMSTREECOMPLETIONMODEL_H
#define CWMSTREECOMPLETIONMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class CdmClass;
class CwmsTreeCompletionItem;

class CwmsTreeCompletionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CwmsTreeCompletionModel(QObject *parent = 0);
    ~CwmsTreeCompletionModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setupModelData(const QStringList &lines, CwmsTreeCompletionItem *parent);

    void setupModelData(QString p_qstrName, const QObject *p_pObject, CwmsTreeCompletionItem *parent);
    CwmsTreeCompletionItem * GetRootItem();
    void setupModelData(const CdmClass *p_pClass, CwmsTreeCompletionItem *parent);
    void clearModel();
private:


    CwmsTreeCompletionItem *rootItem;
    void addDefaultJsFunctions();
    void addMembersToModel(const CdmClass* p_pClass, CwmsTreeCompletionItem *parent, CwmsTreeCompletionItem* pClassItem, int iDepth);
    void addMethodsToModel(const CdmClass* p_pClass, CwmsTreeCompletionItem *parent, CwmsTreeCompletionItem* pClassItem);
    void addObjectFunctions(CwmsTreeCompletionItem *pClassItem);
    void addGlobalFunctionObjects(CwmsTreeCompletionItem *parent);
};

#endif // CWMSTREECOMPLETIONMODEL_H
