#ifndef CDMQUERY_H
#define CDMQUERY_H

// System and QT Includes
#include <QString>
#include <QVariant>
#include <QObject>
#include <QVector>
#include <QLinkedList>
#include <QModelIndex>

// own Includes
#include "datamanager.h"
#include "CdmQueryResultElement.h"


// forwards
class CdmQueryElement;
class CdmQueryResultElement;
class CdmQueryResultObject;
class CdmObjectContainer;
class CdmObject;
class CdmClass;

// defines
#define SCOPED_QUERY(a,b) QScopedPointer<CdmQuery> a(CdmQueryBuilder::ExecuteQuery(b));

/*
 * This class implements the queries for finding
 * datas to an objectlist.
 */
class WMSMANAGER_API CdmQuery : public QObject
{
    Q_OBJECT

    friend class IdmDataAccess;
    friend class CdmDataAccessHelper;
    friend class CdmQueryElement;
    friend class CdmQueryFactory;

protected:
    /*
     * The Keynames and their corresponding Result Elements
     */
    QMap<QString, CdmQueryResultElement*> m_qmResultElements;
    QList<CdmQueryResultElement*> m_qlResultElementsPos;
    QVector<QString> m_qvAddedSequence;

    /*
     * The result Object contains a tree-like represantation of the Query's Results
     */
    CdmQueryResultObject* m_pRoot;

    /*
     * Last added Result object gets cached
     */
    CdmQueryResultObject* m_rpResultLastResultObject;

    /*
     * Should return ObjectId
     */
    bool m_bIsObjectNeededInResult;

    /*
     * The Child Queryelement corresponds to the WHERE clause
     */
    CdmQueryElement* m_pCdmQueryElement;

    /*
     * The name of the database
     */
    QString m_qstrScheme;

    /*
     * This member is the id of the referencing objectlist.
     */
    long m_lContainerId;

    /*
     * The class which is the base for the query
     */
    const CdmClass* m_rpCdmClass;

    /*
     * The classid which is the base for the query
     */
    long m_lClassId;

    /*
     * Limit configuration in query
     */
    int m_iResultStart;
    int m_iMaxResults;

    /*
     *  Members for grouping
     */
    QList<QString> m_qlGroupBy;

    /*
     * The result id should be order by the member order by
     */
    QStringList m_qstrlOrderBy;

    /*
     * True = asc False = desc ordering
     */
    bool m_bOrderAsc;

    /*
     * Flag if this query was executed.
     */
    bool m_bExecuted;

    /*
     * Flag if this query is still valid
     */
    bool m_bValid;

public:
    CdmQuery(QObject* parent = nullptr);
    CdmQuery(CdmObjectContainer* p_pContainer, QObject* parent = nullptr);
    CdmQuery(CdmClass* p_pCdmClass, QObject* parent = nullptr);
    CdmQuery(QVariantMap &p_rqvHash, QObject* parent = nullptr);
    CdmQuery(const CdmQuery &p_rQuery, QObject* parent = nullptr);
    ~CdmQuery();
    static bool IsWql(QString qstrWql);
    void SetVariant(QVariantMap &p_rqvHash);
    QVariant GetVariant() const;
    void SetSubQuery(bool p_bSubQuery);
    void SetObjectNeededInResult(bool p_bObjectNeededInResult);
    bool IsObjectNeededInResult() const;
    int EvaluateComplexity() const;
    void AddResultElement(QString p_qstrKeyname);
    void AddResultElement(QString p_qstrKeyname, EdmQueryResultElementMode p_eDmMode);
    int FindResultElement(QString p_qstrKeyname) const;
    CdmQueryResultElement* GetResultElement(int p_iPos) const;
    CdmQueryResultElement* GetResultElement(QString &p_qstrKeyname) const;
    QVector<QString> GetResultElements() const;
    void DeleteResultElements();
    void SetQueryElement(CdmQueryElement* p_pCdmQueryElement);
    void ResetQueryElement(CdmQueryElement* p_pCdmQueryElement);
    CdmQueryElement* GetQueryElement() const;
    void DeleteQueryElement();
    void AddGroupByElement(QString p_qstrElement);
    QList<QString> GetGroupByElements() const;
    void SetResultStart(int p_iStart);
    int GetResultStart() const;
    void SetLimitResultCount(int p_iMaxResults);
    int GetLimitResultCount() const;
    bool ContainsGrouping() const;
    bool IsHighComplexQuery() const;
    bool IsValid() const;
    int GetColumnCount() const;
    bool IsObjectListTree() const;
    void SetResults(QList<QVariant> &p_rqlResults);
    void ClearResults();
    QString GetKeynameAt(int p_iSection) const;
    QVariant GetResultAt(int p_iColumn, int p_iRow) const;
    QVariant GetResultAt(QString p_qstrKeyname, int p_iPos) const;
    QVariant GetResultAt(const QModelIndex &p_Index) const;
    QString GetResultAsStringAt(int p_iRow) const;
    long GetObjectIdAt(int p_iPos) const;
    CdmObject* GetFirstResultObject() const;
    CdmObject* GetObjectAt(int p_iPos) const;
    CdmObject *GetResultObjectAt(int p_iPos) const;
    long GetObjectListIdAt(int p_iPos) const;
    long GetContainerIdAt(int p_iRow) const;
    int GetRowPosOfObjectInResultTree(long p_lObjectId) const;
    bool IsObjectInResultTree(long p_lObejctId) const;
    bool ContainsResultObject(long p_lObjectId) const;
    bool ContainsResultObject(CdmObject* p_pObject) const;
    //const QList<long> GetResultListAsList();
    QVariant GetResultsAsVariant() const;
    QVariant GetResultElementsAsVariant() const;

public slots:
    int Execute();
    void Clear();
    void ClearAll();
    void AddAllMembers();
    QString GetResultAsString() const;
    const QLinkedList<long> GetResultList() const;
    QVariant GetFirstResultList(QString p_qstrKeyname) const;
    void GetResultElementList(QString p_qstrKeyname, QVector<QVariant> &p_rqllResults) const;
    int CountQueryiedChildren(long p_lParentId) const;
    QList<CdmObject*> GetChildList(long lParentId) const;
    long GetParentObjectId(const QModelIndex &p_rqIndex) const;
    CdmObject* GetChildAt(long p_lParentId, int p_iRow);
    long GetPositionObjectId(long p_lParentId, int p_iPosition);
    int GetResultCount() const;
    bool HasResultElements() const;
    CdmQueryResultObject* GetRootElement() const;
    CdmQueryResultObject* GetChildAtRow(int p_iRow) const;
    void SetSorting(int p_iColumn, Qt::SortOrder p_eSortOrder);
    void SetOrderBy(QStringList &p_qstrOrderBy, bool p_bAsc = true);
    void AddOrderBy(QString p_qstrOrderBy, bool p_bAsc = true);
    QStringList GetOrderBy() const;
    bool GetOrderMode() const;
    void SetContainer(QString p_qstrKeyname);
    void SetContainer(CdmObjectContainer* p_pContainer);
    CdmObjectContainer* GetContainer() const;
    void SetContainerId(long p_lId);
    long GetContainerId() const;
    void SetClass(CdmClass *p_pClass);
    const CdmClass* GetClass() const;
    void SetClassId(long p_lId);
    long GetClassId() const;

private:
    int ExecuteDb();
    bool IsExecuted() const;
    EdmQueryResultElementMode ReadModeFromString(QString p_qstrMode);
    void AddResult(long p_lObjectId, long p_lContainerId);
    void AddResultToColumn(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId);
    void AddResultToColumnInRow(int p_iColumn, int p_iRow, QVariant& p_qvValue);
    void SetResultInternal(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId);
    void IndexOutOfRangeError(int p_iPos, int p_iResultCount) const;
    bool IsEnhancedQuery() const;

};

#endif //
