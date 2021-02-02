#ifndef CWMSWORKFLOWDEFINITION_H
#define CWMSWORKFLOWDEFINITION_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "CwmsWorkflowStepDefinition.h"
#include "basetools.h"

// Forwards


// Enumerations


class BASETOOLS_API CwmsWorkflowDefinition: public CdmObjectAdaptor
{

   public:
      CwmsWorkflowDefinition();
   public:
      CwmsWorkflowDefinition(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsWorkflowDefinition();
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   public:
      CdmObjectContainer* GetWorkflow();
    public:
      QString GetDescription();
   public:
      void SetDescription(QString p_qstrValue);
   public:
      static CwmsWorkflowDefinition Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsWorkflowDefinition cCbmsFeedbackType);

   public:
   /** +-=---------------------------------------------------------Do 18. Okt 16:24:07 2012-------*
    * @method  CwmsWorkflowDefinition::GetObjectWorkflow           // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 18. Okt 16:24:07 2012----------*/
    CdmObjectContainer* GetObjectWorkflow();

   public:
   /** +-=---------------------------------------------------------Di 18. Dez 13:43:37 2012-------*
    * @method  CwmsWorkflowDefinition::GetClass              // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Dez 13:43:37 2012----------*/
    QString GetClass();

   public:
   /** +-=---------------------------------------------------------Di 18. Dez 13:43:53 2012-------*
    * @method  CwmsWorkflowDefinition::SetClass              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrClass                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Dez 13:43:53 2012----------*/
    void SetClass(QString p_qstrClass);

   public:
   /** +-=---------------------------------------------------------So 30. Dez 10:57:11 2012-------*
    * @method  CwmsWorkflowDefinition::GetType               // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 10:57:11 2012----------*/
    int GetType();

   public:
   /** +-=---------------------------------------------------------So 30. Dez 10:57:22 2012-------*
    * @method  CwmsWorkflowDefinition::SetType               // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iType                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 10:57:22 2012----------*/
    void SetType(int p_iType);

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 10:07:05 2012-------*
    * @method  CwmsWorkflowDefinition::GetStartingStep       // public                            *
    * @return  CwmsWorkflowStepDefinition              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 31. Dez 10:07:05 2012----------*/
    CwmsWorkflowStepDefinition GetStartingStep();
};
#endif //
