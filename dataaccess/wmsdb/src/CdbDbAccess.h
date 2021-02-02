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
#include <QLinkedList>

// own Includes
#include "CdbDataAccess.h"

// forwards
class CdbDataAccess;
class CdmScheme;

/*
 * This class implements the dataaccess to
 * virtual databases.
 */
class WMSDB_API CdbSchemeAccess
{

   protected:
      /*
       * The dataaccess
       */
      CdbDataAccess* m_rpCdbDataAccess;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005*
    * @method  CdbDbAccess::CdbDbAccess                  // public                            *
    * @return                                                //                                   *
    * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:30 2005----------*/
CdbSchemeAccess(  CdbDataAccess* p_pCdbDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005*
    * @method  CdbDbAccess::~CdbDbAccess                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdbDbAccess                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:50:33 2005----------*/
virtual ~CdbSchemeAccess(  );

   public:
   /** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005*
    * @method  CdbDbAccess::CreateDb                       // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_rpCdmDatabase                 //                                   *
    * @comment This method creates a new database.                                                *
    *----------------last changed: -----------------------------So 11. Sep 11:54:28 2005----------*/
virtual long CreateScheme(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005*
    * @method  CdbDbAccess::DeleteDb                       // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment Deletes the Database from db.                                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:45 2005----------*/
virtual long DeleteDb(  QString p_qstrKeyname );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:49 2005*
    * @method  CdbDbAccess::ExistDb                        // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool& p_bRet                                  //                                   *
    * @comment This method checks if a database exists.                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:49 2005----------*/
long ExistDb(  QString p_qstrKeyname, bool& p_bRet );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:52 2005*
    * @method  CdbDbAccess::FindDatabase                   // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_pCdmDatabaseManager           //                                   *
    * @comment This method fins a database and returns it.                                        *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:52 2005----------*/
long FindScheme(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager );


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005*
    * @method  CdbDbAccess::GetDatabaseList                // public                            *
    * @return  long                                          //                                   *
    * @param   QValueList<QString>& p_rqvlDatabases          //                                   *
    * @comment This method fills the list of all virutal databases.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:56 2005----------*/
long GetDatabaseList(  QLinkedList<QString>& p_rqvlDatabases );

   public:
   /** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012-------*
    * @method  CdbDbAccess::UpdateDatabase                 // public                            *
    * @return  long                                          //                                   *
    * @param   CdmDatabase* p_pCdmDatabase                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Jun 15:46:44 2012----------*/
    long UpdateDatabase(CdmScheme* p_pCdmDatabase);

   public:
   /** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012--------*
    * @method  CdbDbAccess::AddLanguage                    // public, virtual                   *
    * @return  int                                           //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   QString p_qstrLanguage                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 4. Jul 15:08:16 2012-----------*/
    virtual int AddLanguage(long p_lDatabaseId, QString p_qstrLanguage);

   public:
   /** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012-------*
    * @method  CdbDbAccess::DeleteLanguage                 // public                            *
    * @return  int                                           //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   int p_iLanguageId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 19. Aug 11:24:43 2012----------*/
    int DeleteLanguage(long p_lDatabaseId, int p_iLanguageId);
    bool CleanupDb();
    long FindScheme(long p_lId, CdmScheme *&p_pCdmDatabaseManager);
};


#endif //
