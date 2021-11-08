
#pragma once

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVector>

// WMS Manager Includes
#include "CdmMember.h"

// Own Includes


// Forwards
class CdmQueryEnhanced;
class CdbDataAccess;
class CdmMember;


// Enumerations


/* 
 * This class implements the sql access for enhanced queries
 */
class CdbQueryEnhancedDoubleRequest
{
private:
    CdmQueryEnhanced* m_rpCdmQuery;
    CdbDataAccess* m_rpCdbDataAccess;
    int m_iKeynameCount;
    QMap<QString, int> m_qmKeynames;
    QMap<QString, QString> m_qmKeynamesSave;
    QMap<EdmValueType, QList<const CdmMember*> > m_qmTypesResults;
    QMultiMap<int, QPair<QList<const CdmMember*>, QList<const CdmMember*>>> m_qmmObjectRefMembers;


public:
    CdbQueryEnhancedDoubleRequest(CdmQueryEnhanced* p_pCdmQueryEnhanced, CdbDataAccess* p_pCdbDataAccess);
    virtual ~CdbQueryEnhancedDoubleRequest( );
   qint64 Execute();
    virtual QString GenerateSql(QStringList &qvlObjects);

private:
   qint64 ExecuteQuery(QSqlQuery &cQSqlQuery);
    QString MakeKeynameSave(QString p_qstrKeyname);
    void BuildMemberMap(QVector<QString> &p_qvKeynames);
    void BuildTypeAndReferenceList(QVector<QString> &p_qvKeynames);
    void BuildType(QString p_qstrKeyname);
    void BuildReference(QString p_qstrKeyname);
    QMap<QString, QString> BuildSubQueries();
    QString BuildResultMembers(QList<const CdmMember *> &p_qlMembers);
    QString BuildConditionMembers(QList<const CdmMember *> &p_qlMembers);
    QString ConcatenateQueries(QVector<QString> &p_qvKeynames, QMap<QString, QString> &p_qmSubQueries);
    QString CreateHead(QVector<QString> &p_qvKeynames);
    QString GenerateMemberSql(QVector<QString> &p_qvKeynames);
    QString     GetPartialQueryTemplate();
    QMap<QString, QString> BuildObjectRefSubQueries(bool p_bNoJoins=false);
    QMap<QString, QString> BuildObjectRefSubQueriesPerDepth(QVariantList &pqvlObjResults, bool p_bNoJoins=false);
    QString GetPartialObjRefQueryTemplate();
    QString GetSQlFunction(int pos);
    void AddGroupByToSql(QString &qstrSql);
    void AddOrderByToSql(QString &qstrSql);
    void ExecuteIdQuery(QStringList &qvlResults);
};
