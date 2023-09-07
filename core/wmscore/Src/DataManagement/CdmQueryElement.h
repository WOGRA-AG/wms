#ifndef CDMQUERYELEMENT_H
#define CDMQUERYELEMENT_H

// Systemm and QT Includes
#include <QList>
#include <QVariant>
#include <qstring.h>
#include <QObject>

// own Includes
#include "CdmModelElement.h"
#include "datamanager.h"

// forwards
class CdmQuery;
class CdmObject;
class CdmValue;
class QVariant;
class QTime;
class QDateTime;
class QDomDocument;
class QDomElement;
class QDate;

// Enumerations

/*
 * The Query Compare Type only needed by QueryElementType
 * Compare
 */
enum EdmQueryCompareType
{
    eDmQueryCompareTypeNone,
    eDmQueryCompareTypeEqual,
    eDmQueryCompareTypeNotEqual,
    eDmQueryCompareTypeSmaller,
    eDmQueryCompareTypeSmallerEqual,
    eDmQueryCompareTypeLarger,
    eDmQueryCompareTypeLargerEqual,
    eDmQueryCompareTypeLike,
    eDmQueryCompareTypeIn,
    eDmQueryCompareTypeNotIn,
    eDmQueryCompareTypeNotLike,
    eDmQueryCompareTypeNull,
    eDmQueryCompareTypeNotNull
};


/*
 * The Query Elementtype
 */
enum EdmQueryElementType
{
    eDmQueryElementTypeNone,
    eDmQueryElementTypeAnd,
    eDmQueryElementTypeOr,
    eDmQueryElementTypeCompare
};


/*
 * This class implements one query element
 * the querey elements will be built as a
 * tree of query elements. With the help of
 * the tree it is possible to genereate sql
 * queries or checking local objects.
 */
class WMSMANAGER_API CdmQueryElement : public QObject
{
    Q_OBJECT

private:
    /*
     * The Child Query Elements
     */
    QList<CdmQueryElement*> m_lChildQuerys;

    /*
     * The Query Element Type
     */
    EdmQueryElementType          m_eDmQueryElementType;

    /*
     * The Value
     */
    QVariant                    m_qVariant;

    /*
     * The Query Element Compare Type !=, ==, <,...
     */
    EdmQueryCompareType          m_eDmCompareType;

    /*
     * The Keyname of the value to compare
     */
    QString                      m_qstrCompareKeyname;

    /*
     * The parent query
     */
    CdmQuery*                    m_rpCdmQuery;

    /*
     * A SubQuery
     */
    CdmQuery*                    m_rpCdmSubQuery;

    /*
     * A In  or Not In List for Value Compares (In or NotIn)
     * with Variants
     */
    QList<QVariant>          m_qvlInOrNotInList;

    /*
     * The Type of the value which will be compared
     */
    EdmValueType                  m_eDmValueCompare;

    /*
     * flag for Automated Subquery creation. if this subquery was created
     * in this class the flag must be set to true. So the subquery will be deleted
     * in the destructor.
     */
    bool                           m_bAutomaticSubqueryCreation;

    CdmQueryElement*               m_pParent;



public:
    CdmQueryElement(CdmQuery* p_pCdmQuery);
    CdmQueryElement(CdmQuery* p_pCdmQuery, EdmQueryElementType p_eDmQueryElementType);
    CdmQueryElement(CdmQuery* p_pCdmQuery,
                    EdmQueryElementType p_eDmQueryElementType,
                    EdmQueryCompareType p_eDmQueryCompareType);
    CdmQueryElement(CdmQuery* p_pCdmQuery,
                    EdmQueryElementType p_eDmQueryElementType,
                    EdmQueryCompareType p_eDmQueryCompareType,
                    QVariant p_qVariant,
                    QString p_qstrKeyname);

    CdmQueryElement(CdmQuery* p_pCdmQuery, QString p_qstrCondition);
    CdmQueryElement(CdmQuery* p_pCdmQuery, QDomElement &p_rqDomElement);
    CdmQueryElement(CdmQuery* p_pCdmQuery, QVariantMap &p_rqvHash);
    virtual ~CdmQueryElement();
    void XmlExport(QDomDocument &p_rqdDomDocument, QDomElement &p_rqdeElement) const;
    int GetComplexity() const;
    QVariant GetVariant() const;
    CdmQueryElement* GetParent() const;
    bool HasParent() const;

public slots:
    EdmQueryCompareType GetCompareType() const;
    EdmQueryElementType GetQueryElementType() const;
    void GetChildList(QList<CdmQueryElement*> &p_rqvlChilds) const;
    QString GetCompareKeyname() const;
    EdmValueType GetValueType() const;
    void AddChild(CdmQueryElement* p_pCdmQueryElement);
    void SetComparisonValue(QString p_qstrKeyname, QVariant p_qvValue);
    void SetComparisonValue(QString p_qstrKeyname, bool p_bValue);
    void SetComparisonValue(QString p_qstrKeyname, int p_iValue);
    void SetComparisonValue(QString p_qstrKeyname,qint64 p_lValue);
    void SetComparisonValue(QString p_qstrKeyname, float p_fValue);
    void SetComparisonValue(QString p_qstrKeyname, QList<QVariant> p_qvlList);
    void SetVariant(QVariant p_pqVariant);
    void SetValue(QVariant p_pqVariant);
    QVariant GetValue() const;
    void SetKeyname(QString p_qstrKeyname);
    void SetCompareType(EdmQueryCompareType p_eDmQueryCompareType);
    void SetQueryElementType(EdmQueryElementType p_eDmQueryElementType);
    CdmQuery* GetQuery() const;
    CdmQuery* GetSubQuery() const;
    QList<QVariant>& GetList();
    bool IsValueMember() const;
    QString GetConditionAsString() const;
    QString GetCompareTypeAsString() const;
    static QString CompareTypeToString(EdmQueryCompareType p_eDmQueryCompareType);
    void SetSubQuery(QString p_qstrKeyname, CdmQuery* p_pCdmQuery);
    bool IsThisCompare() const;
    bool HasSubQuery() const;
    bool IsSubQueryEnhanced() const;

private:
    void XmlImport(QDomElement& p_rqDomElement);
    void XmlImportChilds(QDomElement& p_rqDomElement);
    void SetParent(CdmQueryElement *p_pParent);
    void FindValue();
    bool FindValue(QString p_qstrKeyname);
    void CreateSubQueryFromMember(const CdmMember* p_pCdmMember, QString p_qstrSubMemberName);
    void ParseCondition(QString p_qstrCondition);
    void ParseChildConditions(QString p_qstrCondition);
    void ParseCompareCondition(QString p_qstrCondition);
    int FindCompareElement(QString p_qstrCompareElement);
    int GetCompareElementLength();
    void SetInNotInValuesForComparision(QString p_qstrFirst, QString p_qstrSecond);
    void AnalyzeCompare(QString p_qstrFirst, QString p_qstrSecond);
    const CdmMember *GetMember(QString p_qstrKeyname);
};

#endif //
