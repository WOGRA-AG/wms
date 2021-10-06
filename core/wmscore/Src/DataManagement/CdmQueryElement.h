/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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
    /** +-=---------------------------------------------------------Sa 20. Aug 10:54:47 2005-------*
     * @method  CdmQueryElement::CdmQueryElement              // public                            *
     * @return                                                //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @comment the default constructor.                                                           *
     *----------------last changed: -----------------------------Sa 20. Aug 10:54:47 2005----------*/
    CdmQueryElement(CdmQuery* p_pCdmQuery);

    /** +-=---------------------------------------------------------Mo 14. Nov 11:01:26 2005-------*
     * @method  CdmQueryElement::CdmQueryElement              // public                            *
     * @return                                                //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @param   EdmQueryElementType p_eDmQueryElementType     //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 14. Nov 11:01:26 2005----------*/
    CdmQueryElement(CdmQuery* p_pCdmQuery, EdmQueryElementType p_eDmQueryElementType);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:54:50 2005-------*
     * @method  CdmQueryElement::CdmQueryElement              // public                            *
     * @return                                                //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @param   EdmQueryElementType p_eDmQueryElementType     //                                   *
     * @param   EdmQueryCompareType p_eDmQueryCompareType     //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Sa 20. Aug 10:54:50 2005----------*/
    CdmQueryElement(CdmQuery* p_pCdmQuery,
                    EdmQueryElementType p_eDmQueryElementType,
                    EdmQueryCompareType p_eDmQueryCompareType);

    /** +-=---------------------------------------------------------Di 20. Nov 11:10:33 2012-------*
     * @method  CdmQueryElement::CdmQueryElement              // public                            *
     * @return                                                //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @param   EdmQueryElementType p_eDmQueryElementType     //                                   *
     * @param   EdmQueryCompareType p_eDmQueryCompareType     //                                   *
     * @param   QVariant p_qVariant                           // change of OWnership!!!            *
     * @param   QString p_qstrKeyname                         //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:10:33 2012----------*/
    CdmQueryElement(CdmQuery* p_pCdmQuery,
                    EdmQueryElementType p_eDmQueryElementType,
                    EdmQueryCompareType p_eDmQueryCompareType,
                    QVariant p_qVariant,
                    QString p_qstrKeyname);

    CdmQueryElement(CdmQuery* p_pCdmQuery, QString p_qstrCondition);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:55:00 2005-------*
     * @method  CdmQueryElement::CdmQueryElement              // public                            *
     * @return                                                //                                   *
     * @param   CdmQuery* p_pCdmQuery                         //                                   *
     * @param   QDomElement& p_rqDomElement                   //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Sa 20. Aug 10:55:00 2005----------*/
    CdmQueryElement(CdmQuery* p_pCdmQuery, QDomElement &p_rqDomElement);

    CdmQueryElement(CdmQuery* p_pCdmQuery, QVariantMap &p_rqvHash);

    /** +-=---------------------------------------------------------Sa 20. Aug 12:48:38 2005--------*
     * @method  CdmQueryElement::~CdmQueryElement             // public, virtual                    *
     * @return  void                                          //                                    *
     * @comment The Destructor of Class CdmQueryElement                                             *
     *----------------last changed: -----------------------------Sa 20. Aug 12:48:38 2005-----------*/
    virtual ~CdmQueryElement();

    /** +-=---------------------------------------------------------So 10. Feb 10:08:44 2013-------*
     * @method  CdmQueryElement::XmlExport                    // public, const                     *
     * @return  void                                          //                                   *
     * @param   QDomDocument& p_rqdDomDocument                //                                   *
     * @param   QDomElement& p_rqdeElement                    //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:08:44 2013----------*/
    void XmlExport(QDomDocument &p_rqdDomDocument, QDomElement &p_rqdeElement) const;

    /** +-=---------------------------------------------------------Mi 11. Mai 15:38:21 2011-------*
     * @method  CdmQueryElement::GetComplexity                // public                            *
     * @return  int                                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Mai 15:38:21 2011----------*/
    int GetComplexity() const;

    QVariant GetVariant() const;

    CdmQueryElement* GetParent() const;
    bool HasParent() const;



public slots:
    /** +-=---------------------------------------------------------So 10. Feb 17:47:34 2013-------*
     * @method  CdmQueryElement::GetCompareType               // public, const, slots              *
     * @return  EdmQueryCompareType                           //                                   *
     * @comment This method returns the comparetype of the query element.                          *
     *----------------last changed: -----------------------------So 10. Feb 17:47:34 2013----------*/
    EdmQueryCompareType GetCompareType() const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:02:41 2012-------*
     * @method  CdmQueryElement::GetQueryElementType          // public, slots                     *
     * @return  EdmQueryElementType                           //                                   *
     * @comment This method returns the queryelement type.                                         *
     *----------------last changed: -----------------------------Di 20. Nov 11:02:41 2012----------*/
    EdmQueryElementType GetQueryElementType() const;

    /** +-=---------------------------------------------------------So 10. Feb 10:07:32 2013-------*
     * @method  CdmQueryElement::GetChildList                 // public, const, slots              *
     * @return  void                                          //                                   *
     * @param   QList<CdmQueryElement*>& p_rqvlChilds   //                                   *
     * @comment This method fills the refernece with childs.                                       *
     *----------------last changed: -----------------------------So 10. Feb 10:07:32 2013----------*/
    void GetChildList(QList<CdmQueryElement*> &p_rqvlChilds) const;

    /** +-=---------------------------------------------------------So 10. Feb 10:07:40 2013-------*
     * @method  CdmQueryElement::GetCompareKeyname            // public, const, slots              *
     * @return  QString                                       //                                   *
     * @comment This method reutrns the compare keyname.                                           *
     *----------------last changed: -----------------------------So 10. Feb 10:07:40 2013----------*/
    QString GetCompareKeyname() const;

    /** +-=---------------------------------------------------------So 10. Feb 10:08:32 2013-------*
     * @method  CdmQueryElement::GetValueType                 // public, const, slots              *
     * @return  EdmValue                                      //                                   *
     * @comment This method returns the Value for this queryelement.                               *
     *----------------last changed: -----------------------------So 10. Feb 10:08:32 2013----------*/
    EdmValueType GetValueType() const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:17:46 2012-------*
     * @method  CdmQueryElement::AddChild                     // public, slots                     *
     * @return  void                                          //                                   *
     * @param   CdmQueryElement* p_pCdmQueryElement           //                                   *
     * @comment This method adds an child to the query element.                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:17:46 2012----------*/
    void AddChild(CdmQueryElement* p_pCdmQueryElement);

    /** +-=---------------------------------------------------------Di 20. Nov 11:20:28 2012-------*
     * @method  CdmQueryElement::SetComparisonValue           // public, slots                     *
     * @return  void                                          //                                   *
     * @param   QString p_qstrKeyname                         //                                   *
     * @param   QVariant p_qvValue                            //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:20:28 2012----------*/
    void SetComparisonValue(QString p_qstrKeyname, QVariant p_qvValue);

    void SetComparisonValue(QString p_qstrKeyname, bool p_bValue);
    void SetComparisonValue(QString p_qstrKeyname, int p_iValue);
    void SetComparisonValue(QString p_qstrKeyname, long p_lValue);
    void SetComparisonValue(QString p_qstrKeyname, float p_fValue);

    /** +-=---------------------------------------------------------Di 20. Nov 11:20:47 2012-------*
     * @method  CdmQueryElement::SetComparisonValue           // public, slots                     *
     * @return  void                                          //                                   *
     * @param   QString p_qstrKeyname                         //                                   *
     * @param   QList<QVariant> p_qvlList               //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:20:47 2012----------*/
    void SetComparisonValue(QString p_qstrKeyname, QList<QVariant> p_qvlList);

    /** +-=---------------------------------------------------------Di 20. Nov 11:17:34 2012-------*
     * @method  CdmQueryElement::SetVariant                   // public, slots                     *
     * @return  void                                          //                                   *
     * @param   QVariant p_pqVariant                          //                                   *
     * @comment This method sets the Variant of the query element. This method is not a part of    *
     *          the official API. It shouldn't be used outside of WMS. This method makes a         *
     *          transfer of ownership of the variant pointer.                                      *
     *----------------last changed: -----------------------------Di 20. Nov 11:17:34 2012----------*/
    void SetVariant(QVariant p_pqVariant);

    void SetValue(QVariant p_pqVariant);

    /** +-=---------------------------------------------------------So 10. Feb 10:07:48 2013-------*
     * @method  CdmQueryElement::GetValue                     // public, const, slots              *
     * @return  QVariant                                      //                                   *
     * @comment This method returns the Value.                                                     *
     *----------------last changed: -----------------------------So 10. Feb 10:07:48 2013----------*/
    QVariant GetValue() const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:17:22 2012-------*
     * @method  CdmQueryElement::SetKeyname                   // public, slots                     *
     * @return  void                                          //                                   *
     * @param   QString p_qstrKeyname                         //                                   *
     * @comment This method sets the keyname of the comparison value.This method should only be    *
     *          used by internal method, this method is not a part of the official API.            *
     *----------------last changed: -----------------------------Di 20. Nov 11:17:22 2012----------*/
    void SetKeyname(QString p_qstrKeyname);

    /** +-=---------------------------------------------------------Di 20. Nov 11:02:31 2012-------*
     * @method  CdmQueryElement::SetCompareType               // public, slots                     *
     * @return  void                                          //                                   *
     * @param   EdmQueryCompareType p_eDmQueryCompareType     //                                   *
     * @comment This method sets the comparetype of the query.                                     *
     *----------------last changed: -----------------------------Di 20. Nov 11:02:31 2012----------*/
    void SetCompareType(EdmQueryCompareType p_eDmQueryCompareType);

    /** +-=---------------------------------------------------------Di 20. Nov 11:02:52 2012-------*
     * @method  CdmQueryElement::SetQueryElementType          // public, slots                     *
     * @return  void                                          //                                   *
     * @param   EdmQueryElementType p_eDmQueryElementType     //                                   *
     * @comment This method sets the element type of the query.                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:02:52 2012----------*/
    void SetQueryElementType(EdmQueryElementType p_eDmQueryElementType);

    /** +-=---------------------------------------------------------Di 20. Nov 11:17:04 2012-------*
     * @method  CdmQueryElement::GetQuery                     // public, slots                     *
     * @return  CdmQuery*                                     //                                   *
     * @comment returns the query main object.                                                     *
     *----------------last changed: -----------------------------Di 20. Nov 11:17:04 2012----------*/
    CdmQuery* GetQuery() const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:21:30 2012-------*
     * @method  CdmQueryElement::GetSubQuery                  // public, slots                     *
     * @return  CdmQuery*                                     //                                   *
     * @comment This method returns the subquery of this element.                                  *
     *----------------last changed: -----------------------------Di 20. Nov 11:21:30 2012----------*/
    CdmQuery* GetSubQuery() const;

    /** +-=---------------------------------------------------------Di 20. Nov 11:21:55 2012-------*
     * @method  CdmQueryElement::GetList                      // public, slots                     *
     * @return  QList<QVariant>&                        //                                   *
     * @comment This method returns the stringlist of the element.                                 *
     *----------------last changed: -----------------------------Di 20. Nov 11:21:55 2012----------*/
    QList<QVariant>& GetList();

    /** +-=---------------------------------------------------------Di 20. Nov 11:18:55 2012-------*
     * @method  CdmQueryElement::IsValueMember                // public, slots                     *
     * @return  bool                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 20. Nov 11:18:55 2012----------*/
    bool IsValueMember() const;

    /** +-=---------------------------------------------------------So 10. Feb 10:10:35 2013-------*
     * @method  CdmQueryElement::GetConditionAsString         // public, const, slots              *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:10:35 2013----------*/
    QString GetConditionAsString() const;

    /** +-=---------------------------------------------------------So 10. Feb 10:10:14 2013-------*
     * @method  CdmQueryElement::GetCompareTypeAsString       // public, const, slots              *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------So 10. Feb 10:10:14 2013----------*/
    QString GetCompareTypeAsString() const;

    static QString CompareTypeToString(EdmQueryCompareType p_eDmQueryCompareType);

    void SetSubQuery(QString p_qstrKeyname, CdmQuery* p_pCdmQuery);

    bool IsThisCompare() const;

    bool HasSubQuery() const;

    bool IsSubQueryEnhanced() const;



private:
    /** +-=---------------------------------------------------------Sa 20. Aug 10:58:02 2005-------*
     * @method  CdmQueryElement::XmlImport                    // private                           *
     * @return  void                                          //                                   *
     * @param   QDomElement& p_rqDomElement                   //                                   *
     * @comment imports xml datas.                                                                 *
     *----------------last changed: -----------------------------Sa 20. Aug 10:58:02 2005----------*/
    void XmlImport(QDomElement& p_rqDomElement);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:57:47 2005-------*
     * @method  CdmQueryElement::XmlImportChilds              // private                           *
     * @return  void                                          //                                   *
     * @param   QDomElement& p_rqDomElement                   //                                   *
     * @comment This method imports the child queryelements from xml.                              *
     *----------------last changed: -----------------------------Sa 20. Aug 10:57:47 2005----------*/
    void XmlImportChilds(QDomElement& p_rqDomElement);

    void SetParent(CdmQueryElement *p_pParent);

    /** +-=---------------------------------------------------------Sa 20. Aug 10:57:28 2005-------*
     * @method  CdmQueryElement::FindValue                    // private                           *
     * @return  void                                          //                                   *
     * @comment This method finds the Value with the help of the keyname.                          *
     *----------------last changed: -----------------------------Sa 20. Aug 10:57:28 2005----------*/
    void FindValue();

    /** +-=---------------------------------------------------------Fr 12. Nov 15:59:21 2010-------*
     * @method  CdmQueryElement::FindValue                    // private                           *
     * @return  bool                                          //                                   *
     * @param   QString p_qstrKeyname                         //                                   *
     * @comment This method finds the Value with the help of the keyname.                          *
     *----------------last changed: -----------------------------Fr 12. Nov 15:59:21 2010----------*/
    bool FindValue(QString p_qstrKeyname);

    /** +-=---------------------------------------------------------Mo 11. Feb 09:27:27 2013-------*
     * @method  CdmQueryElement::CreateSubQueryFromMember     // private                           *
     * @return  void                                          //                                   *
     * @param   const CdmMember* p_pCdmMember                 //                                   *
     * @param   QString p_qstrSubMemberName                   //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mo 11. Feb 09:27:27 2013----------*/
    void CreateSubQueryFromMember(const CdmMember* p_pCdmMember, QString p_qstrSubMemberName);

    /** +-=---------------------------------------------------------Mi 11. Jul 09:39:21 2012-------*
     * @method  CdmQueryElement::ParseCondition               // private                           *
     * @return  void                                          //                                   *
     * @param   QString p_qstrCondition                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 09:39:21 2012----------*/
    void ParseCondition(QString p_qstrCondition);

    /** +-=---------------------------------------------------------Mi 11. Jul 09:45:02 2012-------*
     * @method  CdmQueryElement::ParseChildConditions         // private                           *
     * @return  void                                          //                                   *
     * @param   QString p_qstrCondition                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 09:45:02 2012----------*/
    void ParseChildConditions(QString p_qstrCondition);

    /** +-=---------------------------------------------------------Mi 11. Jul 09:43:57 2012-------*
     * @method  CdmQueryElement::ParseCompareCondition        // private                           *
     * @return  void                                          //                                   *
     * @param   QString p_qstrCondition                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 09:43:57 2012----------*/
    void ParseCompareCondition(QString p_qstrCondition);

    /** +-=---------------------------------------------------------Mi 11. Jul 10:09:50 2012-------*
     * @method  CdmQueryElement::FindCompareElement           // private                           *
     * @return  int                                           //                                   *
     * @param   QString p_qstrCompareElement                  //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 10:09:50 2012----------*/
    int FindCompareElement(QString p_qstrCompareElement);

    /** +-=---------------------------------------------------------Mi 11. Jul 10:24:44 2012-------*
     * @method  CdmQueryElement::GetCompareElementLength      // private                           *
     * @return  int                                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 10:24:44 2012----------*/
    int GetCompareElementLength();

    /** +-=---------------------------------------------------------Mi 11. Jul 10:48:13 2012-------*
     * @method  CdmQueryElement::SetInNotInValuesForComparision // private                         *
     * @return  void                                          //                                   *
     * @param   QString p_qstrFirst                           //                                   *
     * @param   QString p_qstrSecond                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 11. Jul 10:48:13 2012----------*/
    void SetInNotInValuesForComparision(QString p_qstrFirst, QString p_qstrSecond);

    /** +-=---------------------------------------------------------Do 23. Aug 14:38:47 2012-------*
     * @method  CdmQueryElement::AnalyzeCompare               // private                           *
     * @return  void                                          //                                   *
     * @param   QString p_qstrFirst                           //                                   *
     * @param   QString p_qstrSecond                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 23. Aug 14:38:47 2012----------*/
    void AnalyzeCompare(QString p_qstrFirst, QString p_qstrSecond);
    const CdmMember *GetMember(QString p_qstrKeyname);
};

#endif //
