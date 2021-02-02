#ifndef CWMSJSCOMPLETER_H
#define CWMSJSCOMPLETER_H

#include <QCompleter>

class CwmsJsCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit CwmsJsCompleter(QAbstractItemModel* p_pModel, QObject *parent = 0);
    ~CwmsJsCompleter();

    virtual QStringList splitPath(const QString &path) const;
    virtual QString pathFromIndex(const QModelIndex &index) const;


};

#endif // CWMSJSCOMPLETER_H
