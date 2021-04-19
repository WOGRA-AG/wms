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
    void ParseSelectTree(antlr4::tree::ParseTree* p_pTree);
    bool CheckQueryPointer(bool p_bEnhanced=false);
    void AddFromClause();
    void ParseInsertTree(antlr4::tree::ParseTree* p_pTree);
    void ParseUpdateTree(antlr4::tree::ParseTree* p_pTree);
    void ParseValueTree(antlr4::tree::ParseTree* p_pTree);
    void ParseSetTree(antlr4::tree::ParseTree* p_pTree);
    void ParseFromTree(antlr4::tree::ParseTree* p_pTree);
    void ParseWhereTree(antlr4::tree::ParseTree* p_pTree,
                        CdmQueryElement* p_pParent = nullptr,
                        int p_iRecursionLevel = 0);
    void ParseGroupByTree(antlr4::tree::ParseTree* p_pTree);
    void ParseOrderByTree(antlr4::tree::ParseTree* p_pTree);
    void ParseLimitTree(antlr4::tree::ParseTree* p_pTree);
    void ParseValueCompare(antlr4::tree::ParseTree* p_pTree,
                           CdmQueryElement* p_pParent = nullptr);
    void ParseValueCompareWithInOrNotInCondition(antlr4::tree::ParseTree* p_pTree,
                                                 CdmQueryElement* p_pParent);
    void ParseValueCompareWithLikeOrNotLikeCondition(antlr4::tree::ParseTree* p_pTree,
                                                     CdmQueryElement* p_pParent);
    void ParseValueCompareWithConditionAndValue(antlr4::tree::ParseTree* p_pTree,
                                                EdmQueryCompareType eCompareType,
                                                CdmQueryElement* p_pParent);
    EdmQueryCompareType ReadComparyType(antlr4::RuleContext* p_pTree);
    QVariant ReadComparisionValue(antlr4::tree::ParseTree* p_pTree, EdmValueType &p_eValue);
    void ReplaceApostrophe(QString &p_qstrText);
};

#endif // CdmQueryFactory_H
