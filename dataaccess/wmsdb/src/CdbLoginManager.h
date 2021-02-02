/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CODBCLOGINMANAGER_H
#define CODBCLOGINMANAGER_H

// System and QT Includes
#include <qmap.h>


// own Includes
#include "CumUser.h"
#include "CdbDataAccess.h"


// forwards
class CdbDataAccess;
class CdbUserManager;

 /* 
  * This class manages the login and logout of users on the system
  */
class WMSDB_API CdbLoginManager
{
   protected:

	  /**
	   * The Dataaccess
	   */
      CdbDataAccess* m_rpCdbDataAccess;

	  /**
	   * The user managers for checking logins and logouts
	   */
      CdbUserManager* m_rpCdbUserManager;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:53:24 2005*
    * @method  CdbLoginManager::CdbLoginManager          // public                            *
    * @return                                                //                                   *
    * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
    * @param   CdbUserManager* p_pCdbUserManager         //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:53:24 2005----------*/
CdbLoginManager(  CdbDataAccess* p_pCdbDataAccess, CdbUserManager* p_pCdbUserManager );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:50:49 2005*
    * @method  CdbLoginManager::~CdbLoginManager         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdbLoginManager                                          *
    *----------------last changed: -----------------------------Sa 20. Aug 12:50:49 2005----------*/
virtual ~CdbLoginManager(  );

   public:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:05:28 2007-------*
    * @method  CdbLoginManager::Login                      // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @param   CumUser*& p_rpCumUser                         //                                   *
    * @param   bool& p_bDemo                                 //                                   *
    * @param   int& p_iModules                               //                                   *
    * @param   QString& p_qstrVersion                        //                                   *
    * @comment The login to the erver.                                                            *
    *----------------last changed: -----------------------------Mo 20. Aug 15:05:28 2007----------*/
    long Login(QString p_qstrApplication,
               QString p_qstrLogin,
               QString p_qstrPassword,
               CumUser*& p_rpCumUser,
               bool& p_bDemo,
               int& p_iModules,
               QString& p_qstrVersion);

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:03:34 2005*
    * @method  CdbLoginManager::Logout                     // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment The logout from server.                                                            *
    *----------------last changed: -----------------------------Mo 5. Sep 19:03:34 2005-----------*/
virtual long Logout(  long p_lSessionId );

   public:
   /** +-=---------------------------------------------------------Sa 24. Sep 10:40:49 2005*
    * @method  CdbLoginManager::FindSession                // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment This method searches for session and returns it if found, if not null will returned..*
    *----------------last changed: -----------------------------Sa 24. Sep 10:40:49 2005----------*/
virtual long FindSession(  long p_lSessionId, long p_lUserId );

   public:
   /** +-=---------------------------------------------------------Di 7. Aug 15:34:18 2007--------*
    * @method  CdbLoginManager::GetNewSession              // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment returns a new session number                                                       *
    *----------------last changed: -----------------------------Di 7. Aug 15:34:18 2007-----------*/
    virtual long GetNewSession(QString p_qstrApplication, long p_lUserId);

   public:
   /** +-=---------------------------------------------------------Do 1. Mai 17:02:22 2008--------*
    * @method  CdbLoginManager::LicenceCheck               // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @param   bool& p_bDemo                                 //                                   *
    * @param   int& p_iModules                               //                                   *
    * @param   QString p_qstrVersion                         //                                   *
    * @comment This method will be called to check the licence content.                           *
    *----------------last changed: -----------------------------Do 1. Mai 17:02:22 2008-----------*/
    bool LicenceCheck(QString p_qstrApplication,
                      bool& p_bDemo,
                      int& p_iModules,
                      QString p_qstrVersion);

    public:
        long LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, CumUser*& p_rUser);
        virtual CdmSession* FindSession(int p_iSessionId);
        virtual CdmSession* FindSession(QString p_qstrBaseAuth);
        void UpdateSession(int p_iSessionId);
        void UpdateSession(QString p_qstrBaseAuth);
        void SessionTimeoutCheck(int p_iTimeoutMin);
};

#endif //
