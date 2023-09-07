/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsRuntimeBase.cpp
 ** Started Implementation: 2012/10/06
 ** Description:
 **
 ** implements the base functionality class for the runtime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMainWindow>
#include <QApplication>
#include <QPluginLoader>
#include <QDir>
#include <QFileInfo>

// WMS Includes
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmMessageManager.h"
#include "CdmScheme.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// WMS Basetools
#include "CwmsFormManager.h"
#include "CwmsApplicationServices.h"
#include "CwmsWorkflowStepExecutionEditorDlg.h"
#include "CwmsWorkflowStepEditorDlg.h"
#include "CwmsWorkflowDefitionEditor.h"

// own Includes
#include "CwmsEscalationEditorDlg.h"
#include "CwmsguiApplicationServices.h"
#include "CwmsSearchWindow.h"
#include "CwmsObjectObjectListEditorWidget.h"
#include "CwmsViewObjectListEditorWidget.h"
#include "CwmsHelp.h"
#include "CwmsAboutDlg.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsObjectEditor.h"
#include "CwmsObjectListEditorWidgetIf.h"
#include "CwmsRuntime.h"
#include "CwmsRuntimeBase.h"


/** +-=---------------------------------------------------------Sa 6. Okt 08:57:51 2012-----------*
 * @method  CwmsRuntimeBase::CwmsRuntimeBase                 // public                            *
 * @return                                                   //                                   *
 * @param   bool p_bIsRuntime                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:57:51 2012-----------*/
CwmsRuntimeBase::CwmsRuntimeBase(bool p_bIsRuntime)
: m_pqwMain(nullptr),
  m_bIsWmsRuntime(p_bIsRuntime)

{ 
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:53:30 2012-----------*
 * @method  CwmsRuntimeBase::~CwmsRuntimeBase                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsRuntimeBase                                               *
 *----------------last changed: --------------------------------Sa 6. Okt 08:53:30 2012-----------*/
CwmsRuntimeBase::~CwmsRuntimeBase()
{
}

/** +-=---------------------------------------------------------Sa 6. Okt 09:08:41 2012-----------*
 * @method  CwmsRuntimeBase::SetWidgetContainer              // public                            *
 * @return  void                                             //                                   *
 * @param   QWidget* p_pqWidget                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:08:41 2012-----------*/
void CwmsRuntimeBase::SetWidgetContainer(QWidget* p_pqWidget)
{
   m_pqwMain = p_pqWidget;
}

/** +-=---------------------------------------------------------Sa 6. Okt 09:49:36 2012-----------*
 * @method  CwmsRuntimeBase::InstallTranslator               // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:49:36 2012-----------*/
void CwmsRuntimeBase::InstallTranslator()
{
    BODY_TRY
    CwmsApplication cApp = GetApplication();

    if (cApp.IsValid())
    {
        QString qstrLanguage = cApp.GetCurrentUserLanguage();

        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (pCdmManager)
        {
            pCdmManager->SetCurrentLanguage(qstrLanguage);
        }

        m_cTranslator.LoadTranslations(cApp);
        qApp->installTranslator(&m_cTranslator);
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Mo 19. Aug 22:03:42 2013----------*
 * @method  CwmsRuntimeBase::RemoveTranslator                // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Aug 22:03:42 2013----------*/
void CwmsRuntimeBase::RemoveTranslator()
{
    BODY_TRY
    qApp->removeTranslator(&m_cTranslator);
    BODY_CATCH
}

/** +-=---------------------------------------------------------Di 13. Nov 11:39:48 2012----------*
 * @method  CwmsRuntimeBase::InstallBaseFunctionsToExecutor  // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 11:39:48 2012----------*/
void CwmsRuntimeBase::InstallBaseFunctionsToExecutor()
{
    CwmsguiApplicationServices::InstallUiEditors();
}

/** +-=---------------------------------------------------------Sa 6. Okt 09:32:02 2012-----------*
 * @method  CwmsRuntimeBase::OpenModule                      // protected                         *
 * @return  void                                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:32:02 2012-----------*/
void CwmsRuntimeBase::OpenModule(qint64 p_lObjectId)
{
   if (p_lObjectId > 0)
   {
      CdmObjectContainer* pCdmOLModules = GetApplication().GetModules();

      if (CHKPTR(pCdmOLModules))
      {
         CdmObject* pCdmObject = pCdmOLModules->FindObjectById(p_lObjectId);

         if (CHKPTR(pCdmObject))
         {
            OpenModule(CwmsApplicationModule(pCdmObject));
         }
      }
   }
}



/** +-=---------------------------------------------------------Sa 6. Okt 09:32:14 2012-----------*
 * @method  CwmsRuntimeBase::OpenModule                      // protected                         *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:32:14 2012-----------*/
void CwmsRuntimeBase::OpenModule(CwmsApplicationModule p_cModule)
{
    BODY_TRY
    if (p_cModule.IsValid())
    {
        DELPTR(m_pqwMain)
        m_cCurrentModule = p_cModule;
        CdmObject* pCdmUserInterface = m_cCurrentModule.GetUserInterface();

        if (!pCdmUserInterface)
        {
            OpenDefaultModule();
        }
        else
        {
            if (pCdmUserInterface->IsTypeOf("Technical_Form_Object_ObjectList"))
            {
                OpenObjectObjectListModule(p_cModule);
            }
            else if (pCdmUserInterface->IsTypeOf("Technical_Form_Standard_ObjectList"))
            {
                OpenStandardObjectListModule(p_cModule);
            }
            else if (pCdmUserInterface->IsTypeOf("Technical_Form_View"))
            {
                OpenViewObjectListModule(p_cModule);
            }
            else if (pCdmUserInterface->IsTypeOf("Technical_Form_Object"))
            {
                OpenGenericUserInterface(p_cModule);
            }
            else if (pCdmUserInterface->IsTypeOf("Technical_Form_UserDefined"))
            {
                OpenUserDefinedModule(p_cModule);
            }
            else if (pCdmUserInterface->IsTypeOf("Technical_Form_Search"))
            {
                OpenSearchModule(p_cModule);
            }
            else
            {
                ERR("Unknown Userinterface!")
            }
        }

        if (m_pqwMain)
        {
            QMainWindow* pQMainWindow = dynamic_cast<QMainWindow*>(GetMainWidget());
            pQMainWindow->setCentralWidget(m_pqwMain);
            m_pqwMain->show();

            // show module name in window title
            QString qstrWindowTitle = pQMainWindow->windowTitle();

            int iPos = qstrWindowTitle.lastIndexOf(" <");

            if (iPos > 0)
            {
                qstrWindowTitle.truncate(iPos);
            }

            qstrWindowTitle += QString(" <");
            qstrWindowTitle += p_cModule.GetName();
            qstrWindowTitle += QString(">");
            pQMainWindow->setWindowTitle(qstrWindowTitle);
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:58:49 2012-----------*
 * @method  CwmsRuntimeBase::OpenObjectObjectListModule      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:58:49 2012-----------*/
void CwmsRuntimeBase::OpenObjectObjectListModule(CwmsApplicationModule p_cModule)
{
   m_pqwMain = new CwmsObjectContainerEditorWidget(GetMainWidget());
   dynamic_cast<CwmsObjectContainerEditorWidget*>(m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectListEditorMode();
}


/** +-=---------------------------------------------------------Sa 6. Okt 08:58:54 2012-----------*
 * @method  CwmsRuntimeBase::OpenViewObjectListModule        // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:58:54 2012-----------*/
void CwmsRuntimeBase::OpenViewObjectListModule(CwmsApplicationModule p_cModule)
{
   m_pqwMain = new CwmsViewObjectListEditorWidget(GetMainWidget());
   dynamic_cast<CwmsViewObjectListEditorWidget*>(m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectListEditorMode();
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:58:59 2012-----------*
 * @method  CwmsRuntimeBase::OpenStandardObjectListModule    // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:58:59 2012-----------*/
void CwmsRuntimeBase::OpenStandardObjectListModule(CwmsApplicationModule p_cModule)
{
   m_pqwMain = new CwmsObjectListEditorWidgetIf(GetMainWidget());
   dynamic_cast<CwmsObjectListEditorWidgetIf*>(m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectListEditorMode();
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:59:03 2012-----------*
 * @method  CwmsRuntimeBase::OpenUserDefinedModule           // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:59:03 2012-----------*/
void CwmsRuntimeBase::OpenUserDefinedModule(CwmsApplicationModule p_cModule)
{
    Q_UNUSED(p_cModule);
   /* TODO
   m_pqwMain = new CwmsFormUserDefined(GetMainWidget());
   ((CwmsFormUserDefined*)m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectEditorMode();
   */
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:59:08 2012-----------*
 * @method  CwmsRuntimeBase::OpenSearchModule                // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:59:08 2012-----------*/
void CwmsRuntimeBase::OpenSearchModule(CwmsApplicationModule p_cModule)
{
   m_pqwMain = new CwmsSearchWindow(GetMainWidget());
   ((CwmsSearchWindow*)m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectListEditorMode();
}

/** +-=---------------------------------------------------------Sa 6. Okt 08:59:14 2012-----------*
 * @method  CwmsRuntimeBase::OpenGenericUserInterface        // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:59:14 2012-----------*/
void CwmsRuntimeBase::OpenGenericUserInterface(CwmsApplicationModule p_cModule)
{
   m_pqwMain = new CwmsObjectEditor(GetMainWidget());
   dynamic_cast<CwmsObjectEditor*> (m_pqwMain)->Initialize(p_cModule, nullptr);
   ObjectEditorMode();
}


/** +-=---------------------------------------------------------Sa 6. Okt 08:59:55 2012-----------*
 * @method  CwmsRuntimeBase::ObjectEditorMode                // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 08:59:55 2012-----------*/
void CwmsRuntimeBase::ObjectEditorMode()
{
   // must be reimplemented by MainWindow
}

/** +-=---------------------------------------------------------Sa 6. Okt 09:00:09 2012-----------*
 * @method  CwmsRuntimeBase::ObjectListEditorMode            // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:00:09 2012-----------*/
void CwmsRuntimeBase::ObjectListEditorMode()
{
   // must be reimplemented by MainWindow
}

void CwmsRuntimeBase::OpenDefaultModule()
{
   if (m_cCurrentModule.GetContainerModule() || m_cCurrentModule.GetView())
   {
      OpenDefaultObjectContainerModule();
   }
   else if (m_cCurrentModule.GetObjectModule())
   {
      OpenDefaultObjectModule();
   }
   else
   {
      ERR("Invalid Module configuration!");
   }
}

void CwmsRuntimeBase::OpenDefaultObjectContainerModule()
{
   m_pqwMain = new CwmsObjectListEditorWidgetIf(GetMainWidget());

   CwmsFormManager cManager;
   CdmObject* pFormConfig = cManager.GeDefaultContainerForm(m_cCurrentModule.GetContainerModule());

   if (m_bIsWmsRuntime)
   {
	  if (pFormConfig)
	  {
          ((CwmsObjectListEditorWidgetIf*)m_pqwMain)->SetContainer(m_cCurrentModule.GetContainerModule());
		  ((CwmsObjectListEditorWidgetIf*)m_pqwMain)->SetFormConfiguration(pFormConfig);
	  }
   }

   dynamic_cast<CwmsObjectListEditorWidgetIf*> (m_pqwMain)->Initialize(m_cCurrentModule, nullptr);
   ObjectListEditorMode();
}

void CwmsRuntimeBase::OpenDefaultObjectModule()
{
   CdmObject* pCdmObject = m_cCurrentModule.GetObjectModule();
   CwmsFormManager cManager;
   CdmObject* pFormConfig = cManager.GeDefaultObjectForm(pCdmObject);
   m_pqwMain = new CwmsObjectEditor(pCdmObject, GetMainWidget());

   if (pFormConfig)
   {
	   ((CwmsObjectEditor*)m_pqwMain)->SetFormConfiguration(pFormConfig);
   }

   ((CwmsObjectEditor*)m_pqwMain)->FillObjectEditor();
   ObjectEditorMode();
}

/** +-=---------------------------------------------------------Sa 6. Okt 09:38:29 2012-----------*
 * @method  CwmsRuntimeBase::GetMainWidget                   // public, p virtual                 *
 * @return  QWidget*                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:38:29 2012-----------*/


/** +-=---------------------------------------------------------Sa 6. Okt 09:05:52 2012-----------*
 * @method  CwmsRuntimeBase::GetApplication                  // public, p virtual                 *
 * @return  CwmsApplication                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Okt 09:05:52 2012-----------*/
