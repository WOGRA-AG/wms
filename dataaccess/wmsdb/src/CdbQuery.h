#ifndef CODBCQUERY_H
#define CODBCQUERY_H


// System and QT Includes
#include <QList>


// own Includes
#include "CdbDataAccess.h"


// forwards
class CdbDataAccess;
class CdmQuery;
class CdmQueryElement;

enum EdbQueryEnhanceExecutionMode
{
    eDbQueryEnhancedExecutionModeDefault,
    eDbQueryEnhancedExecutionModeDoubleRequest
};

/*
 * This class implements the queries on db side
 */
class CdbQuery
{
private:

    CdbDataAccess* m_rpCdbDataAccess;
    CdmQuery*        m_rpCdmQuery;
    EdbQueryEnhanceExecutionMode m_eExecutionMode;



public:
    CdbQuery(CdbDataAccess* p_pCdbDataAccess, CdmQuery* p_pCdmQuery);
    virtual ~CdbQuery(  );
    qint64 ExecuteQuery();
    QString GenerateQuerySql();
    void SortResultsReference(QString p_qstrSortKey, QString &p_qstrQuery);
    static QString GetTableName(CdbDataAccess::EodbcBaseType p_eType);
    static QString GetDataFieldName(CdbDataAccess::EodbcBaseType p_eType);
    QString GetTableIdName(CdbDataAccess::EodbcBaseType p_eType);
    virtual QString GenerateSql();
    qint64 Execute();

private:
    void SortResults(QString& p_qstrQuery);
    QString CreateStringFromResultList(QMap<qint64,qint64>& p_rqvlResults);
    void SortResultsOwnMember(QStringList p_qstrSortKey, QString& p_qstrQuery);
    void ReadMemberIdAndBaseType(QString p_qstrSortKey,
                                 CdbDataAccess::EodbcBaseType& p_eBasType,
                                 int& p_iMemberId,
                                 int& p_iObjectRefClassId);
    qint64 ExecuteEnhanced();
    qint64 ExecuteObjectListQuery(QMap<qint64,qint64>& p_rqllResults);
    bool IsQueryElementValid(CdmQueryElement *p_pElement);
    qint64 ExecuteSqlQuery(QMap<qint64,qint64>& p_rqllResults, QString qstrSql);

    bool IsEnhancedQuery();
};

#endif //
