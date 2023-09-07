/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CftlQueryEnhanced.cpp
 ** Started Implementation: 2010/11/11
 ** Description:
 ** 
 ** This class implements the sql access for enhanced queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <qsqlquery.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQueryElement.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CftlCommandQuery.h"
#include "CwmsUtilities.h"
#include "CftlDataStructureHelper.h"
#include "CftlDataAccess.h"
#include "CftlCommandQueryElement.h"
#include "CftlCommandQueryEnhanced.h"

/** +-=---------------------------------------------------------Do 11. Nov 14:13:25 2010----------*
 * @method  CftlQueryEnhanced::CftlQueryEnhanced           // public                            *
 * @return                                                   //                                   *
 * @param   CdmQuery* p_pCdmQuery            //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 14:13:25 2010----------*/
CftlCommandlQueryEnhanced::CftlCommandlQueryEnhanced(CdmQuery* p_pCdmQuery,
                                       CftlDataAccess* p_pCftlDataAccess)
: m_rpCdmQuery(p_pCdmQuery),
  m_rpCftlDataAccess(p_pCftlDataAccess),
  m_iKeynameCount(0)
{
}

/** +-=---------------------------------------------------------Do 11. Nov 09:40:12 2010----------*
 * @method  CftlQueryEnhanced::~CftlQueryEnhanced          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlQueryEnhanced                                            *
 *----------------last changed: --------------------------------Do 11. Nov 09:40:12 2010----------*/
CftlCommandlQueryEnhanced::~CftlCommandlQueryEnhanced()
{
}

/** +-=---------------------------------------------------------Do 11. Nov 09:40:25 2010----------*
 * @method  CftlQueryEnhanced::Execute                      // public                            *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 09:40:25 2010----------*/
qint64 CftlCommandlQueryEnhanced::Execute()
{
  qint64 lRet = CdmLogging::eDmUnknownDBQueryError;

   if(CHKPTR(m_rpCftlDataAccess) && 
      CHKPTR(m_rpCdmQuery))
   {
      QString qstrSql = GenerateSql();

      if (!qstrSql.isEmpty())
      {
         lRet = ExecuteQuery(qstrSql);
      }
      else
      {
         lRet = CdmLogging::eDmFalse;
      }
   }

   return lRet;
}

/** +-=---------------------------------------------------------So 5. Jun 11:36:11 2011-----------*
 * @method  CftlQueryEnhanced::GenerateSql                  // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 5. Jun 11:36:11 2011-----------*/
QString CftlCommandlQueryEnhanced::GenerateSql()
{
   QString qstrSql;

   if(CHKPTR(m_rpCftlDataAccess) && 
      CHKPTR(m_rpCdmQuery))
   {
      QString qstrObjectIdQuery;
      CftlCommandQuery cCftlQuery(m_rpCftlDataAccess, m_rpCdmQuery);
      qstrObjectIdQuery = cCftlQuery.GenerateSql();
      QVector<QString> qvResultElements = m_rpCdmQuery->GetResultElements();
      QString qstrResultFirstPartQuery = ExecuteFirstPartQuery(qstrObjectIdQuery);

      if (!qstrResultFirstPartQuery.isEmpty() && m_rpCdmQuery->HasResultElements())
      {
         qstrSql = GenerateCompleteSql(qvResultElements, qstrResultFirstPartQuery);
         //qstrSql = GenerateCompleteSql(qvResultElements, qstrObjectIdQuery);
      }
      else if (!qstrResultFirstPartQuery.isEmpty())
      {
         qstrSql = qstrResultFirstPartQuery;
      }
   }

   return qstrSql;
}

/** +-=---------------------------------------------------------Mi 11. Mai 18:15:48 2011----------*
 * @method  CftlQueryEnhanced::ExecuteFirstPartQuery        // private                           *
 * @return  QString                                          // the result                        *
 * @param   QString p_qstrQuery                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 11. Mai 18:15:48 2011----------*/
QString CftlCommandlQueryEnhanced::ExecuteFirstPartQuery(QString p_qstrQuery)
{
   QString qstrRet;
   QSqlQuery cQSqlQuery;

   if (!p_qstrQuery.isEmpty())
   {
     qint64 lRet = m_rpCftlDataAccess->ExecuteQuery(p_qstrQuery, cQSqlQuery);

      if(lRet > 0)
      {
         if(cQSqlQuery.first())
         {
            qstrRet = "(";
            bool bFirst = true;

            do
            {
               if (!bFirst)
               {
                  qstrRet += ", ";
               }

               qstrRet += cQSqlQuery.value(0).toString();

               bFirst = false;
            }
            while(cQSqlQuery.next());

            qstrRet += ")";
         }
      }
   }

   if (!qstrRet.isEmpty())
   {
      qstrRet = "select objectid from WMS_DM_OBJECT where Objectid in " + qstrRet;
   }
   
   return qstrRet;
}


/** +-=---------------------------------------------------------Fr 12. Nov 09:15:57 2010----------*
 * @method  CftlQueryEnhanced::ExecuteQuery                 // private                           *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrSql                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 12. Nov 09:15:57 2010----------*/
qint64 CftlCommandlQueryEnhanced::ExecuteQuery(QString p_qstrSql)
{
  qint64 lRet = CdmLogging::eDmUnknownDBQueryError;
   QSqlQuery cQSqlQuery;

   if (!p_qstrSql.isEmpty())
   {
      lRet = m_rpCftlDataAccess->ExecuteQuery(p_qstrSql, cQSqlQuery);

      if(lRet > 0)
      {
         if(cQSqlQuery.first())
         {
            int iRowCount = 0;
            do
            {
               int iColumnCount = m_rpCdmQuery->GetColumnCount();

               if (m_rpCdmQuery->ContainsGrouping()) // only one result means there is no objectid in result
               {
                  QVariant qVariant = cQSqlQuery.value(0);
                  QString qstrTemp = qVariant.toString();
                  CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, 0, qVariant, -1, -1);
               }
               else
               {
                  QVariant qvObjectId = cQSqlQuery.value(iColumnCount);
                 qint64 lObjectId = qvObjectId.toInt();
                 qint64 lContainerId = cQSqlQuery.value(iColumnCount + 1).toInt();

                  for (int iCounter = 0; iCounter < iColumnCount; ++iCounter)
                  {
                     QVariant qVariant = cQSqlQuery.value(iCounter);
                     QString qstrTemp = qVariant.toString();
                     CdmDataAccessHelper::SetQueryEnhancedResult(m_rpCdmQuery, iCounter, qVariant, lObjectId, lContainerId);
                  }

                  ++iRowCount;
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


/** +-=---------------------------------------------------------Do 11. Nov 11:29:36 2010----------*
 * @method  CftlQueryEnhanced::GenerateCompleteSql          // private                           *
 * @return  QString                                          //                                   *
 * @param   QVector<QString> p_qvKeynames                    //                                   *
 * @param   QString p_qstrObjectIdSql                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 11:29:36 2010----------*/
QString CftlCommandlQueryEnhanced::GenerateCompleteSql(QVector<QString> p_qvKeynames,
                                                QString p_qstrObjectIdSql)
{
   QString qstrSql;
   int iCount = p_qvKeynames.count();
   QString qstrSelect = "select distinct ";
   QString qstrFrom;
   QString qstrFirstTableKeyname = "{Missing}";
   bool bNoObjectNeededInResult = !m_rpCdmQuery->IsObjectNeededInResult();

   // if query contains grouping there can be no where condition because connection over objectid from each
   // subquery is not possible.
   for (int iCounter = 0; iCounter < iCount; ++iCounter)
   {
      QString qstrKeyname = p_qvKeynames[iCounter];
      QString qstrSubQuery = GenerateSubQuery(qstrKeyname, p_qstrObjectIdSql);
      qstrKeyname = MakeKeynameSave(qstrKeyname);
      qstrSelect += qstrKeyname + ".Value";

      if (bNoObjectNeededInResult)
      {
         qstrSelect += " as Value";
      }

      if ((qstrFirstTableKeyname == "{Missing}" && !p_qvKeynames[iCounter].contains(".")) || bNoObjectNeededInResult)
      {
         qstrFirstTableKeyname = qstrKeyname;
         qstrFrom = qstrSubQuery + " " + qstrFrom;
      }
      else if (!bNoObjectNeededInResult)
      {
         qstrFrom += " left outer join " + qstrSubQuery + " on " + qstrFirstTableKeyname + ".ObjectId = " + qstrKeyname + ".ObjectId";
      }
      
      if (iCounter + 1 == iCount && !bNoObjectNeededInResult)
      {
         qstrSelect += ", " + qstrFirstTableKeyname + ".ObjectId";
      }
      else if (iCounter + 1 < iCount)
      {
         qstrSelect += ", ";
      }
   }

   if (qstrFirstTableKeyname == "{Missing}")
   {
      FATAL("Invalid wql situation you need at least one member direct in the object!");
   }

   qstrSql = qstrSelect + " from " + qstrFrom;
   qstrSql = qstrSql.replace("{Missing}", qstrFirstTableKeyname);

   if (!m_rpCdmQuery->GetOrderBy().isEmpty())
   {
       // Old COde
//      QString qstrOrderBy = MakeKeynameSave(m_rpCdmQuery->GetOrderBy());
//      qstrSql += " order by " + qstrOrderBy + ".Value";

//      if (m_rpCdmQuery->GetOrderMode())
//      {
//         qstrSql += " asc";
//      }
//      else
//      {
//         qstrSql += " desc";
//      }
   }

   return qstrSql;
}

/** +-=---------------------------------------------------------Sa 14. Mai 14:11:46 2011----------*
 * @method  CftlQueryEnhanced::MakeKeynameSave              // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Mai 14:11:46 2011----------*/
QString CftlCommandlQueryEnhanced::MakeKeynameSave(QString p_qstrKeyname)
{
   return CwmsUtilities::MakeKeynameSave(p_qstrKeyname, m_qmKeynames, m_iKeynameCount);
}

/** +-=---------------------------------------------------------Mo 25. Mrz 14:18:13 2013----------*
 * @method  CftlQueryEnhanced::GenerateCompleteSubSql       // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrObjectIdSql                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Mrz 14:18:13 2013----------*/
QString CftlCommandlQueryEnhanced::GenerateCompleteSubSql(QString p_qstrKeyname, QString p_qstrObjectIdSql)
{
   QString qstrSql;
   QString qstrSelect = "select ";
   QString qstrFrom = " from ";

   // if query contains grouping there can be no where condition because connection over objectid from each
   // subquery is not possible.
   qstrSelect += p_qstrKeyname + ".Value, " + p_qstrKeyname + ".ObjectId";
   qstrFrom += GenerateSubQuery(p_qstrKeyname, p_qstrObjectIdSql);
   qstrSql = qstrSelect + qstrFrom;
   return qstrSql;
}



/** +-=---------------------------------------------------------Do 11. Nov 10:03:25 2010----------*
 * @method  CftlQueryEnhanced::GenerateSubQuery             // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrObjectIdQuery                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 10:03:25 2010----------*/
QString CftlCommandlQueryEnhanced::GenerateSubQuery(QString p_qstrKeyname, QString p_qstrObjectIdQuery)
{
   QString qstrSql;

   if (p_qstrKeyname.contains("."))
   {
      qstrSql = GenerateReferencingSubQuery(p_qstrKeyname, p_qstrObjectIdQuery);
   }
   else
   {
      qstrSql = GenerateDirectSubQuery(p_qstrKeyname, p_qstrObjectIdQuery);
   }

   return qstrSql;
}


/** +-=---------------------------------------------------------Sa 7. Mai 12:51:27 2011-----------*
 * @method  CftlQueryEnhanced::GenerateDirectSubQuery       // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrObjectIdQuery                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 12:51:27 2011-----------*/
QString CftlCommandlQueryEnhanced::GenerateDirectSubQuery(QString p_qstrKeyname,
                                                   QString p_qstrObjectIdQuery)
{
   QString qstrSql;
   QString qstrTableName = GetTableName(p_qstrKeyname);
   QString qstrTableIdName = GetTableIdName();

   qstrSql = CreateSelectPartOfSubquery(p_qstrKeyname) + " from ";
   qstrSql += qstrTableName + " a,";
   qstrSql += "(" + p_qstrObjectIdQuery + ") b ";
   qstrSql += "where ";
   qstrSql += "a.Keyname = '" + p_qstrKeyname + "' and a.objectid = b.objectid";
   qstrSql += ") " + MakeKeynameSave(p_qstrKeyname);

   return qstrSql;
}


/** +-=---------------------------------------------------------Sa 7. Mai 12:52:40 2011-----------*
 * @method  CftlQueryEnhanced::GenerateReferencingSubQuery  // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrObjectIdQuery                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 12:52:40 2011-----------*/
QString CftlCommandlQueryEnhanced::GenerateReferencingSubQuery(QString p_qstrKeyname,
                                                        QString p_qstrObjectIdQuery)
{
   QString qstrSql;

   QString qstrOriginalObjectIdQuery = p_qstrObjectIdQuery;
   QString qstrOriginalKeyname = p_qstrKeyname;

   if (p_qstrKeyname.contains(".")) // iterating over all references and enhancing the objectquery
   {
      int iPos = p_qstrKeyname.indexOf(".");
      QString qstrKeyname = p_qstrKeyname.mid(0, iPos);
      p_qstrKeyname = p_qstrKeyname.mid(iPos + 1, p_qstrKeyname.length() - iPos - 1);
      p_qstrObjectIdQuery = GenerateCompleteSubSql(qstrKeyname, p_qstrObjectIdQuery);
      QString qstrReplaceString = qstrKeyname + ".Value, " + qstrKeyname  + ".ObjectId"; //Team.Value, Team.ObjectId
      QString qstrNewString = MakeKeynameSave(qstrKeyname) + ".Value as objectid, "  + MakeKeynameSave(qstrKeyname) + ".ObjectId as OriginalObjectId";
      p_qstrObjectIdQuery = p_qstrObjectIdQuery.replace(qstrReplaceString, qstrNewString);
   }

   QString qstrTableName = GetTableName(qstrOriginalKeyname);
   QString qstrTableIdName = GetTableIdName();

   qstrSql = CreateSelectPartOfSubquery(qstrOriginalKeyname) + " from ";
   qstrSql += qstrTableName + " a, ";
   qstrSql += "(" + qstrOriginalObjectIdQuery + ") b, "; // this laods the objectids of the first objectref
   qstrSql += "(" + p_qstrObjectIdQuery + ") h "; // this loads the objectids for the referencing values
   qstrSql += "where ";
   qstrSql += "h.objectid = a.ObjectId and ";
   qstrSql += "h.OriginalObjectId = b.objectid and ";
   qstrSql += "a.Keyname = '" + p_qstrKeyname + "' ";
   qstrSql += ") " + MakeKeynameSave(qstrOriginalKeyname);

   return qstrSql;
}


/** +-=---------------------------------------------------------Mi 4. Mai 13:31:21 2011-----------*
 * @method  CftlQueryEnhanced::CreateSelectPartOfSubquery   // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 4. Mai 13:31:21 2011-----------*/
QString CftlCommandlQueryEnhanced::CreateSelectPartOfSubquery(QString p_qstrKeyname)
{
   QString qstrSelect;
   CdmQueryResultElement* pCdmResultElement = m_rpCdmQuery->GetResultElement(p_qstrKeyname);
   QString qstrDataField = GetDataFieldName(p_qstrKeyname);

   if (!pCdmResultElement || pCdmResultElement->GetMode() == eDmQueryResultElementModeNone)
   {
      qstrSelect = "(select " + qstrDataField + " as value, b.objectId as objectid";
   }
   else
   {
      qstrSelect = "(select " + qstrDataField + " as value";
   }

   return qstrSelect;
}


/** +-=---------------------------------------------------------Do 11. Nov 10:09:27 2010----------*
 * @method  CftlQueryEnhanced::GetDataFieldName             // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method returns the name of the datafield.                                        *
 *----------------last changed: --------------------------------Do 11. Nov 10:09:27 2010----------*/
QString CftlCommandlQueryEnhanced::GetDataFieldName(QString p_qstrKeyname)
{
   QString qstrRet;
   CdmQueryResultElement* pCdmResultElement = m_rpCdmQuery->GetResultElement(p_qstrKeyname);

   if (pCdmResultElement)
   {
      qstrRet = CftlDataStructureHelper::GetDataFieldName();

      switch (pCdmResultElement->GetMode())
      {
      case eDmQueryResultElementModeSum:
         qstrRet = "sum(a." + qstrRet + ")";
         break;
      case eDmQueryResultElementModeAvg:
         qstrRet = "avg(a." + qstrRet + ")";
         break;
      case eDmQueryResultElementModeMax:
         qstrRet = "max(a." + qstrRet + ")";
         break;
      case eDmQueryResultElementModeMin:
         qstrRet = "min(a." + qstrRet + ")";
         break;
      default: // no grouping mode
         qstrRet = "a." + qstrRet;
         break;
      }
   }
   else // not found expecting that is it a reference value.
   {
      qstrRet = "a.val";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Do 11. Nov 11:27:19 2010----------*
 * @method  CftlQueryEnhanced::GetTableName                 // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment This method returns the tablename dependent to the queryelement.                      *
 *----------------last changed: --------------------------------Do 11. Nov 11:27:19 2010----------*/
QString CftlCommandlQueryEnhanced::GetTableName(QString p_qstrKeyname)
{
   QString qstrTableName;
   CdmQueryResultElement* pCdmResultElement = m_rpCdmQuery->GetResultElement(p_qstrKeyname);

   if (pCdmResultElement)
   {
      if (p_qstrKeyname.contains("."))
      {
         const CdmClass* pCdmClass = m_rpCdmQuery->GetClass();

         if (CHKPTR(pCdmClass))
         {
            const CdmMember* pMember = pCdmClass->FindMember(p_qstrKeyname);

            if (pMember)
            {
               EdmValueType eDmValueType = pCdmResultElement->GetValueType();

               if (eDmValueType != eDmValueNone)
               {
                  qstrTableName = CftlDataStructureHelper::GetTableName(eDmValueType);
               }
            }
            else
            {
               ERR("Member not found");
               qstrTableName = "NOT_FOUND";
            }
         }
      }
      else
      {
         EdmValueType eDmValueType = pCdmResultElement->GetValueType();

         if (eDmValueType != eDmValueNone)
         {
            qstrTableName = CftlDataStructureHelper::GetTableName(eDmValueType);
         }
      }
   }
   else
   {
      qstrTableName = "V_VALUE_OBJECTREFERENCE";
   }

   return qstrTableName;
}

/** +-=---------------------------------------------------------Mo 25. Mrz 15:35:32 2013----------*
 * @method  CftlQueryEnhanced::GetTableIdName               // public                            *
 * @return  QString                                          //                                   *
 * @comment This method returns the name of the id field in the table.                            *
 *----------------last changed: --------------------------------Mo 25. Mrz 15:35:32 2013----------*/
QString CftlCommandlQueryEnhanced::GetTableIdName()
{
   return "valueid";
}
