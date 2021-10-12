/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CftlQueryEnhanced.h
 ** Started Implementation: 2010/11/11
 ** Description:
 ** 
 ** This class implements the sql access for enhanced queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCQUERYENHANCED_H
#define CODBCQUERYENHANCED_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVector>

// WMS Manager Includes


// Own Includes


// Forwards
class CdmQueryEnhanced;
class CftlDataAccess;

// Enumerations


/* 
 * This class implements the sql access for enhanced queries
 */
class CftlCommandlQueryEnhanced
{
   private:
      CdmQueryEnhanced* m_rpCdmQuery;
      CftlDataAccess* m_rpCftlDataAccess;
      int m_iKeynameCount;
      QMap<QString, int> m_qmKeynames;


   public:
   /** +-=---------------------------------------------------------Do 11. Nov 14:13:25 2010-------*
    * @method  CftlQueryEnhanced::CftlQueryEnhanced        // public                            *
    * @return                                                //                                   *
    * @param   CdmQueryEnhanced* p_pCdmQueryEnhanced         //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 14:13:25 2010----------*/
    CftlCommandlQueryEnhanced( CdmQueryEnhanced* p_pCdmQueryEnhanced, CftlDataAccess* p_pCftlDataAccess);

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 09:40:12 2010-------*
    * @method  CftlQueryEnhanced::~CftlQueryEnhanced       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlQueryEnhanced                                         *
    *----------------last changed: -----------------------------Do 11. Nov 09:40:12 2010----------*/
    virtual ~CftlCommandlQueryEnhanced( );

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 09:40:25 2010-------*
    * @method  CftlQueryEnhanced::Execute                   // public                            *
    * @return qint64                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 09:40:25 2010----------*/
   qint64 Execute();

   private:
   /** +-=---------------------------------------------------------Do 11. Nov 11:29:36 2010-------*
    * @method  CftlQueryEnhanced::GenerateCompleteSql       // private                           *
    * @return  QString                                       //                                   *
    * @param   QVector<QString> p_qvKeynames                 //                                   *
    * @param   QString p_qstrObjectIdSql                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 11:29:36 2010----------*/
    QString GenerateCompleteSql(QVector<QString> p_qvKeynames, QString p_qstrObjectIdSql);

   private:
   /** +-=---------------------------------------------------------Do 11. Nov 10:03:25 2010-------*
    * @method  CftlQueryEnhanced::GenerateSubQuery          // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrObjectIdQuery                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 11. Nov 10:03:25 2010----------*/
    QString GenerateSubQuery(QString p_qstrKeyname, QString p_qstrObjectIdQuery);

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 10:09:27 2010-------*
    * @method  CftlQueryEnhanced::GetDataFieldName          // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method returns the name of the datafield.                                     *
    *----------------last changed: -----------------------------Do 11. Nov 10:09:27 2010----------*/
    QString GetDataFieldName(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Do 11. Nov 11:27:19 2010-------*
    * @method  CftlQueryEnhanced::GetTableName              // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method returns the tablename dependent to the queryelement.                   *
    *----------------last changed: -----------------------------Do 11. Nov 11:27:19 2010----------*/
    QString GetTableName(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mo 25. Mrz 15:35:32 2013-------*
    * @method  CftlQueryEnhanced::GetTableIdName            // public                            *
    * @return  QString                                       //                                   *
    * @comment This method returns the name of the id field in the table.                         *
    *----------------last changed: -----------------------------Mo 25. Mrz 15:35:32 2013----------*/
    QString GetTableIdName();

   private:
   /** +-=---------------------------------------------------------Fr 12. Nov 09:15:57 2010-------*
    * @method  CftlQueryEnhanced::ExecuteQuery              // private                           *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrSql                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Nov 09:15:57 2010----------*/
   qint64 ExecuteQuery(QString p_qstrSql);

   private:
   /** +-=---------------------------------------------------------Mi 4. Mai 13:31:21 2011--------*
    * @method  CftlQueryEnhanced::CreateSelectPartOfSubquery // private                          *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 4. Mai 13:31:21 2011-----------*/
    QString CreateSelectPartOfSubquery(QString p_qstrKeyname);


   private:
   /** +-=---------------------------------------------------------Sa 7. Mai 12:51:27 2011--------*
    * @method  CftlQueryEnhanced::GenerateDirectSubQuery    // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrObjectIdQuery                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 7. Mai 12:51:27 2011-----------*/
    QString GenerateDirectSubQuery(QString p_qstrKeyname, QString p_qstrObjectIdQuery);

   private:
   /** +-=---------------------------------------------------------Sa 7. Mai 12:52:40 2011--------*
    * @method  CftlQueryEnhanced::GenerateReferencingSubQuery // private                         *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrObjectIdQuery                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 7. Mai 12:52:40 2011-----------*/
    QString GenerateReferencingSubQuery(QString p_qstrKeyname, QString p_qstrObjectIdQuery);

   private:
   /** +-=---------------------------------------------------------Mo 25. Mrz 14:18:13 2013-------*
    * @method  CftlQueryEnhanced::GenerateCompleteSubSql    // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrObjectIdSql                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Mrz 14:18:13 2013----------*/
    QString GenerateCompleteSubSql(QString p_qstrKeyname, QString p_qstrObjectIdSql);

   private:
   /** +-=---------------------------------------------------------Mi 11. Mai 18:15:48 2011-------*
    * @method  CftlQueryEnhanced::ExecuteFirstPartQuery     // private                           *
    * @return  QString                                       // the result                        *
    * @param   QString p_qstrQuery                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 11. Mai 18:15:48 2011----------*/
    QString ExecuteFirstPartQuery(QString p_qstrQuery);






   private:
   /** +-=---------------------------------------------------------Sa 14. Mai 14:11:46 2011-------*
    * @method  CftlQueryEnhanced::MakeKeynameSave           // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Mai 14:11:46 2011----------*/
    QString MakeKeynameSave(QString p_qstrKeyname);


   public:
   /** +-=---------------------------------------------------------So 5. Jun 11:36:11 2011--------*
    * @method  CftlQueryEnhanced::GenerateSql               // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 5. Jun 11:36:11 2011-----------*/
    virtual QString GenerateSql();
};

#endif //
