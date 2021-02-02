/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiUserList.h
 ** Started Implementation: 2012/04/15
 ** Description:
 ** 
 ** Implements the userlist interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSUSERGROUPLIST_H
#define CBIWMSUSERGROUPLIST_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSCOM Includes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"

// Forwards
class CwmscomController;
class CwmscomData;

// TypeDefs


/* 
 * This class Implements the userlist
 */
class WMSINTERFACE_API CwiUserGroupList : public CwmscomResourceBase
{


   public:
   /** +-=---------------------------------------------------------Di 5. Feb 13:21:25 2013--------*
    * @method  CwiUserGroupList::CwiUserGroupList      // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 13:21:25 2013-----------*/
    CwiUserGroupList( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 13:21:33 2013--------*
    * @method  CwiUserGroupList::~CwiUserGroupList     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwiUserGroupList                                        *
    *----------------last changed: -----------------------------Di 5. Feb 13:21:33 2013-----------*/
    virtual ~CwiUserGroupList( );

public: void ExecutePut(CwmscomData* p_pData);

public: void ExecuteDelete (CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 13:21:37 2013--------*
    * @method  CwiUserGroupList::ExecuteGet               // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 13:21:37 2013-----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 13:21:44 2013--------*
    * @method  CwiUserGroupList::ExecuteDescription       // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 13:21:44 2013-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Di 5. Feb 13:32:13 2013--------*
    * @method  CwiUserGroupList::GetResourceDescription   // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 13:32:13 2013-----------*/
    QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:30:09 2013-------*
    * @method  CwiUserGroupList::GetVersion               // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:30:09 2013----------*/
    QString getVersion();

public:
    void addNewUsergroup(CwmscomData* p_pData);
    void addNewUserToGroupRelation(CwmscomData* p_pData);
    void updateUsergroup(CwmscomData* p_pData);
    void removeUserToGroupRelation(CwmscomData* p_pData);
    void addUserToGroupRelation(CwmscomData* p_pData);
    void deleteUsergroup(CwmscomData* p_pData);

public: void GetUserGroupByName(CwmscomData* p_pData);

public: void GetUserGroupById(CwmscomData* p_pData);

public: void GetFindGroup(CwmscomData* p_pData);

public: void GetMembersOfGroup(CwmscomData *p_pData);
};

#endif // CBIWMSUSERLIST_H
