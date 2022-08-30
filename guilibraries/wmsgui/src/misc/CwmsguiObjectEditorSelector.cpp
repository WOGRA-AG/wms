// System and QT Includes
#include <QQuickWindow>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CwmsFormUserDefinedExecutor.h"

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

CwmsguiObjectEditorSelector::CwmsguiObjectEditorSelector()
{
}

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

void CwmsguiObjectEditorSelector::InstallContainerEditorDescriptor(IwmsObjectListEditorDescriptor* p_pDescriptor)
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
         else if (ExistUserdefinedForm(pCdmClass))
         {
            bRet = DisplayUserdefinedForm(p_pContainer, p_pqwParent);
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
         else if (ExistUserdefinedForm(p_pCdmObject->GetClass()))
         {
               bRet = DisplayUserdefinedForm(p_pCdmObject, p_pqwParent);
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
       pCoeObjectEditor->FillDialog();

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

   DELPTR(pCoeObjectEditor);
   return bRet;
}

bool CwmsguiObjectEditorSelector::DisplayUserdefinedForm(CdmObject* p_pCdmObject, QWidget* p_pqwParent)
{
    bool bRet = false;

    if (CHKPTR(p_pCdmObject))
    {
        CwmsFormManager cFormManager;
        CdmObject* pFormObj = cFormManager.GetUserDefinedUi(p_pCdmObject);
        CwmsFormUserDefined cForm(pFormObj);
        CwmsFormUserDefinedExecutor cExecutor;
        cExecutor.ExecuteUserDefinedFormObject(cForm, p_pCdmObject, p_pqwParent);
        bRet = true;
    }

    return bRet;
}

bool CwmsguiObjectEditorSelector::DisplayUserdefinedForm(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent)
{
    bool bRet = false;

    if (CHKPTR(p_pContainer))
    {
        CwmsFormManager cFormManager;
        CdmObject* pFormObj = cFormManager.GetUserDefinedUi(p_pContainer);
        CwmsFormUserDefined cForm(pFormObj);
        CwmsFormUserDefinedExecutor cExecutor;
        cExecutor.ExecuteUserDefinedFormContainer(cForm, p_pContainer, p_pqwParent);
        bRet = true;
    }

    return bRet;
}

bool CwmsguiObjectEditorSelector::ExistUserdefinedForm(const CdmClass* p_pClass)
{
   CwmsFormManager cFormManager;

   return (cFormManager.GetUserDefinedUi(p_pClass) != nullptr);
}

