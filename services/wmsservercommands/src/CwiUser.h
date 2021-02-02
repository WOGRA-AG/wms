/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiUser.h
 ** Started Implementation: 2012/04/15
 ** Description:
 ** 
 ** Implements the user interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSUSER_H
#define CBIWMSUSER_H

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
 * This class Implements the user interface
 */
class WMSINTERFACE_API CwiUser : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiUser::CwiUser                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiUser( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiUser::~CwiUser                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiUser( );

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012--------*
    * @method  CwiUser::ExecuteGet                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:18:13 2012-----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiUser::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------So 15. Apr 11:47:14 2012-------*
    * @method  CwiUser::ExecutePut                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 11:47:14 2012----------*/
    virtual void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------So 15. Apr 11:47:08 2012-------*
    * @method  CwiUser::ExecuteDelete                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 11:47:08 2012----------*/
    virtual void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------So 15. Apr 12:44:23 2012-------*
    * @method  CwiUser::GetResourceDescription            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 12:44:23 2012----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:29:39 2013-------*
    * @method  CwiUser::GetVersion                        // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:29:39 2013----------*/
    QString getVersion();

public: void RegisterNewUser(CwmscomData* p_pData);

public: void AddUser(CwmscomData* p_pData);

public: void UpdateUser(CwmscomData* p_pData);

public: void ChangePasswordWithoutSession(CwmscomData* p_pData);

public: void ChangePasswordSession(CwmscomData* p_pData);

public: void GetUserByEmail(CwmscomData* p_pData);

public: void GetUserByLogin(CwmscomData* p_pData);

public: void GetUserByidentityKey(CwmscomData *p_pData);

public: void GetUserById(CwmscomData *p_pData);

public: void GetFindUsers(CwmscomData* p_pData);

};

#endif // CBIWMSUSER_H
