/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiUserGroupList.cpp
 ** Started Implementation: 2012/04/15
 ** Description:
 **
 ** Implements a interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS INcludes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiCommandDeleteUsergroup.h"
#include "CwiCommandRemoveUserToGroupRelation.h"
#include "CwiCommandAddUserToGroupRelation.h"
#include "CwiCommandUpdateUsergroup.h"
#include "CwiCommandAddNewUsergroup.h"
#include "CwiCommandFindGroup.h"
#include "CwiCommandGetGroupUserList.h"
#include "CwiUserGroupList.h"

#include "CwiCommandGetUserGroupById.h"
#include "CwiCommandGetUserGroupByName.h"

/** +-=---------------------------------------------------------Di 5. Feb 13:21:25 2013-----------*
 * @method  CwiUserGroupList::CwiUserGroupList         // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 13:21:25 2013-----------*/
CwiUserGroupList::CwiUserGroupList(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "UsergroupList", true, true)
{
}

/** +-=---------------------------------------------------------Di 5. Feb 13:21:33 2013-----------*
 * @method  CwiUserGroupList::~CwiUserGroupList        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiUserGroupList                                           *
 *----------------last changed: --------------------------------Di 5. Feb 13:21:33 2013-----------*/
CwiUserGroupList::~CwiUserGroupList()
{

}
void CwiUserGroupList::ExecuteDelete(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        QString qstrMode;
        if (p_pData->HasValue("Mode"))
        {
           qstrMode = p_pData->GetValue("Mode").toString();
           if (qstrMode ==  "UserToGroupRelation")
           {
                removeUserToGroupRelation(p_pData);
           }
           else if (qstrMode == "Usergroup")
           {
                deleteUsergroup(p_pData);
           }
        }
    }
}

void CwiUserGroupList::ExecutePut(CwmscomData* p_pData)
{
    if (CHKPTR(p_pData))
    {
        QString qstrMode;
        if (p_pData->HasValue("Mode"))
        {
           qstrMode = p_pData->GetValue("Mode").toString();
           if (qstrMode ==  "Usergroup")
           {
                addNewUsergroup(p_pData);
           }
           else if (qstrMode == "UserToGroupRelation")
           {
                addUserToGroupRelation(p_pData);
           }
           else if (qstrMode == "UpdateUsergroup")
           {
                updateUsergroup(p_pData);
           }
        }
    }
}

/** +-=---------------------------------------------------------Di 5. Feb 13:21:37 2013-----------*
 * @method  CwiUserGroupList::ExecuteGet                  // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 13:21:37 2013-----------*/
void CwiUserGroupList::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      QString qstrMode;
      if(p_pData->HasValue("Mode"))
      {
          qstrMode = p_pData->GetValue("Mode").toString();
          if(qstrMode == "FindGroup")
          {
              GetFindGroup(p_pData);
          }
          else if(qstrMode == "FindGroupId")
          {
              GetUserGroupById(p_pData);
          }
          else if(qstrMode == "FindGroupName")
          {
              GetUserGroupByName(p_pData);
          }
          else if(qstrMode == "GetMembersOfGroup")
          {
              GetMembersOfGroup(p_pData);
          }
      }
      else
      {
          CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
          int iGroupId = p_pData->GetValue("GroupId").toInt();

          if(iGroupId > 0)
          {
              CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

              if(pCdmManager)
              {
                  CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

                  if(pCumUserManager)
                  {
                      CumUserGroup* pCumUserGroup = pCumUserManager->FindUserGroupById(iGroupId);

                      if(pCumUserGroup)
                      {
                          pResult->AddValue("Group", pCumUserGroup->GetVariant());
                          pResult->SetMessage("Group Found!");
                          pResult->SetMessageCode(1);
                          pResult->SetSeverity(eWmscomMessageServerityInfo);
                      }
                      else
                      {
                         pResult->SetMessage("Group not found on Server");
                         pResult->SetMessageCode(-5000);
                         pResult->SetSeverity(eWmscomMessageServerityError);
                      }
                  }
                  else
                  {
                     pResult->SetMessage("User Manager not found");
                     pResult->SetMessageCode(-5000);
                     pResult->SetSeverity(eWmscomMessageServerityFatal);
                  }
              }
              else
              {
                 pResult->SetMessage("Session not found");
                 pResult->SetMessageCode(-5000);
                 pResult->SetSeverity(eWmscomMessageServerityFatal);
              }
          }
      }
   }
}

/** +-=---------------------------------------------------------Di 5. Feb 13:21:44 2013-----------*
 * @method  CwiUserGroupList::ExecuteDescription          // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 13:21:44 2013-----------*/
void CwiUserGroupList::executeDescription(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Userlist");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      pResult->AddValue("Usergroup", "List of Usergroups - Result");
   }
}

void CwiUserGroupList::addNewUsergroup(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandAddNewUsergroup command(p_pData);
        command.Execute();
    }
}



void CwiUserGroupList::updateUsergroup(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandUpdateUsergroup command(p_pData);
        command.Execute();
    }
}


void CwiUserGroupList::addUserToGroupRelation(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandAddUserToGroupRelation command(p_pData);
        command.Execute();
    }
}


void CwiUserGroupList::removeUserToGroupRelation(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandRemoveUserToGroupRelation command(p_pData);
        command.Execute();
    }
}

void CwiUserGroupList::deleteUsergroup(CwmscomData *p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandDeleteUsergroup command(p_pData);
        command.Execute();
    }
}

void CwiUserGroupList::GetFindGroup(CwmscomData * p_pData)
{
    CwiCommandFindGroup command(p_pData);
    command.Execute();
}

void CwiUserGroupList::GetUserGroupById(CwmscomData *p_pData)
{
    CwiCommandGetUserGroupById command(p_pData);
    command.Execute();
}

void CwiUserGroupList::GetUserGroupByName(CwmscomData *p_pData)
{
    CwiCommandGetUserGroupByName command(p_pData);
    command.Execute();
}

void CwiUserGroupList::GetMembersOfGroup(CwmscomData *p_pData)
{
    CwiCommandGetGroupUserList command(p_pData);
    command.Execute();
    QList<CumUser*> qll_Members = command.GetResult();
}


/** +-=---------------------------------------------------------Di 5. Feb 13:32:13 2013-----------*
 * @method  CwiUserGroupList::GetResourceDescription      // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 13:32:13 2013-----------*/
QString CwiUserGroupList::GetResourceDescription()
{
   return "Returns the list of usergroups from server";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:30:09 2013----------*
 * @method  CwiUserGroupList::GetVersion                  // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:30:09 2013----------*/
QString CwiUserGroupList::getVersion()
{
   return "0.1.0";
}
