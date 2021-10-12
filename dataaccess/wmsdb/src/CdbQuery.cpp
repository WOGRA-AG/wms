/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QSqlQuery>
#include <QList>
#include <qvariant.h>


// own Includes
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmDataAccessHelper.h"

// WMS ODBC Includes
#include "CdbDataStructureHelper.h"
#include "CdbObjectAccess.h"
#include "CdbDataAccess.h"
#include "CdbQueryEnhancedNew.h"
#include "CdbQueryElement.h"
#include "CdbQuery.h"





/** +-=---------------------------------------------------------Sa 20. Aug 12:09:48 2005----------*
 * @method  CdbQuery::CdbQuery                           // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @comment The cosntructor                                                                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:09:48 2005----------*/
CdbQuery::CdbQuery(  CdbDataAccess* p_pCdbDataAccess, CdmQuery* p_pCdmQuery )
    : m_rpCdbDataAccess(p_pCdbDataAccess),
      m_rpCdmQuery(p_pCdmQuery)
{

}


/** +-=---------------------------------------------------------Sa 20. Aug 12:09:55 2005----------*
 * @method  CdbQuery::~CdbQuery                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbQuery                                                    *
 *----------------last changed: --------------------------------Sa 20. Aug 12:09:55 2005----------*/
CdbQuery::~CdbQuery(  )
{
    // nothing to do at the moment :-)
}

/** +-=---------------------------------------------------------Do 11. Nov 08:35:32 2010----------*
 * @method  CdbQuery::ExecuteEnhanced                      // private                           *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 08:35:32 2010----------*/
qint64 CdbQuery::ExecuteEnhanced()
{
   qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        CdbQueryEnhancedNew cCdbQuery((CdmQueryEnhanced*)m_rpCdmQuery, m_rpCdbDataAccess);
        lRet = cCdbQuery.Execute();
    }

    return lRet;
}

/** +-=---------------------------------------------------------Do 11. Nov 08:36:07 2010----------*
 * @method  CdbQuery::Execute                              // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 08:36:07 2010----------*/
qint64 CdbQuery::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

    if (m_rpCdmQuery->HasResultElements())
    {
        lRet = ExecuteEnhanced();
    }
    else
    {
        lRet = ExecuteQuery();
    }

    return lRet;
}

/** +-=---------------------------------------------------------Do 11. Nov 08:35:47 2010----------*
 * @method  CdbQuery::ExecuteQuery                         // public                            *
 * @return qint64                                             //                                   *
 * @comment Executes the query without any parameters. Works with the faster query                *
 *          algorithm.                                                                            *
 *----------------last changed: --------------------------------Do 11. Nov 08:35:47 2010----------*/
qint64 CdbQuery::ExecuteQuery()
{
   qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        QMap<qint64,qint64> qvlResults;
        QString  qstrQuery = GenerateQuerySql();


        if(!qstrQuery.isEmpty())
        {
            lRet = ExecuteSqlQuery(qvlResults, qstrQuery);

            QMap<qint64,qint64>::iterator qmIt = qvlResults.begin();
            QMap<qint64,qint64>::iterator qvlItEnd = qvlResults.end();

            for(; qmIt != qvlItEnd; ++qmIt)
            {
                CdmDataAccessHelper::AddQueryResult(m_rpCdmQuery, qmIt.key(), qmIt.value());
            }
        }
    }

    return lRet;
}

qint64 CdbQuery::ExecuteSqlQuery(QMap<qint64,qint64>& p_rqllResults, QString qstrSql)
{
   qint64 lRet =  CdmLogging::eDmUnknownDBQueryError;
    QSqlQuery cQSqlQuery;
    p_rqllResults.clear();


    if (!qstrSql.isEmpty())
    {
        lRet = m_rpCdbDataAccess->ExecuteQuery(qstrSql, cQSqlQuery);

        if(lRet > 0)
        {
            if(cQSqlQuery.first())
            {
                do // reading each objectid
                {
                    int iObjectId = cQSqlQuery.value(0).toInt();
                    int iContainerId = cQSqlQuery.value(1).toInt();

                    if(!p_rqllResults.contains(iObjectId))
                    {
                        p_rqllResults[iObjectId] = iContainerId;
                    }
                }
                while(cQSqlQuery.next());
            }
        }
    }
    else
    {
        lRet = 2;
    }

    return lRet;
}

qint64 CdbQuery::ExecuteObjectListQuery(QMap<qint64,qint64>& p_rqllResults)
{
   qint64 lRet = CdmLogging::eDmUnknownDBQueryError;
   qint64 lObjectListId = m_rpCdmQuery->GetContainerId();
   qint64 lClassId = m_rpCdmQuery->GetClassId();

    if (lObjectListId > 0 || lClassId > 0)
    {
        QString qstrSql = GenerateSql();
        lRet = ExecuteSqlQuery(p_rqllResults, qstrSql);
    }

    return lRet;
}

/** +-=---------------------------------------------------------So 5. Jun 11:38:32 2011-----------*
 * @method  CdbQuery::GenerateSql                          // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 5. Jun 11:38:32 2011-----------*/
QString CdbQuery::GenerateSql()
{
    QString qstrRet;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        if (m_rpCdmQuery->HasResultElements())
        {
            CdbQueryEnhancedNew cCdbQueryEnhanced((CdmQueryEnhanced*)m_rpCdmQuery, m_rpCdbDataAccess);
            qstrRet = cCdbQueryEnhanced.GenerateSql();
        }
        else
        {
            qstrRet = GenerateQuerySql();
        }
    }

    return qstrRet;
}

/** +-=---------------------------------------------------------So 5. Jun 11:47:27 2011-----------*
 * @method  CdbQuery::GenerateQuerySql                     // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 5. Jun 11:47:27 2011-----------*/
QString CdbQuery::GenerateQuerySql()
{
    QString qstrRet;

    if(CHKPTR(m_rpCdbDataAccess) &&
            CHKPTR(m_rpCdmQuery))
    {
        CdmQueryElement* pCdmQueryElement = m_rpCdmQuery->GetQueryElement();

        if(IsQueryElementValid(pCdmQueryElement))
        {
            QScopedPointer<CdbQueryElement> pCdbQueryElement(new CdbQueryElement(m_rpCdbDataAccess, pCdmQueryElement));
            qstrRet = pCdbQueryElement->GenerateQuery();
        }
        else
        {
            if (m_rpCdmQuery->GetContainerId() > 0)
            {
                qstrRet = "select WMS_DM_OBJECT.objectid, WMS_DM_OBJECT.objectlistid from WMS_DM_OBJECT where objectlistid = " + QString::number(m_rpCdmQuery->GetContainerId());
            }
            else if (m_rpCdmQuery->GetClassId() > 0)
            {
                qstrRet = "select WMS_DM_OBJECT.objectid, WMS_DM_OBJECT.objectlistid from WMS_DM_OBJECT "
                          "inner join WMS_DM_OBJECTLIST objlist ON objlist.objectlistid = WMS_DM_OBJECT.ObjectListId "
                          "where objlist.classId = " + QString::number(m_rpCdmQuery->GetClassId());
            }
            else
            {
                ERR("Unknown Target no container and no class selected.")
            }
        }

        if (m_rpCdmQuery->GetLimitResultCount() > 0)
        {
            qstrRet += " limit " + QString::number(m_rpCdmQuery->GetLimitResultCount());

            if (m_rpCdmQuery->GetResultStart() > 0)
            {
                qstrRet += " offset " + QString::number(m_rpCdmQuery->GetResultStart());
            }
        }

        if (!m_rpCdmQuery->GetOrderBy().isEmpty() && !m_rpCdmQuery->HasResultElements())
        {
            SortResults(qstrRet);
        }

    }

    return qstrRet;
}

bool CdbQuery::IsQueryElementValid(CdmQueryElement* p_pElement)
{
    bool bRet = false;

    if (p_pElement)
    {
        if (p_pElement->GetQueryElementType() == eDmQueryElementTypeCompare)
        {
            bRet = true;
        }
        else
        {
            QList<CdmQueryElement*> qllChilds;
            p_pElement->GetChildList(qllChilds);

            if (qllChilds.count() > 0)
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

void CdbQuery::SortResults(QString& p_qstrQuery)
{
    if (CHKPTR(m_rpCdmQuery))
    {
        QStringList qstrlSortKeys = m_rpCdmQuery->GetOrderBy();

        if (qstrlSortKeys.count() > 0)
        {
            QString qstrSortKey = qstrlSortKeys[0];
            bool bReferenceCount = qstrSortKey.contains(".");

            if (bReferenceCount)
            {
                SortResultsReference(qstrSortKey, p_qstrQuery);
            }
            else
            {
                SortResultsOwnMember(qstrlSortKeys, p_qstrQuery);
            }
        }
    }
}

void CdbQuery::SortResultsReference(QString p_qstrSortKey, QString& p_qstrQuery)
{
    int iPos = p_qstrSortKey.indexOf('.');
    QString qsrClassMemberSortKey = p_qstrSortKey.mid(0, iPos);
    QString qstrSortKeyNew = p_qstrSortKey.mid(iPos + 1, p_qstrSortKey.length() - iPos - 1);
    int iMemberId = 0;
    int iObjectRefClassId = 0;
    CdbDataAccess::EodbcBaseType eType = CdbDataAccess::eOdbcNone;


    ReadMemberIdAndBaseType(qsrClassMemberSortKey, eType, iMemberId, iObjectRefClassId);


    if (eType == CdbDataAccess::eOdbcObjRef && iObjectRefClassId > 0)
    {
        auto pClass = m_rpCdmQuery->GetClass();

        if (CHKPTR(pClass))
        {
            auto pClassManager = pClass->GetClassManager();
            auto pRefClass = pClassManager->FindClassById(iObjectRefClassId);

            if (CHKPTR(pRefClass))
            {
                auto pSearchMember = pRefClass->FindMember(qstrSortKeyNew);

                if (CHKPTR(pSearchMember))
                {
                    eType = CdbDataAccess::ConvertValueType(pSearchMember->GetValueType());

                    if (eType != CdbDataAccess::eOdbcNone)
                    {
                        QString qstrTableName = CdbDataStructureHelper::GetTableName(eType);
                        QString qstrDataField = GetDataFieldName(eType);
                        QString qstrValueId = GetTableIdName(eType);
                        QString qstrOrderMode;


                        if (m_rpCdmQuery->GetOrderMode()) // ASC or DESC
                        {
                            qstrOrderMode = "asc";
                        }
                        else // DESC
                        {
                            qstrOrderMode = "desc";
                        }

                        p_qstrQuery = QString("SELECT obj.objectid, obj.objectlistid FROM "
                                              "(%1) obj LEFT JOIN (SELECT obj.objectid, obj.objectlistid, "
                                              "MIN(CASE WHEN %2.objectid = mor.val AND %2.objectlistid = mor.orefobjectlist AND %2.keyname = '%3' "
                                              "THEN %2.%5 ELSE NULL END) AS wms_%3 "
                                              "FROM V_VALUE_OBJECTREFERENCE mor, (%1) obj, %2 "
                                              "WHERE mor.keyname = '%4' AND %2.objectid = mor.val AND %2.objectlistid = mor.orefobjectlist AND mor.objectid = obj.objectid "
                                              "GROUP BY objectid , objectlistid) wms_OBJREF_%4 ON wms_OBJREF_%4.objectId = obj.objectid "
                                              "order by wms_%3 %6")
                                .arg(p_qstrQuery)
                                .arg(qstrTableName)
                                .arg(qstrSortKeyNew)
                                .arg(qsrClassMemberSortKey)
                                .arg(qstrDataField)
                                .arg(qstrOrderMode);
                    }
                }
            }
        }


        // ERR("Sorting on reference is not implemented!");
    }
    else
    {
        ERR("This is no reference and reference sorting is not implemented");
    }
}

void CdbQuery::SortResultsOwnMember(QStringList p_qstrSortKey, QString& p_qstrQuery)
{
    CdbDataAccess::EodbcBaseType eType = CdbDataAccess::eOdbcNone;
    int iMemberId = 0;
    int iObjectRefClassId = 0;

    ReadMemberIdAndBaseType(p_qstrSortKey[0], eType, iMemberId, iObjectRefClassId);

    if (eType != CdbDataAccess::eOdbcNone)
    {
        QString qstrTableName = GetTableName(eType);
        QString qstrDataField = GetDataFieldName(eType);
        QString qstrValueId = GetTableIdName(eType);
        QString qstrOrderMode;


        if (m_rpCdmQuery->GetOrderMode()) // ASC or DESC
        {
            qstrOrderMode = "asc";
        }
        else // DESC
        {
            qstrOrderMode = "desc";
        }

        p_qstrQuery = QString("select val.OBJECTID, sel.OBJECTLISTID from WMS_VALUE val "
                              "inner join (%1) sel on sel.objectid = val.objectid "
                              "inner join %2 t on t.%3 = val.valueid "
                              "where MemberId = %4 "
                              "order by %5 %6")
                .arg(p_qstrQuery)
                .arg(qstrTableName)
                .arg(qstrValueId)
                .arg(iMemberId)
                .arg(qstrDataField)
                .arg(qstrOrderMode);
    }
}

void CdbQuery::ReadMemberIdAndBaseType(QString p_qstrSortKey,
                                       CdbDataAccess::EodbcBaseType& p_eBasType,
                                       int& p_iMemberId,
                                       int& p_iObjectRefClassId)
{
    const CdmClass* pClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pClass))
    {
        const CdmMember* pMember = pClass->FindMember(p_qstrSortKey);

        if (CHKPTR(pMember))
        {
            p_iMemberId = pMember->GetId();
            p_eBasType = CdbDataAccess::ConvertValueType(pMember->GetValueType());

            if (pMember->GetValueType() == eDmValueObjectRef)
            {
                p_iObjectRefClassId = pMember->GetClassReference();
            }
        }
    }
}

/** +-=---------------------------------------------------------Sa 10. Nov 13:20:22 2007----------*
 * @method  CdbQuery::CreateStringFromResultList           // private                           *
 * @return  QString                                          //                                   *
 * @param   QValueList<qint64>& p_rqvlResults                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 10. Nov 13:20:22 2007----------*/
QString CdbQuery::CreateStringFromResultList(QMap<qint64,qint64>& p_rqvlResults)
{
    QString qstrRet;

    QMap<qint64,qint64>::iterator qvlIt = p_rqvlResults.begin();
    QMap<qint64,qint64>::iterator qvlItEnd = p_rqvlResults.end();

    int iObjectId = qvlIt.key();
    qstrRet += QString::number(iObjectId);
    ++qvlIt;

    for (; qvlIt != qvlItEnd; ++qvlIt)
    {
        int iObjectId = qvlIt.key();
        qstrRet += "," + QString::number(iObjectId);
    }

    return qstrRet;
}

/** +-=---------------------------------------------------------Sa 10. Nov 13:13:20 2007----------*
 * @method  CdbQuery::GetTableIdName                       // public                            *
 * @return  QString                                          //                                   *
 * @param   CdbDataAccess::EodbcBaseType p_eType           //                                   *
 * @comment This method returns the name of the id field in the table.                            *
 *----------------last changed: Wolfgang Graßhof----------------Sa 10. Nov 13:13:20 2007----------*/
QString CdbQuery::GetTableIdName(CdbDataAccess::EodbcBaseType p_eType)
{
    QString qstrTableIdName;

    switch(p_eType)
    {
    case CdbDataAccess::eOdbcLong:
        qstrTableIdName = "LONGID";
        break;
    case CdbDataAccess::eOdbcInt:
    case CdbDataAccess::eOdbcUser:
    case CdbDataAccess::eOdbcUserGroup:
    case CdbDataAccess::eOdbcEnum:
        qstrTableIdName = "INTID";
        break;
    case CdbDataAccess::eOdbcObjRef:
        qstrTableIdName = "OBJECTREFERENCEID";
        break;
    case CdbDataAccess::eOdbcCounter:
        qstrTableIdName = "COUNTERID";
        break;
    case CdbDataAccess::eOdbcBool:
        qstrTableIdName = "BOOLID";
        break;
    case CdbDataAccess::eOdbcFloat:
        qstrTableIdName = "FLOATID";
        break;
    case CdbDataAccess::eOdbcDouble:
        qstrTableIdName = "DOUBLEID";
        break;
    case CdbDataAccess::eOdbcString:
        qstrTableIdName = "STRINGID";
        break;
    case CdbDataAccess::eOdbcDate:
        qstrTableIdName = "DATEID";
        break;
    case CdbDataAccess::eOdbcTime:
        qstrTableIdName = "TIMEID";
        break;
    case CdbDataAccess::eOdbcDateTime:
        qstrTableIdName = "DATETIMEID";
        break;
    case CdbDataAccess::eOdbcObjListRef:
        qstrTableIdName = "OBJECTLISTREFERENCEID";
        break;
    case CdbDataAccess::eOdbcBinDoc:
        qstrTableIdName = "";
        break;
    case CdbDataAccess::eOdbcCharDoc:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
        // The following types are all derived from chardoc
    case CdbDataAccess::eOdbcListInt:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcListDouble:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcListString:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcDictStringInt:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcDictStringString:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcDictStringDouble:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcDictIntInt:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eOdbcDictIntString:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    case CdbDataAccess::eODbcDictIntDouble:
        qstrTableIdName = "CHARACTERDOCUMENTID";
        break;
    default:
        qstrTableIdName = "Invalid Type";
        break;
    }

    return qstrTableIdName;
}

/** +-=---------------------------------------------------------Do 23. Aug 15:22:34 2007----------*
 * @method  CdbQuery::GetTableName                         // public, static                    *
 * @return  QString                                          //                                   *
 * @param   CdbDataAccess::EodbcBaseType p_eType           //                                   *
 * @comment This method returns the tablename dependent to the queryelement.                      *
 *----------------last changed: --------------------------------Do 23. Aug 15:22:34 2007----------*/
QString CdbQuery::GetTableName(CdbDataAccess::EodbcBaseType p_eType)
{
    QString qstrTableName;

    switch(p_eType)
    {
    case CdbDataAccess::eOdbcLong:
        qstrTableName = "WMS_VALUE_LONG";
        break;
    case CdbDataAccess::eOdbcInt:
    case CdbDataAccess::eOdbcUser:
    case CdbDataAccess::eOdbcUserGroup:
    case CdbDataAccess::eOdbcEnum:
        qstrTableName = "WMS_VALUE_INT";
        break;
    case CdbDataAccess::eOdbcObjRef:
        qstrTableName = "WMS_VALUE_OBJECTREFERENCE";
        break;
    case CdbDataAccess::eOdbcCounter:
        qstrTableName = "WMS_VALUE_COUNTER";
        break;
    case CdbDataAccess::eOdbcBool:
        qstrTableName = "WMS_VALUE_BOOL";
        break;
    case CdbDataAccess::eOdbcFloat:
        qstrTableName = "WMS_VALUE_FLOAT";
        break;
    case CdbDataAccess::eOdbcDouble:
        qstrTableName = "WMS_VALUE_DOUBLE";
        break;
    case CdbDataAccess::eOdbcString:
        qstrTableName = "WMS_VALUE_STRING";
        break;
    case CdbDataAccess::eOdbcDate:
        qstrTableName = "WMS_VALUE_DATE";
        break;
    case CdbDataAccess::eOdbcTime:
        qstrTableName = "WMS_VALUE_TIME";
        break;
    case CdbDataAccess::eOdbcDateTime:
        qstrTableName = "WMS_VALUE_DATETIME";
        break;
    case CdbDataAccess::eOdbcObjListRef:
        qstrTableName = "WMS_VALUE_OBJECTLISTREFERENCE";
        break;
    case CdbDataAccess::eOdbcBinDoc:
        qstrTableName = "";
        break;
    case CdbDataAccess::eOdbcCharDoc:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
        // The following types are all derived from chardoc
    case CdbDataAccess::eOdbcListInt:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcListDouble:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcListString:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcDictStringInt:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcDictStringString:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcDictStringDouble:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcDictIntInt:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eOdbcDictIntString:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    case CdbDataAccess::eODbcDictIntDouble:
        qstrTableName = "WMS_VALUE_CHARACTERDOCUMENT";
        break;
    default:
        qstrTableName = "Invalid Type";
        break;
    }

    return qstrTableName;
}


/** +-=---------------------------------------------------------Do 23. Aug 15:24:41 2007----------*
 * @method  CdbQuery::GetDataFieldName                     // public, static                    *
 * @return  QString                                          //                                   *
 * @param   CdbDataAccess::EodbcBaseType p_eType           //                                   *
 * @comment This method returns the name of the datafield.                                        *
 *----------------last changed: --------------------------------Do 23. Aug 15:24:41 2007----------*/
QString CdbQuery::GetDataFieldName(CdbDataAccess::EodbcBaseType p_eType)
{
    // the default
    QString qstrRet = "Val";

    if (p_eType == CdbDataAccess::eOdbcObjRef)
    {
        qstrRet = "ObjectId";
    }

    return qstrRet;
}
