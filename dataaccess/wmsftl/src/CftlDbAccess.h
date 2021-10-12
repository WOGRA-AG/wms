/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CODBCDBACCESS_H
#define CODBCDBACCESS_H

// System and QT Includes
#include <qstring.h>
#include <QList>

// own Includes
#include "CftlDataAccess.h"

// forwards
class CftlDataAccess;
class CdmScheme;

/*
 * This class implements the dataaccess to
 * virtual databases.
 */
class CftlSchemeAccess
{

   protected:
      /*
       * The dataaccess
       */
      CftlDataAccess* m_rpCftlDataAccess;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005*
    * @method  CftlDbAccess::CftlDbAccess                  // public                            *
    * @return                                                //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:30 2005----------*/
CftlSchemeAccess(  CftlDataAccess* p_pCftlDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005*
    * @method  CftlDbAccess::~CftlDbAccess                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlDbAccess                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:50:33 2005----------*/
virtual ~CftlSchemeAccess(  );

   public:
   /** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005*
    * @method  CftlDbAccess::CreateDb                       // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_rpCdmDatabase                 //                                   *
    * @comment This method creates a new database.                                                *
    *----------------last changed: -----------------------------So 11. Sep 11:54:28 2005----------*/
virtual qint64 CreateDb(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005*
    * @method  CftlDbAccess::DeleteDb                       // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment Deletes the Database from db.                                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:45 2005----------*/
virtual qint64 DeleteDb(  QString p_qstrKeyname );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:49 2005*
    * @method  CftlDbAccess::ExistDb                        // public                            *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool& p_bRet                                  //                                   *
    * @comment This method checks if a database exists.                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:49 2005----------*/
qint64 ExistDb(  QString p_qstrKeyname, bool& p_bRet );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:52 2005*
    * @method  CftlDbAccess::FindDatabase                   // public                            *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_pCdmDatabaseManager           //                                   *
    * @comment This method fins a database and returns it.                                        *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:52 2005----------*/
qint64 FindDatabase(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager );


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005*
    * @method  CftlDbAccess::GetDatabaseList                // public                            *
    * @return qint64                                          //                                   *
    * @param   QValueList<QString>& p_rqvlDatabases          //                                   *
    * @comment This method fills the list of all virutal databases.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:56 2005----------*/
qint64 GetDatabaseList(  QList<QString>& p_rqvlDatabases );

   public:
   /** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012-------*
    * @method  CftlDbAccess::UpdateDatabase                 // public                            *
    * @return qint64                                          //                                   *
    * @param   CdmDatabase* p_pCdmDatabase                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Jun 15:46:44 2012----------*/
   qint64 UpdateDatabase(CdmScheme* p_pCdmDatabase);

   public:
   /** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012--------*
    * @method  CftlDbAccess::AddLanguage                    // public, virtual                   *
    * @return  int                                           //                                   *
    * @param  qint64 p_lDatabaseId                            //                                   *
    * @param   QString p_qstrLanguage                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 4. Jul 15:08:16 2012-----------*/
    virtual int AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage);

   public:
   /** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012-------*
    * @method  CftlDbAccess::DeleteLanguage                 // public                            *
    * @return  int                                           //                                   *
    * @param  qint64 p_lDatabaseId                            //                                   *
    * @param   int p_iLanguageId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 19. Aug 11:24:43 2012----------*/
    int DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId);
    bool CleanupDb();
   qint64 FindDatabase(qint64 p_lId, CdmScheme *&p_pCdmDatabaseManager);
};


#endif //
