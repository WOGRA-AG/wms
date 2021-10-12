/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>


// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CumUserManager.h"
#include "CdmModelElement.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmSettings.h"
#include "CdmModelElementBase.h"


/** +-=---------------------------------------------------------Fr 23. Nov 14:24:16 2012----------*
 * @method  CdmModelElementBase::CdmModelElementBase                   // public                            *
 * @return                                                   //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Fr 23. Nov 14:24:16 2012----------*/
CdmModelElementBase::CdmModelElementBase(qint64 p_lDbId)
: CdmLocatedElement(),
  m_lSchemeId(p_lDbId)
{
   m_lSchemeId = p_lDbId;
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:35:52 2005----------*
 * @method  CdmModelElementBase::~CdmModelElementBase                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmModelElementBase                                                *
 *----------------last changed: --------------------------------Sa 20. Aug 12:35:52 2005----------*/
CdmModelElementBase::~CdmModelElementBase(  )
{
   // nothing to do :-)
}

/** +-=---------------------------------------------------------Fr 23. Nov 14:47:04 2012----------*
 * @method  CdmModelElementBase::GetSchemeId               // public, const, slots              *
 * @return qint64                                             //                                   *
 * @comment This method returns the DatabaseId.                                                   *
 *----------------last changed: --------------------------------Fr 23. Nov 14:47:04 2012----------*/
qint64 CdmModelElementBase::GetSchemeId() const
{
   return m_lSchemeId.load();
}

/** +-=---------------------------------------------------------Fr 23. Nov 14:53:44 2012----------*
 * @method  CdmModelElementBase::SetDatabaseId               // public                            *
 * @return  void                                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @comment sets the db id in the base object.                                                    *
 *----------------last changed: --------------------------------Fr 23. Nov 14:53:44 2012----------*/
void CdmModelElementBase::SetSchemeId(qint64 p_lDbId)
{
   m_lSchemeId = p_lDbId;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:49:29 2013-----------*
 * @method  CdmModelElementBase::GetDatabaseName             // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment returns the name of the database.                                                     *
 *----------------last changed: --------------------------------Sa 9. Feb 11:49:29 2013-----------*/
QString CdmModelElementBase::GetSchemeName() const
{
   QString qstrDbName;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      const CdmScheme* pDb = pManager->FindSchemeById(m_lSchemeId.load());

      if (CHKPTR(pDb))
      {
         qstrDbName = pDb->GetSchemeName();
      }
   }

   return qstrDbName;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:50:37 2013-----------*
 * @method  CdmModelElementBase::GetDatabase                 // public, const, slots              *
 * @return  CdmScheme*                                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:50:37 2013-----------*/
CdmScheme* CdmModelElementBase::GetScheme() const
{
   CdmScheme* pCdmDatabase = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      pCdmDatabase = pCdmManager->FindSchemeById(m_lSchemeId.load());
   }

   return pCdmDatabase;
}

/** +-=---------------------------------------------------------Mo 18. Feb 11:47:09 2013----------*
 * @method  CdmModelElementBase::IsInDeploymentMode          // protected, const                  *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Feb 11:47:09 2013----------*/
bool CdmModelElementBase::IsInDeploymentMode() const
{
   bool bRet = false;
   CdmScheme* pDatabase = GetScheme();

   if (CHKPTR(pDatabase))
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:50:55 2013-----------*
 * @method  CdmModelElementBase::GetDataProvider                  // public, const                     *
 * @return  CdmManager*                                      //                                   *
 * @comment returns the Manager object to get access to him.                                      *
 *----------------last changed: --------------------------------Sa 9. Feb 11:50:55 2013-----------*/
CdmDataProvider* CdmModelElementBase::GetDataProvider() const
{
   return CdmSessionManager::GetDataProvider();
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:51:09 2013-----------*
 * @method  CdmModelElementBase::GetSettings                 // public, const                     *
 * @return  CdmSettings*                                     //                                   *
 * @comment returns the system settings.                                                          *
 *----------------last changed: --------------------------------Sa 9. Feb 11:51:09 2013-----------*/
CdmSettings* CdmModelElementBase::GetSettings() const
{
   CdmSettings* pCdmSettings = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pCdmSettings = pManager->GetSettings();
   }

   return pCdmSettings;
}

/** +-=---------------------------------------------------------Fr 23. Nov 14:50:16 2012----------*
 * @method  CdmModelElementBase::GetClassManager             // public, const                     *
 * @return  CdmClassManager*                                 //                                   *
 * @comment This method returns the CdmClassManager of this Database.                             *
 *----------------last changed: --------------------------------Fr 23. Nov 14:50:16 2012----------*/
CdmClassManager* CdmModelElementBase::GetClassManager() const
{
   CdmClassManager* pCdmClassManager = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pCdmClassManager = pManager->GetClassManager(m_lSchemeId.load());
   }

   return pCdmClassManager;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:51:39 2013-----------*
 * @method  CdmModelElementBase::GetContainerManager        // public, const                     *
 * @return  CdmContainerManager*                            //                                   *
 * @comment This method returns the ObjectListManager of this Database.                           *
 *----------------last changed: --------------------------------Sa 9. Feb 11:51:39 2013-----------*/
CdmContainerManager* CdmModelElementBase::GetContainerManager() const
{
   CdmContainerManager* pContainerManager = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pContainerManager = pManager->GetContainerManager();
   }

   return pContainerManager;
}

/** +-=---------------------------------------------------------Sa 9. Feb 11:51:47 2013-----------*
 * @method  CdmModelElementBase::GetDataAccess               // public, const                     *
 * @return  IdmDataAccess*                                   //                                   *
 * @comment This method returns the DataAccess of this Database.                                  *
 *----------------last changed: --------------------------------Sa 9. Feb 11:51:47 2013-----------*/
IdmDataAccess* CdmModelElementBase::GetDataAccess() const
{
   IdmDataAccess* pIdmDataAccess = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pManager))
   {
      pIdmDataAccess = pManager->GetDataAccess();
   }

   return pIdmDataAccess;
}


/** +-=---------------------------------------------------------Sa 9. Feb 11:51:57 2013-----------*
 * @method  CdmModelElementBase::GetSessionId                // public, const                     *
 * @return qint64                                             //                                   *
 * @comment This method returns the userId.                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 11:51:57 2013-----------*/
qint64 CdmModelElementBase::GetSessionId() const
{
   return CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
}

/** +-=---------------------------------------------------------Fr 12. Aug 00:36:58 2005----------*
 * @method  CdmModelElementBase::GetUserId                        // public, const                     *
 * @return qint64                                             //                                   *
 * @comment This method returns the Id of the logged in user.                                     *
 *----------------last changed: --------------------------------Fr 12. Aug 00:36:58 2005----------*/
qint64 CdmModelElementBase::GetUserId(  ) const
{
   return CdmSessionManager::GetSessionManager()->GetCurrentUserId();
}

/** +-=---------------------------------------------------------So 10. Feb 18:33:32 2013----------*
 * @method  CdmModelElementBase::CreateUri                   // public, const                     *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrValueKeyname = ""                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 18:33:32 2013----------*/
QString CdmModelElementBase::CreateUri(QString p_qstrType,
                                       QString p_qstrKeyname,
                                       QString p_qstrKeyname2,
                                       QString p_qstrKeyname3) const
{
   return CdmLocatedElement::CreateUri(p_qstrType, p_qstrKeyname, p_qstrKeyname2, p_qstrKeyname3);
}
