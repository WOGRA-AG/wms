// System and QT Includes
#include <QApplication>

// WMS Includes
#include "CumUser.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"

// Own Includes
#include "CwmsSmtpManager.h"
#include "CwmsbtMailMessage.h"
#include "CwmsWorkflowDefinition.h"
#include "CwmsWorkflowObject.h"
#include "CwmsWorkflowManager.h"
#include "CwmsEscalation.h"
#include "CwmsWorkflowStepDefinition.h"
#include "CwmsWorkflowStepExecution.h"

// Forwards

// Enumerations

CwmsWorkflowStepExecution::CwmsWorkflowStepExecution()
 : CwmsWorkflowBase()
{
}

CwmsWorkflowStepExecution::CwmsWorkflowStepExecution(CdmObject* p_pCdmObject)
 : CwmsWorkflowBase(p_pCdmObject)
{
}

CwmsWorkflowStepExecution::~CwmsWorkflowStepExecution()
{
}

CumUser* CwmsWorkflowStepExecution::GetEditor()
{
   return GetUser("Editor");
}

void CwmsWorkflowStepExecution::SetEditor(CumUser* p_pCumValue)
{
   SetValue("Editor", p_pCumValue);
}

CdmObject* CwmsWorkflowStepExecution::GetCurrentEscalationStep()
{
   return GetObjectRefValue("Current_Escalation_Step");
}

int CwmsWorkflowStepExecution::GetCurrentState()
{
   return GetInt("Current_State");
}

void CwmsWorkflowStepExecution::SetCurrentState(int p_iValue)
{
   SetValue("Current_State", p_iValue);
}

void CwmsWorkflowStepExecution::SetCurrentEscalationStep(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Current_Escalation_Step", p_pCdmValue);
}

CdmObject* CwmsWorkflowStepExecution::GetWorkflowStep()
{
   return GetObjectRefValue("Workflow_Step");
}

void CwmsWorkflowStepExecution::SetWorkflowStep(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Workflow_Step", p_pCdmValue);
}

CdmObject* CwmsWorkflowStepExecution::GetWorkflowObject()
{
   return GetObjectRefValue("Workflow_Object");
}

void CwmsWorkflowStepExecution::SetWorkflowObject(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Workflow_Object", p_pCdmValue);
}

/** +-=---------------------------------------------------------Mo 31. Dez 10:43:44 2012----------*
 * @method  CwmsWorkflowStepExecution::SetWorkflowStep // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowStepDefinition p_cStep         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 10:43:44 2012----------*/
void CwmsWorkflowStepExecution::SetWorkflowStep(CwmsWorkflowStepDefinition p_cStep)
{
   if (p_cStep.IsValid())
   {
      SetWorkflowStep(p_cStep.GetObject());
      CalculateEscalationDate();
      UpdateValuesOnWorkflowObject();
      CdmObject* pObject = p_cStep.GetSubWorkflow();

      if (pObject)
      {
         CwmsWorkflowDefinition cDef(pObject);
         CwmsWorkflowStepDefinition cStep = cDef.GetStartingStep();

         if (cStep.IsValid())
         {
            SetCurrentSubWorkflowStep(cStep);
         }
      }

      SendMailToResponsibleTeam();
   }
}

/** +-=---------------------------------------------------------Di 23. Jul 16:51:36 2013----------*
 * @method  CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep // public                        *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowStepDefinition p_cStep               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 23. Jul 16:51:36 2013----------*/
void CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep(CwmsWorkflowStepDefinition p_cStep)
{
   if (p_cStep.IsValid())
   {
      CwmsWorkflowManager cManager;
      CdmObjectContainer* pList = cManager.GetWorkflowStepsObjectList();

      if (CHKPTR(pList))
      {
         CdmObject* pObject = pList->CreateNewObject();
         CwmsWorkflowStepExecution cExecutor(pObject);
         cExecutor.SetWorkflowObject(GetWorkflowObject()); // must be first because of sub workflows
         cExecutor.SetWorkflowStep(p_cStep);
         cExecutor.CommitObject();
         cExecutor.SendMailToResponsibleTeam();
         SetCurrentSubWorkflowStep(cExecutor.GetObject());
         cExecutor.CommitObject();
      }
   }
}

/** +-=---------------------------------------------------------Mo 31. Dez 12:00:59 2012----------*
 * @method  CwmsWorkflowStepExecution::UpdateValuesOnWorkflowObject // private              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 31. Dez 12:00:59 2012----------*/
void CwmsWorkflowStepExecution::UpdateValuesOnWorkflowObject()
{
   CdmObject* pObjectStep = GetWorkflowStep();
   CdmObject* pObjectWorkflowObject = GetWorkflowObject();

   if (CHKPTR(pObjectStep) && CHKPTR(pObjectWorkflowObject))
   {
      CwmsWorkflowStepDefinition cStep(pObjectStep);

      QMap<QString, QString> qmChangingValues = cStep.GetChangingValues();

      QMap<QString, QString>::iterator qmIt = qmChangingValues.begin();
      QMap<QString, QString>::iterator qmItEnd = qmChangingValues.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QString qstrKeyname = qmIt.key();
         QString qstrValue = qmIt.value();
         CdmValue* pValue = pObjectWorkflowObject->GetValue(qstrKeyname);

         if (CHKPTR(pValue))
         {
            pValue->FromStringToValue(qstrValue);
         }
      }

      pObjectWorkflowObject->Commit();
   }
}

/** +-=---------------------------------------------------------Mi 17. Okt 08:12:45 2012----------*
 * @method  CwmsWorkflowStepExecution::SendMailToResponsibleTeam // public                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 08:12:45 2012----------*/
void CwmsWorkflowStepExecution::SendMailToResponsibleTeam()
{
   CdmObject* pCdmObject = GetResponsibility();

   if (CHKPTR(pCdmObject))
   {
      QString qstrReceiver = pCdmObject->GetVariant("E-Mail").toString();
      QString qstrContent = CreateMailContent();
      CwmsSmtpManager cSmtpManager;
      CwmsbtMailMessage* pCwmsbtMailMessage = cSmtpManager.CreateMailMessage();

      if (CHKPTR(pCwmsbtMailMessage))
      {
         pCwmsbtMailMessage->SetBody(qstrContent);
         QString qstrSubject = "[" + qApp->applicationName() + " " + tr("Prozessabarbeitung") + " (" + GetPosition() + ")]" + GetName();
         pCwmsbtMailMessage->SetSubject(qstrSubject);
         pCwmsbtMailMessage->AddRecipients(qstrReceiver);

         CdmObject* pObject = GetWorkflowObject();

         if (CHKPTR(pObject))
         {
            CwmsWorkflowObject cWorkflow(pObject);
            CumUser* pCumUser = cWorkflow.GetCreator();

            if (CHKPTR(pCumUser))
            {
               pCwmsbtMailMessage->AddBlindCopy(pCumUser->GetEmail());
            }
         
            pCwmsbtMailMessage->SendMessage();
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 17. Okt 15:25:34 2012----------*
 * @method  CwmsWorkflowStepExecution::CreateMailContent // private                         *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 15:25:34 2012----------*/
QString CwmsWorkflowStepExecution::CreateMailContent()
{
   QString qstrText;
   CdmObject* pCdmWorkflowObject = GetWorkflowObject();
   CdmObject* pCdmTeam = GetResponsibility();

   if (CHKPTR(pCdmWorkflowObject) && CHKPTR(pCdmTeam))
   {
      QString qstrProcess = pCdmWorkflowObject->GetVariant("Name").toString();
      QString qstrNumber = pCdmWorkflowObject->GetVariant("Number").toString();
      QString qstrDescription = pCdmWorkflowObject->GetVariant("Description").toString();
      QString qstrTeam = pCdmTeam->GetVariant("Name").toString();

      qstrText += tr("Arbeitsschritt: ") + GetName() + "<br>";
      qstrText += tr("Team: ") + qstrTeam + "<br>";
      qstrText += tr("Termin: ") + GetNextEscalation().toString() + "<br>";
      qstrText += tr("Prozess: ") + qstrProcess + "<br>";
      qstrText += tr("Nummer: ") + qstrNumber + "<br><br>";
      qstrText += tr("Beschreibung: ") +  "<br>";
      qstrText += qstrDescription;
   }

   return qstrText;
}

/** +-=---------------------------------------------------------Mi 17. Okt 15:52:44 2012----------*
 * @method  CwmsWorkflowStepExecution::FindEscalation  // private                           *
 * @return  CdmObject*                                       //                                   *
 * @param   int p_iPos                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 15:52:44 2012----------*/
CdmObject* CwmsWorkflowStepExecution::FindEscalation(int p_iPos)
{
   CdmObject* pCdmRet = nullptr;
   CdmObject* pCdmWorkflowDef = GetWorkflowStep();

   if (CHKPTR(pCdmWorkflowDef))
   {
      CwmsWorkflowStepDefinition cDef(pCdmWorkflowDef);
      CdmObjectContainer* pCdmList = cDef.GetEscalation();
      
      if (CHKPTR(pCdmList))
      {
         QString qstrWql = "select from \"" + pCdmList->GetKeyname() + "\" where Position = " + QString::number(p_iPos);
         CdmQuery* pCdmQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

         if (pCdmQuery)
         {
            QLinkedList<long> qllResults = pCdmQuery->GetResultList();

            if (qllResults.count() > 0)
            {
               long lObjectId = *qllResults.begin();

               pCdmRet = pCdmList->FindObjectById(lObjectId);
            }

            DELPTR(pCdmQuery);
         }
      }
   }

   return pCdmRet;
}

/** +-=---------------------------------------------------------Di 8. Jan 15:59:20 2013-----------*
 * @method  CwmsWorkflowStepExecution::IsFinished      // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 15:59:20 2013-----------*/
bool CwmsWorkflowStepExecution::IsFinished()
{
   return (GetState() == 5);
}

/** +-=---------------------------------------------------------Di 8. Jan 16:08:57 2013-----------*
 * @method  CwmsWorkflowStepExecution::CalculateEscalationDate // private                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 16:08:57 2013-----------*/
void CwmsWorkflowStepExecution::CalculateEscalationDate()
{
   QDate qdDate = QDate::currentDate();
   CdmObject* pCdmEscalation = GetCurrentEscalationStep();
   int iMaxDuration = GetMaxDuration();

   if (pCdmEscalation != nullptr)
   {
      CwmsEscalation cCbmsEscalation(pCdmEscalation);
      iMaxDuration = cCbmsEscalation.GetViolationOfLimit() + iMaxDuration;
   }

   qdDate = qdDate.addDays(iMaxDuration);
   SetNextEscalationDate(qdDate);
}

/** +-=---------------------------------------------------------Di 8. Jan 16:08:14 2013-----------*
 * @method  CwmsWorkflowStepExecution::Escalate        // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 16:08:14 2013-----------*/
void CwmsWorkflowStepExecution::Escalate()
{
   CdmObject* pCdmObjectEscalation = GetCurrentEscalationStep();
   CdmObject* pCdmWorkflowObject = GetWorkflowObject();
   
   if (CHKPTR(pCdmWorkflowObject))
   {
      int iPos = 0;

      if (pCdmObjectEscalation)
      {
         CwmsEscalation cEscalation(pCdmObjectEscalation);
         iPos = cEscalation.GetEscalationStep();
      }

      CdmObject* pCdmObjectEscalationNew = FindEscalation(++iPos);

      if (pCdmObjectEscalationNew)
      {
         SetCurrentEscalationStep(pCdmObjectEscalationNew);
         CwmsEscalation cEscalation(pCdmObjectEscalationNew);
         cEscalation.SendEscalationMail(GetWorkflowObject());
      }
      else
      {
         CwmsEscalation cEscalation(pCdmObjectEscalation);
         Escalate();
      }
   }
}

/** +-=---------------------------------------------------------Mi 17. Okt 08:24:03 2012----------*
 * @method  CwmsWorkflowStepExecution::SetNextEscalationDate // public                      *
 * @return  void                                             //                                   *
 * @param   QDate p_qdDate                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 08:24:03 2012----------*/
void CwmsWorkflowStepExecution::SetNextEscalationDate(QDate p_qdDate)
{
   SetValue("Next_Escalation_Date", p_qdDate);
}

/** +-=---------------------------------------------------------Mi 17. Okt 08:24:14 2012----------*
 * @method  CwmsWorkflowStepExecution::GetNextEscalation // public                          *
 * @return  QDate                                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 08:24:14 2012----------*/
QDate CwmsWorkflowStepExecution::GetNextEscalation()
{
   return GetDate("Next_Escalation_Date");
}

/** +-=---------------------------------------------------------So 30. Dez 12:10:30 2012----------*
 * @method  CwmsWorkflowStepExecution::GetCurrentSubWorkflowStep // public                  *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 12:10:30 2012----------*/
CdmObject* CwmsWorkflowStepExecution::GetCurrentSubWorkflowStep()
{
   return GetObjectRefValue("Current_Sub_Workflow_Step");
}

/** +-=---------------------------------------------------------So 30. Dez 12:10:48 2012----------*
 * @method  CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep // public                  *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 12:10:48 2012----------*/
void CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep(CdmObject* p_pCdmObject)
{
   SetObjectRefValue("Current_Sub_Workflow_Step", p_pCdmObject);
}



/** +-=---------------------------------------------------------Di 8. Jan 16:06:57 2013-----------*
 * @method  CwmsWorkflowStepExecution::CheckEscalation // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 16:06:57 2013-----------*/
void CwmsWorkflowStepExecution::CheckEscalation()
{
   QDate qdEscalationDate = GetNextEscalation();

   if (qdEscalationDate < QDate::currentDate())
   {
      Escalate();
   }
}

CwmsWorkflowStepExecution CwmsWorkflowStepExecution::Create(CdmObjectContainer* p_pContainer)
{
   CwmsWorkflowStepExecution cCbmsSimpleWorkflowStepExecution;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCbmsSimpleWorkflowStepExecution.SetObject(pCdmObject);
   }

   return cCbmsSimpleWorkflowStepExecution;
}
bool CwmsWorkflowStepExecution::Delete(CwmsWorkflowStepExecution cCbmsSimpleWorkflowStepExecution)
{
   bool bSuccess = false;
   if (cCbmsSimpleWorkflowStepExecution.IsValid())
   {
      cCbmsSimpleWorkflowStepExecution.SetDeleted();
      cCbmsSimpleWorkflowStepExecution.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
