/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsguiObjectEditorSelector.cpp
 ** Started Implementation: 2011/07/14
 ** Description:
 **
 ** this class choses the right editor for editing a given object.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QQuickWindow>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"

// WMSQML Includes
#include "CwqQmlObjectViewer.h"

// WMS BASETOOLS Includes
#include "CwmsFormUserDefined.h"

// own Includes
#include "cwmsbtplattforminformation.h"
#include "CwmsObjectListEditorIf.h"
#include "IwmsObjectEditorDescriptor.h"
#include "IwmsObjectListEditorDescriptor.h"
#include "CwmsFormManager.h"
#include "CwmsWorkflowDefinition.h"
#include "CwmsWorkflowDefitionEditor.h"
#include "CwmsWorkflowStepDefinition.h"
#include "CwmsWorkflowStepExecution.h"
#include "CwmsWorkflowStepEditorDlg.h"
#include "CwmsWorkflowStepExecutionEditorDlg.h"
#include "CwmsEscalation.h"
#include "CwmsEscalationEditorDlg.h"
#include "CwmsguiObjectEditorIf.h"
#include "CwmsguiObjectEditorSelector.h"

CwmsguiObjectEditorSelector* CwmsguiObjectEditorSelector::m_pSelector = nullptr;

/** +-=---------------------------------------------------------Di 14. Aug 16:11:01 2012----------*
 * @method  CwmsguiObjectEditorSelector::CwmsguiObjectEditorSelector // public                    *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 16:11:01 2012----------*/
CwmsguiObjectEditorSelector::CwmsguiObjectEditorSelector()
{
}

/** +-=---------------------------------------------------------Di 14. Aug 16:11:08 2012----------*
 * @method  CwmsguiObjectEditorSelector::~CwmsguiObjectEditorSelector // public, virtual          *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsguiObjectEditorSelector                                   *
 *----------------last changed: --------------------------------Di 14. Aug 16:11:08 2012----------*/
CwmsguiObjectEditorSelector::~CwmsguiObjectEditorSelector()
{
}


void CwmsguiObjectEditorSelector::Init()
{
    if (!m_pSelector)
    {
       m_pSelector = new CwmsguiObjectEditorSelector();
    }
}

CwmsguiObjectEditorSelector* CwmsguiObjectEditorSelector::GetSelector()
{
   Init();
   return m_pSelector;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:47:22 2011----------*
 * @method  CwmsguiObjectEditorSelector::Create              // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObjectAdaptor& p_CdmObjectAdaptor             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:47:22 2011----------*/
bool CwmsguiObjectEditorSelector::Create(CdmObjectAdaptor& p_CdmObjectAdaptor, QWidget* p_pqwParent)
{
   bool bRet = false;
   CdmObject* pCdmObject = p_CdmObjectAdaptor.GetObject();

   if (CHKPTR(pCdmObject))
   {
      // shows a new object in the editor
      bRet = Create(pCdmObject, p_pqwParent); 
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:47:57 2011----------*
 * @method  CwmsguiObjectEditorSelector::Create              // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:47:57 2011----------*/
bool CwmsguiObjectEditorSelector::Create(CdmObject* p_pCdmObject, QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

   if (CHKPTR(pSelector))
   {
      // shows a new object in the editor
       bRet = pSelector->DisplayObjectEditor(p_pCdmObject, eWmsGuiDisplayModeNew, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:49:14 2011----------*
 * @method  CwmsguiObjectEditorSelector::View                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObjectAdaptor p_CdmObjectAdaptor              //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:49:14 2011----------*/
bool CwmsguiObjectEditorSelector::View(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent)
{
   bool bRet = false;
   CdmObject* pCdmObject = p_CdmObjectAdaptor.GetObject();

   if (CHKPTR(pCdmObject))
   {
      // shows the object in view mode
      bRet = View(pCdmObject, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 17. Dez 10:09:31 2012----------*
 * @method  CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor // public, static          *
 * @return  void                                             //                                   *
 * @param   IwmsObjectEditorDescriptor* p_pDescriptor        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Dez 10:09:31 2012----------*/
void CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(IwmsObjectEditorDescriptor* p_pDescriptor)
{
   if (CHKPTR(p_pDescriptor))
   {
      CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

      if (CHKPTR(pSelector))
      {
         if (pSelector->m_qmObjectDescriptors.contains(p_pDescriptor->GetClassKeyname()))
         {
            IwmsObjectEditorDescriptor* pDescriptor = pSelector->m_qmObjectDescriptors[p_pDescriptor->GetClassKeyname()];
            DELPTR(pDescriptor);
         }

         pSelector->m_qmObjectDescriptors.insert(p_pDescriptor->GetClassKeyname(), 
                                                 p_pDescriptor);
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Dez 10:09:02 2012----------*
 * @method  CwmsguiObjectEditorSelector::InstallObjectListEditorDescriptor // public, static      *
 * @return  void                                             //                                   *
 * @param   IwmsObjectListEditorDescriptor* p_pDescriptor    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Dez 10:09:02 2012----------*/
void CwmsguiObjectEditorSelector::InstallObjectListEditorDescriptor(IwmsObjectListEditorDescriptor* p_pDescriptor)
{
   if (CHKPTR(p_pDescriptor))
   {
      CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

      if (CHKPTR(pSelector))
      {
         pSelector->m_qmObjectListDescriptors.insert(p_pDescriptor->GetClassKeyname(), 
                                                     p_pDescriptor);
      }
   }
}

/** +-=---------------------------------------------------------Do 14. Jul 15:49:56 2011----------*
 * @method  CwmsguiObjectEditorSelector::View                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:49:56 2011----------*/
bool CwmsguiObjectEditorSelector::View(CdmObject* p_pCdmObject, QWidget* p_pqwParent)
{
   bool bRet = true;
   CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

   if (CHKPTR(pSelector))
   {
      // shows the object in view mode
      bRet =pSelector->DisplayObjectEditor(p_pCdmObject, eWmsGuiDisplayModeRead, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 17. Dez 10:14:51 2012----------*
 * @method  CwmsguiObjectEditorSelector::View                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Dez 10:14:51 2012----------*/
bool CwmsguiObjectEditorSelector::View(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent)
{
   bool bRet = true;
   CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

   if (CHKPTR(pSelector))
   {
      // shows the object in view mode
      bRet =pSelector->DisplayContainerEditor(p_pContainer, eWmsGuiDisplayModeRead, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:50:25 2011----------*
 * @method  CwmsguiObjectEditorSelector::Edit                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObjectAdaptor p_CdmObjectAdaptor              //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:50:25 2011----------*/
bool CwmsguiObjectEditorSelector::Edit(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent)
{
   bool bRet = false;
   CdmObject* pCdmObject = p_CdmObjectAdaptor.GetObject();

   if (CHKPTR(pCdmObject))
   {
      // shows the object in edit mode
      bRet = Edit(pCdmObject, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:51:08 2011----------*
 * @method  CwmsguiObjectEditorSelector::Edit                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:51:08 2011----------*/
bool CwmsguiObjectEditorSelector::Edit(CdmObject* p_pCdmObject, QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

   if (CHKPTR(pSelector))
   {
       // shows the object in edit mode
       bRet = pSelector->DisplayObjectEditor(p_pCdmObject, eWmsGuiDisplayModeWrite, p_pqwParent);
   }
   return bRet;
}

/** +-=---------------------------------------------------------Mo 17. Dez 10:13:48 2012----------*
 * @method  CwmsguiObjectEditorSelector::Edit                // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Dez 10:13:48 2012----------*/
bool CwmsguiObjectEditorSelector::Edit(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsguiObjectEditorSelector* pSelector = CwmsguiObjectEditorSelector::GetSelector();

   if (CHKPTR(pSelector))
   {
      // shows the object in edit mode
      bRet = pSelector->DisplayContainerEditor(p_pContainer, eWmsGuiDisplayModeWrite, p_pqwParent);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 17. Dez 10:12:04 2012----------*
 * @method  CwmsguiObjectEditorSelector::DisplayObjectListEditor // protected, virtual            *
 * @return  bool                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Dez 10:12:04 2012----------*/
bool CwmsguiObjectEditorSelector::DisplayContainerEditor(CdmObjectContainer* p_pContainer,
                                                          EwmsGuiDisplayMode p_eDisplayMode,
                                                          QWidget* p_pqwParent)
{
   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      const CdmClass* pCdmClass = p_pContainer->GetClass();

      if (CHKPTR(pCdmClass))
      {
         if (m_qmObjectListDescriptors.contains(pCdmClass->GetKeyname()))
         {
            IwmsObjectListEditorDescriptor* pDescriptor = m_qmObjectListDescriptors[pCdmClass->GetKeyname()];

            if (CHKPTR(pDescriptor))
            {
               bRet = pDescriptor->DisplayEditor(p_pContainer, p_eDisplayMode, p_pqwParent);
            }
         }
         else if (ExistQmlForThisPlattform(pCdmClass))
         {

         }
         else
         {
            // Opening the standard editor
            CwmsObjectListEditorIf cEdit(p_pContainer, p_pqwParent);
            cEdit.FillDialog();
            if (cEdit.exec() == QDialog::Accepted)
            {
               bRet = true;
            }
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 14. Jul 15:51:50 2011----------*
 * @method  CwmsguiObjectEditorSelector::DisplayObjectEditor // protected, virtual                *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 15:51:50 2011----------*/
bool CwmsguiObjectEditorSelector::DisplayObjectEditor(CdmObject* p_pCdmObject,
                                                      EwmsGuiDisplayMode p_eDisplayMode,
                                                      QWidget* p_pqwParent)
{
   bool bRet = false;

   if (CHKPTR(p_pCdmObject))
   {
       CdmClass* pCdmClass = p_pCdmObject->GetClass();
	   // if there are local changes there must be stored
	   // otherwise they will be overridden by the refresh call.
       if (p_pCdmObject->IsModified() && !p_pCdmObject->IsNew())
	   {
		   p_pCdmObject->Commit();
	   }

       if(!p_pCdmObject->IsNew())
       {
        p_pCdmObject->Refresh();
       }


      if (CHKPTR(pCdmClass))
      {
         // Plugin
         if (m_qmObjectDescriptors.contains(pCdmClass->GetKeyname()))
         {            IwmsObjectEditorDescriptor* pDescriptor = m_qmObjectDescriptors[pCdmClass->GetKeyname()];

            if (CHKPTR(pDescriptor))
            {
               bRet = pDescriptor->DisplayEditor(p_pCdmObject, p_eDisplayMode, p_pqwParent);
            }
         }
         // QML
         else if (ExistQmlForThisPlattform(p_pCdmObject->GetClass()))
         {
               bRet = DisplayQmlForm(p_pCdmObject, p_eDisplayMode, p_pqwParent);
         }
         // Configured UI
         else if (HasConfiguredObjectEditor(p_pCdmObject))
         {
            bRet = DisplayConfiguredObjectEditor(p_pCdmObject, p_eDisplayMode, p_pqwParent);
         }
         // Default Generic Object Editor
         else
         {
            bRet = DisplayDefaultObjectEditor(p_pCdmObject, p_eDisplayMode, p_pqwParent);
         }
      }
   }
   return bRet;
}

/** +-=---------------------------------------------------------Fr 14. Dez 11:24:58 2012----------*
 * @method  CwmsguiObjectEditorSelector::HasConfiguredObjectEditor // private                     *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 11:24:58 2012----------*/
bool CwmsguiObjectEditorSelector::HasConfiguredObjectEditor(CdmObject* p_pCdmObject)
{
   bool bRet = false;
   CwmsFormManager cManager;

   if (cManager.GeDefaultObjectForm(p_pCdmObject))
   {
      bRet = true;
   }

   return bRet;   
}

/** +-=---------------------------------------------------------Fr 14. Dez 11:21:20 2012----------*
 * @method  CwmsguiObjectEditorSelector::DisplayConfiguredObjectEditor // private                 *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 11:21:20 2012----------*/
bool CwmsguiObjectEditorSelector::DisplayConfiguredObjectEditor(CdmObject* p_pCdmObject,
                                                                EwmsGuiDisplayMode p_eDisplayMode,
                                                                QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsFormManager cManager;
   CdmObject* pCdmObject = cManager.GeDefaultObjectForm(p_pCdmObject);

   if (pCdmObject)
   {
       CdmObjectAdaptor cObject(pCdmObject);
       CwmsguiObjectEditorIf* pCoeObjectEditor = new CwmsguiObjectEditorIf(p_pCdmObject, p_pqwParent);
       CdmClass* pCdmClass = p_pCdmObject->GetClass();

       if (CHKPTR(pCdmClass))
       {
          pCoeObjectEditor->SetCaptionValue(pCdmClass->GetCaptionMemberKeyname());
       }

       if(pCdmClass->IsEventSourcingActive() || pCdmClass->IsEventClass())
       {
           if(p_eDisplayMode == eWmsGuiDisplayModeNew)
           {
               pCoeObjectEditor->SetObjectEventMode(WMS_NEW);
           }
           else if(p_eDisplayMode == eWmsGuiDisplayModeRead)
           {
               pCoeObjectEditor->SetObjectEventMode(WMS_DELETE);
           }
           else if(p_eDisplayMode ==  eWmsGuiDisplayModeWrite)
           {
               pCoeObjectEditor->SetObjectEventMode(WMS_UPDATE);
           }
       }
       
       pCoeObjectEditor->SetFormConfiguration(cObject.GetObject());
       if(pCdmClass->IsEventSourcingActive())
       {
           pCoeObjectEditor->FillEventDialog();
       }
        else
       {
           pCoeObjectEditor->FillDialog();
       }
       

       if (pCoeObjectEditor->exec() != QDialog::Accepted)
       {
          if (p_eDisplayMode == eWmsGuiDisplayModeNew)
          {
             cObject.SetDeleted();
             cObject.CommitObject();
          }
          else
          {
             cObject.Refresh();
          }
       }
       else
       {
          bRet = true;
       }
   }

   return bRet;  
}

/** +-=---------------------------------------------------------Fr 14. Dez 11:19:03 2012----------*
 * @method  CwmsguiObjectEditorSelector::DisplayDefaultObjectEditor // private                    *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 11:19:03 2012----------*/
bool CwmsguiObjectEditorSelector::DisplayDefaultObjectEditor(CdmObject* p_pCdmObject,
                                                             EwmsGuiDisplayMode p_eDisplayMode,
                                                             QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsguiObjectEditorIf* pCoeObjectEditor = new CwmsguiObjectEditorIf(p_pCdmObject, p_pqwParent);
   CdmClass* pCdmClass = p_pCdmObject->GetClass();

   if (CHKPTR(pCdmClass))
   {
       CdmObjectAdaptor cObject(p_pCdmObject);
      pCoeObjectEditor->SetCaptionValue(pCdmClass->GetCaptionMemberKeyname());

      if(pCdmClass->IsEventSourcingActive()|| pCdmClass->IsEventClass())
      {
          if(p_eDisplayMode == eWmsGuiDisplayModeNew)
          {
              pCoeObjectEditor->SetObjectEventMode(WMS_NEW);
          }
          else if(p_eDisplayMode == eWmsGuiDisplayModeRead)
          {
              pCoeObjectEditor->SetObjectEventMode(WMS_DELETE);
          }
          else if(p_eDisplayMode ==  eWmsGuiDisplayModeWrite)
          {
              pCoeObjectEditor->SetObjectEventMode(WMS_UPDATE);
          }

          pCoeObjectEditor->FillEventDialog();

          if (pCoeObjectEditor->exec() != QDialog::Accepted)
          {
             if (p_eDisplayMode == eWmsGuiDisplayModeNew)
             {
                 cObject.SetDeleted();
             }
             else
             {
                 cObject.Refresh();
             }
          }
          else
          {
              bRet = true;
          }
      }
      else
      {
          if(p_eDisplayMode == eWmsGuiDisplayModeRead)
          {
              pCoeObjectEditor->SetReadOnly();
          }
          pCoeObjectEditor->FillDialog();
          if (pCoeObjectEditor->exec() != QDialog::Accepted)
          {
             if (p_eDisplayMode == eWmsGuiDisplayModeNew)
             {
                 cObject.SetDeleted();
             }
             else
             {
                 cObject.Refresh();
             }
          }
          else
          {
              bRet = true;
          }

          cObject.CommitObject();
      }
   }
   DELPTR(pCoeObjectEditor);
   return bRet;
}

QString CwmsguiObjectEditorSelector::GenerateQmlQuery(const CdmClass* p_pClass)
{
    QString qstrUri = p_pClass->GetUri();
    CwmsbtPlattformInformation cPlattformInfo;
    QString qstrWql = QString("select from \"TechnicalFormUserDefined\" where and(Class_Uri = \"%1\", Context = %2, Default = 1, ")
    .arg(qstrUri)
    .arg(0);

    if (cPlattformInfo.isDesktop())
    {
        qstrWql += "Desktop_Form = 1)";
    }
    else if (cPlattformInfo.isMobile())
    {
        qstrWql += "Mobile_Form = 1)";
    }
    else if (cPlattformInfo.isTablet())
    {
        qstrWql += "Tablet_Form = 1)";
    }

    return qstrWql;
}

bool CwmsguiObjectEditorSelector::ShowQmlForm(CdmObject* p_pCdmObject, long p_lObjectId, QWidget* p_pqParent)
{
    bool bRet = false;
    CwmsFormManager cFormManager;
    CdmObjectContainer* pContainer = cFormManager.GetFormUserDefinedContainer();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = pContainer->FindObjectById(p_lObjectId);

        if (CHKPTR(pObject))
        {
            CwmsFormUserDefined cForm(pObject);
            CwqQmlObjectViewer*  pViewer = new CwqQmlObjectViewer(p_pqParent);

            QQuickWindow* pWindow = pViewer->CreateView(p_pCdmObject,
                                                       cForm.GetName(),
                                                       cForm.GetUICode());

            if (pWindow)
            {
                if (cForm.GetFormType() == 1) // Widget
                {
                   QWidget::createWindowContainer(pWindow, p_pqParent);
                   pViewer->ShowNoneModal();
                }
                else
                {
                  pViewer->ShowModal();
                }
                
                bRet = true;
            }
            else
            {
                ERR("Could not create UI Form.");
            }
        }
    }

    return bRet;
}

bool CwmsguiObjectEditorSelector::DisplayQmlForm(CdmObject* p_pCdmObject, EwmsGuiDisplayMode p_eDisplayMode, QWidget* p_pqwParent)
{
    bool bRet = false;
    Q_UNUSED(p_eDisplayMode);

    if (CHKPTR(p_pCdmObject))
    {
       QString qstrWql = GenerateQmlQuery(p_pCdmObject->GetClass());
       QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));

       if (pQuery)
       {
           const QLinkedList<long>& qllResults = pQuery->GetResultList();

           if (qllResults.count() > 0)
           {
               if (qllResults.count() > 1)
               {
                   WARNING("More than one default dialog found. take first one.");
               }

               long lObjectId = (*qllResults.begin());
               bRet = ShowQmlForm(p_pCdmObject, lObjectId, p_pqwParent);
           }
       }
    }

    return bRet;
}

bool CwmsguiObjectEditorSelector::ExistQmlForThisPlattform(const CdmClass* p_pClass)
{
   bool bRet = false;

   if (CHKPTR(p_pClass))
   {
      QString qstrWql = GenerateQmlQuery(p_pClass);
      CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pQuery))
      {
          const QLinkedList<long>& qllResults = pQuery->GetResultList();

          if (qllResults.count() > 0)
          {
            bRet = true;
          }
      }
   }

   return bRet;
}

