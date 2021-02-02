#include <QDate>

#include "CwmsTreeWidgetItem.h"

CwmsTreeWidgetItem::CwmsTreeWidgetItem(QTreeWidget *p_pWidget)
    : QTreeWidgetItem(p_pWidget)
{

}

CwmsTreeWidgetItem::~CwmsTreeWidgetItem()
{

}

bool CwmsTreeWidgetItem::operator<(const QTreeWidgetItem &other)const
{
    bool bRet = false;
    int column = treeWidget()->sortColumn();
    QString qstrFirstText = text(column).toLower();
    QString qstrOtherText = other.text(column).toLower();

    bool bOkFirst;
    bool bOkOther;
    QLocale loc;
    double dTextFirst = loc.toDouble(qstrFirstText, &bOkFirst);
    double dTextOther = loc.toDouble(qstrOtherText, &bOkOther);


    if(bOkFirst && bOkOther)
    {
        bRet = (dTextFirst < dTextOther);
    }
    else
    {
        auto dFirstDate = loc.toDate(qstrFirstText, "dd.MM.yyyy");
        auto dSecondDate = loc.toDate(qstrOtherText, "dd.MM.yyyy");

        if (dFirstDate.isValid() && dSecondDate.isValid())
        {
            bRet = dFirstDate < dSecondDate;
        }
        else
        {
            bRet = qstrFirstText < qstrOtherText;
        }
    }

    return bRet;
}

