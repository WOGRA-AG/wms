/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsApplicationManager.h
 ** Started Implementation: 2012/08/30
 ** Description:
 ** 
 ** manages the user defined applications in WMS Runtime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSAPPLICATIONMANAGER_H
#define CWMSAPPLICATIONMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsApplication.h"
#include "basetools.h"

// Forwards
class CdmObjectContainer;
class CdmClassManager;
class CdmClass;
class CdmObject;

// TypeDefs


/* 
 * This class manages the user defined applications in WMS Runtime
 */
class BASETOOLS_API CwmsApplicationManager : public QObject
{

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 13:29:51 2012-------*
    * @method  CwmsApplicationManager::CwmsApplicationManager // public                           *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 13:29:51 2012----------*/
    CwmsApplicationManager( );

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 13:29:58 2012-------*
    * @method  CwmsApplicationManager::~CwmsApplicationManager // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsApplicationManager                                     *
    *----------------last changed: -----------------------------Do 30. Aug 13:29:58 2012----------*/
    virtual ~CwmsApplicationManager( );

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 13:31:06 2012-------*
    * @method  CwmsApplicationManager::GetObjectList         // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 13:31:06 2012----------*/
    CdmObjectContainer* GetObjectList();

   private:
   /** +-=---------------------------------------------------------Do 30. Aug 13:32:46 2012-------*
    * @method  CwmsApplicationManager::CreateApplicationClass // private                          *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 13:32:46 2012----------*/
    void CreateApplicationClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Do 30. Aug 13:32:24 2012-------*
    * @method  CwmsApplicationManager::CheckApplicationDataStructure // private                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 13:32:24 2012----------*/
    void CheckApplicationDataStructure();

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 16:42:07 2012-------*
    * @method  CwmsApplicationManager::FindApplication       // public                            *
    * @return  CwmsApplication                               //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:42:07 2012----------*/
    CwmsApplication FindApplication(QString p_qstrName);

   private:
   /** +-=---------------------------------------------------------Do 30. Aug 13:45:52 2012-------*
    * @method  CwmsApplicationManager::CreateAppModuleClass  // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 13:45:52 2012----------*/
    void CreateAppModuleClass(CdmClass* p_pCdmClass);

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 14:44:05 2012-------*
    * @method  CwmsApplicationManager::GetApplicationList    // public                            *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:44:05 2012----------*/
    QStringList GetApplicationList();

   public:
   /** +-=---------------------------------------------------------Do 30. Aug 16:16:51 2012-------*
    * @method  CwmsApplicationManager::GetApplication        // public                            *
    * @return  CwmsApplication                               //                                   *
    * @param   int p_iObjectId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:16:51 2012----------*/
    CwmsApplication GetApplication(int p_iObjectId);

    void AddPluginsMember(CdmClass *p_pCdmClass);
private:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:02:43 2012--------*
    * @method  CwmsApplicationManager::CreateUserLanguageClass // private                         *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:02:43 2012-----------*/
    void CreateUserLanguageClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:02:32 2012--------*
    * @method  CwmsApplicationManager::CreateRuntimeTranslationClass // private                   *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:02:32 2012-----------*/
    void CreateRuntimeTranslationClass(CdmClass* p_pCdmClass);
    void AddMainMethodToClass(CdmClass *p_pClass);
    void AddIconToClass(CdmClass *p_pClass);
};

#endif // CWMSAPPLICATIONMANAGER_H
