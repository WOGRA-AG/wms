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
#include <QLinkedList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CftlCommandExistScheme.h"
#include "CftlCommandCleanupDB.h"
#include "CftlCommandCreateScheme.h"
#include "CftlCommandDeleteScheme.h"
#include "CftlCommandFindScheme.h"
#include "CftlCommandGetSchemeList.h"
#include "CftlCommandUpdateScheme.h"
#include "CftlCommandAddSchemeLanguage.h"
#include "CftlCommandDeleteSchemeLanguage.h"
#include "CwmsUtilities.h"
#include "CftlDataAccess.h"
#include "CftlDbAccess.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005----------*
 * @method  CftlDbAccess::CftlDbAccess                     // public                            *
 * @return                                                   //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:30 2005----------*/
CftlSchemeAccess::CftlSchemeAccess(  CftlDataAccess* p_pCftlDataAccess )
   : m_rpCftlDataAccess(p_pCftlDataAccess)
{
   // nothing todo
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005----------*
 * @method  CftlDbAccess::~CftlDbAccess                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlDbAccess                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:50:33 2005----------*/
CftlSchemeAccess::~CftlSchemeAccess(  )
{
   // nothing todo
}

/** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005----------*
 * @method  CftlDbAccess::CreateDb                          // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_rpCdmDatabase                    //                                   *
 * @comment This method creates a new database.                                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:54:28 2005----------*/
long CftlSchemeAccess::CreateDb(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CftlCommandCreateScheme command(p_qstrKeyname, m_rpCftlDataAccess);
   lRet = command.Run();
   p_rpCdmDatabase = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005----------*
 * @method  CftlDbAccess::DeleteDb                          // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment Deletes the Database from db.                                                         *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:45 2005----------*/
long CftlSchemeAccess::DeleteDb(  QString p_qstrKeyname )
{
    CftlCommandDeleteScheme command(p_qstrKeyname, m_rpCftlDataAccess);
    return command.Run();
}

bool CftlSchemeAccess::CleanupDb() 
{
    CftlCommandCleanupDB command(m_rpCftlDataAccess);

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
 * @method  CftlDbAccess::ExistDb                           // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if a database exists.                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:49 2005----------*/
long CftlSchemeAccess::ExistDb(  QString p_qstrKeyname, bool& p_bRet )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CftlCommandExistScheme command(p_qstrKeyname, m_rpCftlDataAccess);
   long lId = command.Run();

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
 * @method  CftlDbAccess::FindDatabase                      // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_pCdmDatabaseManager              //                                   *
 * @comment This method fins a database and returns it.                                           *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:52 2005----------*/
long CftlSchemeAccess::FindDatabase(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CftlCommandFindScheme command(p_qstrKeyname, m_rpCftlDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

long CftlSchemeAccess::FindDatabase(long p_lId, CdmScheme*& p_pCdmDatabaseManager)
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CftlCommandFindScheme command(p_lId, m_rpCftlDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005----------*
 * @method  CftlDbAccess::GetDatabaseList                   // public                            *
 * @return  long                                             //                                   *
 * @param   QValueList<QString>& p_rqvlDatabases             //                                   *
 * @comment This method fills the list of all virutal databases.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:56 2005----------*/
long CftlSchemeAccess::GetDatabaseList(  QLinkedList<QString>& p_rqvlDatabases )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CftlCommandGetSchemeList command(m_rpCftlDataAccess);
   lRet = command.Run();
   p_rqvlDatabases.clear();

   if (SUCCESSFULL(lRet))
   {
     p_rqvlDatabases = command.GetSchemes();
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012----------*
 * @method  CftlDbAccess::UpdateDatabase                    // public                            *
 * @return  long                                             //                                   *
 * @param   CdmDatabase* p_pCdmDatabase                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 15:46:44 2012----------*/
long CftlSchemeAccess::UpdateDatabase(CdmScheme* p_pCdmDatabase)
{
   CftlCommandUpdateScheme command(p_pCdmDatabase, m_rpCftlDataAccess);
   return command.Run();
}


/** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012----------*
 * @method  CftlDbAccess::DeleteLanguage                    // public                            *
 * @return  int                                              //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   int p_iLanguageId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 19. Aug 11:24:43 2012----------*/
int CftlSchemeAccess::DeleteLanguage(long p_lDatabaseId, int p_iLanguageId)
{
    CftlCommandDeleteSchemeLanguage command(p_lDatabaseId, p_iLanguageId, m_rpCftlDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012-----------*
 * @method  CftlDbAccess::AddLanguage                       // public, virtual                   *
 * @return  int                                              //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   QString p_qstrLanguage                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 4. Jul 15:08:16 2012-----------*/
int CftlSchemeAccess::AddLanguage(long p_lDatabaseId, QString p_qstrLanguage)
{
    CftlCommandAddSchemeLanguage command(p_lDatabaseId, p_qstrLanguage, m_rpCftlDataAccess);
    return command.Run();
}


