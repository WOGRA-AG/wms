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
#include <QList>
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
#include "CwmsUtilities.h"
#include "CftlCommandCreatePackage.h"
#include "CftlCommandUpdatePackage.h"
#include "CftlCommandLockMethod.h"
#include "CftlCommandGetClass.h"
#include "CftlCommandDeletePackage.h"
#include "CftlCommandLoadPackages.h"
#include "CftlCommandLoadClassManager.h"
#include "CftlCommandGetNewClassId.h"
#include "CftlCommandExistClass.h"
#include "CftlCommandDeleteClass.h"
#include "CftlCommandUpdateClass.h"
#include "CftlCommandUnlockMethod.h"
#include "CftlDataAccess.h"
#include "CftlClassAccess.h"


/** +-=---------------------------------------------------------Sa 20. Aug 11:40:53 2005----------*
 * @method  CftlClassAccess::CftlClassAccess               // public                            *
 * @return                                                   //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 11:40:53 2005----------*/
CftlClassAccess::CftlClassAccess(  CftlDataAccess* p_pCftlDataAccess )
   : m_rpCftlDataAccess(p_pCftlDataAccess),
     m_iNewClassCounter(0)
{
   // nothing todo here
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:01 2005----------*
 * @method  CftlClassAccess::~CftlClassAccess              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlClassAccess                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:01 2005----------*/
CftlClassAccess::~CftlClassAccess(  )
{
   // nothing todo at the moment :-)
}

/** +-=---------------------------------------------------------So 11. Sep 11:41:31 2005----------*
 * @method  CftlClassAccess::GetNewClassId                  // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDataBaseId                               //                                   *
 * @param  qint64 p_lSessionId                                //                                   *
 * @comment This mehtod returns a new class id for a new class.                                   *
 *----------------last changed: --------------------------------So 11. Sep 11:41:31 2005----------*/
qint64 CftlClassAccess::GetNewClassId( qint64 p_lDataBaseId,qint64 p_lSessionId )
{
  qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

   CftlCommandGetNewClassId command(p_lSessionId, p_lDataBaseId, m_rpCftlDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:10 2005----------*
 * @method  CftlClassAccess::ExistClass                     // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDataBaseId                               //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   bool& p_bRet                                     //                                   *
 * @comment This method checks if the class with the overgiven keyname exists.                    *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:10 2005----------*/
qint64 CftlClassAccess::ExistClass( qint64 p_lDataBaseId, QString p_qstrKeyname, bool& p_bRet )
{
  qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

   CftlCommandExistClass command(p_lDataBaseId, p_qstrKeyname, m_rpCftlDataAccess);
   lRet = command.Run();
   p_bRet = command.GetResult();

   return lRet;
}

/** +-=---------------------------------------------------------Di 23. Aug 15:49:41 2005----------*
 * @method  CftlClassAccess::DeleteClass                    // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment This method deletes a class from db.                                                  *
 *----------------last changed: --------------------------------Di 23. Aug 15:49:41 2005----------*/
qint64 CftlClassAccess::DeleteClass( qint64 p_lClassId )
{
  qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

   CftlCommandDeleteClass command(p_lClassId, m_rpCftlDataAccess);
   lRet = command.Run();

   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 11:41:33 2005----------*
 * @method  CftlClassAccess::LoadClassManager               // public                            *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lDataBaseId                               //                                   *
 * @param   CdmClassManager*& p_rpCdmClassManager            //                                   *
 * @comment This method loads the complete class manager of a class.                              *
 *----------------last changed: --------------------------------Sa 20. Aug 11:41:33 2005----------*/
qint64 CftlClassAccess::LoadClassManager( qint64 p_lDataBaseId,
                                         CdmClassManager*& p_rpCdmClassManager )
{
   INFO("Loading all classes!");
  qint64 lRet = CdmLogging::eDmUnknownClassAccessError;
   
   CftlCommandLoadClassManager command(p_lDataBaseId, m_rpCftlDataAccess);
   lRet = command.Run();

   // add new class manager
   p_rpCdmClassManager = command.GetResult();

   return lRet;
}

/** +-=---------------------------------------------------------Fr 8. Aug 21:18:37 2008-----------*
 * @method  CftlClassAccess::UpdateClass                    // public, virtual                   *
 * @return qint64                                             //                                   *
 * @param   CdmClass*& p_rpCdmClass                          //                                   *
 * @comment This method updates a class.                                                          *
 *----------------last changed: --------------------------------Fr 8. Aug 21:18:37 2008-----------*/
qint64 CftlClassAccess::UpdateClass(CdmClass*& p_rpCdmClass)
{
  qint64 lRet = CdmLogging::eDmUnknownClassAccessError;

   CftlCommandUpdateClass command(p_rpCdmClass, m_rpCftlDataAccess);
   lRet = command.Run();

   return lRet;
}

bool CftlClassAccess::LockMethod(int p_lMethodId)
{
   bool bSuccess = false;

   CftlCommandLockMethod command(p_lMethodId, m_rpCftlDataAccess);
   command.Run();
   bSuccess = command.GetResult();

   return bSuccess;
}

bool CftlClassAccess::UnlockMethod(int p_lMethodId)
{
   bool bSuccess = false;

   CftlCommandUnlockMethod command(p_lMethodId, m_rpCftlDataAccess);
   command.Run();
   bSuccess = command.GetResult();

   return bSuccess;
}

int CftlClassAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
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

int CftlClassAccess::CreatePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CftlCommandCreatePackage command(p_pCdmPackage, m_rpCftlDataAccess);
    iRet = command.Run();


    return iRet;
}

int CftlClassAccess::UpdatePackageP(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CftlCommandUpdatePackage command(p_pCdmPackage, m_rpCftlDataAccess);
    iRet = command.Run();

    return iRet;
}

int CftlClassAccess::DeletePackage(CdmPackage *&p_pCdmPackage)
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    CftlCommandDeletePackage command(p_pCdmPackage, m_rpCftlDataAccess);
    iRet = command.Run();

    if (iRet > 0)
    {
       p_pCdmPackage = nullptr;
    }

    return iRet;
}

void CftlClassAccess::LoadPackages(CdmClassManager* p_pClassManager)
{
    CftlCommandLoadPackages command(p_pClassManager, m_rpCftlDataAccess);
    command.Run();
}

