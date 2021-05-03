/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsWorkflowManager.h
 ** Started Implementation: 2012/08/24
 ** Description:
 ** 
 ** implements the manager for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSWORKFLOWMANAGER_H
#define CWMSWORKFLOWMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsWorkflowDefinition.h"
#include "basetools.h"

// Forwards
class CdmClassManager;
class CdmObject;
class CdmObjectContainer;
class CdmContainerManager;

// TypeDefs


/* 
 * This class implements the manager for views
 */
class BASETOOLS_API CwmsWorkflowManager : public QObject
{


   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:08:34 2012-------*
    * @method  CwmsWorkflowManager::CwmsWorkflowManager              // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:08:34 2012----------*/
    CwmsWorkflowManager( );

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:08:44 2012-------*
    * @method  CwmsWorkflowManager::~CwmsWorkflowManager             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsWorkflowManager                                            *
    *----------------last changed: -----------------------------Fr 24. Aug 10:08:44 2012----------*/
    virtual ~CwmsWorkflowManager( );

   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:29:10 2012-------*
    * @method  CwmsWorkflowManager::CheckWorkflowDataStructure // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:29:10 2012----------*/
    void CheckWorkflowDataStructure();


   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:10:31 2012-------*
    * @method  CwmsWorkflowManager::GetObjectList                // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:10:31 2012----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:30:59 2012-------*
    * @method  CwmsWorkflowManager::GetWorkflowList          // public                            *
    * @return  void                                          //                                   *
    * @param   QList<CdmObject*>& p_rqlViews           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:30:59 2012----------*/
    void GetWorkflowList(QList<CdmObject*>& p_rqlViews);




   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:36:23 2012-------*
    * @method  CwmsWorkflowManager::CreateClasses            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:36:23 2012----------*/
    void CreateClasses();

   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:50:29 2012-------*
    * @method  CwmsWorkflowManager::GetClassManager          // private                           *
    * @return  CdmClassManager*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:50:29 2012----------*/
    CdmClassManager* GetClassManager();

   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:44:51 2012-------*
    * @method  CwmsWorkflowManager::CreateTeamClass          // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:44:51 2012----------*/
    void CreateTeamClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:44:42 2012-------*
    * @method  CwmsWorkflowManager::CreateEscalationClass    // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:44:42 2012----------*/
    void CreateEscalationClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mi 24. Okt 15:16:33 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowStepDefinitionClass // private                  *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 15:16:33 2012----------*/
    void CreateWorkflowStepDefinitionClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mi 24. Okt 15:16:55 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowBaseClass  // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 15:16:55 2012----------*/
    void CreateWorkflowBaseClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mi 24. Okt 15:17:15 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowStepExecutionClass // private                   *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 15:17:15 2012----------*/
    void CreateWorkflowStepExecutionClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mo 22. Okt 15:43:02 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowObjectClass // private                          *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 22. Okt 15:43:02 2012----------*/
    void CreateWorkflowObjectClass(CdmClassManager* p_pCdmClassManager);


   private:
   /** +-=---------------------------------------------------------Di 23. Okt 18:30:30 2012-------*
    * @method  CwmsWorkflowManager::CreateObjectLists        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmContainerManager* p_pCmOLManager          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Okt 18:30:30 2012----------*/
    void CreateObjectLists(CdmContainerManager* p_pCmOLManager);

   private:
   /** +-=---------------------------------------------------------Di 23. Okt 18:42:07 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowDefinitionClass // private                      *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Okt 18:42:07 2012----------*/
    void CreateWorkflowDefinitionClass(CdmClassManager* p_pCdmClassManager);

   private:
   /** +-=---------------------------------------------------------Mi 24. Okt 15:21:32 2012-------*
    * @method  CwmsWorkflowManager::CreateWorkflowStepSuccessorClass // private                   *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 15:21:32 2012----------*/
    void CreateWorkflowStepSuccessorClass(CdmClassManager* p_pCdmClassManager);

    void RefactorClasses();
public:
   /** +-=---------------------------------------------------------Fr 21. Dez 11:09:06 2012-------*
    * @method  CwmsWorkflowManager::FindWorkflowByName       // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Dez 11:09:06 2012----------*/
    CdmObject* FindWorkflowByName(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Fr 21. Dez 11:09:11 2012-------*
    * @method  CwmsWorkflowManager::FindWorkflowById         // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 21. Dez 11:09:11 2012----------*/
    CdmObject* FindWorkflowById(long p_lObjectId);

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:10:38 2012-------*
    * @method  CwmsWorkflowManager::FindMajorWorkflowByClassUri // public                         *
    * @return  CwmsWorkflowDefinition                        //                                   *
    * @param   QString p_qstrClassUri                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:10:38 2012----------*/
    CwmsWorkflowDefinition FindMajorWorkflowByClassUri(QString p_qstrClassUri);

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:37:49 2012-------*
    * @method  CwmsWorkflowManager::GetWorkflowStepsObjectList // public                          *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:37:49 2012----------*/
    CdmObjectContainer* GetWorkflowStepsObjectList();
};

#endif // CwmsWorkflowManager_H
