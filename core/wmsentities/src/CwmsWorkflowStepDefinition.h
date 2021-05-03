#ifndef CWMSWORKFLOWSTEPDEFINITION_H
#define CWMSWORKFLOWSTEPDEFINITION_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes

// Own Includes
#include "basetools.h"
#include "CwmsWorkflowBase.h"

// Forwards
class CwmsWorkflowStepExecution;

// Enumerations

class BASETOOLS_API CwmsWorkflowStepDefinition: public CwmsWorkflowBase
{

   public:
      CwmsWorkflowStepDefinition();
   public:
      CwmsWorkflowStepDefinition(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsWorkflowStepDefinition();
   public:
      CdmObjectContainer* GetEscalation();
   public:
      void SetEscalation(CdmObjectContainer* p_pCdmOLValue);
   public:
      static CwmsWorkflowStepDefinition Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsWorkflowStepDefinition cCbmsSimpleWorkflowStepDefinition);

   public:
   /** +-=---------------------------------------------------------So 30. Dez 10:05:54 2012-------*
    * @method  CwmsWorkflowStepDefinition::SetSubWorkflow // public                         *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pObject                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 10:05:54 2012----------*/
    void SetSubWorkflow(CdmObject* p_pObject);

   public:
   /** +-=---------------------------------------------------------So 30. Dez 10:05:14 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetSubWorkflow // public                         *
    * @return  CdmObject*                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 10:05:14 2012----------*/
    CdmObject* GetSubWorkflow();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:14:44 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetSuccessors // public                          *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:14:44 2012----------*/
    CdmObjectContainer* GetSuccessors();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:14:51 2012-------*
    * @method  CwmsWorkflowStepDefinition::SetChangingValues // public                      *
    * @return  void                                          //                                   *
    * @param   QMap<QString, QString> p_qmValues             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:14:51 2012----------*/
    void SetChangingValues(QMap<QString, QString> p_qmValues);

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:14:55 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetChangingValues // public                      *
    * @return  QMap<QString, QString>                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:14:55 2012----------*/
    QMap<QString, QString> GetChangingValues();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:01 2012-------*
    * @method  CwmsWorkflowStepDefinition::SetType     // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iType                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:01 2012----------*/
    void SetType(int p_iType);

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:05 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetType     // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:05 2012----------*/
    int GetType();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:10 2012-------*
    * @method  CwmsWorkflowStepDefinition::SetReadOnlyMembers // public                     *
    * @return  void                                          //                                   *
    * @param   QList<QString> p_qstrlKeynames          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:10 2012----------*/
    void SetReadOnlyMembers(QList<QString> p_qstrlKeynames);

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:14 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetReadOnlyMembers // public                     *
    * @return  QList<QString>                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:14 2012----------*/
    QList<QString> GetReadOnlyMembers();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:18 2012-------*
    * @method  CwmsWorkflowStepDefinition::SetHiddenMembers // public                       *
    * @return  void                                          //                                   *
    * @param   QList<QString> p_qstrlKeynames          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:18 2012----------*/
    void SetHiddenMembers(QList<QString> p_qstrlKeynames);

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 14:15:30 2012-------*
    * @method  CwmsWorkflowStepDefinition::GetHiddenMembers // public                       *
    * @return  QList<QString>                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:15:30 2012----------*/
    QList<QString> GetHiddenMembers();

   public:
   /** +-=---------------------------------------------------------Do 18. Jul 16:41:07 2013-------*
    * @method  CwmsWorkflowStepDefinition::GetNextSteps      // public                            *
    * @return  QList<CdmObject*>                             //                                   *
    * @param   CdmObject* p_pCdmWorkflowObject               //                                   *
    * @param   CwmsWorkflowStepExecution p_cExec             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 18. Jul 16:41:07 2013----------*/
    QList<CdmObject*> GetNextSteps(CdmObject* p_pCdmWorkflowObject,
                                   CwmsWorkflowStepExecution p_cExec);
};
#endif //
