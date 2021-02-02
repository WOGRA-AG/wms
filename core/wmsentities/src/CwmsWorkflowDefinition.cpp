// System and QT Includes


// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"

// Own Includes
#include "CdmQuery.h"
#include "CdmMessageManager.h"
#include "CdmQueryBuilder.h"
#include "CdmObjectContainer.h"
#include "CwmsWorkflowDefinition.h"

// Forwards

// Enumerations

CwmsWorkflowDefinition::CwmsWorkflowDefinition()
 : CdmObjectAdaptor()
{
}

CwmsWorkflowDefinition::CwmsWorkflowDefinition(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsWorkflowDefinition::~CwmsWorkflowDefinition()
{
}

QString CwmsWorkflowDefinition::GetName()
{
   return GetString("Name");
}

void CwmsWorkflowDefinition::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

CdmObjectContainer* CwmsWorkflowDefinition::GetWorkflow()
{
   CdmObjectContainer* pCdmList = GetContainerRefValue("Workflow");

   if (pCdmList->CountObjectsOnDb() == 0)
   {
      CdmObject* pCdmObject = GetObject();

      if (pCdmObject->HasParent())
      {
         CdmObject* pCdmParent = pCdmObject->GetParent();

         if (CHKPTR(pCdmParent))
         {
            CwmsWorkflowDefinition cType(pCdmParent);
            pCdmList = cType.GetWorkflow();
         }
      }
   }

   return pCdmList;
}

/** +-=---------------------------------------------------------Do 18. Okt 16:24:07 2012----------*
 * @method  CwmsWorkflowDefinition::GetObjectWorkflow              // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 18. Okt 16:24:07 2012----------*/
CdmObjectContainer* CwmsWorkflowDefinition::GetObjectWorkflow()
{
   return GetContainerRefValue("Workflow");
}

QString CwmsWorkflowDefinition::GetDescription()
{
   return GetString("Description");
}

void CwmsWorkflowDefinition::SetDescription(QString p_qstrValue)
{
   SetValue("Description", p_qstrValue);
}

/** +-=---------------------------------------------------------Di 18. Dez 13:43:37 2012----------*
 * @method  CwmsWorkflowDefinition::GetClass                 // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Dez 13:43:37 2012----------*/
QString CwmsWorkflowDefinition::GetClass()
{
   return GetString("Class");
}

/** +-=---------------------------------------------------------Di 18. Dez 13:43:53 2012----------*
 * @method  CwmsWorkflowDefinition::SetClass                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrClass                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Dez 13:43:53 2012----------*/
void CwmsWorkflowDefinition::SetClass(QString p_qstrClass)
{
   SetValue("Class", p_qstrClass);
}

/** +-=---------------------------------------------------------So 30. Dez 10:57:11 2012----------*
 * @method  CwmsWorkflowDefinition::GetType                  // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 10:57:11 2012----------*/
int CwmsWorkflowDefinition::GetType()
{
   return GetInt("Type");
}

/** +-=---------------------------------------------------------So 30. Dez 10:57:22 2012----------*
 * @method  CwmsWorkflowDefinition::SetType                  // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iType                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 10:57:22 2012----------*/
void CwmsWorkflowDefinition::SetType(int p_iType)
{
   SetValue("Type", p_iType);
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:07:05 2012----------*
 * @method  CwmsWorkflowDefinition::GetStartingStep          // public                            *
 * @return  CwmsWorkflowStepDefinition                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:07:05 2012----------*/
CwmsWorkflowStepDefinition CwmsWorkflowDefinition::GetStartingStep()
{
   CwmsWorkflowStepDefinition cStep;
   CdmObjectContainer* pList = GetObjectWorkflow();

   if (CHKPTR(pList))
   {
      QString qstrWql = "select from \"" + pList->GetKeyname() + "\" where Type = 0";

      CdmQuery* pCdmQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

      if (CHKPTR(pCdmQuery))
      {
         int iResultCount = pCdmQuery->GetResultCount();

         if (iResultCount > 1)
         {
            CdmMessageManager::warning(tr("Mehrere Startprozessschritte vorhanden"), 
               tr("Zu diesem GeschÃ¤ftsprozess existieren mehrere Startprozessschritte. Der erst Gefundene wird verwendet!"));
         }


         CdmObject* pObject = pCdmQuery->GetFirstResultObject();

         if (pObject)
         {
            cStep.SetObject(pObject);
         }
         else
         {
            CdmMessageManager::critical(tr("Kein Startprozessschritt vorhanden"), 
               tr("Zu diesem GeschÃ¤ftsprozess existiert kein Startprozessschritt. Die Prozessverarbeitung kann nicht durchgefÃ¼hrt werden!"));
         }
      }
   }

   return cStep;
}

CwmsWorkflowDefinition CwmsWorkflowDefinition::Create(CdmObjectContainer* p_pContainer)
{
   CwmsWorkflowDefinition cCbmsWorkflow;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCbmsWorkflow.SetObject(pCdmObject);
   }

   return cCbmsWorkflow;
}

bool CwmsWorkflowDefinition::Delete(CwmsWorkflowDefinition cCbmsFeedbackType)
{
   bool bSuccess = false;

   if (cCbmsFeedbackType.IsValid())
   {
      cCbmsFeedbackType.SetDeleted();
      cCbmsFeedbackType.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}