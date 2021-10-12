// System and QT Includes
#include <QStringList>
#include <QVariant>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmClass.h"

// own Includes
#include "CwmsTreeCompletionItem.h"


CwmsTreeCompletionItem::CwmsTreeCompletionItem(QString qstrData, CwmsTreeCompletionItem *parent)
    : m_parentItem(parent),
      m_rpMember(nullptr),
      m_rpClass(nullptr)
{
    m_itemData = qstrData;
}

CwmsTreeCompletionItem::CwmsTreeCompletionItem(CdmMember* p_pMember, CwmsTreeCompletionItem *parent)
    : m_parentItem(parent),
      m_rpMember(p_pMember),
      m_rpClass(nullptr)
{
    if (CHKPTR(p_pMember))
    {
        m_itemData = p_pMember->GetKeyname();
    }
}

CwmsTreeCompletionItem::CwmsTreeCompletionItem(QString qstrData, CdmClass* p_pClass, CwmsTreeCompletionItem *parent)
    : m_parentItem(parent),
      m_rpMember(nullptr),
      m_rpClass(p_pClass)
{
    m_itemData = qstrData;
}

CwmsTreeCompletionItem::~CwmsTreeCompletionItem()
{
    DeleteChildrens();
}

void CwmsTreeCompletionItem::DeleteChildrens()
{
  qDeleteAll(m_childItems);
  m_childItems.clear();
}

void CwmsTreeCompletionItem::appendChild(CwmsTreeCompletionItem *item)
{
    m_childItems.append(item);
}

CwmsTreeCompletionItem *CwmsTreeCompletionItem::child(int row)
{
    return m_childItems.value(row);
}

int CwmsTreeCompletionItem::childCount() const
{
    if (m_childItems.count() == 0 && (m_rpMember != nullptr || m_rpClass != nullptr))
    {
        const_cast<CwmsTreeCompletionItem*> (this)->fillTypeFunctions();
    }

    return m_childItems.count();
}

int CwmsTreeCompletionItem::columnCount() const
{
    return 1;
}

QVariant CwmsTreeCompletionItem::data(int column) const
{
    Q_UNUSED(column);
    return m_itemData;
}

CwmsTreeCompletionItem *CwmsTreeCompletionItem::parentItem()
{
    return m_parentItem;
}

int CwmsTreeCompletionItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<CwmsTreeCompletionItem*>(this));

    return 0;
}

void CwmsTreeCompletionItem::fillTypeFunctions()
{
    if (m_rpClass)
    {
        fillClassTypeFunctions();
    }
    else if (m_rpMember)
    {
        fillMemberTypeFunctions();
    }
}

void CwmsTreeCompletionItem::fillClassTypeFunctions()
{
    if (CHKPTR(m_rpClass))
    {
        QMap<qint64, CdmMember*> qmMembers;
        m_rpClass->GetMemberMap(qmMembers);

        QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
        QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CwmsTreeCompletionItem* pMemberItem = new CwmsTreeCompletionItem(qmIt.value(), this);
            appendChild(pMemberItem);
        }
    }
}

void CwmsTreeCompletionItem::fillMemberTypeFunctions()
{
    CwmsTreeCompletionItem* pNewItem = new CwmsTreeCompletionItem("toString", this);
    appendChild(pNewItem);

    if (m_rpMember->GetValueType() == eDmValueDate ||
        m_rpMember->GetValueType() == eDmValueDateTime ||
        m_rpMember->GetValueType() == eDmValueTime)
    {
        pNewItem = new CwmsTreeCompletionItem("toDateString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCMonth", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getMonth", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCFullYear", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getFullYear", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getTime", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("valueOf", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleTimeString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleDateString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toTimeString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getMilliseconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCSeconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getSeconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCMinutes", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getMinutes", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCHours", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getHours", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCDay", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCDate", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getDate", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toJSON", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toISOString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toUTCString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCFullYear", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setFullYear", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCMonth", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setMonth", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCDate", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCHours", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setHours", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCMinutes", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setMinutes", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCSeconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setSeconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setUTCMilliseconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setMilliseconds", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setTime", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getTimeZoneOffset", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("getUTCMilliseconds", this);
        appendChild(pNewItem);
    }
    else if (m_rpMember->GetValueType() == eDmValueString)
    {
        pNewItem = new CwmsTreeCompletionItem("valueOf", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("charAt", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("charCodeAt", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("concat", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("indexOf", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("lastIndexOf", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("localeCompare", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("match", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("replace", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("search", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("slice", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("split", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("substring", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLowerCase", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleLowerCase", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toUpperCase", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toLocaleUpperCase", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("trim", this);
        appendChild(pNewItem);
    }
    else if (m_rpMember->GetValueType() == eDmValueInt ||
             m_rpMember->GetValueType() == eDmValueLong ||
             m_rpMember->GetValueType() == eDmValueFloat ||
             m_rpMember->GetValueType() == eDmValueDouble)
    {
        pNewItem = new CwmsTreeCompletionItem("toLocaleString", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toFixed", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toExponential", this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("toPrecision", this);
        appendChild(pNewItem);
    }
    else if (m_rpMember->GetValueType() == eDmValueObjectRef ||
             m_rpMember->GetValueType() == eDmValueContainerRef)
    {
        CdmClass* pClass = nullptr;
       qint64 lClassId = m_rpMember->GetClassReference();

        if (lClassId > 0)
        {
            CdmClassManager* pClassManager = m_rpMember->GetClassManager();
            pClass = pClassManager->FindClassById(lClassId);
        }

        pNewItem = new CwmsTreeCompletionItem("getValueReference()", pClass, this);
        appendChild(pNewItem);
        pNewItem = new CwmsTreeCompletionItem("setValueReference(", pClass, this);
        appendChild(pNewItem);
    }


}
