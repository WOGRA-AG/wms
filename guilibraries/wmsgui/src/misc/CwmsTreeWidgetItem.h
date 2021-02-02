#ifndef CWMSTREEWIDGETITEM_H
#define CWMSTREEWIDGETITEM_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

// own Includes
#include "wmsgui.h"

class WMSGUI_API CwmsTreeWidgetItem : public QTreeWidgetItem
{
public:
    CwmsTreeWidgetItem(QTreeWidget *p_pWidget);
    virtual ~CwmsTreeWidgetItem();

    virtual bool operator <(const QTreeWidgetItem &other) const;
};

#endif // CWMSTREEWIDGETITEM_H
