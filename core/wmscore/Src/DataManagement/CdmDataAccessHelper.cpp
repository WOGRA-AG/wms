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
#include <qdatetime.h>
#include <math.h>

// WMS Commons Includes
#include "CwmsUtilities.h"

// own Includes
#include "CdmScheme.h"
#include "CdmSettings.h"
#include "CdmLogging.h"
#include "CdmModelElement.h"
#include "CdmMember.h"
#include "CdmPackage.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
#include "CdmSession.h"
 #include "CdmSessionManager.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmQuery.h"
#include "CdmQuery.h"
#include "CdmQueryElement.h"
#include "CdmValue.h"
#include "CdmDataAccessHelper.h"
#include "CumUser.h"
#include "CumUserManager.h"


/** +-=---------------------------------------------------------Sa 13. Aug 21:23:31 2005----------*
 * @method  CdmDataAccessHelper::CdmDataAccessHelper                     // public                            *
 * @return                                                   //                                   *
 * @comment The constructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:23:31 2005----------*/
CdmDataAccessHelper::CdmDataAccessHelper(  )
{
   // nothing to do here
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:43:37 2005----------*
 * @method  CdmDataAccessHelper::~CdmDataAccessHelper                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmDataAccessHelper                                                 *
 *----------------last changed: --------------------------------Sa 20. Aug 12:43:37 2005----------*/
CdmDataAccessHelper::~CdmDataAccessHelper(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:24:49 2005----------*
 * @method  CdmDataAccessHelper::SetNameAndIdOfDatabase            // public                            *
 * @return  int                                              //                                   *
 * @param  qint64 p_lId                                       // Database Id                       *
 * @param   QString p_qstrName                               // Database name                     *
 * @param   CdmScheme* p_pCdmDatabase                      // Database Object                   *
 * @comment ONLY FOR INTERNAL USE!!!!!!!                                                          *
 *          This method sets the name and id for a database                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:24:49 2005----------*/
int CdmDataAccessHelper::SetNameAndIdOfDatabase( qint64 p_lId,
                                           QString p_qstrName,
                                           CdmScheme* p_pCdmDatabase )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmDatabase))
   {
      p_pCdmDatabase->m_lId = p_lId;
      p_pCdmDatabase->m_qstrSchemeName = p_qstrName;

      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:25:14 2005----------*
 * @method  CdmDataAccessHelper::CreateClass                       // public                            *
 * @return  CdmClass*                                        //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method is a helper function for creating classes.                                *
 *----------------last changed: --------------------------------Sa 13. Aug 21:25:14 2005----------*/
CdmClass* CdmDataAccessHelper::CreateClass( qint64 p_lDbId,qint64 p_lId, QString p_qstrKeyname )
{
   CdmClass* pCdmClass = new CdmClass(p_lDbId, p_lId, p_qstrKeyname);
   return pCdmClass;
}

CdmClass* CdmDataAccessHelper::CreateClass(QVariantMap& p_qvMap)
{
   CdmClass* pCdmClass = new CdmClass(p_qvMap);
   return pCdmClass;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:26:09 2005----------*
 * @method  CdmDataAccessHelper::CreateMember                      // public                            *
 * @return  CdmMember*                                       //                                   *
 * @param  qint64 p_lDbId                                     // database Id                       *
 * @param  qint64 p_lId                                       // Member Id                         *
 * @param   QString p_qstrkeyname                            // Member Keyname                    *
 * @param   int p_iType                                      // Value Type                        *
 * @param   bool p_bMust                                     // Is Must Value                     *
 * @param   int p_iSize                                      // Value Size                        *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method is a helper function for creating Members in derived classes.             *
 *----------------last changed: --------------------------------Sa 13. Aug 21:26:09 2005----------*/
CdmMember* CdmDataAccessHelper::CreateMember( qint64 p_lDbId,
                                       qint64 p_lId,
                                        QString p_qstrkeyname,
                                        int p_iType,
                                        bool p_bMust,
                                        int p_iSize )
{
   CdmMember* pCdmMember = nullptr;

   pCdmMember = new CdmMember(p_lDbId,
                              p_lId,
                              p_qstrkeyname,
                              (EdmValueType)p_iType,
                              p_bMust,
                              p_iSize);
   return pCdmMember;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:26:47 2005----------*
 * @method  CdmDataAccessHelper::AddObjectToObjectList             // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method adds an object to it's objectlist.                                        *
 *----------------last changed: --------------------------------Sa 13. Aug 21:26:47 2005----------*/
int CdmDataAccessHelper::AddObjectToObjectList(  CdmObject* p_pCdmObject,
                                          CdmObjectContainer* p_pContainer )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pContainer) && CHKPTR(p_pCdmObject))
   {
      iRet = p_pContainer->AddObject(p_pCdmObject);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:26:58 2005----------*
 * @method  CdmDataAccessHelper::AddValueToObject                  // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method adds a Value to an object.                                                *
 *----------------last changed: --------------------------------Sa 13. Aug 21:26:58 2005----------*/
int CdmDataAccessHelper::AddValueToObject(  CdmObject* p_pCdmObject, CdmValue* p_pCdmValue )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject) && CHKPTR(p_pCdmValue))
   {
      p_pCdmObject->AddObjectValue(p_pCdmValue);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:27:18 2005----------*
 * @method  CdmDataAccessHelper::AddMemberToClass                  // public                            *
 * @return  int                                              //                                   *
 * @param   CdmClass* pCdmClass                              //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This m4ethod adds member to classes                                                   *
 *----------------last changed: --------------------------------Sa 13. Aug 21:27:18 2005----------*/
int CdmDataAccessHelper::AddMemberToClass(  CdmClass* pCdmClass, CdmMember* p_pCdmMember )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(pCdmClass) && CHKPTR(p_pCdmMember))
   {
      INFO ("Call AddMember!")
      if(!pCdmClass->FindMember(p_pCdmMember->GetKeyname()))
      {
        pCdmClass->m_qmMembers.insert(p_pCdmMember->GetId(), p_pCdmMember);
      }

      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:27:32 2005----------*
 * @method  CdmDataAccessHelper::AddQueryResult                    // public                            *
 * @return  int                                              //                                   *
 * @param   CdmQuery* p_pCdmQuery                            //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method adds an result object to the overgiven query.                             *
 *----------------last changed: --------------------------------Sa 13. Aug 21:27:32 2005----------*/
int CdmDataAccessHelper::AddQueryResult(CdmQuery* p_pCdmQuery,qint64 p_lObjectId,qint64 p_lContainerId)
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmQuery))
   {
       if (p_lContainerId == 0)
       {
           CdmDataAccessHelper::SetQueryEnhancedResult(p_pCdmQuery, 0, p_lObjectId, -1, -1);
       }
       else
       {
            p_pCdmQuery->AddResult(p_lObjectId, p_lContainerId);
       }
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:27:47 2005----------*
 * @method  CdmDataAccessHelper::SetId                             // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          Sets the Id in base objects.                                                          *
 *----------------last changed: --------------------------------Sa 13. Aug 21:27:47 2005----------*/
int CdmDataAccessHelper::SetId(  CdmModelElement* p_pCdmBase,qint64 p_lId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      if(p_lId > 0)
      {
         p_pCdmBase->SetId(p_lId);
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(eDmInvalidId);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:28:01 2005----------*
 * @method  CdmDataAccessHelper::InitializeObject                  // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method initialize object afterwards.                                             *
 *----------------last changed: --------------------------------Sa 13. Aug 21:28:01 2005----------*/
int CdmDataAccessHelper::InitializeObject(  CdmObject* p_pCdmObject, CdmClass* p_pCdmClass )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject) && CHKPTR(p_pCdmClass))
   {
      p_pCdmObject->InitObject(p_pCdmClass);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:28:17 2005----------*
 * @method  CdmDataAccessHelper::AddClass                          // public                            *
 * @return  int                                              //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This emthod adds a class to the overgiven classmanager.                               *
 *----------------last changed: --------------------------------Sa 13. Aug 21:28:17 2005----------*/
int CdmDataAccessHelper::AddClass(  CdmClassManager* p_pCdmClassManager, CdmClass* p_pCdmClass )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmClassManager) && CHKPTR(p_pCdmClass))
   {
      p_pCdmClassManager->AddClass(p_pCdmClass);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmDataAccessHelper::AddPackageToClass(CdmClassManager* p_pCdmClassManager, CdmClass* p_pCdmClass, QString p_qstrPackage)
{
    int iRet = CdmLogging::eDmUnknownDataAccessError;

   if (CHKPTR(p_pCdmClassManager) && CHKPTR(p_pCdmClass) && !p_qstrPackage.isEmpty())
   {
      if (!p_qstrPackage.isEmpty())
      {
         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (CHKPTR(pManager))
         {
                QString qstrKey = pManager->GetUriMajorId(p_qstrPackage);

                if (qstrKey.isEmpty())
                {
                    qstrKey = p_qstrPackage;
                }

                CdmPackage* pPackage = p_pCdmClassManager->FindPackageByName(qstrKey);

                if (pPackage)
            {
               p_pCdmClass->SetPackage(pPackage);
               pPackage->AddClass(p_pCdmClass);
               p_pCdmClass->SetModified();
            }
                else
                {
                    ERR("Package with name " + qstrKey + " not found.");
                }
         }
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:28:29 2005----------*
 * @method  CdmDataAccessHelper::SetKeyname                        // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          Sets the keyname in base objects.                                                     *
 *----------------last changed: --------------------------------Sa 13. Aug 21:28:29 2005----------*/
int CdmDataAccessHelper::SetKeyname(  CdmModelElement* p_pCdmBase, QString p_qstrKeyname )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->CdmModelElement::SetKeyname(p_qstrKeyname);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:29:19 2005----------*
 * @method  CdmDataAccessHelper::GetValue                          // public                            *
 * @return  CdmValue*                                        //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method retunrs a value of an object.                                             *
 *----------------last changed: --------------------------------Sa 13. Aug 21:29:19 2005----------*/
CdmValue* CdmDataAccessHelper::GetValue(  CdmObject* p_pCdmObject, QString p_qstrKeyname )
{
   CdmValue* pCdmValue = nullptr;

   if(CHKPTR(p_pCdmObject))
   {
      pCdmValue = p_pCdmObject->GetValue(p_qstrKeyname);
   }

   return pCdmValue;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:28:26 2013-----------*
 * @method  CdmDataAccessHelper::GetManager                        // public, const                     *
 * @return  CdmManager*                                      //                                   *
 * @comment returns the Manager object to get access to him.                                      *
 *----------------last changed: --------------------------------Sa 9. Feb 12:28:26 2013-----------*/
CdmDataProvider* CdmDataAccessHelper::GetManager()
{
   return CdmSessionManager::GetDataProvider();
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:28:34 2013-----------*
 * @method  CdmDataAccessHelper::GetSettings                       // public, const                     *
 * @return  CdmSettings*                                     //                                   *
 * @comment returns the system settings.                                                          *
 *----------------last changed: --------------------------------Sa 9. Feb 12:28:34 2013-----------*/
CdmSettings* CdmDataAccessHelper::GetSettings()
{
   CdmSettings* pCdmSettings = nullptr;
   CdmDataProvider* pCdmManager = GetManager();

   if(pCdmManager)
   {
      pCdmSettings = pCdmManager->GetSettings();
   }

   return pCdmSettings;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:29:49 2005----------*
 * @method  CdmDataAccessHelper::SetModified                       // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the modified flag                                                    *
 *----------------last changed: --------------------------------Sa 13. Aug 21:29:49 2005----------*/
int CdmDataAccessHelper::SetModified(  CdmModelElement* p_pCdmBase )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetModified();
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:30:11 2005----------*
 * @method  CdmDataAccessHelper::SetNew                            // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the new flag.                                                        *
 *----------------last changed: --------------------------------Sa 13. Aug 21:30:11 2005----------*/
int CdmDataAccessHelper::SetNew(  CdmModelElement* p_pCdmBase )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetNew();
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:30:49 2005----------*
 * @method  CdmDataAccessHelper::SetValid                          // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the valid flag.                                                      *
 *----------------last changed: --------------------------------Sa 13. Aug 21:30:49 2005----------*/
int CdmDataAccessHelper::SetValid(  CdmModelElement* p_pCdmBase )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetValid();
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:31:06 2005----------*
 * @method  CdmDataAccessHelper::SetDeleted                        // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the deleted flag.                                                    *
 *----------------last changed: --------------------------------Sa 13. Aug 21:31:06 2005----------*/
int CdmDataAccessHelper::SetDeleted(  CdmModelElement* p_pCdmBase )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetDeleted();
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:31:26 2005----------*
 * @method  CdmDataAccessHelper::SetDatabaseId                     // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          Sets the databseid in the Data Access.                                                *
 *----------------last changed: --------------------------------Sa 13. Aug 21:31:26 2005----------*/
int CdmDataAccessHelper::SetDatabaseId(  CdmModelElement* p_pCdmBase,qint64 p_lDbId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetSchemeId(p_lDbId);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:31:40 2005----------*
 * @method  CdmDataAccessHelper::GetValueMap                       // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QMap<QString,CdmValue*>& p_pqmValues             //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method returns the Value Map of the overgiven Object.                            *
 *----------------last changed: --------------------------------Sa 13. Aug 21:31:40 2005----------*/
int CdmDataAccessHelper::GetValueMap(  CdmObject* p_pCdmObject, QMap<QString,CdmValue*>& p_pqmValues )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject))
   {
      p_pqmValues = p_pCdmObject->m_qmValues;
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:32:00 2005----------*
 * @method  CdmDataAccessHelper::SetCreatorId                      // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This emthod sets the creator Id.                                                      *
 *----------------last changed: --------------------------------Sa 13. Aug 21:32:00 2005----------*/
int CdmDataAccessHelper::SetCreatorId(  CdmModelElement* p_pCdmBase,qint64 p_lId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetCreatorId(p_lId);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:32:20 2005----------*
 * @method  CdmDataAccessHelper::SetModifierId                     // public                            *
 * @return  int                                              //                                   *
 * @param   CdmModelElement* p_pCdmBase                              //                                   *
 * @param  qint64 p_lId                                       //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the modifier Id.                                                     *
 *----------------last changed: --------------------------------Sa 13. Aug 21:32:20 2005----------*/
int CdmDataAccessHelper::SetModifierId(  CdmModelElement* p_pCdmBase,qint64 p_lId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmBase))
   {
      p_pCdmBase->SetModifierId(p_lId);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:32:35 2005----------*
 * @method  CdmDataAccessHelper::SetObjectInitialized              // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the initialized flag in the object.                                  *
 *----------------last changed: --------------------------------Sa 13. Aug 21:32:35 2005----------*/
int CdmDataAccessHelper::SetObjectInitialized(  CdmObject* p_pCdmObject )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject))
   {
      p_pCdmObject->m_bIsInitialized = true;
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:33:32 2005----------*
 * @method  CdmDataAccessHelper::SetObjectValueIdCounter           // public                            *
 * @return  int                                              //                                   *
 * @param   int p_iCounter                                   //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method sets the valueidcounter for the object.                                   *
 *----------------last changed: --------------------------------Sa 13. Aug 21:33:32 2005----------*/
int CdmDataAccessHelper::SetObjectValueIdCounter(  int p_iCounter, CdmObject* p_pCdmObject )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject))
   {
      p_pCdmObject->SetValueIdCounter(p_iCounter);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:33:46 2005----------*
 * @method  CdmDataAccessHelper::SetMemberClassId                  // public                            *
 * @return  int                                              //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param  qint64 p_lClassId                                  //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method sets the clasid of the member.                                            *
 *----------------last changed: --------------------------------Sa 13. Aug 21:33:46 2005----------*/
int CdmDataAccessHelper::SetMemberClassId(  CdmMember* p_pCdmMember,qint64 p_lClassId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->SetClassId(p_lClassId);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:34:16 2005----------*
 * @method  CdmDataAccessHelper::RemoveObjectFromObjectList        // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!!!                                                           *
 *          This method removes anobject from objectlist.                                         *
 *----------------last changed: --------------------------------Sa 13. Aug 21:34:16 2005----------*/
int CdmDataAccessHelper::RemoveObjectFromObjectList(  CdmObjectContainer* p_pContainer,qint64 p_lObjectId )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pContainer))
   {
      p_pContainer->m_qmObjects.remove(p_lObjectId);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Fr 23. Mai 17:20:56 2008----------*
 * @method  CdmDataAccessHelper::RemoveMemberFromClass             // public                            *
 * @return qint64                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 23. Mai 17:20:56 2008----------*/
qint64 CdmDataAccessHelper::RemoveMemberFromClass(CdmClass* p_pCdmClass, CdmMember* p_pCdmMember)
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if (CHKPTR(p_pCdmClass) && CHKPTR(p_pCdmMember))
   {
      if (p_pCdmClass->m_qmMembers.remove(p_pCdmMember->GetId()) == 1)
      {
         DELPTR(p_pCdmMember);
         iRet = 1;
      }
   }

   return iRet;
}

/** +-=---------------------------------------------------------Do 15. Nov 14:40:05 2012----------*
 * @method  CdmDataAccessHelper::UpdateMemberId                    // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 15. Nov 14:40:05 2012----------*/
void CdmDataAccessHelper::UpdateMemberId(CdmClass* p_pCdmClass, CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmClass) && CHKPTR(p_pCdmMember))
   {
      QMap<qint64, CdmMember*>::iterator qmIt = p_pCdmClass->m_qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = p_pCdmClass->m_qmMembers.end();
     qint64 lOldId = 0;

      for (; qmIt != qmItEnd; ++qmIt)
      {
         if (qmIt.value() == p_pCdmMember)
         {
            lOldId = qmIt.key();
            break;
         }
      }

      if (p_pCdmClass->m_qmMembers.remove(lOldId) == 1)
      {
         p_pCdmClass->m_qmMembers.insert(p_pCdmMember->GetId(), p_pCdmMember);
      }

   }
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:34:35 2005----------*
 * @method  CdmDataAccessHelper::SetMemberSize                     // public                            *
 * @return  int                                              //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param  qint64 m_lSize                                     //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method sets the Value size.                                                      *
 *----------------last changed: --------------------------------Sa 13. Aug 21:34:35 2005----------*/
int CdmDataAccessHelper::SetMemberSize(  CdmMember* p_pCdmMember,qint64 m_lSize )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if (CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->SetSize(m_lSize);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:35:05 2005----------*
 * @method  CdmDataAccessHelper::SetMemberMustValue                // public                            *
 * @return  int                                              //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   bool p_bMustValue                                //                                   *
 * @comment ONLY FOR INTERNAL USE!!!!                                                             *
 *          This method sets the msut value flag                                                  *
 *----------------last changed: --------------------------------Sa 13. Aug 21:35:05 2005----------*/
int CdmDataAccessHelper::SetMemberMustValue(  CdmMember* p_pCdmMember, bool p_bMustValue )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if (CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->SetMustValue(p_bMustValue);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Sa 13. Aug 21:36:13 2005----------*
 * @method  CdmDataAccessHelper::UpdateObjectWithClass             // public                            *
 * @return  int                                              //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment ONLY FOR INTERNAL USE!!!                                                              *
 *          This method updates an object with class.                                             *
 *          This means if a class has a new member a                                              *
 *          value must be created for the new member                                              *
 *          in the class.                                                                         *
 *----------------last changed: --------------------------------Sa 13. Aug 21:36:13 2005----------*/
int CdmDataAccessHelper::UpdateObjectWithClass(  CdmObject* p_pCdmObject, CdmClass* p_pCdmClass )
{
   int iRet = CdmLogging::eDmUnknownDataAccessError;

   if(CHKPTR(p_pCdmObject) && CHKPTR(p_pCdmClass))
   {
      // first step check class for new Members
      QMap<qint64, CdmMember*> qmValueDescritpions;
      p_pCdmClass->GetClassMemberMap(qmValueDescritpions);

      QMap<qint64, CdmMember*>::iterator qmIt    = qmValueDescritpions.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmValueDescritpions.end();

      for(; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if(CHKPTR(pCdmMember))
         {
            if(!p_pCdmObject->GetValue(pCdmMember->GetKeyname()))
            {
               // Value does not exist must be created
               p_pCdmObject->CreateObjectValue(pCdmMember);
            }
         }
         else
         {
            iRet = EC(eDmInvalidPtr);
         }
      }

      // second step check if there are deleted Members in Object
      QMap<QString, CdmValue*> qmValues;
      p_pCdmObject->GetValueMap(qmValues);

      QMap<QString, CdmValue*>::iterator qmItDt    = qmValues.begin();
      QMap<QString, CdmValue*>::iterator qmItDtEnd = qmValues.end();

      for(; qmItDt != qmItDtEnd; ++qmItDt)
      {
         CdmValue* pCdmValue = qmItDt.value();

         if(CHKPTR(pCdmValue) && !p_pCdmClass->FindMember(pCdmValue->GetKeyname()))
         {
            p_pCdmObject->RemoveValue(pCdmValue->GetKeyname());
         }
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

/** +-=---------------------------------------------------------Di 27. Dez 15:14:28 2005----------*
 * @method  CdmDataAccessHelper::DecodeString                      // private, static                   *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrString                             //                                   *
 * @param   QString p_qstrSource                             //                                   *
 * @comment This method decodes an string.                                                        *
 *----------------last changed: Wolfgang Graßhof----------------Di 27. Dez 15:14:28 2005----------*/
bool CdmDataAccessHelper::DecodeString(  QString p_qstrString, QString p_qstrSource )
{
   bool bRet = false;
   QString qstrTemp;
   QString qstrResult;
   int iLength = p_qstrString.length();

   if (p_qstrSource == "-1")
   {
      bRet = true;
   }
   else
   {
      if (iLength > 0 && iLength % 2 == 0)
      {
         while (p_qstrString.length() > 0)
         {
            QString qstrTemp = p_qstrString.mid(0, 2);
            p_qstrString = p_qstrString.mid(2, p_qstrString.length() - 2);

            int iNumber = qstrTemp.toInt();

            if(iNumber > 0)
            {
               iNumber -= 10;
               iNumber = pow(iNumber, 0.5);
               qstrResult += QChar(iNumber);
            }
            else
            {
               break;
            }
         }
      }

      if(p_qstrSource.length() == qstrResult.length())
      {
         bool bTemp = true;

         for (int iCounter = 0; iCounter < qstrResult.length(); ++iCounter)
         {
            int iValue1 = p_qstrSource[iCounter].unicode();
            int iValue2 = qstrResult[iCounter].unicode();

            if(iValue1 % 10 != iValue2)
            {
               bTemp = false;
               break;
            }
         }

         if (bTemp)
         {
            bRet = true;
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Di 27. Dez 15:14:21 2005----------*
 * @method  CdmDataAccessHelper::DecodeInt                         // private, static                   *
 * @return  int                                              //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment this method decodes the integer.                                                      *
 *----------------last changed: Wolfgang Graßhof----------------Di 27. Dez 15:14:21 2005----------*/
int CdmDataAccessHelper::DecodeInt(  QString p_qstrValue )
{
   int iRet = -1;
   QString qstrTemp;

   for (int iCounter = 0; iCounter < p_qstrValue.length(); ++iCounter)
   {
      QChar qcChar = p_qstrValue[iCounter];
      int iValue = qcChar.unicode();
      iValue -= 18;
      qstrTemp += QChar(iValue);
   }

   if(qstrTemp.length() > 0)
   {
      iRet = qstrTemp.toInt();
   }

   return iRet;
}

/** +-=---------------------------------------------------------Do 1. Mai 16:36:53 2008-----------*
 * @method  CdmDataAccessHelper::ValidateLicence                   // public, static                    *
 * @return  int                                              // the number of licences            *
 * @param   QString p_qstrSoftware                           //                                   *
 * @param   QString p_qstrLicencee                           //                                   *
 * @param   QString p_qstrLicenceKey                         //                                   *
 * @param   int& p_iModules                                  //                                   *
 * @param   QString p_qstrVersion                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 1. Mai 16:36:53 2008-----------*/
int CdmDataAccessHelper::ValidateLicence(QString p_qstrSoftware,
                                   QString p_qstrLicencee,
                                   QString p_qstrLicenceKey,
                                   int& p_iModules,
                                   QString p_qstrVersion)
{
   int iRet = 0;
   QString qstrFirst;
   QString qstrSecond;
   QString qstrThird;
   QString qstrFourth;
   QString qstrFifth;
   QString qstrSixth;
   QDate qdExpires;

   int iPos = p_qstrLicenceKey.indexOf("-");

   if(iPos > 0)
   {
      qstrFirst = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf("-");

   if(iPos > 0)
   {
      qstrSecond = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf("-");
   
   if(iPos > 0)
   {
      qstrThird = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');
   
   if(iPos > 0)
   {
      qstrFourth = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrFifth = p_qstrLicenceKey.mid(0, iPos);
      p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
      
      if(p_qstrLicenceKey.length() > 0)
      {
         qstrSixth = p_qstrLicenceKey;
      }
   }
   else
   {
      qstrFifth = p_qstrLicenceKey;
   }

   // the modulecheck!!!
   p_iModules = DecodeInt(qstrFifth);

   // Version check!!!!
   if (DecodeString(qstrFourth, p_qstrVersion))
   {
      if(DecodeString(qstrFirst, p_qstrSoftware.right(4)) &&
         DecodeString(qstrSecond, p_qstrLicencee.mid(0,4)))
      {
         if(!qstrSixth.isEmpty())
         {
            int iTimeT = DecodeInt(qstrSixth);
            QDateTime qdtExpires;
            qdtExpires.setTime_t(iTimeT);
            qdExpires = qdtExpires.date();
         }

         if(qdExpires.isValid() && qdExpires > QDate::currentDate())
         {
            iRet = DecodeInt(qstrThird);
         }
         else if(!qdExpires.isValid())
         {
            iRet = DecodeInt(qstrThird);
         }
         else
         {
            iRet = -1;
         }
      }
   }
   else
   {
      iRet = -1;
   }

   return iRet;
}

/** +-=---------------------------------------------------------Do 29. Dez 12:11:30 2005----------*
 * @method  CdmDataAccessHelper::GetLicenceExpirationDate          // public, static                    *
 * @return  QDate                                            //                                   *
 * @param   QString p_qstrLicenceKey                         //                                   *
 * @comment This method returns the expirationdate of the licence.                                *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 12:11:30 2005----------*/
QDate CdmDataAccessHelper::GetLicenceExpirationDate(  QString p_qstrLicenceKey )
{
   QString qstrFirst;
   QString qstrSecond;
   QString qstrThird;
   QString qstrFourth;
   QString qstrFifth;
   QString qstrSixth;
   QDate qdExpires;

   int iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrFirst = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrSecond = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrThird = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrFourth = p_qstrLicenceKey.mid(0, iPos);
   }

   p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);
   iPos = p_qstrLicenceKey.indexOf('-');

   if(iPos > 0)
   {
      qstrFifth = p_qstrLicenceKey.mid(0, iPos);
      p_qstrLicenceKey = p_qstrLicenceKey.mid(iPos + 1, p_qstrLicenceKey.length() - iPos - 1);

      if(p_qstrLicenceKey.length() > 0)
      {
         qstrSixth = p_qstrLicenceKey;
      }
   }
   else
   {
      qstrFifth = p_qstrLicenceKey;
   }

   if(!qstrSixth.isEmpty())
   {
      int iTimeT = DecodeInt(qstrSixth);
      QDateTime qdtExpires;
      qdtExpires.setTime_t(iTimeT);
      qdExpires = qdtExpires.date();
   }

   return qdExpires;
}

void CdmDataAccessHelper::SetQueryEnhancedResult(CdmQuery* p_pCdmQuery,
                                           int p_iColumn,
                                           QVariant p_qvValue,
                                          qint64 p_lObjectId,
                                                qint64 p_lContainerId)
{
   if (CHKPTR(p_pCdmQuery))
   {
      p_pCdmQuery->SetResultInternal(p_iColumn, p_qvValue, p_lObjectId, p_lContainerId);
   }
}

void CdmDataAccessHelper::AddBaseClassToClass(CdmClass* p_pClass,qint64 p_lBaseClassId)
{
    if (CHKPTR(p_pClass))
    {
        p_pClass->m_lBaseClassCounter++;
        p_pClass->m_qmBaseClasses.insert(p_pClass->m_lBaseClassCounter, p_lBaseClassId);
    }
}

CdmPackage *CdmDataAccessHelper::CreatePackage(qint64 p_lSchemeId, QString p_qstrKeyname)
{
    return new CdmPackage(p_lSchemeId, p_qstrKeyname);
}

void CdmDataAccessHelper::AddPackageToClassManager(CdmClassManager* p_pClassManager, CdmPackage *p_pPackage)
{
    if (CHKPTR(p_pPackage))
    {
      if (CHKPTR(p_pClassManager))
        {
         p_pClassManager->AddPackage(p_pPackage);
        }
    }
}

void CdmDataAccessHelper::SetOriginalPackageName(CdmPackage* p_pPackage, QString p_qstrName)
{
    p_pPackage->m_qstrOriginalPackageString = p_qstrName;
}

void CdmDataAccessHelper::SetCurrentScheme(CdmScheme *p_pScheme)
{
    Q_UNUSED(p_pScheme);
    //   CdmManager*
}

CdmClass *CdmDataAccessHelper::CreateNewTestClass(qint64 scheme,qint64 classid, QString name)
{
    return new CdmClass(scheme,classid,name);
}

CdmSession* CdmDataAccessHelper::CreateNewSession(qint64 p_lSessionId,qint64 p_lUser, IdmDataAccess* p_pDataAccess)
{
    CdmSession* pSession = nullptr;
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        if (!pSessionManager->m_qmSessionManager.contains(p_lSessionId))
        {
            pSession = new CdmSession();
            pSession->m_lSessionId = p_lSessionId;
            pSession->InitNewManager(p_pDataAccess);

            CdmDataProvider* pManager = pSession->GetDataProvider();

            if (CHKPTR(pManager))
            {
                CumUserManager* pUserManager = pManager->GetUserManager();

                if (CHKPTR(pUserManager))
                {
                    pSession->m_pSessionUser = pUserManager->FindUserById(p_lUser)                    ;
                }
            }


            pSessionManager->m_qmSessionManager.insert(pSession->GetId(), pSession);
            pSessionManager->m_qmSessionManagerAuth.insert(pSession->GetBaseAuth(), pSession);
        }
        else
        {
            pSession = pSessionManager->m_qmSessionManager[p_lSessionId];
        }
    }

    return pSession;
}

CdmClassManager* CdmDataAccessHelper::CreateClassManager(qint64 p_lSchemeId)
{
    return new CdmClassManager(p_lSchemeId);
}

CdmObjectContainer* CdmDataAccessHelper::CreateObjectContainer(qint64 p_lSchemeId,qint64 p_lContainerId, QString& p_qstrKeyname,qint64 p_lClassId)
{
    return new CdmObjectContainer(p_lSchemeId, p_lContainerId, p_qstrKeyname, p_lClassId);
}

CdmObjectContainer* CdmDataAccessHelper::CreateObjectContainer(QVariantMap& p_rMap)
{
    return new CdmObjectContainer(p_rMap);
}

void CdmDataAccessHelper::DeleteObjectContainer(CdmObjectContainer*& p_pContainer)
{
    DELPTR(p_pContainer);
}

CdmObject* CdmDataAccessHelper::CreateObject(QVariantMap& p_rMap)
{
    return new CdmObject(p_rMap);
}

CdmObject* CdmDataAccessHelper::CreateObject(qint64 p_lSchemeId,
                                            qint64 p_lObjectId,
                                            qint64 p_lClassId,
                                            qint64 p_lContainerId)
{
    return new CdmObject(p_lSchemeId,
                         p_lObjectId,
                         p_lClassId,
                         p_lContainerId);
}

void CdmDataAccessHelper::DeleteObject(CdmObject*& p_pObject)
{
    DELPTR(p_pObject);
}
