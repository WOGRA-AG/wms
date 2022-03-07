/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsLoginEstablishConnection.cpp
 ** Started Implementation: 2008/03/23
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <qapplication.h>
#include <qdir.h>

// WMS Webclient Includes
#include "CwcDataAccessPlugin.h"

// WMS ODBC Includes
#include "CdbDataAccessPlugin.h"

// WMS GUI Includes
#include "CdmMessageManager.h"
#include "CwmsQmlApplicationSelection.h"


// Own Includes
#include "CdmManager.h"
#include "CdmSessionManager.h"
#include "CslDataAccess.h"
#include "CdbDataAccess.h"
#include "CwcDataAccess.h"
#include "CdmError.h"
#include "CwmsLoginEstablishConnection.h"



/** +-=---------------------------------------------------------Mo 5. Mai 20:24:59 2008-----------*
 * @method  CwmsLoginEstablishConnection::CwmsLoginEstablishConnection // public                  *
 * @return                                                   //                                   *
 * @param   QString p_qstrApplicationName                    //                                   *
 * @param   QString p_qstrVersion                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Mai 20:24:59 2008-----------*/
CwmsLoginEstablishConnection::CwmsLoginEstablishConnection(QString p_qstrApplicationName,
                                                           QString p_qstrVersion)
: m_qstrApplicationName(p_qstrApplicationName),
  m_qstrVersion(p_qstrVersion)
{
}

/** +-=---------------------------------------------------------So 23. Mrz 21:40:03 2008----------*
 * @method  CwmsLoginEstablishConnection::~CwmsLoginEstablishConnection // public, virtual        *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsLoginEstablishConnection                                  *
 *----------------last changed: --------------------------------So 23. Mrz 21:40:03 2008----------*/
CwmsLoginEstablishConnection::~CwmsLoginEstablishConnection()
{
}

/** +-=---------------------------------------------------------Mo 17. Aug 18:33:27 2009----------*
 * @method  CwmsLoginEstablishConnection::EstablishConnection // public                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Aug 18:33:27 2009----------*/
bool CwmsLoginEstablishConnection::EstablishConnection()
{
   bool bRet = false;

   if (!m_qstrApplicationName.isEmpty())
   {
        bRet = CreateManager();
   }

   if (bRet)
   {
      CdmManager* pCdmManager = CdmSessionManager::GetManager();

      if (pCdmManager)
      {
         pCdmManager->LicenceCheck(m_qstrApplicationName, m_qstrVersion);
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 23. Mrz 11:58:43 2008----------*
 * @method  CwmsLoginEstablishConnection::CreateManager      // private                           *
 * @return  bool                                             //                                   *
 * @param   IdmDataAccess* p_pIdmDataAccess                  //                                   *
 * @comment this method creates the manager object.                                               *
 *----------------last changed: --------------------------------So 23. Mrz 11:58:43 2008----------*/
bool CwmsLoginEstablishConnection::CreateManager()
{
   bool bRet = false;
   CdmManager* pCdmManager = CdmSessionManager::CreateSession(m_qstrApplicationName);

   if(pCdmManager)
   {
      pCdmManager->CreateSettings(eDmSettingsModeClient);
      bRet = true;
   }
   
   return bRet;
}

/** +-=---------------------------------------------------------So 18. Mai 12:49:43 2008----------*
 * @method  CwmsLoginEstablishConnection::GetApplicationName // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 12:49:43 2008----------*/
QString CwmsLoginEstablishConnection::GetApplicationName()
{
   return m_qstrApplicationName;
}
