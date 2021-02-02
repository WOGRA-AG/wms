
// System and QT Includes


// Own Includes
#include "CwmsEscalationEditorDlg.h"
#include "CwmsWorkflowStepExecutionEditorDlg.h"
#include "CwmsWorkflowStepEditorDlg.h"
#include "CwmsWorkflowDefitionEditor.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsguiApplicationServices.h"


void CwmsguiApplicationServices::InstallUiEditors()
{
   CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsEscalationObjectEditorDescriptor());
   CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowStepExecutionObjectEditorDescriptor());
   CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowStepObjectEditorDescriptor());
   CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowDefintionObjectEditorDescriptor());
}
