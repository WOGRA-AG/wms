/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdbQueryEnhanced.h
 ** Started Implementation: 2010/11/11
 ** Description:
 ** 
 ** This class implements the sql access for enhanced queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCQUERYENHANCEDNEW_H
#define CODBCQUERYENHANCEDNEW_H

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
class CdbQueryEnhancedNew
{
private:
    CdmQueryEnhanced* m_rpCdmQuery;
    CdbDataAccess* m_rpCdbDataAccess;
    int m_iKeynameCount;
    QMap<QString, int> m_qmKeynames;
    QMap<QString, QString> m_qmKeynamesSave;
    QMap<EdmValueType, QList<const CdmMember*> > m_qmTypesResults;
    QMultiMap<int, QPair<QLinkedList<const CdmMember*>, QList<const CdmMember*>>> m_qmmObjectRefMembers;


public:
    CdbQueryEnhancedNew(CdmQueryEnhanced* p_pCdmQueryEnhanced, CdbDataAccess* p_pCdbDataAccess);
    virtual ~CdbQueryEnhancedNew( );
    long Execute();
    virtual QString GenerateSql();

private:
    long ExecuteQuery(QString p_qstrSql);
    QString MakeKeynameSave(QString p_qstrKeyname);
    void BuildMemberMap(QVector<QString> &p_qvKeynames);
    void BuildTypeAndReferenceList(QVector<QString> &p_qvKeynames);
    void BuildType(QString p_qstrKeyname);
    void BuildReference(QString p_qstrKeyname);
    QMap<QString, QString> BuildSubQueries(QString &p_qstrIdQuery);
    QString BuildResultMembers(QList<const CdmMember *> &p_qlMembers);
    QString BuildConditionMembers(QList<const CdmMember *> &p_qlMembers);
    QString ConcatenateQueries(QVector<QString> &p_qvKeynames, QMap<QString, QString> &p_qmSubQueries, QString &p_qstrObjectIdSql);
    QString CreateHead(QVector<QString> &p_qvKeynames);
    QString GenerateCompleteSql(QVector<QString> &p_qvKeynames, QString &p_qstrObjectIdSql);
    QString GetPartialQueryTemplate();
    QMap<QString, QString> BuildObjectRefSubQueries(QString &p_qstrIdQuery, bool p_bNoJoins=false);
    QMap<QString, QString> BuildObjectRefSubQueriesPerDepth(QString &p_qstrIdQuery, bool p_bNoJoins=false);
    QString GetPartialObjRefQueryTemplate();
    QString GetSQlFunction(int pos);
    void AddGroupByToSql(QString &qstrSql);
    void AddOrderByToSql(QString &qstrSql);
};

#endif
