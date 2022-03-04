
// System and QT Includes

#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"

// Own Includes
#include "CwmsEscalationEditorDlg.h"
#include "CwmsWorkflowStepExecutionEditorDlg.h"
#include "CwmsWorkflowStepEditorDlg.h"
#include "CwmsWorkflowDefitionEditor.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsguiApplicationServices.h"
#include "CwmsScriptableUi.h"

#include <CwmsApplicationServices.h>


void CwmsguiApplicationServices::InstallUiEditors()
{
    CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsEscalationObjectEditorDescriptor());
    CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowStepExecutionObjectEditorDescriptor());
    CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowStepObjectEditorDescriptor());
    CwmsguiObjectEditorSelector::InstallObjectEditorDescriptor(new CwmsWorkflowDefintionObjectEditorDescriptor());
}

void CwmsguiApplicationServices::InstallFunctionsAndPlugins()
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (pExecutor)
    {
        CdmExecutorAddOnManager* pAddOnManager = pExecutor->GetAddOnManager();

        if (pAddOnManager)
        {
            if (!pAddOnManager->ContainsFunctionality("ui"))
            {
                pAddOnManager->InstallAdditionalFunctionality("ui", new CwmsScriptableUi());
            }
        }

        CwmsApplicationServices::InstallFunctionsAndPlugins();
    }
}
