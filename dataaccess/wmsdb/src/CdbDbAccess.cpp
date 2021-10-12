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
#include <qsqlquery.h>
#include <qvariant.h>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbCommandExistScheme.h"
#include "CdbCommandCleanupDB.h"
#include "CdbCommandCreateScheme.h"
#include "CdbCommandDeleteScheme.h"
#include "CdbCommandFindScheme.h"
#include "CdbCommandGetSchemeList.h"
#include "CdbCommandUpdateScheme.h"
#include "CdbCommandAddSchemeLanguage.h"
#include "CdbCommandDeleteSchemeLanguage.h"
#include "CdbDataAccess.h"
#include "CdbDbAccess.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005----------*
 * @method  CdbDbAccess::CdbDbAccess                     // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:30 2005----------*/
CdbSchemeAccess::CdbSchemeAccess(CdbDataAccess* p_pCdbDataAccess)
   : m_rpCdbDataAccess(p_pCdbDataAccess)
{
   // nothing todo
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005----------*
 * @method  CdbDbAccess::~CdbDbAccess                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbDbAccess                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:50:33 2005----------*/
CdbSchemeAccess::~CdbSchemeAccess(  )
{
   // nothing todo
}

/** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005----------*
 * @method  CdbDbAccess::CreateDb                          // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_rpCdmDatabase                    //                                   *
 * @comment This method creates a new database.                                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:54:28 2005----------*/
qint64 CdbSchemeAccess::CreateScheme(QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandCreateScheme command(p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();
   p_rpCdmDatabase = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005----------*
 * @method  CdbDbAccess::DeleteDb                          // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment Deletes the Database from db.                                                         *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:45 2005----------*/
qint64 CdbSchemeAccess::DeleteDb(QString p_qstrKeyname)
{
    CdbCommandDeleteScheme command(p_qstrKeyname, m_rpCdbDataAccess);
    return command.Run();
}

bool CdbSchemeAccess::CleanupDb() 
{
    CdbCommandCleanupDB command(m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:49 2005----------*
 * @method  CdbDbAccess::ExistDb                           // public                            *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if a database exists.                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:49 2005----------*/
qint64 CdbSchemeAccess::ExistDb(QString p_qstrKeyname, bool& p_bRet)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandExistScheme command(p_qstrKeyname, m_rpCdbDataAccess);
  qint64 lId = command.Run();

   if (lId > 0)
   {
      p_bRet = true;
      lRet = EC(eDmOk);
   }
   else if (lId == 0)
   {
      p_bRet = false;
      lRet = EC(eDmFalse);
   }
   else
   {
      lRet = lId;
      p_bRet = false;
   }
  
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:52 2005----------*
 * @method  CdbDbAccess::FindDatabase                      // public                            *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_pCdmDatabaseManager              //                                   *
 * @comment This method fins a database and returns it.                                           *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:52 2005----------*/
qint64 CdbSchemeAccess::FindScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandFindScheme command(p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

qint64 CdbSchemeAccess::FindScheme(qint64 p_lId, CdmScheme*& p_pCdmDatabaseManager)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandFindScheme command(p_lId, m_rpCdbDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005----------*
 * @method  CdbDbAccess::GetDatabaseList                   // public                            *
 * @return qint64                                             //                                   *
 * @param   QValueList<QString>& p_rqvlDatabases             //                                   *
 * @comment This method fills the list of all virutal databases.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:56 2005----------*/
qint64 CdbSchemeAccess::GetDatabaseList(QList<QString>& p_rqvlDatabases)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandGetSchemeList command(m_rpCdbDataAccess);
   lRet = command.Run();
   p_rqvlDatabases.clear();

   if (SUCCESSFULL(lRet))
   {
     p_rqvlDatabases = command.GetSchemes();
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012----------*
 * @method  CdbDbAccess::UpdateDatabase                    // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmDatabase* p_pCdmDatabase                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 15:46:44 2012----------*/
qint64 CdbSchemeAccess::UpdateDatabase(CdmScheme* p_pCdmDatabase)
{
   CdbCommandUpdateScheme command(p_pCdmDatabase, m_rpCdbDataAccess);
   return command.Run();
}


/** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012----------*
 * @method  CdbDbAccess::DeleteLanguage                    // public                            *
 * @return  int                                              //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param   int p_iLanguageId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 19. Aug 11:24:43 2012----------*/
int CdbSchemeAccess::DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId)
{
    CdbCommandDeleteSchemeLanguage command(p_lDatabaseId, p_iLanguageId, m_rpCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012-----------*
 * @method  CdbDbAccess::AddLanguage                       // public, virtual                   *
 * @return  int                                              //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param   QString p_qstrLanguage                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 4. Jul 15:08:16 2012-----------*/
int CdbSchemeAccess::AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage)
{
    CdbCommandAddSchemeLanguage command(p_lDatabaseId, p_qstrLanguage, m_rpCdbDataAccess);
    return command.Run();
}


