#ifndef CWMSWORKFLOWOBJECT_H
#define CWMSWORKFLOWOBJECT_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "CwmsWorkflowStepExecution.h"
#include "CwmsWorkflowStepDefinition.h"
#include "CwmsWorkflowDefinition.h"
#include "basetools.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsWorkflowObject: public CdmObjectAdaptor
{

   public:
      CwmsWorkflowObject();
   public:
      CwmsWorkflowObject(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsWorkflowObject();
   public:
      int GetInternalNumber();
   public:
      void SetInternalNumber(int p_iValue);
   public:
      QString GetNumberPreSign();
   public:
      void SetNumberPreSign(QString p_qstrValue);
   public:
      int GetNumberStartCounter();
   public:
      void SetNumberStartCounter(int p_iValue);
   public:
      QString GetNumber();
   public:
      void SetNumber(QString p_qstrValue);
   public:
      CdmObjectContainer* GetNotes();
   public:
      void SetNotes(CdmObjectContainer* p_pCdmOLValue);
   public:
      int GetState();
   public:
      void SetState(int p_iStat);
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   public:
      CumUser* GetCreator();
   public:
      void SetCreator(CumUser* p_pCumValue);
   public:
      QString GetDescription();
   public:
      void SetDescription(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 18:12:32 2012-------*
    * @method  CwmsWorkflowObject::UpdateCurrentWorkflowStep // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 18:12:32 2012----------*/
    void UpdateCurrentWorkflowStep();

   public:
   /** +-=---------------------------------------------------------So 30. Dez 13:17:46 2012-------*
    * @method  CwmsWorkflowObject::StartWorkflow             // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 13:17:46 2012----------*/
    void StartWorkflow();

   private:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:01:47 2012-------*
    * @method  CwmsWorkflowObject::FindWorkflow              // private                           *
    * @return  CwmsWorkflowDefinition                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:01:47 2012----------*/
    CwmsWorkflowDefinition FindWorkflow();

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:35:40 2012-------*
    * @method  CwmsWorkflowObject::SetCurrentStep            // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsWorkflowStepDefinition p_cStep      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:35:40 2012----------*/
    void SetCurrentStep(CwmsWorkflowStepDefinition p_cStep);

   private:
   /** +-=---------------------------------------------------------Di 8. Jan 15:21:06 2013--------*
    * @method  CwmsWorkflowObject::AddCurrentStep            // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 15:21:06 2013-----------*/
    void AddCurrentStep(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Di 8. Jan 15:21:24 2013--------*
    * @method  CwmsWorkflowObject::CurrentStepFinished       // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 15:21:24 2013-----------*/
    void CurrentStepFinished(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 8. Jan 15:26:56 2013--------*
    * @method  CwmsWorkflowObject::GetCurrentSteps           // public                            *
    * @return  QList<CdmObject*>                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 15:26:56 2013-----------*/
    QList<CdmObject*> GetCurrentSteps();

   public:
   /** +-=---------------------------------------------------------Di 8. Jan 15:26:47 2013--------*
    * @method  CwmsWorkflowObject::GetDoneSteps              // public                            *
    * @return  QList<CdmObject*>                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Jan 15:26:47 2013-----------*/
    QList<CdmObject*> GetDoneSteps();

   public:
   /** +-=---------------------------------------------------------Do 18. Jul 15:44:34 2013-------*
    * @method  CwmsWorkflowObject::ContinueWithNextSteps     // public                            *
    * @return  bool                                          //                                   *
    * @param   CwmsWorkflowStepExecution p_cExec             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 18. Jul 15:44:34 2013----------*/
    bool ContinueWithNextSteps(CwmsWorkflowStepExecution p_cExec);
};
#endif //
