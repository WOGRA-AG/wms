/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsRuntimeManager.h
 ** Started Implementation: 2012/08/30
 ** Description:
 ** 
 ** implements the runtime manager
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSRUNTIMEMANAGER_H
#define CWMSRUNTIMEMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// Own Includes
#include "wmsgui.h"
#include "CwmsApplicationManager.h"

// Forwards
class CwmsRuntime;

// TypeDefs


/* 
 * This class implements the manager for the runtime
 */
class WMSGUI_API CwmsRuntimeManager
{
   private:
      CwmsRuntime* m_pCwmsRuntime;
      QString m_qstrApplicationName;

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:06:09 2012-------*
    * @method  CwmsRuntimeManager::CwmsRuntimeManager        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:06:09 2012----------*/
    CwmsRuntimeManager( );

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:06:19 2012-------*
    * @method  CwmsRuntimeManager::~CwmsRuntimeManager       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsRuntimeManager                                         *
    *----------------last changed: -----------------------------Do 30. Aug 14:06:19 2012----------*/
    virtual ~CwmsRuntimeManager( );

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:06:38 2012-------*
    * @method  CwmsRuntimeManager::SetApplicationName        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:06:38 2012----------*/
    void SetApplicationName(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:07:13 2012-------*
    * @method  CwmsRuntimeManager::GetApplicationName        // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:07:13 2012----------*/
    QString GetApplicationName();

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:33:25 2012-------*
    * @method  CwmsRuntimeManager::StartApplication          // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:33:25 2012----------*/
    void StartApplication();

   private:
   /** +-=---------------------------------------------------------Do 30. Aug 14:20:08 2012-------*
    * @method  CwmsRuntimeManager::OpenApplicationSelection  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:20:08 2012----------*/
    void OpenApplicationSelection();

   public:
   /** +-=---------------------------------------------------------Di 4. Sep 08:57:51 2012--------*
    * @method  CwmsRuntimeManager::GetApplication            // public                            *
    * @return  CwmsApplication                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 4. Sep 08:57:51 2012-----------*/
    CwmsApplication GetApplication();
};

#endif // CWMSRUNTIMEMANAGER_H
