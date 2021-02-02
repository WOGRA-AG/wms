/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Grasshof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qdatetime.h>
#include <qvariant.h>
#include <QLinkedList>
#include <qsqlquery.h>
#include <qmap.h>


// WMS Includes
#include "CdmLogging.h"
#include "CdmSettings.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmPackage.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmClassMethod.h"
#include "CdmClassValidator.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbCommandCreatePackage.h"
#include "CdbCommandUpdatePackage.h"
#include "CdbCommandLockMethod.h"
#include "CdbCommandGetClass.h"
#include "CdbCommandDeletePackage.h"
#include "CdbCommandLoadPackages.h"
#include "CdbCommandLoadClassManager.h"
#include "CdbCommandGetNewClassId.h"
#include "CdbCommandExistClass.h"
#include "CdbCommandDeleteClass.h"
#include "CdbCommandUpdateClass.h"
#include "CdbCommandUnlockMethod.h"
#include "CdbDataAccess.h"
#include "CdbClassAccess.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:40:53 2005----------*
 * @method  CdbClassAccess::CdbClassAccess               // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:40:53 2005----------*/
CdbClassAccess::CdbClassAccess(CdbDataAccess* p_pCdbDataAccess)
   : m_rpCdbDataAccess(p_pCdbDataAccess),
     m_iNewClassCounter(0)
{
   // nothing todo here
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:01 2005----------*
 * @method  CdbClassAccess::~CdbClassAccess              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbClassAccess                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:01 2005----------*/
CdbClassAccess::~CdbClassAccess(  )
{
   // nothing todo at the moment :-)
}

/** +-=---------------------------------------------------------So 11. Sep 11:41:31 2005----------*
 * @method  CdbClassAccess::GetNewClassId                  // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This mehtod returns a new class id for a new class.                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:41:31 2005----------*/
long CdbClassAccess::GetNewClassId(  long p_lDataBaseId, long p_lSessionId )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CdbCommandGetNewClassId command(p_lSessionId, p_lDataBaseId, m_rpCdbDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:10 2005----------*
 * @method  CdbClassAccess::ExistClass                     // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if the class with the overgiven keyname exists.                    *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:10 2005----------*/
long CdbClassAccess::ExistClass(  long p_lDataBaseId, QString p_qstrKeyname, bool& p_bRet )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CdbCommandExistClass command(p_lDataBaseId, p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();
   p_bRet = command.GetResult();

   return lRet;
}

/** +-=---------------------------------------------------------Di 23. Aug 15:49:41 2005----------*
 * @method  CdbClassAccess::DeleteClass                    // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @comment This method deletes a class from db.                                                  *
 *----------------last changed: --------------------------------Di 23. Aug 15:49:41 2005----------*/
long CdbClassAccess::DeleteClass(  long p_lClassId )
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CdbCommandDeleteClass command(p_lClassId, m_rpCdbDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:33 2005----------*
 * @method  CdbClassAccess::LoadClassManager               // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   CdmClassManager*& p_rpCdmClassManager            //                                   *
 * @comment This method loads the complete class manager of a class.                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:33 2005----------*/
long CdbClassAccess::LoadClassManager(  long p_lDataBaseId,
                                         CdmClassManager*& p_rpCdmClassManager )
{
   INFO("Loading all classes!");
   long lRet = CdmLogging::eDmUnknownClassAccessError;
   
   CdbCommandLoadClassManager command(p_lDataBaseId, m_rpCdbDataAccess);
   lRet = command.Run();

   // add new class manager
   p_rpCdmClassManager = command.GetResult();

   return lRet;
}

/** +-=---------------------------------------------------------Fr 8. Aug 21:18:37 2008-----------*
 * @method  CdbClassAccess::UpdateClass                    // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmClass*& p_rpCdmClass                          //                                   *
 * @comment This method updates a class.                                                          *
 *----------------last changed: --------------------------------Fr 8. Aug 21:18:37 2008-----------*/
long CdbClassAccess::UpdateClass(CdmClass*& p_rpCdmClass)
{
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CdbCommandUpdateClass command(p_rpCdmClass, m_rpCdbDataAccess);
   lRet = command.Run();

   return lRet;
}

bool CdbClassAccess::LockMethod(long p_lSessionId, int p_lMethodId)
{
   bool bSuccess = false;

   CdbCommandLockMethod command(p_lMethodId, p_lSessionId, m_rpCdbDataAccess);
   command.Run();
   bSuccess = command.GetResult();

   return bSuccess;
}

bool CdbClassAccess::UnlockMethod(long p_lSessionId, int p_lMethodId)
{
   bool bSuccess = false;

   CdbCommandUnlockMethod command(p_lMethodId, p_lSessionId, m_rpCdbDataAccess);
   command.Run();
   bSuccess = command.GetResult();

   return bSuccess;
}

int CdbClassAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    if (CHKPTR(p_pCdmPackage))
    {
        if (p_pCdmPackage->IsNew() && !p_pCdmPackage->IsDeleted())
        {
            iRet = CreatePackage(p_pCdmPackage);
        }
        else if (p_pCdmPackage->IsModified() && !p_pCdmPackage->IsDeleted())
        {
            iRet = UpdatePackageP(p_pCdmPackage);
        }
        else if (p_pCdmPackage->IsDeleted())
        {
            iRet = DeletePackage(p_pCdmPackage);
        }
    }

    return iRet;
}

int CdbClassAccess::CreatePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CdbCommandCreatePackage command(p_pCdmPackage, m_rpCdbDataAccess);
    iRet = command.Run();


    return iRet;
}

int CdbClassAccess::UpdatePackageP(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CdbCommandUpdatePackage command(p_pCdmPackage, m_rpCdbDataAccess);
    iRet = command.Run();

    return iRet;
}

int CdbClassAccess::DeletePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CdbCommandDeletePackage command(p_pCdmPackage, m_rpCdbDataAccess);
    iRet = command.Run();

    if (iRet > 0)
    {
       p_pCdmPackage = nullptr;
    }

    return iRet;
}

void CdbClassAccess::LoadPackages(CdmClassManager* p_pClassManager)
{
    CdbCommandLoadPackages command(p_pClassManager, m_rpCdbDataAccess);
    command.Run();
}

