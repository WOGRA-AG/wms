/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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

/*
 * This class implements the queries on db side
 */
class CdbQuery
{
   private:

	  /*
	   * The dataacces
	   */
      CdbDataAccess* m_rpCdbDataAccess;
      /*
       * The soruce query
       */
      CdmQuery*        m_rpCdmQuery;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:09:48 2005*
    * @method  CdbQuery::CdbQuery                        // public                            *
    * @return                                                //                                   *
    * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
    * @param   CdmQuery* p_pCdmQuery                         //                                   *
    * @comment The cosntructor                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:09:48 2005----------*/
CdbQuery(  CdbDataAccess* p_pCdbDataAccess, CdmQuery* p_pCdmQuery );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:09:55 2005*
    * @method  CdbQuery::~CdbQuery                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdbQuery                                                 *
    *----------------last changed: -----------------------------Sa 20. Aug 12:09:55 2005----------*/
virtual ~CdbQuery(  );




   public:
   /** +-=---------------------------------------------------------Do 11. Nov 08:35:47 2010-------*
    * @method  CdbQuery::ExecuteQuery                      // public                            *
    * @return qint64                                          //                                   *
    * @comment Executes the query without any parameters. Works with the faster query             *
    *          algorithm.                                                                         *
    *----------------last changed: -----------------------------Do 11. Nov 08:35:47 2010----------*/
   qint64 ExecuteQuery();

   private:
    void SortResults(QString& p_qstrQuery);

   public:
   /** +-=---------------------------------------------------------Do 23. Aug 15:22:34 2007-------*
    * @method  CdbQuery::GetTableName                      // public, static                    *
    * @return  QString                                       //                                   *
    * @param   CdbDataAccess::EodbcBaseType p_eType        //                                   *
    * @comment This method returns the tablename dependent to the queryelement.                   *
    *----------------last changed: -----------------------------Do 23. Aug 15:22:34 2007----------*/
    static QString GetTableName(CdbDataAccess::EodbcBaseType p_eType);

   public:
   /** +-=---------------------------------------------------------Do 23. Aug 15:24:41 2007-------*
    * @method  CdbQuery::GetDataFieldName                  // public, static                    *
    * @return  QString                                       //                                   *
    * @param   CdbDataAccess::EodbcBaseType p_eType        //                                   *
    * @comment This method returns the name of the datafield.                                     *
    *----------------last changed: -----------------------------Do 23. Aug 15:24:41 2007----------*/
    static QString GetDataFieldName(CdbDataAccess::EodbcBaseType p_eType);

   public:
   /** +-=---------------------------------------------------------Sa 10. Nov 13:13:20 2007-------*
    * @method  CdbQuery::GetTableIdName                    // public                            *
    * @return  QString                                       //                                   *
    * @param   CdbDataAccess::EodbcBaseType p_eType        //                                   *
    * @comment This method returns the name of the id field in the table.                         *
    *----------------last changed: Wolfgang Gra�of-------------Sa 10. Nov 13:13:20 2007----------*/
    QString GetTableIdName(CdbDataAccess::EodbcBaseType p_eType);

   private:
   /** +-=---------------------------------------------------------Sa 10. Nov 13:20:22 2007-------*
    * @method  CdbQuery::CreateStringFromResultList        // private                           *
    * @return  QString                                       //                                   *
    * @param   QValueList<qint64>& p_rqvlResults               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Gra�of-------------Sa 10. Nov 13:20:22 2007----------*/
    QString CreateStringFromResultList(QMap<qint64,qint64>& p_rqvlResults);

   private:
    void SortResultsOwnMember(QStringList p_qstrSortKey, QString& p_qstrQuery);

   private:

    void ReadMemberIdAndBaseType(QString p_qstrSortKey,
                                 CdbDataAccess::EodbcBaseType& p_eBasType,
                                 int& p_iMemberId,
                                 int& p_iObjectRefClassId);

   public:
   /** +-=---------------------------------------------------------So 5. Jun 11:38:32 2011--------*
    * @method  CdbQuery::GenerateSql                       // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 5. Jun 11:38:32 2011-----------*/
    virtual QString GenerateSql();

   private:
   /** +-=---------------------------------------------------------Do 11. Nov 08:35:32 2010-------*
    * @method  CdbQuery::ExecuteEnhanced                   // private                           *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 08:35:32 2010----------*/
   qint64 ExecuteEnhanced();

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 08:36:07 2010-------*
    * @method  CdbQuery::Execute                           // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 08:36:07 2010----------*/
   qint64 Execute();

   private:
   /** +-=---------------------------------------------------------Mo 9. Mai 15:56:25 2011--------*
    * @method  CdbQuery::ExecuteObjectListQuery            // private                           *
    * @return qint64                                          //                                   *
    * @param   QList<qint64>& p_rqllResults              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Mai 15:56:25 2011-----------*/
   qint64 ExecuteObjectListQuery(QMap<qint64,qint64>& p_rqllResults);

    bool IsQueryElementValid(CdmQueryElement *p_pElement);
   qint64 ExecuteSqlQuery(QMap<qint64,qint64>& p_rqllResults, QString qstrSql);

public:
   /** +-=---------------------------------------------------------So 5. Jun 11:47:27 2011--------*
    * @method  CdbQuery::GenerateQuerySql                  // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 5. Jun 11:47:27 2011-----------*/
    QString GenerateQuerySql();
    void SortResultsReference(QString p_qstrSortKey, QString &p_qstrQuery);
};

#endif //
