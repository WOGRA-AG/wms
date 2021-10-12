/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsRuntimeBase.h
 ** Started Implementation: 2012/10/06
 ** Description:
 ** 
 ** implements the base functionality class for the runtime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSRUNTIMEBASE_H
#define CWMSRUNTIMEBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes
#include "wmsgui.h"
#include "CwmsApplication.h"
#include "CwmsApplicationModule.h"
#include "CwmsTranslator.h"

// Forwards
class QWidget;

// TypeDefs


/* 
 * This class implements the base functionality class for the runtime
 */
class WMSGUI_API CwmsRuntimeBase
{
   protected:
      QWidget* m_pqwMain;
      CwmsApplicationModule m_cCurrentModule;

   private:
      bool m_bIsWmsRuntime;
      CwmsTranslator m_cTranslator;

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:57:51 2012--------*
    * @method  CwmsRuntimeBase::CwmsRuntimeBase              // public                            *
    * @return                                                //                                   *
    * @param   bool p_bIsRuntime                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:57:51 2012-----------*/
    CwmsRuntimeBase( bool p_bIsRuntime);

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:53:30 2012--------*
    * @method  CwmsRuntimeBase::~CwmsRuntimeBase             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsRuntimeBase                                            *
    *----------------last changed: -----------------------------Sa 6. Okt 08:53:30 2012-----------*/
    virtual ~CwmsRuntimeBase( );

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:38:29 2012--------*
    * @method  CwmsRuntimeBase::GetMainWidget                // public, p virtual                 *
    * @return  QWidget*                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:38:29 2012-----------*/
    virtual QWidget* GetMainWidget()= 0;

   protected:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:32:14 2012--------*
    * @method  CwmsRuntimeBase::OpenModule                   // protected                         *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:32:14 2012-----------*/
    void OpenModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:58:49 2012--------*
    * @method  CwmsRuntimeBase::OpenObjectObjectListModule   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:58:49 2012-----------*/
    void OpenObjectObjectListModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:58:54 2012--------*
    * @method  CwmsRuntimeBase::OpenViewObjectListModule     // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:58:54 2012-----------*/
    void OpenViewObjectListModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:58:59 2012--------*
    * @method  CwmsRuntimeBase::OpenStandardObjectListModule // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:58:59 2012-----------*/
    void OpenStandardObjectListModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:59:03 2012--------*
    * @method  CwmsRuntimeBase::OpenUserDefinedModule        // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:59:03 2012-----------*/
    void OpenUserDefinedModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:59:08 2012--------*
    * @method  CwmsRuntimeBase::OpenSearchModule             // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:59:08 2012-----------*/
    void OpenSearchModule(CwmsApplicationModule p_cModule);

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:59:14 2012--------*
    * @method  CwmsRuntimeBase::OpenGenericUserInterface     // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:59:14 2012-----------*/
    void OpenGenericUserInterface(CwmsApplicationModule p_cModule);

   protected:
   /** +-=---------------------------------------------------------Sa 6. Okt 08:59:55 2012--------*
    * @method  CwmsRuntimeBase::ObjectEditorMode             // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 08:59:55 2012-----------*/
    virtual void ObjectEditorMode();

   protected:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:00:09 2012--------*
    * @method  CwmsRuntimeBase::ObjectListEditorMode         // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:00:09 2012-----------*/
    virtual void ObjectListEditorMode();

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:05:52 2012--------*
    * @method  CwmsRuntimeBase::GetApplication               // public, p virtual                 *
    * @return  CwmsApplication                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:05:52 2012-----------*/
    virtual CwmsApplication GetApplication()= 0;

   protected:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:32:02 2012--------*
    * @method  CwmsRuntimeBase::OpenModule                   // protected                         *
    * @return  void                                          //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:32:02 2012-----------*/
    void OpenModule(qint64 p_lObjectId);

    void OpenDefaultModule();

    void OpenDefaultObjectModule();

    void OpenDefaultObjectContainerModule();

   public:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:08:41 2012--------*
    * @method  CwmsRuntimeBase::SetWidgetContainer           // public                            *
    * @return  void                                          //                                   *
    * @param   QWidget* p_pqWidget                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:08:41 2012-----------*/
    void SetWidgetContainer(QWidget* p_pqWidget);

   protected:
   /** +-=---------------------------------------------------------Sa 6. Okt 09:49:36 2012--------*
    * @method  CwmsRuntimeBase::InstallTranslator            // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 6. Okt 09:49:36 2012-----------*/
    virtual void InstallTranslator();

   protected:
   /** +-=---------------------------------------------------------Di 13. Nov 11:39:48 2012-------*
    * @method  CwmsRuntimeBase::InstallBaseFunctionsToExecutor // protected, virtual              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:39:48 2012----------*/
    virtual void InstallBaseFunctionsToExecutor();

   protected:
   /** +-=---------------------------------------------------------Mo 19. Aug 22:03:42 2013-------*
    * @method  CwmsRuntimeBase::RemoveTranslator             // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Aug 22:03:42 2013----------*/
    virtual void RemoveTranslator();
};

#endif // CWMSRUNTIMEBASE_H
