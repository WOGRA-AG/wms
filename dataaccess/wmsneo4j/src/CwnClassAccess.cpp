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
#include <qmap.h>

// WMS Includes
#include "CdmScheme.h"
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
#include "CwnClassAccess.h"
#include "CwnCommandGetNewClassId.h"
#include "CwnCommandLoadClassManager.h"
#include "CwnCommandLoadPackages.h"
#include "CwnCommandDeletePackage.h"
#include "CwnCommandUpdatePackage.h"
#include "CwnCommandCreatePackage.h"
#include "CwnCommandUpdateClass.h"
#include "CwnCommandExistClass.h"
#include "CwnCommandLockMethod.h"
#include "CwnCommandUnlockMethod.h"
#include "CwnCommandDeleteClass.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:40:53 2005----------*
 * @method  CwnClassAccess::CwnClassAccess               // public                            *
 * @return                                                   //                                   *
 * @param   CwnDataAccess* p_pCwnDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:40:53 2005----------*/
CwnClassAccess::CwnClassAccess(  CwnDataAccess* p_pCwnDataAccess ):
     m_rpCwnDataAccess(p_pCwnDataAccess),
     m_iNewClassCounter(0)
{
   // nothing todo here
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:01 2005----------*
 * @method  CwnClassAccess::~CwnClassAccess              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwnClassAccess                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:01 2005----------*/
CwnClassAccess::~CwnClassAccess(  )
{
   // nothing todo at the moment
}

/** +-=---------------------------------------------------------So 11. Sep 11:41:31 2005----------*
 * @method  CwnClassAccess::GetNewClassId                  // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   long p_lSessionId                                //                                   *
 * @comment This mehtod returns a new class id for a new class.                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:41:31 2005----------*/
long CwnClassAccess::GetNewClassId(  long p_lDataBaseId, long p_lSessionId )
{

   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CwnCommandGetNewClassId command(p_lSessionId, p_lDataBaseId, m_rpCwnDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:10 2005----------*
 * @method  CwnClassAccess::ExistClass                     // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if the class with the overgiven keyname exists.                    *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:10 2005----------*/
long CwnClassAccess::ExistClass(  long p_lDataBaseId, QString p_qstrKeyname, bool& p_bRet )
{

   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CwnCommandExistClass command(p_lDataBaseId, p_qstrKeyname, m_rpCwnDataAccess);
   lRet = command.Run();
   p_bRet = command.GetResult();

   return lRet;

}

/** +-=---------------------------------------------------------Di 23. Aug 15:49:41 2005----------*
 * @method  CwnClassAccess::DeleteClass                    // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lClassId                                  //                                   *
 * @comment This method deletes a class from db.                                                  *
 *----------------last changed: --------------------------------Di 23. Aug 15:49:41 2005----------*/
long CwnClassAccess::DeleteClass(  long p_lClassId )
{

   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CwnCommandDeleteClass command(p_lClassId, m_rpCwnDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:33 2005----------*
 * @method  CwnClassAccess::LoadClassManager               // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lDataBaseId                               //                                   *
 * @param   CdmClassManager*& p_rpCdmClassManager            //                                   *
 * @comment This method loads the complete class manager of a class.                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:33 2005----------*/
long CwnClassAccess::LoadClassManager(long p_lDataBaseId,CdmClassManager*& p_rpCdmClassManager)
{

   INFO("Loading all classes!");
   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CwnCommandLoadClassManager command(p_lDataBaseId, m_rpCwnDataAccess);
   lRet = command.Run();

   // add new class manager
   p_rpCdmClassManager = command.GetResult();

   return lRet;

}

/** +-=---------------------------------------------------------Fr 8. Aug 21:18:37 2008-----------*
 * @method  CwnClassAccess::UpdateClass                    // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   CdmClass*& p_rpCdmClass                          //                                   *
 * @comment This method updates a class.                                                          *
 *----------------last changed: --------------------------------Fr 8. Aug 21:18:37 2008-----------*/
long CwnClassAccess::UpdateClass(CdmClass*& p_rpCdmClass)
{

   long lRet = CdmLogging::eDmUnknownClassAccessError;

   CwnCommandUpdateClass command(p_rpCdmClass, m_rpCwnDataAccess);
   lRet = command.Run();

   return lRet;

    //return 0;
}

bool CwnClassAccess::LockMethod(long p_lSessionId, int p_lMethodId)
{
   CwnCommandLockMethod command(p_lMethodId, p_lSessionId, m_rpCwnDataAccess);
   bool bSuccess = command.Run();

   return bSuccess;
}

bool CwnClassAccess::UnlockMethod(long p_lSessionId, int p_lMethodId)
{
   CwnCommandUnlockMethod command(p_lMethodId, p_lSessionId, m_rpCwnDataAccess);
   bool bSuccess = command.Run();;

   return bSuccess;
}

int CwnClassAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
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

int CwnClassAccess::CreatePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CwnCommandCreatePackage command(p_pCdmPackage, m_rpCwnDataAccess);
    iRet = command.Run();


    return iRet;
}

int CwnClassAccess::UpdatePackageP(CdmPackage *&p_pCdmPackage)
{

    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CwnCommandUpdatePackage command(p_pCdmPackage, m_rpCwnDataAccess);
    iRet = command.Run();

    return iRet;
}

int CwnClassAccess::DeletePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CwnCommandDeletePackage command(p_pCdmPackage, m_rpCwnDataAccess);
    iRet = command.Run();

    if (iRet > 0)
    {
       p_pCdmPackage = nullptr;
    }

    return iRet;
}

void CwnClassAccess::LoadPackages(CdmClassManager* p_pClassManager)
{
    CwnCommandLoadPackages command(p_pClassManager, m_rpCwnDataAccess, p_pClassManager->GetScheme()->GetSchemeName());
    command.Run();
}
