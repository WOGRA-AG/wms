#ifndef CWMSTREECOMPLETIONITEM_H
#define CWMSTREECOMPLETIONITEM_H


// forwards
class CdmMember;
class CdmClass;

class CwmsTreeCompletionItem
{
public:
    explicit CwmsTreeCompletionItem(QString qstrData, CwmsTreeCompletionItem *parentItem = 0);
    ~CwmsTreeCompletionItem();

    void appendChild(CwmsTreeCompletionItem *child);

    CwmsTreeCompletionItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    CwmsTreeCompletionItem *parentItem();

    void DeleteChildrens();
    CwmsTreeCompletionItem(QString qstrData, CdmClass *p_pClass, CwmsTreeCompletionItem *parent);
    CwmsTreeCompletionItem(CdmMember *p_pMember, CwmsTreeCompletionItem *parent);

private:
    QList<CwmsTreeCompletionItem*> m_childItems;
    QString m_itemData;
    CwmsTreeCompletionItem *m_parentItem;
    CdmMember* m_rpMember;
    CdmClass* m_rpClass;
    void fillClassTypeFunctions();
    void fillMemberTypeFunctions();
    void fillTypeFunctions();
};

#endif // CWMSTREECOMPLETIONITEM_H
