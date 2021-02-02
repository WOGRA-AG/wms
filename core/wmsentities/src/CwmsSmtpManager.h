/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsSmtpManager.h
 ** Started Implementation: 2012/11/21
 ** Description:
 ** 
 ** implements the smtp manager.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSMTPMANAGER_H
#define CWMSSMTPMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsSmtpConfiguration.h"
#include "basetools.h"

// Forwards
class CwmsbtMailMessage;

// TypeDefs


/* 
 * This class implements the smtp manager.
 */
class BASETOOLS_API CwmsSmtpManager : public QObject
{

   public:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:26:33 2012-------*
    * @method  CwmsSmtpManager::CwmsSmtpManager              // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:26:33 2012----------*/
    CwmsSmtpManager( );

   public:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:26:41 2012-------*
    * @method  CwmsSmtpManager::~CwmsSmtpManager             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsSmtpManager                                            *
    *----------------last changed: -----------------------------Mi 21. Nov 10:26:41 2012----------*/
    virtual ~CwmsSmtpManager( );

   private:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:30:16 2012-------*
    * @method  CwmsSmtpManager::CreateSmtpClass              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pClassManager              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:30:16 2012----------*/
    void CreateSmtpClass(CdmClassManager* p_pClassManager);

   private:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:28:25 2012-------*
    * @method  CwmsSmtpManager::CheckDataStructure           // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:28:25 2012----------*/
    bool CheckDataStructure();

   private:
   /** +-=---------------------------------------------------------Mi 21. Nov 10:28:43 2012-------*
    * @method  CwmsSmtpManager::CreateDataStructure          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 10:28:43 2012----------*/
    void CreateDataStructure();

    void CreateSender(CdmClass *p_pClass);
public:
   /** +-=---------------------------------------------------------Mi 21. Nov 16:20:15 2012-------*
    * @method  CwmsSmtpManager::GetSmtpConfiguration         // public                            *
    * @return  CwmsSmtpConfiguration*                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 16:20:15 2012----------*/
    CwmsSmtpConfiguration* GetSmtpConfiguration();

   public:
   /** +-=---------------------------------------------------------Mi 21. Nov 11:41:56 2012-------*
    * @method  CwmsSmtpManager::GetObjectList                // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 11:41:56 2012----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Mi 21. Nov 11:42:19 2012-------*
    * @method  CwmsSmtpManager::GetSmtpObject                // public                            *
    * @return  CdmObject*                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 11:42:19 2012----------*/
    CdmObject* GetSmtpObject();

   public:
   /** +-=---------------------------------------------------------Di 8. Jan 17:18:47 2013--------*
    * @method  CwmsSmtpManager::CreateMailMessage            // public                            *
    * @return  CwmsbtMailMessage*                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 17:18:47 2013-----------*/
    CwmsbtMailMessage*  CreateMailMessage();
};

#endif // CWMSSMTPMANAGER_H
