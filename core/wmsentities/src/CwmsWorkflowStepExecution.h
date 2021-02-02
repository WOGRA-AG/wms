#ifndef CWMSWORKFLOWSTEPEXECUTION_H
#define CWMSWORKFLOWSTEPEXECUTION_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes

// Own Includes
#include "basetools.h"
#include "CwmsWorkflowBase.h"
#include "CwmsWorkflowStepDefinition.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsWorkflowStepExecution: public CwmsWorkflowBase
{

   public:
      CwmsWorkflowStepExecution();
   public:
      CwmsWorkflowStepExecution(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsWorkflowStepExecution();
   public:
      int GetCurrentState();
   public:
      void SetCurrentState(int p_iValue);
   public:
      CumUser* GetEditor();
   public:
      void SetEditor(CumUser* p_pCumValue);
   public:
      CdmObject* GetCurrentEscalationStep();
   public:
      void SetCurrentEscalationStep(CdmObject* p_pCdmValue);
   public:
      CdmObject* GetWorkflowStep();
   public:
      void SetWorkflowStep(CdmObject* p_pCdmValue);
   public:
      CdmObject* GetWorkflowObject();
   public:
      void SetWorkflowObject(CdmObject* p_pCdmValue);
   public:
      static CwmsWorkflowStepExecution Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsWorkflowStepExecution cCbmsSimpleWorkflowStepExecution);

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 08:12:45 2012-------*
    * @method  CwmsWorkflowStepExecution::SendMailToResponsibleTeam // public               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 08:12:45 2012----------*/
    void SendMailToResponsibleTeam();

   private:
   /** +-=---------------------------------------------------------Di 8. Jan 16:08:57 2013--------*
    * @method  CwmsWorkflowStepExecution::CalculateEscalationDate // private                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 16:08:57 2013-----------*/
    void CalculateEscalationDate();

   private:
   /** +-=---------------------------------------------------------Di 8. Jan 16:08:14 2013--------*
    * @method  CwmsWorkflowStepExecution::Escalate     // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 16:08:14 2013-----------*/
    void Escalate();

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 08:24:03 2012-------*
    * @method  CwmsWorkflowStepExecution::SetNextEscalationDate // public                   *
    * @return  void                                          //                                   *
    * @param   QDate p_qdDate                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 08:24:03 2012----------*/
    void SetNextEscalationDate(QDate p_qdDate);

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 08:24:14 2012-------*
    * @method  CwmsWorkflowStepExecution::GetNextEscalation // public                       *
    * @return  QDate                                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 08:24:14 2012----------*/
    QDate GetNextEscalation();

   private:
   /** +-=---------------------------------------------------------Mi 17. Okt 15:25:34 2012-------*
    * @method  CwmsWorkflowStepExecution::CreateMailContent // private                      *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 15:25:34 2012----------*/
    QString CreateMailContent();


   private:
   /** +-=---------------------------------------------------------Mi 17. Okt 15:52:44 2012-------*
    * @method  CwmsWorkflowStepExecution::FindEscalation // private                         *
    * @return  CdmObject*                                    //                                   *
    * @param   int p_iPos                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 15:52:44 2012----------*/
    CdmObject* FindEscalation(int p_iPos);

   public:
   /** +-=---------------------------------------------------------So 30. Dez 12:10:30 2012-------*
    * @method  CwmsWorkflowStepExecution::GetCurrentSubWorkflowStep // public               *
    * @return  CdmObject*                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 12:10:30 2012----------*/
    CdmObject* GetCurrentSubWorkflowStep();

   public:
   /** +-=---------------------------------------------------------So 30. Dez 12:10:48 2012-------*
    * @method  CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep // public               *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 12:10:48 2012----------*/
    void SetCurrentSubWorkflowStep(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:43:44 2012-------*
    * @method  CwmsWorkflowStepExecution::SetWorkflowStep // public                         *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowStepDefinition p_cStep      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:43:44 2012----------*/
    void SetWorkflowStep(CwmsWorkflowStepDefinition p_cStep);

   public:
   /** +-=---------------------------------------------------------Di 23. Jul 16:51:36 2013-------*
    * @method  CwmsWorkflowStepExecution::SetCurrentSubWorkflowStep // public                     *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowStepDefinition p_cStep            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Jul 16:51:36 2013----------*/
    void SetCurrentSubWorkflowStep(CwmsWorkflowStepDefinition p_cStep);

   private:
   /** +-=---------------------------------------------------------Mo 31. Dez 12:00:59 2012-------*
    * @method  CwmsWorkflowStepExecution::UpdateValuesOnWorkflowObject // private           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 12:00:59 2012----------*/
    void UpdateValuesOnWorkflowObject();

   public:
   /** +-=---------------------------------------------------------Di 8. Jan 15:59:20 2013--------*
    * @method  CwmsWorkflowStepExecution::IsFinished   // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 15:59:20 2013-----------*/
    bool IsFinished();


   public:
   /** +-=---------------------------------------------------------Di 8. Jan 16:06:57 2013--------*
    * @method  CwmsWorkflowStepExecution::CheckEscalation // public                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 16:06:57 2013-----------*/
    void CheckEscalation();
};
#endif //
