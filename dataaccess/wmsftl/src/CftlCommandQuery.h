/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CFTLQUERY_H
#define CFTLQUERY_H


// System and QT Includes
#include <QList>


// own Includes
#include "CftlJoinData.h"
#include "CftlDataAccess.h"


// forwards
class CftlDataAccess;
class CftlDialect;
class CdmQuery;
class CdmQueryElement;
class CdmQueryResultElement;

/*
 * This class implements the queries on db side
 */
class CftlCommandQuery
{
private:
    CftlDataAccess* m_rpCftlDataAccess;
    CdmQuery*        m_rpCdmQuery;
    //QMap<QString, CftlJoinData*> m_qmLeftJoins;
    QMap<const CdmMember*, CftlJoinData*> m_qmLeftJoins;

private:
   qint64 ExecuteQueryP();
    bool IsQueryElementValid(CdmQueryElement *p_pElement);
    CftlInterface *GetInterface();
    CftlDialect *GetDialect();
    QString GenerateContainerQuery();
    QString GenerateClassQuery();

    QString AddSelectMembers();
    QString GetMemberFieldName(QString p_qstrKeyname, CdmQueryEnhanced* pQuery);
    bool IsObjectNeededInResult();
    QString GetReferenceMemberFieldName(QString p_qstrKeyname, CdmQueryEnhanced *pQuery);
    void AddFunctionToSelectMember(CdmQueryResultElement* pCdmResultElement, QString& qstrRet);
public:
    CftlCommandQuery(CftlDataAccess* p_pCdbDataAccess, CdmQuery* p_pCdmQuery);
    virtual ~CftlCommandQuery();
   qint64 ExecuteQuery();
    QString GenerateSql();
    static qint64 Execute(CftlDataAccess *p_pCftlDataAccess, CdmQuery *p_pCdmQuery);
    QString AddOrUpdateLeftJoin(const CdmMember*p_pMember, QString &p_qstrJoin, QString &p_qstrCompareKeyname);
    QString AddOrUpdateLeftJoin(const CdmMember*p_pMember, QString &p_qstrJoin, QString &p_qstrCompareKeyname, QString &p_qstrJoinPartner);
    /*bool ContainsLeftJoin(QString &p_qstrMember);
    CftlJoinData *GetJoinData(QString &p_qstrMember);
    QString GetJoinName(QString &p_qstrMember);*/
    bool ContainsLeftJoin(const CdmMember* p_pMember);
    CftlJoinData *GetJoinData(const CdmMember* p_pMember);
    QString GetJoinName(const CdmMember* p_pMember);
    QString GetJoinsAsString();
    void AddOrderByToQuery(QString &qstrRet);
    void AddLimitToQuery(QString &qstrRet);
};

#endif
