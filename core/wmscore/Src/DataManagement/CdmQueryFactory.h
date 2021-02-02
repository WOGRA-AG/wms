#ifndef CdmQueryFactory_H
#define CdmQueryFactory_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QObject>
#include <QString>

// Own Includes
#include "datamanager.h"
#include "CdmObjectContainer.h"
#include "CdmQueryElement.h"
#include "CdmQueryResultElement.h"
#include "antlr4-common.h"


// Forwards
class CdmQuery;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the Query builder. It creates a CdmQuery Object by parsing a string
 */
class WMSMANAGER_API CdmQueryFactory : public QObject
{
    Q_OBJECT

private:
    CdmQuery* m_pCdmQuery;
    QString m_qstrFromReference;
    CdmObjectContainer* m_rpContainer;



private:
    /** +-=---------------------------------------------------------Di 10. Jul 14:31:50 2012-------*
     * @method  CdmQueryFactory::CdmQueryFactory              // public                            *
     * @return                                                //                                   *
     * @param   QString p_qstrQuery                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Di 10. Jul 14:31:50 2012----------*/
    CdmQueryFactory();
    virtual ~CdmQueryFactory();

public:
    static CdmQuery* ParseString(QString p_qstrQuery, CdmObjectContainer* p_pContainer=nullptr);
    static CdmQuery* ParseTree(antlr4::tree::ParseTree* p_pAntlrTree, CdmObjectContainer* p_pContainer=nullptr);



private:
    void SetContainer(CdmObjectContainer* p_pContainer);

    bool AntlrParser(antlr4::tree::ParseTree* p_pAntlrTree);

    bool AntlrParserSelect(antlr4::tree::ParseTree* p_pAntlrTree);
    bool AntlrParserInsert(antlr4::tree::ParseTree* p_pAntlrTree);
    bool AntlrParserUpdate(antlr4::tree::ParseTree* p_pAntlrTree);
    bool AntlrParserDelete(antlr4::tree::ParseTree* p_pAntlrTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:45 2013-------*
     * @method  CdmQueryFactorySelect::ParseSelectTree        // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:45 2013----------*/
    void ParseSelectTree(antlr4::tree::ParseTree* p_pTree);

    bool CheckQueryPointer(bool p_bEnhanced=false);
    void AddFromClause();

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:45 2013-------*
     * @method  CdmQueryFactorySelect::ParseInsertTree        // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:45 2013----------*/
    void ParseInsertTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:45 2013-------*
     * @method  CdmQueryFactorySelect::ParseUpdateTree        // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:45 2013----------*/
    void ParseUpdateTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:45 2013-------*
     * @method  CdmQueryFactorySelect::ParseValueTree        // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:45 2013----------*/
    void ParseValueTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:45 2013-------*
     * @method  CdmQueryFactorySelect::ParseSetTree        // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:45 2013----------*/
    void ParseSetTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:45:59 2013-------*
     * @method  CdmQueryFactorySelect::ParseFromTree          // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:45:59 2013----------*/
    void ParseFromTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 15. Feb 16:25:15 2013-------*
     * @method  CdmQueryFactorySelect::ParseWhereTree         // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @param   CdmQueryElement* p_pParent = nullptr          //                                   *
     * @param   int p_iRecursionLevel = 0                     //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 15. Feb 16:25:15 2013----------*/
    void ParseWhereTree(antlr4::tree::ParseTree* p_pTree,
                        CdmQueryElement* p_pParent = nullptr,
                        int p_iRecursionLevel = 0);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:49:29 2013-------*
     * @method  CdmQueryFactorySelect::ParseGroupByTree       // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:49:29 2013----------*/
    void ParseGroupByTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:52:42 2013-------*
     * @method  CdmQueryFactorySelect::ParseOrderByTree       // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:52:42 2013----------*/
    void ParseOrderByTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 25. Jan 15:52:57 2013-------*
     * @method  CdmQueryFactorySelect::ParseLimitTree         // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 25. Jan 15:52:57 2013----------*/
    void ParseLimitTree(antlr4::tree::ParseTree* p_pTree);

    /** +-=---------------------------------------------------------Fr 15. Feb 15:13:52 2013-------*
     * @method  CdmQueryFactorySelect::ParseValueCompare      // private                           *
     * @return  void                                          //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @param   CdmQueryElement* p_pParent = nullptr          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 15. Feb 15:13:52 2013----------*/
    void ParseValueCompare(antlr4::tree::ParseTree* p_pTree,
                           CdmQueryElement* p_pParent = nullptr);

    void ParseValueCompareWithInOrNotInCondition(antlr4::tree::ParseTree* p_pTree,
                                                 CdmQueryElement* p_pParent);
    void ParseValueCompareWithLikeOrNotLikeCondition(antlr4::tree::ParseTree* p_pTree,
                                                     CdmQueryElement* p_pParent);
    void ParseValueCompareWithConditionAndValue(antlr4::tree::ParseTree* p_pTree,
                                                EdmQueryCompareType eCompareType,
                                                CdmQueryElement* p_pParent);

    /** +-=---------------------------------------------------------Fr 15. Feb 15:44:01 2013-------*
    * @method  CdmQueryFactorySelect::ReadComparyType         // private                           *
     * @return  EdmQueryCompareType                           //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 15. Feb 15:44:01 2013----------*/
    EdmQueryCompareType ReadComparyType(antlr4::RuleContext* p_pTree);

    /** +-=---------------------------------------------------------Fr 15. Feb 16:23:39 2013-------*
     * @method  CdmQueryFactorySelect::ReadComparisionValue   // private                           *
     * @return  QVariant                                      //                                   *
     * @param   antlr4::tree::ParseTree* p_pTree              //                                   *
     * @param   EdmValue &p_eValue                            //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Fr 15. Feb 16:23:39 2013----------*/
    QVariant ReadComparisionValue(antlr4::tree::ParseTree* p_pTree, EdmValueType &p_eValue);
    
    /** +-=---------------------------------------------------------Do 14. Mrz 15:00:17 2013-------*
     * @method  CdmQueryFactorySelect::ReplaceApostrophe      // private                           *
     * @return  void                                          //                                   *
     * @param   QString &p_qstrText                           //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 14. Mrz 15:00:17 2013----------*/
    void ReplaceApostrophe(QString &p_qstrText);
};

#endif // CdmQueryFactory_H
