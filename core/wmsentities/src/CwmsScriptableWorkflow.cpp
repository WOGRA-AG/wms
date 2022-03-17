// System and QT Includes

// WMS INcludes
#include "CdmLogging.h"
#include "CdmObject.h"

// own Includes
#include "CwmsWorkflowObject.h"
#include "CwmsScriptableWorkflow.h"

CwmsScriptableWorkflow::CwmsScriptableWorkflow()
{
}

CwmsScriptableWorkflow::~CwmsScriptableWorkflow()
{
}

void CwmsScriptableWorkflow::StartWorkflow(CdmObject* p_pCdmObject)
{
   if (CHKPTR(p_pCdmObject))
   {
      if (p_pCdmObject->IsTypeOf("Workflow_Object"))
      {
         CwmsWorkflowObject cObject(p_pCdmObject);
         cObject.StartWorkflow();
      }
   }
}

void CwmsScriptableWorkflow::UpdateWorkflow(CdmObject* p_pCdmObject)
{
   if (CHKPTR(p_pCdmObject))
   {
      if (p_pCdmObject->IsTypeOf("Workflow_Object"))
      {
         CwmsWorkflowObject cObject(p_pCdmObject);
         cObject.UpdateCurrentWorkflowStep();
      }
   }
}
