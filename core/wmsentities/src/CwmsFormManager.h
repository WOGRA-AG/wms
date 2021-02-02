/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsFormManager.h
 ** Started Implementation: 2012/09/09
 ** Description:
 ** 
 ** impelments the manager for forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSFORMMANAGER_H
#define CWMSFORMMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "basetools.h"

// Forwards
class CdmContainerManager;

// TypeDefs


/* 
 * This class implements the manager for forms
 */
class BASETOOLS_API CwmsFormManager : public QObject
{

   public:
   /** +-=---------------------------------------------------------So 9. Sep 13:33:41 2012--------*
    * @method  CwmsFormManager::CwmsFormManager              // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:33:41 2012-----------*/
    CwmsFormManager( );

   public:
   /** +-=---------------------------------------------------------So 9. Sep 13:33:50 2012--------*
    * @method  CwmsFormManager::~CwmsFormManager             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsFormManager                                            *
    *----------------last changed: -----------------------------So 9. Sep 13:33:50 2012-----------*/
    virtual ~CwmsFormManager( );

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:34:49 2012--------*
    * @method  CwmsFormManager::CheckFormDataStructure       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:34:49 2012-----------*/
    void CheckFormDataStructure();

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:35:23 2012--------*
    * @method  CwmsFormManager::CreateFormClasses            // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmManager                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:35:23 2012-----------*/
    void CreateFormClasses(CdmClassManager* p_pCdmManager);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:39:10 2012--------*
    * @method  CwmsFormManager::CreateFormBaseClass          // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:39:10 2012-----------*/
    void CreateFormBaseClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:40:04 2012--------*
    * @method  CwmsFormManager::CreateFormObjectListClass    // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:40:04 2012-----------*/
    void CreateFormObjectListClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:40:21 2012--------*
    * @method  CwmsFormManager::CreateFormObjectClass        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:40:21 2012-----------*/
    void CreateFormObjectClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:40:42 2012--------*
    * @method  CwmsFormManager::CreateFormUserDefinedClass   // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:40:42 2012-----------*/
    void CreateFormUserDefinedClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:41:07 2012--------*
    * @method  CwmsFormManager::CreateFormViewClass          // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:41:07 2012-----------*/
    void CreateFormViewClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:49:08 2012--------*
    * @method  CwmsFormManager::CreateFormStandardObjectListClass // private                      *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:49:08 2012-----------*/
    void CreateFormStandardObjectListClass(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------So 9. Sep 13:49:25 2012--------*
    * @method  CwmsFormManager::CreateFormObjectObjectListClass // private                        *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 9. Sep 13:49:25 2012-----------*/
    void CreateFormObjectObjectListClass(CdmClass* p_pCdmClass);


   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 09:52:35 2012-------*
    * @method  CwmsFormManager::GetOLManager                 // private                           *
    * @return  CdmContainerManager*                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 09:52:35 2012----------*/
    CdmContainerManager* GetContainerManager();

   private:
   /** +-=---------------------------------------------------------Mo 10. Sep 09:55:54 2012-------*
    * @method  CwmsFormManager::CreateObjectList             // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 09:55:54 2012----------*/
    void CreateObjectContainer(CdmClass* p_pCdmClass, QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:53:11 2012-------*
    * @method  CwmsFormManager::GetStandardFormObjectList    // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:53:11 2012----------*/
    CdmObjectContainer* GetStandardFormContainer();

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:53:19 2012-------*
    * @method  CwmsFormManager::GetGenericFormObjectList     // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:53:19 2012----------*/
    CdmObjectContainer* GetGenericFormContainer();

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:53:26 2012-------*
    * @method  CwmsFormManager::GetFormObjectObjectList      // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:53:26 2012----------*/
    CdmObjectContainer* GetFormObjectObjectContainer();

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:53:34 2012-------*
    * @method  CwmsFormManager::GetFormViewObjectList        // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:53:34 2012----------*/
    CdmObjectContainer* GetFormViewContainer();

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:53:42 2012-------*
    * @method  CwmsFormManager::GetFormUserDefinedObjectList // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:53:42 2012----------*/
    CdmObjectContainer* GetFormUserDefinedContainer();

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:17:26 2012-------*
    * @method  CwmsFormManager::CreateFormSearchClass        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:17:26 2012----------*/
    void CreateFormSearchClass(CdmClass* p_pCdmClass);

   public:
   /** +-=---------------------------------------------------------Di 18. Sep 09:22:26 2012-------*
    * @method  CwmsFormManager::GetFormSearchObjectList      // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 09:22:26 2012----------*/
    CdmObjectContainer* GetFormSearchContainer();

   public:
   /** +-=---------------------------------------------------------Fr 14. Dez 11:26:44 2012-------*
    * @method  CwmsFormManager::GeDefaultObjectForm          // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 11:26:44 2012----------*/
    CdmObject* GeDefaultObjectForm(CdmObject* p_pCdmObject);
    
	CdmObject* GeDefaultContainerForm(CdmObjectContainer* p_pContainer);
	private:
    void CreateFormLibrary( CdmClass* pCdmClassFormLibrary );
    QString GenerateWqlByName(QString p_qstrName, CdmObjectContainer *pContainer);
    QString GenerateWqlByClassUri(QString qstrClassUri, CdmObjectContainer* pContainer);
    QString GenerateLibraryWql(QString p_qstrName, QString p_qstrVersion, CdmObjectContainer *pContainer);
    QString GenerateResourceWql(QString p_qstrName, int p_type, CdmObjectContainer *pContainer);
    void CreateResource();
    void AddWqlMemberToClass(CdmClass *p_pClass);
    void CreateInteractiveComponentClass(CdmClass *pClass);
    void CreateInteractiveComponent();
public:
    CdmObjectContainer* GetFormLibrary();
    QString GetClassUri(CdmModelElement* p_pElement);
    QString GetUserDefinedUiForElement(CdmModelElement *p_pElement);
	QString GetUserDefinedUi(CdmObject *p_pElement);
	QString GetUserDefinedUi(CdmObjectContainer *p_pElement);
    QString GetUserDefinedUi(QString p_qstrName);
    QString GetWmsLibrary(QString p_qstrName, QString p_qstrVersion);
    void CreateFormResourceClass(CdmClass* pCdmClassFormResources);
    QByteArray GetResource(QString p_qstrName, int p_iType);
    CdmObjectContainer *GetResourceContainer();
    CdmObjectContainer *GetInteractiveComponentContainer();
};

#endif // CWMSFORMMANAGER_H
