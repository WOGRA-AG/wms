/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsScriptableWorkflow.cpp
 ** Started Implementation: 2012/12/30
 ** Description:
 **
 ** implements the scriptinterface for workflows
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS INcludes
#include "CdmLogging.h"
#include "CdmObject.h"

// own Includes
#include "CwmsWorkflowObject.h"
#include "CwmsScriptableWorkflow.h"

/** +-=---------------------------------------------------------So 30. Dez 12:39:00 2012----------*
 * @method  CwmsScriptableWorkflow::CwmsScriptableWorkflow   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 12:39:00 2012----------*/
CwmsScriptableWorkflow::CwmsScriptableWorkflow()
{
}

/** +-=---------------------------------------------------------So 30. Dez 12:39:06 2012----------*
 * @method  CwmsScriptableWorkflow::~CwmsScriptableWorkflow  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsScriptableWorkflow                                        *
 *----------------last changed: --------------------------------So 30. Dez 12:39:06 2012----------*/
CwmsScriptableWorkflow::~CwmsScriptableWorkflow()
{
}


/** +-=---------------------------------------------------------So 30. Dez 12:39:30 2012----------*
 * @method  CwmsScriptableWorkflow::StartWorkflow            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 12:39:30 2012----------*/
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

/** +-=---------------------------------------------------------So 30. Dez 12:39:53 2012----------*
 * @method  CwmsScriptableWorkflow::UpdateWorkflow           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 12:39:53 2012----------*/
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