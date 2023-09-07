#ifndef NOMINMAX
#define NOMINMAX
#endif

// System and QT Includes

// WMS Commons Includes
#include "CwmsUtilities.h"

// antlr4::Lexer::emit() : Avoid conflict with emit keyword
#undef emit
// own Includes
//#include "antlr4-runtime.h"
#include "WmsQL1Lexer.h"
#include "WmsQL1Parser.h"
#include "CdmAntlrErrorListener.h"
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmQuery.h"
#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmQueryFactory.h"



using namespace antlr4;

CdmQueryFactory::CdmQueryFactory()
    : m_pCdmQuery(nullptr),
      m_qstrFromReference(),
      m_rpContainer(nullptr)
{
}

CdmQueryFactory::~CdmQueryFactory()
{
}

void CdmQueryFactory::SetContainer(CdmObjectContainer* p_pContainer)
{
    m_rpContainer = p_pContainer;
}

bool CdmQueryFactory::AntlrParser(tree::ParseTree* p_pAntlrTree)
{
    bool bRet = false;
    WmsQL1Parser::StatementContext* pTree = dynamic_cast<WmsQL1Parser::StatementContext*>(p_pAntlrTree);

    if (pTree)
    {
        tree::ParseTree* pSelect = pTree->select_statement();
        tree::ParseTree* pInsert = pTree->insert_statement();
        tree::ParseTree* pUpdate = pTree->update_statement();
        tree::ParseTree* pDelete = pTree->delete_statement();

        if (pSelect)
        {
            bRet = AntlrParserSelect(pSelect);
        }
        else if (pInsert)
        {
            bRet = AntlrParserInsert(pInsert);
        }
        else if (pUpdate)
        {
            bRet = AntlrParserUpdate(pUpdate);
        }
        else if (pDelete)
        {
            bRet = AntlrParserDelete(pDelete);
        }
        else
        {
            bRet = false;
        }
    }

    return bRet;
}

bool CdmQueryFactory::AntlrParserSelect(tree::ParseTree* p_pAntlrTree)
{
    bool bRet = false;

    WmsQL1Parser::Select_statementContext* pTree = dynamic_cast<WmsQL1Parser::Select_statementContext*>(p_pAntlrTree);

    if (pTree)
    {
        if (pTree->from_clause())
        {
            ParseFromTree(pTree->from_clause());
        }

        if (CheckQueryPointer())
        {
            if (pTree->select_clause())
            {
                bRet = true;
                ParseSelectTree(pTree->select_clause());
            }

            WmsQL1Parser::Where_clauseContext* pWhere = pTree->where_clause();

            if (pWhere && pWhere->where_expression())
            {
                ParseWhereTree(pWhere->where_expression());
            }

            if (pTree->groupby_clause())
            {
                ParseGroupByTree(pTree->groupby_clause());
            }

            if (pTree->orderby_clause())
            {
                ParseOrderByTree(pTree->orderby_clause());
            }

            if (pTree->limit_clause())
            {
                ParseLimitTree(pTree->limit_clause());
            }
        }
        else
        {
            ERR("From value is missing in query.");
        }
    }
    else
    {
        QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
        ERR("Tree is not a select statement!\nTree: " + qstrTree);
    }

    return bRet;
}

bool CdmQueryFactory::AntlrParserInsert(tree::ParseTree* p_pAntlrTree)
{
    bool bRet = false;

    WmsQL1Parser::Insert_statementContext* pTree = dynamic_cast<WmsQL1Parser::Insert_statementContext*>(p_pAntlrTree);

    if (pTree)
    {
        if (pTree->insert_clause())
        {
            QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
            ERR("Insert is not implemented yet!\nTree: " + qstrTree);
            //ParseInsertTree(pTree->insert_clause());
        }

        if (CheckQueryPointer())
        {
            if (pTree->value_clause())
            {
                bRet = true;
                ParseValueTree(pTree->value_clause());
            }
            else if (pTree->set_clause())
            {
                bRet = true;
                ParseSetTree(pTree->set_clause());
            }
            else
            {
                ERR("Values to insert are missing in query.");
            }
        }
        else
        {
            ERR("Table to insert into is missing in query.");
        }
    }
    else
    {
        QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
        ERR("Tree is not an insert statement!\nTree: " + qstrTree);
    }

    return bRet;
}

bool CdmQueryFactory::AntlrParserUpdate(tree::ParseTree* p_pAntlrTree)
{
    bool bRet = false;

    WmsQL1Parser::Update_statementContext* pTree = dynamic_cast<WmsQL1Parser::Update_statementContext*>(p_pAntlrTree);

    if (pTree)
    {
        if (pTree->update_clause())
        {
            QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
            ERR("Update is not implemented yet!\nTree: " + qstrTree);
            //ParseUpdateTree(pTree->update_clause());
        }

        if (CheckQueryPointer())
        {
            if (pTree->set_clause())
            {
                bRet = true;
                ParseSetTree(pTree->set_clause());
            }

            WmsQL1Parser::Where_clauseContext* pWhere = pTree->where_clause();

            if (pWhere && pWhere->where_expression())
            {
                ParseWhereTree(pWhere->where_expression());
            }

            if (pTree->orderby_clause())
            {
                ParseOrderByTree(pTree->orderby_clause());
            }

            if (pTree->limit_clause())
            {
                ParseLimitTree(pTree->limit_clause());
            }
        }
        else
        {
            ERR("Table to update is missing in query.");
        }
    }
    else
    {
        QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
        ERR("Tree is not an update statement!\nTree: " + qstrTree);
    }

    return bRet;
}

bool CdmQueryFactory::AntlrParserDelete(tree::ParseTree* p_pAntlrTree)
{
    bool bRet = false;

    WmsQL1Parser::Delete_statementContext* pTree = dynamic_cast<WmsQL1Parser::Delete_statementContext*>(p_pAntlrTree);

    if (pTree)
    {
        if (pTree->from_clause())
        {
            QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
            ERR("Delete is not implemented yet!\nTree: " + qstrTree);
            //ParseFromTree(pTree->from_clause());
        }

        if (CheckQueryPointer())
        {
            if (pTree->delete_clause() && pTree->delete_clause()->DELETE())
            {
                bRet = true;
            }

            WmsQL1Parser::Where_clauseContext* pWhere = pTree->where_clause();

            if (pWhere && pWhere->where_expression())
            {
                ParseWhereTree(pWhere->where_expression());
            }

            if (pTree->orderby_clause())
            {
                ParseOrderByTree(pTree->orderby_clause());
            }

            if (pTree->limit_clause())
            {
                ParseLimitTree(pTree->limit_clause());
            }
        }
        else
        {
            ERR("From value is missing in query.");
        }
    }
    else
    {
        QString qstrTree = QString::fromStdString(p_pAntlrTree->toStringTree());
        ERR("Tree is not a delete statement!\nTree: " + qstrTree);
    }

    return bRet;
}

void CdmQueryFactory::ParseSelectTree(tree::ParseTree* p_pTree)
{
    WmsQL1Parser::Select_clauseContext* pSelect = dynamic_cast<WmsQL1Parser::Select_clauseContext*>(p_pTree);
    if (CHKPTR(pSelect))
    {
        for (WmsQL1Parser::Select_expressionContext* pExpr : pSelect->select_expression())
        {
            if (CHKPTR(pExpr))
            {
                WmsQL1Parser::Aggregate_expressionContext* pAgg = pExpr->aggregate_expression();
                WmsQL1Parser::Object_refContext* pObjectRef = pExpr->object_ref();
                bool distinct = false;
                EdmQueryResultElementMode eMode = eDmQueryResultElementModeNone;

                if (pAgg && pAgg->aggFunc)
                {
                    pObjectRef = pAgg->object_ref();
                    if (pAgg->DISTINCT())
                    {
                        distinct = true;
                    }

                    switch(pAgg->aggFunc->getType())
                    {
                    case WmsQL1Parser::AVG:
                        eMode = eDmQueryResultElementModeAvg;
                        break;
                    case WmsQL1Parser::SUM:
                        eMode = eDmQueryResultElementModeSum;
                        break;
                    case WmsQL1Parser::MIN:
                        eMode = eDmQueryResultElementModeMin;
                        break;
                    case WmsQL1Parser::MAX:
                        eMode = eDmQueryResultElementModeMax;
                        break;
                    case WmsQL1Parser::COUNT:
                        eMode = eDmQueryResultElementModeCount;
                        break;
                    default:
                        eMode = eDmQueryResultElementModeNone;
                        break;
                    }
                }
                else if (pExpr->DISTINCT())
                {
                    distinct = true;
                }

                if (CheckQueryPointer(true))
                {
                    if (pObjectRef)
                    {
                        QString qstrElement = QString::fromStdString(pObjectRef->getText());
                        ReplaceApostrophe(qstrElement);
                        if (distinct)
                        {
                            // TODO: Actually select distinct
                            m_pCdmQuery->AddResultElement(qstrElement, eMode);
                        }
                        else
                        {
                            m_pCdmQuery->AddResultElement(qstrElement, eMode);
                        }
                    }
                    else if (pAgg && pAgg->STAR() && eMode == eDmQueryResultElementModeCount)
                    {
                        m_pCdmQuery->AddResultElement("count", eMode);
                    }
                    else if (pExpr->STAR())
                    {
                        m_pCdmQuery->AddAllMembers();
                    }
                }
            }
        }
    }
}

bool CdmQueryFactory::CheckQueryPointer(bool p_bEnhanced)
{
    bool bRet = false;

    if (m_pCdmQuery)
    {
        bRet = m_pCdmQuery->IsValid();
    }
    else
    {
        m_pCdmQuery = new CdmQuery();

        if (m_rpContainer)
        {
            m_pCdmQuery->SetContainer(m_rpContainer);
        }
        else
        {
            AddFromClause();
        }

        bRet = m_pCdmQuery->IsValid();
    }

    return bRet;
}

void CdmQueryFactory::AddFromClause()
{
    int iPos = m_qstrFromReference.lastIndexOf(".class");

    if (iPos > 0)
    {
        QString qstrClassReference = m_qstrFromReference.left(iPos);
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            CdmClassManager* pClassManager = pManager->GetClassManager();

            if (CHKPTR(pClassManager))
            {
                CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClassReference);

                if (pClass)
                {
                    m_pCdmQuery->SetClass(pClass);
                }
                else
                {
                    m_pCdmQuery->m_bValid = false;
                    ERR("Class reference not found in WQL Reference: " + m_qstrFromReference);
                }
            }
        }
    }
    else
    {
        if (CwmsUtilities::IsNumber(m_qstrFromReference))
        {
            m_pCdmQuery->SetContainerId(m_qstrFromReference.toInt());
        }
        else
        {
            m_pCdmQuery->SetContainer(m_qstrFromReference);
        }
    }
}

void CdmQueryFactory::ParseInsertTree(antlr4::tree::ParseTree *p_pTree)
{
    WmsQL1Parser::Insert_clauseContext* pInsert = dynamic_cast<WmsQL1Parser::Insert_clauseContext*>(p_pTree);
    if (CHKPTR(pInsert))
    {
        tree::ParseTree* pClass = pInsert->class_ref();

        if (CHKPTR(pClass))
        {
            m_qstrFromReference = QString::fromStdString(pClass->getText());
        }

        ReplaceApostrophe(m_qstrFromReference);

        for (WmsQL1Parser::Object_refContext* pMember : pInsert->members)
        {
            if (CHKPTR(pMember))
            {
                QString qstrElement = QString::fromStdString(pMember->getText());
                m_pCdmQuery->AddResultElement(qstrElement);
            }
        }

        if (!m_pCdmQuery->HasResultElements())
        {
            m_pCdmQuery->AddAllMembers();
        }
    }
}

void CdmQueryFactory::ParseUpdateTree(antlr4::tree::ParseTree *p_pTree)
{
    WmsQL1Parser::Update_clauseContext* pUpdate = dynamic_cast<WmsQL1Parser::Update_clauseContext*>(p_pTree);
    if (CHKPTR(pUpdate))
    {
        QVector<WmsQL1Parser::Class_refContext*> qvObjectRefs;
        qvObjectRefs = QVector<WmsQL1Parser::Class_refContext*>::fromStdVector(pUpdate->class_ref());

        if (qvObjectRefs.size() == 1)
        {
            tree::ParseTree* pClass = qvObjectRefs[0];

            if (CHKPTR(pClass))
            {
                m_qstrFromReference = QString::fromStdString(pClass->getText());
            }

            ReplaceApostrophe(m_qstrFromReference);
        }
        else if (qvObjectRefs.size() == 0)
        {
            ERR("Fehlende Quellenangabe\nDie Datenquelle (Objektliste) wurde nicht angegeben.");
        }
        else
        {
            ERR("Zu viele Quellenangabe\nDie Datenquelle (Objektliste) ist nicht eindeutig.");
        }
    }
}

void CdmQueryFactory::ParseValueTree(antlr4::tree::ParseTree *p_pTree)
{
    WmsQL1Parser::Value_clauseContext* pValue = dynamic_cast<WmsQL1Parser::Value_clauseContext*>(p_pTree);
    if (CHKPTR(pValue))
    {
        int iRow = 0;
        for (WmsQL1Parser::Value_listContext* pList : pValue->value_list())
        {
            if (CHKPTR(pList))
            {
                int iColumn = 0;

                for (WmsQL1Parser::Value_refContext* pValueRef : pList->value_ref())
                {
                    if (CHKPTR(pValueRef))
                    {
                        EdmValueType eValue = eDmValueNone;
                        QVariant qvValue = ReadComparisionValue(pValueRef, eValue);

                        if (qvValue.isValid())
                        {
                            if (eValue != eDmValueNone)
                            {
                                m_pCdmQuery->AddResultToColumnInRow(iColumn, iRow, qvValue);
                            }
                            else
                            {
                                ERR("Unknown type for comparision");
                            }
                        }
                        else
                        {
                            QString qstrValueRef = QString::fromStdString(pValueRef->getText());
                            ERR("Value '" + qstrValueRef + "' is empty.");
                        }
                    }
                    ++iColumn;
                }
                ++iRow;
            }
        }
    }
}

void CdmQueryFactory::ParseSetTree(antlr4::tree::ParseTree *p_pTree)
{
    WmsQL1Parser::Set_clauseContext* pSet = dynamic_cast<WmsQL1Parser::Set_clauseContext*>(p_pTree);
    if (CHKPTR(pSet))
    {
        for (WmsQL1Parser::Set_assignmentContext* pAssignment : pSet->set_assignment())
        {
            if (CHKPTR(pAssignment))
            {
                QString qstrKeyname = QString::fromStdString(pAssignment->object_ref()->getText());
                EdmValueType eValue = eDmValueNone;
                QVariant qvValue = ReadComparisionValue(pAssignment->value_ref(), eValue);

                int iColumn = m_pCdmQuery->FindResultElement(qstrKeyname);

                if (iColumn < 0)
                {
                    m_pCdmQuery->AddResultElement(qstrKeyname);
                    iColumn = m_pCdmQuery->FindResultElement(qstrKeyname);
                }

                if (iColumn >= 0)
                {
                    m_pCdmQuery->AddResultToColumnInRow(iColumn, 0, qvValue);
                }
            }
        }
    }
}

void CdmQueryFactory::ParseFromTree(tree::ParseTree* p_pTree)
{
    WmsQL1Parser::From_clauseContext* pFrom = dynamic_cast<WmsQL1Parser::From_clauseContext*>(p_pTree);
    if (CHKPTR(pFrom))
    {
        QVector<WmsQL1Parser::Class_refContext*> qvObjectRefs;
        qvObjectRefs = QVector<WmsQL1Parser::Class_refContext*>::fromStdVector(pFrom->class_ref());

        if (qvObjectRefs.size() == 1)
        {
            tree::ParseTree* pClass = qvObjectRefs[0];

            if (CHKPTR(pClass))
            {
                m_qstrFromReference = QString::fromStdString(pClass->getText());
            }

            ReplaceApostrophe(m_qstrFromReference);
        }
        else if (qvObjectRefs.size() == 0)
        {
            ERR("Fehlende Quellenangabe\nDie Datenquelle (Objektliste) wurde nicht angegeben.");
        }
        else
        {
            ERR("Zu viele Quellenangabe\nDie Datenquelle (Objektliste) ist nicht eindeutig.");
        }
    }
}

void CdmQueryFactory::ParseWhereTree(tree::ParseTree* p_pTree,
                                     CdmQueryElement* p_pParent,
                                     int p_iRecursionLevel)
{
    if (p_iRecursionLevel > 500)
    {
        return;
    }

    WmsQL1Parser::Where_expressionContext* pWhere = dynamic_cast<WmsQL1Parser::Where_expressionContext*>(p_pTree);
    if (CHKPTR(pWhere))
    {
        Token* pTokenOp = pWhere->logical_operator;
        if (pTokenOp && pTokenOp->getType() == WmsQL1Parser::AND) // AND
        {
            CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeAnd);

            if (p_pParent)
            {
                p_pParent->AddChild(pElement);
            }
            else
            {
                m_pCdmQuery->SetQueryElement(pElement);
            }

            for (WmsQL1Parser::Where_expressionContext* pCond : pWhere->where_expression())
            {
                ParseWhereTree(pCond, pElement, ++p_iRecursionLevel);
            }
        }
        else if (pTokenOp && pTokenOp->getType() == WmsQL1Parser::OR) // OR
        {
            CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeOr);

            if (p_pParent)
            {
                p_pParent->AddChild(pElement);
            }
            else
            {
                m_pCdmQuery->SetQueryElement(pElement);
            }

            for (WmsQL1Parser::Where_expressionContext* pCond : pWhere->where_expression())
            {
                ParseWhereTree(pCond, pElement, ++p_iRecursionLevel);
            }
        }
        else if (pWhere->where_expression().size() == 1) // Brackets with or without NOT
        {
            WmsQL1Parser::Where_expressionContext* pInner = pWhere->where_expression(0);
            ParseWhereTree(pInner, p_pParent, ++p_iRecursionLevel);
        }
        else if (pWhere->cond_expression()) // Valuecompare
        {
            ParseValueCompare(pWhere->cond_expression(), p_pParent);
        }
    }
}

void CdmQueryFactory::ParseValueCompare(tree::ParseTree* p_pTree, CdmQueryElement* p_pParent)
{
    WmsQL1Parser::Cond_expressionContext* pCond = dynamic_cast<WmsQL1Parser::Cond_expressionContext*>(p_pTree);
    if (CHKPTR(pCond) && CheckQueryPointer())
    {
        if (pCond->in_condition())
        {
            ParseValueCompareWithInOrNotInCondition(pCond->in_condition(), p_pParent);
        }
        else if (pCond->like_condition())
        {
            ParseValueCompareWithLikeOrNotLikeCondition(pCond->like_condition(), p_pParent);
        }
        else if (pCond->compare_condition())
        {
            EdmQueryCompareType eCompareType = ReadComparyType(pCond->compare_condition());
            ParseValueCompareWithConditionAndValue(pCond->compare_condition(), eCompareType, p_pParent);
        }
        else
        {
            ERR("Kein Vergleichsoperator vorhanden!");
        }
    }
}

void CdmQueryFactory::ParseValueCompareWithInOrNotInCondition(tree::ParseTree* p_pTree,
                                                              CdmQueryElement* p_pParent)
{
    WmsQL1Parser::In_conditionContext* pTree = dynamic_cast<WmsQL1Parser::In_conditionContext*>(p_pTree);
    if (CHKPTR(pTree))
    {
        WmsQL1Parser::Object_refContext* pMember = pTree->object_ref();
        WmsQL1Parser::In_itemsContext* pItems = pTree->in_items();
        EdmQueryCompareType eCompareType = ReadComparyType(pTree);
        QVariantList qvlComparisonValues;
        EdmValueType eValue = eDmValueNone;

        if (pMember && pItems)
        {
            QString qstrMember = QString::fromStdString(pMember->getText());

            for (RuleContext* item : pItems->arithmetic_expression())
            {
                qvlComparisonValues.append(ReadComparisionValue(item, eValue));
            }
            for (RuleContext* item : pItems->string_expression())
            {
                qvlComparisonValues.append(ReadComparisionValue(item, eValue));
            }

            CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeCompare, eCompareType);
            pElement->SetComparisonValue(qstrMember, qvlComparisonValues);

            if (p_pParent)
            {
                p_pParent->AddChild(pElement);
            }
            else if (m_pCdmQuery)
            {
                m_pCdmQuery->SetQueryElement(pElement);
            }
        }
    }
}

void CdmQueryFactory::ParseValueCompareWithLikeOrNotLikeCondition(tree::ParseTree* p_pTree,
                                                                  CdmQueryElement* p_pParent)
{
    WmsQL1Parser::Like_conditionContext* pTree = dynamic_cast<WmsQL1Parser::Like_conditionContext*>(p_pTree);
    if (CHKPTR(pTree))
    {
        RuleContext* pFirst = pTree->object;
        RuleContext* pSecond = pTree->compareString;
        QString qstrMember = QString::fromStdString(pFirst->getText());
        EdmQueryCompareType eCompareType = ReadComparyType(pTree);

        EdmValueType eValue = eDmValueNone;
        QVariant qvComparisionValue = ReadComparisionValue(pSecond, eValue);

        if (qvComparisionValue.isValid())
        {
            CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeCompare, eCompareType);

            switch(eValue)
            {
            case eDmValueString:
                pElement->SetComparisonValue(qstrMember, qvComparisionValue.toString());
                break;
            default:
                WARNING("Compare with Like, but not String type");
                break;
            }

            if (p_pParent)
            {
                p_pParent->AddChild(pElement);
            }
            else if (m_pCdmQuery)
            {
                m_pCdmQuery->SetQueryElement(pElement);
            }
        }
        else
        {
            ERR("Invalid value for comparison");
        }
    }
}

void CdmQueryFactory::ParseValueCompareWithConditionAndValue(tree::ParseTree* p_pTree,
                                                             EdmQueryCompareType eCompareType,
                                                             CdmQueryElement* p_pParent)
{
    WmsQL1Parser::Compare_conditionContext* pTree = dynamic_cast<WmsQL1Parser::Compare_conditionContext*>(p_pTree);
    if (CHKPTR(pTree))
    {
        RuleContext* pFirst = pTree->object_ref(0);
        tree::ParseTree* pSecond = pTree->children[pTree->children.size()-1];

        if (pFirst != nullptr && pSecond != nullptr)
        {
            QString qstrMember = QString::fromStdString(pFirst->getText());

            EdmValueType eValue = eDmValueNone;
            QVariant qvComparisionValue = ReadComparisionValue(pSecond, eValue);

            if (qvComparisionValue.isValid())
            {
                CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeCompare, eCompareType);

                switch(eValue)
                {
                case eDmValueString:
                    pElement->SetComparisonValue(qstrMember, qvComparisionValue.toString());
                    break;
                case eDmValueInt:
                    pElement->SetComparisonValue(qstrMember, qvComparisionValue.toInt());
                    break;
                case eDmValueFloat:
                    pElement->SetComparisonValue(qstrMember, qvComparisionValue.toFloat());
                    break;
                case eDmValueDate:
                    pElement->SetComparisonValue(qstrMember, qvComparisionValue.toDate());
                    break;
                case eDmValueBool:
                    pElement->SetComparisonValue(qstrMember, qvComparisionValue.toBool());
                    break;
                default:
                    WARNING("Unknown type for comparision");
                    break;
                }

                if (p_pParent)
                {
                    p_pParent->AddChild(pElement);
                }
                else if (m_pCdmQuery)
                {
                    m_pCdmQuery->SetQueryElement(pElement);
                }
            }
            // IS NULL case
            else if ((eCompareType == eDmQueryCompareTypeNull || eCompareType == eDmQueryCompareTypeNotNull)
                     && qvComparisionValue.isNull()
                     && eValue == eDmValueNone)
            {
                CdmQueryElement* pElement = new CdmQueryElement(m_pCdmQuery, eDmQueryElementTypeCompare, eCompareType);
                pElement->SetComparisonValue(qstrMember, qvComparisionValue);
                if (p_pParent)
                {
                    p_pParent->AddChild(pElement);
                }
                else if (m_pCdmQuery)
                {
                    m_pCdmQuery->SetQueryElement(pElement);
                }
            }
        }
    }
}

EdmQueryCompareType CdmQueryFactory::ReadComparyType(RuleContext* p_pRule)
{
    EdmQueryCompareType eType = eDmQueryCompareTypeNone;

    if (CHKPTR(p_pRule))
    {
        switch (p_pRule->getRuleIndex()) {
        case WmsQL1Parser::RuleIn_condition:
        {
            WmsQL1Parser::In_conditionContext* pInRule = static_cast<WmsQL1Parser::In_conditionContext*>(p_pRule);
            eType = eDmQueryCompareTypeIn;
            if (pInRule->NOT())
            {
                eType = eDmQueryCompareTypeNotIn;
            }
            break;
        }
        case WmsQL1Parser::RuleLike_condition:
        {
            WmsQL1Parser::Like_conditionContext* pLikeRule = static_cast<WmsQL1Parser::Like_conditionContext*>(p_pRule);
            eType = eDmQueryCompareTypeLike;
            if (pLikeRule->NOT())
            {
                eType = eDmQueryCompareTypeNotLike;
            }
            if (pLikeRule->EQ())
            {
                eType = eDmQueryCompareTypeEqual;
            }
            if (pLikeRule->NEQ())
            {
                eType = eDmQueryCompareTypeNotEqual;
            }
            break;
        }
        case WmsQL1Parser::RuleCompare_condition:
        {
            WmsQL1Parser::Compare_conditionContext* pCompareRule = static_cast<WmsQL1Parser::Compare_conditionContext*>(p_pRule);
            if (pCompareRule->compare_sign())
            {
                if (pCompareRule->compare_sign()->EQ())
                {
                    eType = eDmQueryCompareTypeEqual;
                }
                else if (pCompareRule->compare_sign()->LT())
                {
                    eType = eDmQueryCompareTypeSmaller;
                }
                else if (pCompareRule->compare_sign()->GT())
                {
                    eType = eDmQueryCompareTypeLarger;
                }
                else if (pCompareRule->compare_sign()->LEQ())
                {
                    eType = eDmQueryCompareTypeSmallerEqual;
                }
                else if (pCompareRule->compare_sign()->GEQ())
                {
                    eType = eDmQueryCompareTypeLargerEqual;
                }
                else if (pCompareRule->compare_sign()->NEQ())
                {
                    eType = eDmQueryCompareTypeNotEqual;
                }
            }
            else if (pCompareRule->IS())
            {
                eType = eDmQueryCompareTypeNull;
                if (pCompareRule->NOT())
                {
                    eType = eDmQueryCompareTypeNotNull;
                }
            }
            else if (pCompareRule->EQ())
            {
                eType = eDmQueryCompareTypeEqual;
            }
            else if (pCompareRule->NEQ())
            {
                eType = eDmQueryCompareTypeNotEqual;
            }
            break;
        }
        default:
            break;
        }
    }

    return eType;
}

QVariant CdmQueryFactory::ReadComparisionValue(tree::ParseTree* p_pTree, EdmValueType &p_eValue)
{
    QVariant qvValue;

    if (CHKPTR(p_pTree))
    {
        QString qstrTree = QString::fromStdString(p_pTree->getText());

        if (antlrcpp::is<tree::TerminalNode*>(p_pTree))
        {
            tree::TerminalNode* pNode = static_cast<tree::TerminalNode*>(p_pTree);
            if (pNode && pNode->getSymbol())
            {
                switch (pNode->getSymbol()->getType())
                {
                case WmsQL1Parser::STRING_TYPE:
                case WmsQL1Parser::ID:
                case WmsQL1Parser::IDPATH:
                    ReplaceApostrophe(qstrTree);
                    qvValue = QVariant(qstrTree);
                    p_eValue = eDmValueString;
                    break;
                case WmsQL1Parser::FLOAT_TYPE:
                    qvValue = qstrTree.toFloat();
                    p_eValue = eDmValueFloat;
                    break;
                case WmsQL1Parser::INT_TYPE:
                    qvValue = qstrTree.toInt();
                    p_eValue = eDmValueInt;
                    break;
                case WmsQL1Parser::DATE_TYPE:
                    qvValue = QVariant(qstrTree).toDate();
                    p_eValue = eDmValueDate;
                    break;
                case WmsQL1Parser::TRUE:
                    qvValue = true;
                    p_eValue = eDmValueBool;
                    break;
                case WmsQL1Parser::FALSE:
                    qvValue = false;
                    p_eValue = eDmValueBool;
                    break;
                case WmsQL1Parser::NULL_REPR:
                    qvValue = QVariant();
                    p_eValue = eDmValueNone;
                    break;
                }
            }
        }
        else if (antlrcpp::is<ParserRuleContext*>(p_pTree))
        {
            ParserRuleContext* pRule = static_cast<ParserRuleContext*>(p_pTree);
            if (pRule->getRuleIndex() == WmsQL1Parser::RuleString_expression)
            {
                ReplaceApostrophe(qstrTree);
                qvValue = QVariant(qstrTree);
                p_eValue = eDmValueString;
            }
            else if (pRule->getRuleIndex() == WmsQL1Parser::RuleValue_ref)
            {
                for (tree::ParseTree* pItem : tree::Trees::getDescendants(pRule))
                {
                    tree::TerminalNode* pNode = dynamic_cast<tree::TerminalNode*>(pItem);
                    if (pNode && pNode->getSymbol())
                    {
                        qvValue = ReadComparisionValue(pNode, p_eValue);
                        break;
                    }
                }
            }
            else
            {
                for (tree::ParseTree* pItem : tree::Trees::getDescendants(pRule))
                {
                    tree::TerminalNode* pNode = dynamic_cast<tree::TerminalNode*>(pItem);
                    if (pNode && pNode->getSymbol())
                    {
                        qvValue = ReadComparisionValue(pNode, p_eValue);
                        break;
                    }
                }
            }
        }
    }

    return qvValue;
}

void CdmQueryFactory::ParseGroupByTree(tree::ParseTree* p_pTree)
{
    WmsQL1Parser::Groupby_clauseContext* pGroupBy = dynamic_cast<WmsQL1Parser::Groupby_clauseContext*>(p_pTree);
    if (CHKPTR(pGroupBy))
    {
        for (WmsQL1Parser::Object_refContext* pObject : pGroupBy->object_ref())
        {
            if (CHKPTR(pObject))
            {
                QString qstrElement = QString::fromStdString(pObject->getText());
                m_pCdmQuery->AddGroupByElement(qstrElement);
            }
        }
    }
}

void CdmQueryFactory::ParseOrderByTree(tree::ParseTree* p_pTree)
{
    WmsQL1Parser::Orderby_clauseContext* pOrderBy = dynamic_cast<WmsQL1Parser::Orderby_clauseContext*>(p_pTree);
    if (CHKPTR(pOrderBy))
    {
        for (WmsQL1Parser::Orderby_expressionContext* pOrderByExpr : pOrderBy->orderby_expression())
        {
            if (CHKPTR(pOrderByExpr) && pOrderByExpr->object_ref())
            {
                QString qstrElement = QString::fromStdString(pOrderByExpr->object_ref()->getText());
                bool bAscSorting = true;
                if (pOrderByExpr->DESC())
                {
                    bAscSorting = false;
                }
                m_pCdmQuery->AddOrderBy(qstrElement, bAscSorting);
            }
        }
    }
}

void CdmQueryFactory::ParseLimitTree(tree::ParseTree* p_pTree)
{
    WmsQL1Parser::Limit_clauseContext* pLimit = dynamic_cast<WmsQL1Parser::Limit_clauseContext*>(p_pTree);
    if (CHKPTR(pLimit))
    {
        QVector<tree::TerminalNode*> qvLimit;
        qvLimit = QVector<tree::TerminalNode*>::fromStdVector(pLimit->INT_TYPE());

        if (qvLimit.size() == 1)
        {
            QString qstrResCount = QString::fromStdString(qvLimit[0]->toString());
            m_pCdmQuery->SetLimitResultCount(qstrResCount.toInt());
        }
        else if (qvLimit.size() == 2)
        {
            QString qstrResStart = QString::fromStdString(qvLimit[0]->toString());
            QString qstrResCount = QString::fromStdString(qvLimit[1]->toString());
            m_pCdmQuery->SetResultStart(qstrResStart.toInt());
            m_pCdmQuery->SetLimitResultCount(qstrResCount.toInt());
        }
    }
}


void CdmQueryFactory::ReplaceApostrophe(QString &p_qstrText)
{
    p_qstrText = p_qstrText.trimmed();

    if (p_qstrText.startsWith("\""))
    {
        p_qstrText = p_qstrText.remove(0,1);

        if (p_qstrText.endsWith("\""))
        {
            p_qstrText = p_qstrText.remove(p_qstrText.length() - 1, 1);
        }
    }
}

CdmQuery* CdmQueryFactory::ParseString(QString p_qstrQuery, CdmObjectContainer* p_pContainer)
{
    CdmQuery* pQuery = nullptr;

    ANTLRErrorListener* pErrListener = new CdmAntlrErrorListener();

    antlr4::ANTLRInputStream* pInputStream = new antlr4::ANTLRInputStream(p_qstrQuery.toStdString());

    if (CHKPTR(pInputStream))
    {
        WmsQL1Lexer* lxr = new WmsQL1Lexer(pInputStream);

        if (CHKPTR(lxr))
        {
            lxr->removeErrorListeners();
            lxr->addErrorListener(pErrListener);
            antlr4::CommonTokenStream* tstream = new antlr4::CommonTokenStream(lxr);

            if (CHKPTR(tstream))
            {
                WmsQL1Parser* pParser = new WmsQL1Parser(tstream);

                if (CHKPTR(pParser))
                {
                    pParser->removeErrorListeners();
                    pParser->addErrorListener(pErrListener);

                    CdmQueryFactory factory;
                    if (p_pContainer)
                    {
                        factory.SetContainer(p_pContainer);
                    }

                    WmsQL1Parser::StatementContext* result = pParser->statement();

                    if (result && factory.AntlrParser(result))
                    {
                        pQuery = factory.m_pCdmQuery;
                    }
                    else
                    {
                        pQuery = nullptr;
                        ERR("Failed to parse Query:" + p_qstrQuery);
                    }
                    DELPTR(pParser);
                }
                DELPTR(tstream);
            }
            DELPTR(lxr);
        }
        DELPTR(pInputStream);
    }
    DELPTR(pErrListener);

    return pQuery;
}

CdmQuery* CdmQueryFactory::ParseTree(tree::ParseTree* p_pAntlrTree, CdmObjectContainer* p_pContainer)
{
    CdmQueryFactory factory;
    if (p_pContainer)
    {
        factory.SetContainer(p_pContainer);
    }
    CdmQuery* pQuery = nullptr;
    if (factory.AntlrParser(p_pAntlrTree))
    {
        pQuery = factory.m_pCdmQuery;
    }
    return pQuery;
}
