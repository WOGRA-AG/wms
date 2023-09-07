// System and QT Includes


// WMS Includes
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmValue.h"
#include "CdmValueObjectRef.h"


// Own Includes
#include "CwmsWorkflowStepExecution.h"
#include "CwmsWorkflowManager.h"
#include "CwmsWorkflowObject.h"

// Forwards

// Enumerations

CwmsWorkflowObject::CwmsWorkflowObject()
 : CdmObjectAdaptor()
{
}

CwmsWorkflowObject::CwmsWorkflowObject(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsWorkflowObject::~CwmsWorkflowObject()
{
}

int CwmsWorkflowObject::GetInternalNumber()
{
   return GetInt("Internal_Number");
}

void CwmsWorkflowObject::SetInternalNumber(int p_iValue)
{
   SetValue("Internal_Number", p_iValue);
}

QString CwmsWorkflowObject::GetNumberPreSign()
{
   return GetString("Number_PreSign");
}

void CwmsWorkflowObject::SetNumberPreSign(QString p_qstrValue)
{
   SetValue("Number_PreSign", p_qstrValue);
}

int CwmsWorkflowObject::GetNumberStartCounter()
{
   return GetInt("Number_Start_Counter");
}

void CwmsWorkflowObject::SetNumberStartCounter(int p_iValue)
{
   SetValue("Number_Start_Counter", p_iValue);
}

QString CwmsWorkflowObject::GetNumber()
{
   return GetString("Number");
}

void CwmsWorkflowObject::SetNumber(QString p_qstrValue)
{
   SetValue("Number", p_qstrValue);
}

CdmObjectContainer* CwmsWorkflowObject::GetNotes()
{
   return GetContainerRefValue("Notes");
}

void CwmsWorkflowObject::SetNotes(CdmObjectContainer* p_pCdmOLValue)
{
   SetContainerRefValue("Notes", p_pCdmOLValue);
}

QString CwmsWorkflowObject::GetName()
{
   return GetString("Name");
}

void CwmsWorkflowObject::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

CumUser* CwmsWorkflowObject::GetCreator()
{
   return GetUser("Creator");
}

void CwmsWorkflowObject::SetCreator(CumUser* p_pCumValue)
{
   SetValue("Creator", p_pCumValue);
}

QString CwmsWorkflowObject::GetDescription()
{
   return GetString("Description");
}

void CwmsWorkflowObject::SetDescription(QString p_qstrValue)
{
   SetValue("Description", p_qstrValue);
}

int CwmsWorkflowObject::GetState()
{
   return GetInt("State");
}
   
void CwmsWorkflowObject::SetState(int p_iState)
{
   SetValue("State", p_iState);
}

/** +-=---------------------------------------------------------Di 8. Jan 15:21:06 2013-----------*
 * @method  CwmsWorkflowObject::AddCurrentStep               // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 15:21:06 2013-----------*/
void CwmsWorkflowObject::AddCurrentStep(CdmObject* p_pCdmObject)
{
   AddListObjectsValue("Current_Steps", p_pCdmObject);
}

/** +-=---------------------------------------------------------Di 8. Jan 15:21:24 2013-----------*
 * @method  CwmsWorkflowObject::CurrentStepFinished          // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 15:21:24 2013-----------*/
void CwmsWorkflowObject::CurrentStepFinished(CdmObject* p_pCdmObject)
{
   if (CHKPTR(p_pCdmObject))
   {
      RemoveListObjectsValue("Curent_Steps", p_pCdmObject);
      CwmsWorkflowStepExecution cExec(p_pCdmObject);
      cExec.SetState(2);
      cExec.CommitObject();
      AddListObjectsValue("Done_Steps", p_pCdmObject);
   }
}

/** +-=---------------------------------------------------------Di 8. Jan 15:26:56 2013-----------*
 * @method  CwmsWorkflowObject::GetCurrentSteps              // public                            *
 * @return  QList<CdmObject*>                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 15:26:56 2013-----------*/
QList<CdmObject*> CwmsWorkflowObject::GetCurrentSteps()
{
   return GetListObjects("Current_Steps");
}

/** +-=---------------------------------------------------------Di 8. Jan 15:26:47 2013-----------*
 * @method  CwmsWorkflowObject::GetDoneSteps                 // public                            *
 * @return  QList<CdmObject*>                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 15:26:47 2013-----------*/
QList<CdmObject*> CwmsWorkflowObject::GetDoneSteps()
{
   return GetListObjects("Done_Streps");
}

/** +-=---------------------------------------------------------Mi 17. Okt 18:12:32 2012----------*
 * @method  CwmsWorkflowObject::UpdateCurrentWorkflowStep    // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 18:12:32 2012----------*/
void CwmsWorkflowObject::UpdateCurrentWorkflowStep()
{
   QList<CdmObject*> qllCurrentSteps = GetCurrentSteps();
   QList<CdmObject*>::iterator qllIt = qllCurrentSteps.begin();
   QList<CdmObject*>::iterator qllItEnd = qllCurrentSteps.end();

   for (; qllIt != qllItEnd; ++qllItEnd)
   {
      CdmObject* pObject = *qllIt;

      if (CHKPTR(pObject))
      {
         CwmsWorkflowStepExecution cExec(pObject);

         if (ContinueWithNextSteps(cExec))
         {
            CurrentStepFinished(pObject);
         }
         else 
         {
            cExec.CheckEscalation();
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 18. Jul 15:44:34 2013----------*
 * @method  CwmsWorkflowObject::ContinueWithNextSteps        // public                            *
 * @return  bool                                             //                                   *
 * @param   CwmsWorkflowStepExecution p_cExec                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 18. Jul 15:44:34 2013----------*/
bool CwmsWorkflowObject::ContinueWithNextSteps(CwmsWorkflowStepExecution p_cExec)
{
   bool bRet = false;

   if (p_cExec.IsValid())
   {
      CdmObject* pObject = p_cExec.GetWorkflowStep();
      CwmsWorkflowStepDefinition cStep(pObject);

      if (cStep.GetType() == 2)
      {
         MSG_CRIT("Geschäftsprozess abgeschlossen", "Der Geschäftsprozess wurde abgeschlossen");
         SetState(5);
         CommitObject();
      }
      else
      {
         QList<CdmObject*> qlNextSteps = cStep.GetNextSteps(GetObject(), p_cExec);

         if (qlNextSteps.count() > 0)
         {
            for (int iCounter = 0; iCounter < qlNextSteps.count(); ++iCounter)
            {
               CdmObject* pObject = qlNextSteps[iCounter];

               if (CHKPTR(pObject))
               {
                  CwmsWorkflowStepDefinition cStepTemp(pObject);
                  SetCurrentStep(cStepTemp);
                  bRet = true;
               }
            }
         }
         else
         {
             QString qstrMessage = QString::fromUtf8("Es wurde kein Nachfolgeschritt gültiger Nachfolgeschritt anhand der Selektionskriterien\n"
                                              "des abgeschlossenen Schritts ") + cStep.GetName() + QString::fromUtf8("gefunden. Bitte überprüfen Sie die\n"
                                              "Geschäftsprozessmodellierung. Der Prozess wird aktuell nicht fortgeführt.");
               MSG_CRIT("Keinen Nachfolgeschritt ermittelt",qstrMessage.toUtf8());
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 30. Dez 13:17:46 2012----------*
 * @method  CwmsWorkflowObject::StartWorkflow                // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 13:17:46 2012----------*/
void CwmsWorkflowObject::StartWorkflow()
{
   CwmsWorkflowDefinition cDef = FindWorkflow();

   if (cDef.IsValid())
   {
      CwmsWorkflowStepDefinition cStep = cDef.GetStartingStep();

      if (cStep.IsValid())
      {
         SetCurrentStep(cStep);
         CommitObject();
      }
   }
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:35:40 2012----------*
 * @method  CwmsWorkflowObject::SetCurrentStep               // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowStepDefinition p_cStep         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:35:40 2012----------*/
void CwmsWorkflowObject::SetCurrentStep(CwmsWorkflowStepDefinition p_cStep)
{
   if (p_cStep.IsValid())
   {
      CwmsWorkflowManager cManager;
      CdmObjectContainer* pList = cManager.GetWorkflowStepsObjectList();

      if (CHKPTR(pList))
      {
         CdmObject* pObject = pList->CreateNewObject();
         CwmsWorkflowStepExecution cExecutor(pObject);
         cExecutor.SetWorkflowObject(GetObject()); // must be first because of sub workflows
         cExecutor.SetWorkflowStep(p_cStep);
         cExecutor.CommitObject();
         cExecutor.SendMailToResponsibleTeam();
         AddCurrentStep(cExecutor.GetObject());
         cExecutor.CommitObject();
      }
   }
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:01:47 2012----------*
 * @method  CwmsWorkflowObject::FindWorkflow                 // private                           *
 * @return  CwmsWorkflowDefinition                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:01:47 2012----------*/
CwmsWorkflowDefinition CwmsWorkflowObject::FindWorkflow()
{
   CwmsWorkflowDefinition cDef;
   CwmsWorkflowManager cManager;
   CdmObject* pObject = GetObject();

   if (CHKPTR(pObject))
   {
      CdmClass* pClass = pObject->GetClass();

      if (CHKPTR(pClass))
      {
         cDef = cManager.FindMajorWorkflowByClassUri(pClass->GetUriInternal());
      }
   }

   return cDef;
}
