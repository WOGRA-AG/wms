
// System and Qt Inlcudes
#include <QStringList>
#include <QMetaMethod>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmClassMethod.h"
#include "CdmClass.h"

// WMS Basetools Includes
#include "CwmsScriptableLogger.h"
#include "CwmsScriptableMailer.h"
#include "CwmsScriptableMessage.h"
#include "CwmsScriptablePlugin.h"
#include "CwmsScriptablePrinter.h"
#include "CwmsScriptableStatic.h"
#include "CwmsScriptableUi.h"
#include "CwmsScriptableWorkflow.h"
#include "CwmsScriptableWql.h"
#include "CwmsScriptableGeoServices.h"
#include "CwmsScriptableFile.h"
#include "CwmsScriptableHttpClient.h"
#include "CwmsScriptableSql.h"
#include "CwmsScriptableTimer.h"


// Own Includes
#include "CwmsTreeCompletionItem.h"
#include "CwmsTreeCompletionModel.h"



CwmsTreeCompletionModel::CwmsTreeCompletionModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootItem = new CwmsTreeCompletionItem("Root");
}

CwmsTreeCompletionModel::~CwmsTreeCompletionModel()
{
    delete rootItem;
}

int CwmsTreeCompletionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<CwmsTreeCompletionItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}



QVariant CwmsTreeCompletionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    CwmsTreeCompletionItem *item = static_cast<CwmsTreeCompletionItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags CwmsTreeCompletionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant CwmsTreeCompletionModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex CwmsTreeCompletionModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CwmsTreeCompletionItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CwmsTreeCompletionItem*>(parent.internalPointer());

    CwmsTreeCompletionItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CwmsTreeCompletionModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CwmsTreeCompletionItem *childItem = static_cast<CwmsTreeCompletionItem*>(index.internalPointer());
    CwmsTreeCompletionItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CwmsTreeCompletionModel::rowCount(const QModelIndex &parent) const
{
    CwmsTreeCompletionItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CwmsTreeCompletionItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void CwmsTreeCompletionModel::setupModelData(const QStringList &lines, CwmsTreeCompletionItem *parent)
{
    QList<CwmsTreeCompletionItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {

        QString lineData = lines[number];
        QString qstrVariableName;

        QStringList qstrlWords = lineData.split(" ");

        if (qstrlWords.contains("var"))
        {
            int iPos = qstrlWords.indexOf("var");

            if (qstrlWords.count() >= iPos + 2)
            {
                qstrVariableName = qstrlWords[iPos + 1];

                if (qstrVariableName.indexOf(QRegExp("[;=]")) > 0)
                {
                    qstrVariableName = qstrVariableName.left(qstrVariableName.indexOf(QRegExp("[;=]")));
                }
            }
        }

        if (!qstrVariableName.isEmpty())
        {
            // add variable to model
            CwmsTreeCompletionItem* pNewItem = new CwmsTreeCompletionItem(qstrVariableName, parent);
            parent->appendChild(pNewItem);
        }

        ++number;
    }

    addDefaultJsFunctions();
}

void CwmsTreeCompletionModel::setupModelData(QString p_qstrName, const QObject* p_pObject, CwmsTreeCompletionItem *parent)
{
    if (p_pObject && parent)
    {
        CwmsTreeCompletionItem* pObjectItem = new CwmsTreeCompletionItem(p_qstrName, parent);
        parent->appendChild(pObjectItem);
        QList<QByteArray> qlProperties = p_pObject->dynamicPropertyNames();

        for (int iCounter = 0; iCounter < qlProperties.count(); ++ iCounter)
        {
            CwmsTreeCompletionItem* pPropertyItem = new CwmsTreeCompletionItem(qlProperties[iCounter], pObjectItem);
            pObjectItem->appendChild(pPropertyItem);
        }

        const QMetaObject* pMetaObject = p_pObject->metaObject();

        if (CHKPTR(pMetaObject))
        {
            for (int iPos = 0; iPos < pMetaObject->methodCount(); ++iPos)
            {
                QMetaMethod cMethod = pMetaObject->method(iPos);

                if (cMethod.isValid())
                {
                    QString qstrName(cMethod.name());
                    if (qstrName != "destroyed" &&
                        qstrName != "deleteLater" &&
                        qstrName != "objectNameChanged" &&
                        qstrName != "_q_reregisterTimers")
                    {
                        CwmsTreeCompletionItem* pNewItem = new CwmsTreeCompletionItem(qstrName +"(", pObjectItem);
                        pObjectItem->appendChild(pNewItem);
                    }
                }
            }
        }
    }
}

CwmsTreeCompletionItem *CwmsTreeCompletionModel::GetRootItem()
{
    return rootItem;
}

void CwmsTreeCompletionModel::addMembersToModel(const CdmClass* p_pClass, CwmsTreeCompletionItem *parent, CwmsTreeCompletionItem* pClassItem, int iDepth)
{
    if (iDepth > 3)
    {
        return;
    }

    QMap<qint64, CdmMember*> qmMembers;
    p_pClass->GetMemberMap(qmMembers);

    QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
    QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        CdmMember* pMember = qmIt.value();
        if (pClassItem)
        {
            CwmsTreeCompletionItem* pMemberItem = new CwmsTreeCompletionItem(pMember, pClassItem);
            pClassItem->appendChild(pMemberItem);
        }

        CwmsTreeCompletionItem* pMemberItem = new CwmsTreeCompletionItem(pMember, parent);
        parent->appendChild(pMemberItem);

        if (pMember->GetClassReferencePtr() != nullptr)
        {
            addMembersToModel(pMember->GetClassReferencePtr(), pMemberItem, nullptr, ++iDepth);
        }
    }
}

void CwmsTreeCompletionModel::addMethodsToModel(const CdmClass* p_pClass, CwmsTreeCompletionItem *parent, CwmsTreeCompletionItem* pClassItem)
{
    Q_UNUSED(parent)
    QMap<QString, CdmClassMethod*> qmMethods = const_cast<CdmClass*>(p_pClass)->GetAllMethods();
    QMap<QString, CdmClassMethod*>::iterator qmMethodIt = qmMethods.begin();
    QMap<QString, CdmClassMethod*>::iterator qmItMethodEnd = qmMethods.end();

    for (; qmMethodIt != qmItMethodEnd; ++qmMethodIt)
    {
        CwmsTreeCompletionItem* pMethodItem = new CwmsTreeCompletionItem(qmMethodIt.value()->GetMethodName(), pClassItem);
        pClassItem->appendChild(pMethodItem);
    }
}

void CwmsTreeCompletionModel::addObjectFunctions(CwmsTreeCompletionItem* pClassItem)
{
    CwmsTreeCompletionItem* pMemberItem = new CwmsTreeCompletionItem("findValue(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getContainer()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("commit()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("refreshObject()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("addValueListObjectItem(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("removeValueListObjectItem(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("setValueBinaryDocument(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getJson()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("execute(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getValueDisplayString(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("setDeleted(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isDeleted()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isModified()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getKeyname()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getCaption()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("setCaption(", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getLastChanged()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getCreatorId()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getModifierId()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getUri()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isObject()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isContainer()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isClass()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isMember()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("isValue()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getId()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getFactory()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getManager()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getContainerManager()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getClassManager()", pClassItem);
    pClassItem->appendChild(pMemberItem);
    pMemberItem = new CwmsTreeCompletionItem("getScheme()", pClassItem);
    pClassItem->appendChild(pMemberItem);
}

void CwmsTreeCompletionModel::addGlobalFunctionObjects(CwmsTreeCompletionItem *parent)
{
    CwmsScriptableLogger logger;
    setupModelData("log", &logger, parent);
    CwmsScriptableMailer mailer;
    setupModelData("mail", &mailer, parent);
    CwmsScriptableMessage message;
    setupModelData("message", &message, parent);
    CwmsScriptablePlugin plugin;
    setupModelData("plugin", &plugin, parent);
    CwmsScriptablePrinter printer;
    setupModelData("printing", &plugin, parent);
    CwmsScriptableStatic staticexec;
    setupModelData("staticExec", &staticexec, parent);
    CwmsScriptableWorkflow workflow;
    setupModelData("workflow", &workflow, parent);
    CwmsScriptableWql wql;
    setupModelData("wql", &wql, parent);
    CwmsScriptableFile file;
    setupModelData("file", &file, parent);
    CwmsScriptableGeoServices geo;
    setupModelData("geo", &geo, parent);
    CwmsScriptableHttpClient http;
    setupModelData("httpClient", &http, parent);
    CwmsScriptableSql sql;
    setupModelData("sql", &sql, parent);
    CwmsScriptableTimer timer;
    setupModelData("timer", &timer, parent);
}

void CwmsTreeCompletionModel::setupModelData(const CdmClass* p_pClass, CwmsTreeCompletionItem *parent)
{
    if (p_pClass && parent)
    {
        CwmsTreeCompletionItem* pClassItem = new CwmsTreeCompletionItem("me", parent);
        parent->appendChild(pClassItem);
        addMembersToModel(p_pClass, parent, pClassItem, 0);
        addMethodsToModel(p_pClass, parent, pClassItem);
        addObjectFunctions(pClassItem);
        addGlobalFunctionObjects(parent);
    }
}

void CwmsTreeCompletionModel::clearModel()
{
    rootItem->DeleteChildrens();
}

void CwmsTreeCompletionModel::addDefaultJsFunctions()
{
    CwmsTreeCompletionItem* pNewItem = new CwmsTreeCompletionItem("eval(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("parseInt(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("parseFloat(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("isNaN(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("isFinite(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("decodeURI(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("decodeURIComponent(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("encodeURI(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("encodeURIComponent(", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Object", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Function", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Array", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("String", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Boolean", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Number", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Date", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("RegExp", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("Error", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("EvalError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("RangeError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("ReferenceError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("SyntaxError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("TypeError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("URIError", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("instanceof", rootItem);
    rootItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("typeof", rootItem);
    rootItem->appendChild(pNewItem);

    // Math Object
    CwmsTreeCompletionItem* pMathItem = new CwmsTreeCompletionItem("Math", rootItem);
    rootItem->appendChild(pMathItem);

    pNewItem = new CwmsTreeCompletionItem("E", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("LN10", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("LN2", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("LOG2E", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("LOG10E", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("PI", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("SQRT1_2", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("SQRT2", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("abs(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("acos(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("asin(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("atan(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("atan2(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("ceil(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("cos(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("exp(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("floor(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("log(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("max(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("min(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("pow(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("random(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("round(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("sin(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("sqrt(", pMathItem);
    pMathItem->appendChild(pNewItem);
    pNewItem = new CwmsTreeCompletionItem("tan(", pMathItem);
    pMathItem->appendChild(pNewItem);
}
