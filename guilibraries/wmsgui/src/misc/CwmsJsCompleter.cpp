#include "CwmsJsCompleter.h"

CwmsJsCompleter::CwmsJsCompleter(QAbstractItemModel* p_pModel, QObject *parent) :
    QCompleter(p_pModel, parent)
{
}

CwmsJsCompleter::~CwmsJsCompleter()
{

}


QStringList CwmsJsCompleter::splitPath(const QString & path) const
{
    return path.split(".");
}


QString CwmsJsCompleter::pathFromIndex(const QModelIndex &index) const
 {
     QStringList dataList;
     for (QModelIndex i = index; i.isValid(); i = i.parent()) {
         dataList.prepend(model()->data(i, completionRole()).toString());
     }

     return dataList.join(".");
 }
