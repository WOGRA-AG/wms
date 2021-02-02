
#ifndef CWTQUERYTEST_H
#define CWTQUERYTEST_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QtTest>
#include <QObject>
#include <QDateTime>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Own Includes
#include "CwtTestBase.h"

// Forwards
class CdmScheme;
class CdmManager;
class CdmClassManager;
class CdmContainerManager;

// TypeDefs



/*
 * This class implements the main test class which starts all tests
 */
class CwtQuery : public CwtTestBase
{
    Q_OBJECT

private:
    QTime m_qTimeStart;
    long m_lObjectId;
    long m_lClassId;
    long m_lRefObjectId;
    long m_lRefRefObjectId;
    QTime m_qTestTimeWithPreparation;
    QDateTime m_qdTestDateTime;
    QString m_qstrDbName;
    int m_iObjectToCreate;
    CdmClass* pClassDerived1;
    CdmClass* pClassDerived2;
    void CreateObject();
    void CreateObject(QString p_qstrContainerKeyname);
    void CreateMultipleObjects(int p_iObjectCount);
    void CreateReferencingObject();
    void CreateReferencingObject(CdmObject *p_pObject);
    void CreateDoubleReferencingObject();
    void CreateDoubleReferencingObject(CdmObject* p_pObject);
    void PrepareMultiInheritanceTestCase();

public: static long mem;

public:
    CwtQuery( );
    virtual ~CwtQuery( );

private slots:
    void initTestCase( );
    void cleanupTestCase( );
    void init();
    void cleanup();
    void SimpleQueryWithoutCondition();
    void SimpleQueryWithOneValueConditionInt( );
    void SimpleQueryWithOrConditionOfTwoValuesBothConditionsFitting( );
    void SimpleQueryWithAndConditionOfTwoValuesBothConditionFitting( );
    void SimpleQueryWithOrConditionOfMultipleValuesEveryConditionFits( );
    void QueryEnhancedWithOneSelectMember( );
    void SimpleQueryWithOneValueConditionNoResult();
    void SimpleQueryWithOrConditionOfTwoValuesNoResult();
    void SimpleQueryWithAndConditionOfTwoValuesNothingFits();

    void SimpleQueryWithoutConditionWithLimit();
    void EnhancedQueryWithoutConditionWithGroupBy();
    void SimpleQueryWithoutConditionWithOrderBy();
    void SimpleClassQueryWithoutCondition();
    void SimpleQueryWithOneReferenceCondition();
    void SimpleClassQueryWithOneValueConditionNoResult();
    void SimpleQueryWithOneValueConditionString();
    void SimpleQueryWithOneValueConditionDate();
    void SimpleQueryWithOrConditionOfTwoValuesOneConditionsFitting();
    void SimpleQueryWithAndConditionOfTwoValuesFirstConditionsFitting();
    void SimpleQueryWithAndConditionOfTwoValuesSecondConditionsFitting();
    void SimpleQueryWithOrConditionOfMultipleValuesTwoOfThreeConditionFits();
    void SimpleQueryWithOrConditionOfMultipleValuesOneOfThreeConditionFits();
    void SimpleQueryWithOrConditionOfMultipleValuesNoConditionFits();
    void SimpleQueryWithAndConditionOfMultipleValuesEveryConditionFits();
    void SimpleQueryWithAndConditionOfMultipleValuesTwoOfThreeConditionFits();
    void SimpleQueryWithAndConditionOfMultipleValuesOneOfThreeConditionFits();
    void SimpleQueryWithAndConditionOfMultipleValuesNoConditionFits();
    void SimpleQueryWithAndOrConditionOfMultipleValuesEveryConditionFits();
    void SimpleQueryWithAndOrConditionOfMultipleValuesOneOrConditionFits();
    void SimpleQueryWithAndOrConditionOfMultipleValuesAndDoesNotFitOneOrConditionFits();
    void SimpleQueryWithoutConditionWithLimitMoreThanOneResults();
    void SimpleQueryWithTwoReferenceConditionAnd();
    void SimpleQueryWithTwoReferenceConditionOr();
    void SimpleQueryWithReferenceToBaseClass();
    void SimpleQueryWithReferenceToBaseClassAndCondition();
    void SimpleQueryWithReferenceToBaseClassOrCondition();
    void SimpleQueryWithReferenceToBaseClassAndConditionFirstWrong();
    void SimpleQueryWithReferenceToBaseClassAndConditionSecondWrong();
    void QueryEnhancedWithTwoSelectMember();
    void QueryEnhancedWithSum();
    void QueryEnhancedWithAvg();
    void QueryEnhancedWithMax();
    void QueryEnhancedWithMin();
    void QueryEnhancedWithCount();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelect();
    void QueryEnhancedWithTwoReferencesInSelect();
    void QueryEnhancedWithOneReferenceInSelect();
    void QueryEnhancedWithOneReferenceInSelectMax();
    void QueryEnhancedWithOneReferenceInSelectMin();
    void QueryEnhancedWithOneReferenceInSelectAvg();
    void QueryEnhancedWithOneReferenceInSelectSum();
    void QueryEnhancedWithOneReferenceInSelectCount();
    void QueryEnhancedWithOneReferenceInSelectWithClass();
    void QueryEnhancedWithSumReferenceInSelectWithClass();
    void QueryEnhancedWithAvgReferenceInSelectWithClass();
    void QueryEnhancedWithMinReferenceInSelectWithClass();
    void QueryEnhancedWithMaxReferenceInSelectWithClass();
    void QueryEnhancedWithCountReferenceInSelectWithClass();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithSimpleWhereClause();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClause();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithAndWhereClause();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithAndWhereClauseOneConditionWrong();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClauseOneConditionWrong();
    void QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClauseBothConditionWrong();
    void SimpleClassQueryModelWithoutCondition();
    void QueryEnhancedWithMixedReferenceChainsAndNoReferenecesInSelect();
    void QueryEnhancedWithMixedReferenceChainsAndReferenecesInSelect();
    void SimpleQueryWithTwoReferenceChainsConditionAnd();
    void SimpleQueryWithTwoReferenceChainsConditionOr();
    void QueryEnhancedWithReferenceReferenceChainInSelect();
};

#endif // CwtQueryTest_H
