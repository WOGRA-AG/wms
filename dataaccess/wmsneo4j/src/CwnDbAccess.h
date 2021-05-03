/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�of
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CODBCwnACCESS_H
#define CODBCwnACCESS_H

// System and QT Includes
#include <qstring.h>
#include <QList>

// own Includes
#include "CwnDataAccess.h"

// forwards
class CwnDataAccess;
class CdmScheme;

/*
 * This class implements the dataaccess to
 * virtual databases.
 */
class CwnSchemeAccess
{

   protected:
      /*
       * The dataaccess
       */
      CwnDataAccess* m_rpCwnDataAccess;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005*
    * @method  CwnDbAccess::CwnDbAccess                  // public                            *
    * @return                                                //                                   *
    * @param   CwnDataAccess* p_pCwnDataAccess           //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:30 2005----------*/
CwnSchemeAccess(  CwnDataAccess* p_pCwnDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005*
    * @method  CwnDbAccess::~CwnDbAccess                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwnDbAccess                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:50:33 2005----------*/
virtual ~CwnSchemeAccess(  );

   public:
   /** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005*
    * @method  CwnDbAccess::CreateDb                       // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_rpCdmDatabase                 //                                   *
    * @comment This method creates a new database.                                                *
    *----------------last changed: -----------------------------So 11. Sep 11:54:28 2005----------*/
virtual long CreateDb(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005*
    * @method  CwnDbAccess::DeleteDb                       // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment Deletes the Database from db.                                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:45 2005----------*/
virtual long DeleteScheme(  QString p_qstrKeyname );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:49 2005*
    * @method  CwnDbAccess::ExistDb                        // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool& p_bRet                                  //                                   *
    * @comment This method checks if a database exists.                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:49 2005----------*/
long ExistDb(  QString p_qstrKeyname, bool& p_bRet );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:52 2005*
    * @method  CwnDbAccess::FindDatabase                   // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmDatabase*& p_pCdmDatabaseManager           //                                   *
    * @comment This method fins a database and returns it.                                        *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:52 2005----------*/
long FindDatabase(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager );
long FindDatabase(long p_lSchemeId, CdmScheme*& p_pCdmDatabaseManager );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005*
    * @method  CwnDbAccess::GetDatabaseList                // public                            *
    * @return  long                                          //                                   *
    * @param   QValueList<QString>& p_rqvlDatabases          //                                   *
    * @comment This method fills the list of all virutal databases.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:51:56 2005----------*/
long GetDatabaseList(  QList<QString>& p_rqvlDatabases );

   public:
   /** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012-------*
    * @method  CwnDbAccess::UpdateDatabase                 // public                            *
    * @return  long                                          //                                   *
    * @param   CdmDatabase* p_pCdmDatabase                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Jun 15:46:44 2012----------*/
    long UpdateDatabase(CdmScheme* p_pCdmDatabase);

   public:
   /** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012--------*
    * @method  CwnDbAccess::AddLanguage                    // public, virtual                   *
    * @return  int                                           //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   QString p_qstrLanguage                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 4. Jul 15:08:16 2012-----------*/
    virtual int AddLanguage(long p_lDatabaseId, QString p_qstrLanguage);

   public:
   /** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012-------*
    * @method  CwnDbAccess::DeleteLanguage                 // public                            *
    * @return  int                                           //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   int p_iLanguageId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 19. Aug 11:24:43 2012----------*/
    int DeleteLanguage(long p_lDatabaseId, int p_iLanguageId);
    //bool CleanupDb();
};


#endif
