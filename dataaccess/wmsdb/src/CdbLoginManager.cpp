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
#include <qdatetime.h>
#include <qsqlquery.h>
#include <qvariant.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmSettings.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbDataAccess.h"
#include "CdbCommandUpdateSession.h"
#include "CdbUserManager.h"
#include "CdbCommandCheckSessionTimeout.h"
#include "CdbCommandLicenceCheck.h"
#include "CdbCommandLogin.h"
#include "CdbCommandGetNewSession.h"
#include "CdbCommandFindSession.h"
#include "CdbCommandLogout.h"
#include "CdbCommandLdapLogin.h"
#include "CdbLoginManager.h"

/** +-=---------------------------------------------------------Sa 20. Aug 11:53:24 2005----------*
 * @method  CdbLoginManager::CdbLoginManager             // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @param   CdbUserManager* p_pCdbUserManager            //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:53:24 2005----------*/
CdbLoginManager::CdbLoginManager(  CdbDataAccess* p_pCdbDataAccess,
                                      CdbUserManager* p_pCdbUserManager )
   : m_rpCdbDataAccess(p_pCdbDataAccess),
     m_rpCdbUserManager(p_pCdbUserManager)

{
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:50:49 2005----------*
 * @method  CdbLoginManager::~CdbLoginManager            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbLoginManager                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:50:49 2005----------*/
CdbLoginManager::~CdbLoginManager(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:05:28 2007----------*
 * @method  CdbLoginManager::Login                         // public                            *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @param   CumUser*& p_rpCumUser                            //                                   *
 * @param   bool& p_bDemo                                    //                                   *
 * @param   int& p_iModules                                  //                                   *
 * @param   QString& p_qstrVersion                           //                                   *
 * @comment The login to the erver.                                                               *
 *----------------last changed: --------------------------------Mo 20. Aug 15:05:28 2007----------*/
qint64 CdbLoginManager::Login(QString p_qstrApplication,
                            QString p_qstrLogin,
                            QString p_qstrPassword,
                            CumUser*& p_rpCumUser,
                            bool& p_bDemo,
                            int& p_iModules,
                            QString& p_qstrVersion)
{
  qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
   
   CdbCommandLogin command(p_qstrApplication,
                           p_qstrVersion,
                           p_qstrLogin,
                           p_qstrPassword,
                           m_rpCdbDataAccess,
                           m_rpCdbUserManager);

   lRet = command.Run();

   if (lRet > 0)
   {
       lRet = command.GetSessionId();
       p_rpCumUser = command.GetUser();
       p_iModules = command.GetModules();
       p_bDemo = command.IsDemo();
   }
   
   return lRet;
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:03:34 2005-----------*
 * @method  CdbLoginManager::Logout                        // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment The logout from server.                                                               *
 *----------------last changed: --------------------------------Mo 5. Sep 19:03:34 2005-----------*/
qint64 CdbLoginManager::Logout( qint64 p_lSessionId )
{
   CdbCommandLogout command(p_lSessionId, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Sa 24. Sep 10:40:49 2005----------*
 * @method  CdbLoginManager::FindSession                   // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @param  qint64 p_lUserId                                   //                                   *
 * @comment This method searches for session and returns it if found, if not nullptr will returned.. *
 *----------------last changed: --------------------------------Sa 24. Sep 10:40:49 2005----------*/
qint64 CdbLoginManager::FindSession(qint64 p_lSessionId,qint64 p_lUserId)
{
   CdbCommandFindSession command(p_lSessionId, p_lUserId, m_rpCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Di 7. Aug 15:34:18 2007-----------*
 * @method  CdbLoginManager::GetNewSession                 // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param  qint64 p_lUserId                                   //                                   *
 * @comment returns a new session number                                                          *
 *----------------last changed: --------------------------------Di 7. Aug 15:34:18 2007-----------*/
qint64 CdbLoginManager::GetNewSession(QString p_qstrApplication,qint64 p_lUserId)
{
  qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
   CdbCommandGetNewSession command(p_qstrApplication, p_lUserId, "", m_rpCdbDataAccess);
   lRet = command.Run();

   if (lRet > 0)
   {
       lRet = command.GetResult();
   }

   return lRet;
}


/** +-=---------------------------------------------------------Do 1. Mai 17:02:22 2008-----------*
 * @method  CdbLoginManager::LicenceCheck                  // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param   bool& p_bDemo                                    //                                   *
 * @param   int& p_iModules                                  //                                   *
 * @param   QString p_qstrVersion                            //                                   *
 * @comment This method will be called to check the licence content.                              *
 *----------------last changed: --------------------------------Do 1. Mai 17:02:22 2008-----------*/
bool CdbLoginManager::LicenceCheck(QString p_qstrApplication,
                                     bool& p_bDemo,
                                     int& p_iModules,
                                     QString p_qstrVersion)
{
   bool bRet = false;

   CdbCommandLicenceCheck command(p_qstrApplication, p_qstrVersion, m_rpCdbDataAccess);
   bRet = (command.Run() > 0);
   p_bDemo = command.IsDemo();
   p_iModules = command.GetModules();

   return bRet;
}

qint64 CdbLoginManager::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rUser)
{
#ifndef WMS_NO_LDAP
    CdbCommandLdapLogin command(p_qstrApplication, "", p_qstrLogin, p_qstrPassword, m_rpCdbDataAccess, m_rpCdbUserManager);
   qint64 lRet = command.Run();

    if (SUCCESSFULL(lRet))
    {
        p_rUser = command.GetUser();
    }

    return lRet;
#else
    return CdmError::eDmNotSupportedFeatureForThisDb;
#endif
}

CdmSession *CdbLoginManager::FindSession(int p_iSessionId)
{
    CdmSession* pSesion = nullptr;
    CdbCommandFindSession command(p_iSessionId, m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

CdmSession *CdbLoginManager::FindSession(QString p_qstrBaseAuth)
{
    CdmSession* pSesion = nullptr;
    CdbCommandFindSession command(p_qstrBaseAuth, m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

void CdbLoginManager::UpdateSession(int p_iSessionId)
{
    CdbCommandUpdateSession command(p_iSessionId, m_rpCdbDataAccess);
    command.Run();
}

void CdbLoginManager::UpdateSession(QString p_qstrBaseAuth)
{
    CdbCommandUpdateSession command(p_qstrBaseAuth, m_rpCdbDataAccess);
    command.Run();
}

void CdbLoginManager::SessionTimeoutCheck(int p_iTimeoutMin)
{
    CdbCommandCheckSessionTimeout command(p_iTimeoutMin, m_rpCdbDataAccess);
    command.Run();
}
