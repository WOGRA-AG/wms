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
#include "CwmsUtilities.h"
#include "CftlDataAccess.h"
#include "CftlUserManager.h"
#include "CftlCommandLicenceCheck.h"
#include "CftlCommandLogin.h"
#include "CftlCommandGetNewSession.h"
#include "CftlCommandFindSession.h"
#include "CftlCommandLogout.h"
#include "CftlCommandLdapLogin.h"
#include "CftlCommandUpdateSession.h"
#include "CftlCommandCheckSessionTimeout.h"
#include "CftlLoginManager.h"

/** +-=---------------------------------------------------------Sa 20. Aug 11:53:24 2005----------*
 * @method  CftlLoginManager::CftlLoginManager             // public                            *
 * @return                                                   //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @param   CftlUserManager* p_pCftlUserManager            //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:53:24 2005----------*/
CftlLoginManager::CftlLoginManager(  CftlDataAccess* p_pCftlDataAccess,
                                      CftlUserManager* p_pCftlUserManager )
   : m_rpCftlDataAccess(p_pCftlDataAccess),
     m_rpCftlUserManager(p_pCftlUserManager)

{
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:50:49 2005----------*
 * @method  CftlLoginManager::~CftlLoginManager            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlLoginManager                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:50:49 2005----------*/
CftlLoginManager::~CftlLoginManager(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:05:28 2007----------*
 * @method  CftlLoginManager::Login                         // public                            *
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
qint64 CftlLoginManager::Login(QString p_qstrApplication,
                            QString p_qstrLogin,
                            QString p_qstrPassword,
                            CumUser*& p_rpCumUser,
                            bool& p_bDemo,
                            int& p_iModules,
                            QString& p_qstrVersion)
{
  qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
   
   CftlCommandLogin command(p_qstrApplication,
                           p_qstrVersion,
                           p_qstrLogin,
                           p_qstrPassword,
                           m_rpCftlDataAccess,
                           m_rpCftlUserManager);

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
 * @method  CftlLoginManager::Logout                        // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment The logout from server.                                                               *
 *----------------last changed: --------------------------------Mo 5. Sep 19:03:34 2005-----------*/
qint64 CftlLoginManager::Logout()
{
   CftlCommandLogout command(m_rpCftlDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Sa 24. Sep 10:40:49 2005----------*
 * @method  CftlLoginManager::FindSession                   // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @param  qint64 p_lUserId                                   //                                   *
 * @comment This method searches for session and returns it if found, if not nullptr will returned.. *
 *----------------last changed: --------------------------------Sa 24. Sep 10:40:49 2005----------*/
qint64 CftlLoginManager::FindSession(qint64 p_lSessionId,qint64 p_lUserId)
{
   CftlCommandFindSession command(p_lSessionId, p_lUserId, m_rpCftlDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Di 7. Aug 15:34:18 2007-----------*
 * @method  CftlLoginManager::GetNewSession                 // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param  qint64 p_lUserId                                   //                                   *
 * @comment returns a new session number                                                          *
 *----------------last changed: --------------------------------Di 7. Aug 15:34:18 2007-----------*/
qint64 CftlLoginManager::GetNewSession(QString p_qstrApplication,qint64 p_lUserId)
{
  qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
   CftlCommandGetNewSession command(p_qstrApplication, p_lUserId, m_rpCftlDataAccess);
   lRet = command.Run();

   if (lRet > 0)
   {
       lRet = command.GetResult();
   }

   return lRet;
}


/** +-=---------------------------------------------------------Do 1. Mai 17:02:22 2008-----------*
 * @method  CftlLoginManager::LicenceCheck                  // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrApplication                        //                                   *
 * @param   bool& p_bDemo                                    //                                   *
 * @param   int& p_iModules                                  //                                   *
 * @param   QString p_qstrVersion                            //                                   *
 * @comment This method will be called to check the licence content.                              *
 *----------------last changed: --------------------------------Do 1. Mai 17:02:22 2008-----------*/
bool CftlLoginManager::LicenceCheck(QString p_qstrApplication,
                                     bool& p_bDemo,
                                     int& p_iModules,
                                     QString p_qstrVersion)
{
   bool bRet = false;

   CftlCommandLicenceCheck command(p_qstrApplication, p_qstrVersion, m_rpCftlDataAccess);
   bRet = (command.Run() > 0);
   p_bDemo = command.IsDemo();
   p_iModules = command.GetModules();

   return bRet;
}

qint64 CftlLoginManager::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rUser)
{
#ifndef WMS_NO_LDAP
    CftlCommandLdapLogin command(p_qstrApplication, "", p_qstrLogin, p_qstrPassword, m_rpCftlDataAccess, m_rpCftlUserManager);
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

CdmSession *CftlLoginManager::FindSession(int p_iSessionId)
{
    CdmSession* pSesion = nullptr;
    CftlCommandFindSession command(p_iSessionId, m_rpCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

CdmSession *CftlLoginManager::FindSession(QString p_qstrBaseAuth)
{
    CdmSession* pSesion = nullptr;
    CftlCommandFindSession command(p_qstrBaseAuth, m_rpCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pSesion = command.GetResult();
    }

    return pSesion;
}

void CftlLoginManager::UpdateSession(int p_iSessionId)
{
    CftlCommandUpdateSession command(p_iSessionId, m_rpCftlDataAccess);
    command.Run();
}

void CftlLoginManager::UpdateSession(QString p_qstrBaseAuth)
{
    CftlCommandUpdateSession command(p_qstrBaseAuth, m_rpCftlDataAccess);
    command.Run();
}

void CftlLoginManager::SessionTimeoutCheck(int p_iTimeoutMin)
{
    CftlCommandCheckSessionTimeout command(p_iTimeoutMin, m_rpCftlDataAccess);
    command.Run();
}
