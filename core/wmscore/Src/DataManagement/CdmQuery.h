/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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
     * Force the Query to have Result Elements
     */
    bool m_bForceEnhanced;

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
     * This flag shows if this is a local query or a server query
     */
    bool m_bLocal;

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
    /** +-=---------------------------------------------------------Mi 10. Nov 18:43:42 2010-------*
     * @method  CdmQuery::CdmQuery                            // public                            *
     * @return                                                //                                   *
     * @comment The Default constructor.                                                           *
     *----------------last changed: -----------------------------Mi 10. Nov 18:43:42 2010----------*/
    CdmQuery(QObject* parent = nullptr);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:51:08 2005*
     * @method  CdmQuery::CdmQuery                            // public                            *
     * @return                                                //                                   *
     * @param   CdmObjectContainer* p_pContainer               //                                  *
     * @comment The constructor of the query. this query searches for object specified in the      *
     *          query element.                                                                     *
     *----------------last changed: -----------------------------Sa 20. Aug 10:51:08 2005----------*/
    CdmQuery(CdmObjectContainer* p_pContainer, QObject* parent = nullptr);

    /** +-=---------------------------------------------------------So 11. Nov 10:40:53 2007-------*
     * @method  CdmQuery::CdmQuery                            // public                            *
     * @return                                                //                                   *
     * @param   CdmClass* p_pCdmClass                         //                                   *
     * @comment The Default constructor.                                                           *
     *----------------last changed: Wolfgang Graßhof-------------So 11. Nov 10:40:53 2007----------*/
    CdmQuery(CdmClass* p_pCdmClass, QObject* parent = nullptr);

    /** +-=---------------------------------------------------------Di 17. Apr 10:48:51 2012-------*
     * @method  CdmQuery::CdmQuery                            // public                            *
     * @return                                                //                                   *
     * @param   QVariantMap& p_rqvHash                        //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 17. Apr 10:48:51 2012----------*/
    CdmQuery(QVariantMap &p_rqvHash, QObject* parent = nullptr);

    /** +-=---------------------------------------------------------Mi 26. Sep 09:29:45 2012-------*
     * @method  CdmQuery::CdmQuery                            // public                            *
     * @return                                                //                                   *
     * @param   const CdmQuery& p_rQuery                      //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 26. Sep 09:29:45 2012----------*/
    CdmQuery(const CdmQuery &p_rQuery, QObject* parent = nullptr);

    /** +-=---------------------------------------------------------Sa 20. Aug 12:48:29 2005*
     * @method  CdmQuery::~CdmQuery                           // public, virtual                   *
     * @return  void                                          //                                   *
     * @comment The Destructor of Class CdmQuery                                                   *
     *----------------last changed: -----------------------------Sa 20. Aug 12:48:29 2005----------*/
    ~CdmQuery();



public:
    static bool IsWql(QString qstrWql);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:52:10 2005*
     * @method  CdmQuery::XmlImport                           // public, static                    *
     * @return  CdmQuery*                                     //                                   *
     * @param   QString p_qstrXmlSource                       //                                   *
     * @comment This static method reads an xml string and creates from it the xml query object.   *
     *----------------last changed: -----------------------------Sa 20. Aug 10:52:10 2005----------*/
    static CdmQuery* XmlImport(QString p_qstrXmlSource);



    // QVariant of whole Class
public:
    void SetVariant(QVariantMap &p_rqvHash);
    QVariant GetVariant() const;



    // Internal Crap
public:
    void SetLocalSearch();
    void SetSchemeSearch();
    void SetSubQuery(bool p_bSubQuery);
    void SetObjectNeededInResult(bool p_bObjectNeededInResult);
    bool IsObjectNeededInResult() const;

    int EvaluateComplexity() const;
public slots:
    /** +-=---------------------------------------------------------Di 20. Nov 10:55:12 2012-------*
     * @method  CdmQuery::Execute                             // public, slots                     *
     * @return  int                                           //                                   *
     * @comment This method call executes the query and fills the result list with correct         *
     *          results.                                                                           *
     *----------------last changed: -----------------------------Di 20. Nov 10:55:12 2012----------*/
    int Execute();

    /** +-=---------------------------------------------------------Di 20. Nov 10:55:00 2012-------*
     * @method  CdmQuery::Clear                               // public, slots                     *
     * @return  void                                          //                                   *
     * @comment Clears the child elements of the query.                                            *
     *----------------last changed: -----------------------------Di 20. Nov 10:55:00 2012----------*/
    void Clear();
    void ClearAll();

    void AddAllMembers();



    // Necessary Elements (Container, Where, ...)
public:
    void AddResultElement(QString p_qstrKeyname);
    void AddResultElement(QString p_qstrKeyname, EdmQueryResultElementMode p_eDmMode);
    int FindResultElement(QString p_qstrKeyname) const;
    CdmQueryResultElement* GetResultElement(int p_iPos) const;
    CdmQueryResultElement* GetResultElement(QString &p_qstrKeyname) const;
    QVector<QString> GetResultElements() const;
    void DeleteResultElements();

    /** +-=---------------------------------------------------------Sa 20. Aug 10:51:55 2005----------*
     * @method  CdmQuery::SetScheme                              // public                            *
     * @return  void                                             //                                   *
     * @param   QString p_qstrDatabase                           //                                   *
     * @comment This method sets the name of the database which should be used for the query.         *
     *----------------last changed: --------------------------------Sa 20. Aug 10:51:55 2005----------*/
    void SetScheme(QString p_qstrDatabase);
    QString GetScheme() const;

    /** +-=---------------------------------------------------------Di 20. Nov 10:59:04 2012-------*
     * @method  CdmQuery::SetQueryElement                     // public                            *
     * @return  void                                          //                                   *
     * @param   CdmQueryElement* p_pCdmQueryElement           // change of ownership!!!!!!!!       *
     * @comment This method sets a query element in the query. The query element will be deleted   *
     *----------------last changed: -----------------------------Di 20. Nov 10:59:04 2012----------*/
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
public slots:
    void SetSorting(int p_iColumn, Qt::SortOrder p_eSortOrder);

    /** +-=---------------------------------------------------------Di 20. Nov 10:59:43 2012----------*
     * @method  CdmQuery::SetOrderBy                             // public, slots                     *
     * @return  void                                             //                                   *
     * @param   QStringList &p_qstrOrderBy                       //                                   *
     * @param   bool p_bAsc = true                               // order asc = true desc = false     *
     * @comment The result of the query should be ordered by the overgiven members.                   *
     *----------------last changed: --------------------------------Di 20. Nov 10:59:43 2012----------*/
    void SetOrderBy(QStringList &p_qstrOrderBy, bool p_bAsc = true);
    void AddOrderBy(QString p_qstrOrderBy, bool p_bAsc = true);
    QStringList GetOrderBy() const;
    bool GetOrderMode() const;

    /** +-=---------------------------------------------------------Mo 28. Jan 13:20:28 2013----------*
     * @method  CdmQuery::SetContainer                           // public, slots                     *
     * @return  void                                             //                                   *
     * @param   QString p_qstrKeyname                            //                                   *
     * @comment this method sets the object list for the case of default constructor.                 *
     *----------------last changed: --------------------------------Mo 28. Jan 13:20:28 2013----------*/
    void SetContainer(QString p_qstrKeyname);
    void SetContainer(CdmObjectContainer* p_pContainer);
    CdmObjectContainer* GetContainer() const;
    void SetContainerId(long p_lId, QString p_qstrDatabase);
    void SetContainerId(long p_lId);
    long GetContainerId() const;

    void SetClass(CdmClass *p_pClass);
    const CdmClass* GetClass() const;
    void SetClassId(long p_lId, QString p_qstrDatabase);
    void SetClassId(long p_lId);
    long GetClassId() const;



    // IsT()
public:
    bool ContainsGrouping() const;
    bool IsHighComplexQuery() const;
    bool IsValid() const;

    int GetColumnCount() const;

    bool IsObjectListTree() const;
public slots:
    bool IsEnhancedQuery() const;
    bool HasResultElements() const;



    // Resultree methods
public slots:
    CdmQueryResultObject* GetRootElement() const;
    CdmQueryResultObject* GetChildAtRow(int p_iRow) const;



    // Results
public:
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
    QString GetResultAsString() const;

    /** +-=---------------------------------------------------------Di 20. Nov 10:59:28 2012----------*
     * @method  CdmQuery::GetResultList                          // public, slots                     *
     * @return  const QLinkedList<long>                          //                                   *
     * @comment returns the list of results.                                                          *
     *----------------last changed: --------------------------------Di 20. Nov 10:59:28 2012----------*/
    const QLinkedList<long> GetResultList() const;


    QVariant GetFirstResultList(QString p_qstrKeyname) const;
    void GetResultElementList(QString p_qstrKeyname, QVector<QVariant> &p_rqllResults) const;

    int CountQueryiedChildren(long p_lParentId) const;
    QList<CdmObject*> GetChildList(long lParentId) const;
    long GetParentObjectId(const QModelIndex &p_rqIndex) const;

    CdmObject* GetChildAt(long p_lParentId, int p_iRow);
    long GetPositionObjectId(long p_lParentId, int p_iPosition);

    int GetResultCount() const;



private:
    int ExecuteDb();
    bool IsExecuted() const;
    EdmQueryResultElementMode ReadModeFromString(QString p_qstrMode);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:51:46 2005-------*
     * @method  CdmQuery::AddResult                           // private                           *
     * @return  void                                          //                                   *
     * @param   long p_lObjectId                              //                                   *
     * @comment This method adds an result to this query.                                          *
     *----------------last changed: -----------------------------Sa 20. Aug 10:51:46 2005----------*/
    void AddResult(long p_lObjectId, long p_lContainerId);

    void AddResultToColumn(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId);
    void AddResultToColumnInRow(int p_iColumn, int p_iRow, QVariant& p_qvValue);

    /** +-=---------------------------------------------------------So 14. Okt 15:25:18 2012-------*
     * @method  CdmQueryEnhanced::SetResultInternal           // private                           *
     * @return  void                                          //                                   *
     * @param   int p_iColumn                                 //                                   *
     * @param   QVariant p_qvValue                            //                                   *
     * @param   long p_lObjectId                              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 14. Okt 15:25:18 2012----------*/
    void SetResultInternal(int p_iColumn, QVariant p_qvValue, long p_lObjectId, long p_lContainerId);

    void IndexOutOfRangeError(int p_iPos, int p_iResultCount) const;
};

#endif //
