/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
//#include <qsqlquery.h>
#include <qvariant.h>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CwnCommandExistScheme.h"
//#include "CwnCommandCleanupDB.h"
#include "CwnCommandCreateScheme.h"
#include "CwnCommandDeleteScheme.h"
#include "CwnCommandFindScheme.h"
#include "CwnCommandGetSchemeList.h"
#include "CwnCommandUpdateScheme.h"
#include "CwnCommandAddSchemeLanguage.h"
#include "CwnCommandDeleteSchemeLanguage.h"
#include "CwnHelper.h"
#include "CwnDataAccess.h"
#include "CwnDbAccess.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:51:30 2005----------*
 * @method  CwnDbAccess::CwnDbAccess                     // public                            *
 * @return                                                   //                                   *
 * @param   CwnDataAccess* p_pCwnDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:30 2005----------*/
CwnSchemeAccess::CwnSchemeAccess(  CwnDataAccess* p_pCwnDataAccess )
   : m_rpCwnDataAccess(p_pCwnDataAccess)
{
   // nothing todo
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:50:33 2005----------*
 * @method  CwnDbAccess::~CwnDbAccess                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwnDbAccess                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:50:33 2005----------*/
CwnSchemeAccess::~CwnSchemeAccess(  )
{
   // nothing todo
}

/** +-=---------------------------------------------------------So 11. Sep 11:54:28 2005----------*
 * @method  CwnDbAccess::CreateDb                          // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_rpCdmDatabase                    //                                   *
 * @comment This method creates a new database.                                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:54:28 2005----------*/
long CwnSchemeAccess::CreateDb(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CwnCommandCreateScheme command(p_qstrKeyname, m_rpCwnDataAccess);
   lRet = command.Run();
   p_rpCdmDatabase = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:45 2005----------*
 * @method  CwnDbAccess::DeleteDb                          // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment Deletes the Database from db.                                                         *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:45 2005----------*/
long CwnSchemeAccess::DeleteScheme(  QString p_qstrKeyname )
{
    CwnCommandDeleteScheme command(m_rpCwnDataAccess,p_qstrKeyname);
    return command.Run();
}
/*
bool CwnSchemeAccess::CleanupDb()
{
    CwnCommandCleanupDB command(m_rpCwnDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
*/
/** +-=---------------------------------------------------------Sa 20. Aug 11:51:49 2005----------*
 * @method  CwnDbAccess::ExistDb                           // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if a database exists.                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:49 2005----------*/
long CwnSchemeAccess::ExistDb(  QString p_qstrKeyname, bool& p_bRet )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CwnCommandExistScheme command(m_rpCwnDataAccess,p_qstrKeyname);
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
 * @method  CwnDbAccess::FindDatabase                      // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmDatabase*& p_pCdmDatabaseManager              //                                   *
 * @comment This method fins a database and returns it.                                           *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:52 2005----------*/
long CwnSchemeAccess::FindDatabase(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CwnCommandFindScheme command(p_qstrKeyname, m_rpCwnDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}
long CwnSchemeAccess::FindDatabase(  long p_lSchemeId, CdmScheme*& p_pCdmDatabaseManager )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CwnCommandFindScheme command(p_lSchemeId, m_rpCwnDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:51:56 2005----------*
 * @method  CwnDbAccess::GetDatabaseList                   // public                            *
 * @return  long                                             //                                   *
 * @param   QValueList<QString>& p_rqvlDatabases             //                                   *
 * @comment This method fills the list of all virutal databases.                                  *
 *----------------last changed: --------------------------------Sa 20. Aug 11:51:56 2005----------*/

long CwnSchemeAccess::GetDatabaseList(  QList<QString>& p_rqvlDatabases )
{
   long lRet = CdmLogging::eDmUnknownDbAccessError;
   CwnCommandGetSchemeList command(m_rpCwnDataAccess);
   lRet = command.Run();
   p_rqvlDatabases.clear();

   if (SUCCESSFULL(lRet))
   {
     p_rqvlDatabases = command.GetSchemes();
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 25. Jun 15:46:44 2012----------*
 * @method  CwnDbAccess::UpdateDatabase                    // public                            *
 * @return  long                                             //                                   *
 * @param   CdmDatabase* p_pCdmDatabase                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 25. Jun 15:46:44 2012----------*/
long CwnSchemeAccess::UpdateDatabase(CdmScheme* p_pCdmDatabase)
{
   CwnCommandUpdateScheme command(p_pCdmDatabase, m_rpCwnDataAccess);
   return command.Run();
}


/** +-=---------------------------------------------------------So 19. Aug 11:24:43 2012----------*
 * @method  CwnDbAccess::DeleteLanguage                    // public                            *
 * @return  int                                              //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   int p_iLanguageId                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 19. Aug 11:24:43 2012----------*/

int CwnSchemeAccess::DeleteLanguage(long p_lDatabaseId, int p_iLanguageId)
{
    CwnCommandDeleteSchemeLanguage command(p_lDatabaseId, p_iLanguageId, m_rpCwnDataAccess);
    return static_cast<int>(command.Run());
}

/** +-=---------------------------------------------------------Mi 4. Jul 15:08:16 2012-----------*
 * @method  CwnDbAccess::AddLanguage                       // public, virtual                   *
 * @return  int                                              //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   QString p_qstrLanguage                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 4. Jul 15:08:16 2012-----------*/
int CwnSchemeAccess::AddLanguage(long p_lDatabaseId, QString p_qstrLanguage)
{
    CwnCommandAddSchemeLanguage command(p_lDatabaseId, p_qstrLanguage, m_rpCwnDataAccess);
    return static_cast<int>(command.Run());
}
