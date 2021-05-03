// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmValueObjectRef.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmContainerManager.h"
#include "CwmsWorkflowStepExecution.h"
#include "CwmsWorkflowStepDefinition.h"

// Forwards

// Enumerations

CwmsWorkflowStepDefinition::CwmsWorkflowStepDefinition()
 : CwmsWorkflowBase()
{
}

CwmsWorkflowStepDefinition::CwmsWorkflowStepDefinition(CdmObject* p_pCdmObject)
 : CwmsWorkflowBase(p_pCdmObject)
{
}

CwmsWorkflowStepDefinition::~CwmsWorkflowStepDefinition()
{
}

CdmObjectContainer* CwmsWorkflowStepDefinition::GetEscalation()
{
   return GetContainerRefValue("Escalation");
}

void CwmsWorkflowStepDefinition::SetEscalation(CdmObjectContainer* p_pCdmOLValue)
{
   SetContainerRefValue("Escalation", p_pCdmOLValue);
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:30 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetHiddenMembers // public                          *
 * @return  QList<QString>                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:30 2012----------*/
QList<QString> CwmsWorkflowStepDefinition::GetHiddenMembers()
{
   return GetStringList("Hidden_Members");
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:18 2012----------*
 * @method  CwmsWorkflowStepDefinition::SetHiddenMembers // public                          *
 * @return  void                                             //                                   *
 * @param   QList<QString> p_qstrlKeynames             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:18 2012----------*/
void CwmsWorkflowStepDefinition::SetHiddenMembers(QList<QString> p_qstrlKeynames)
{
   SetStringList("Hidden_Members", p_qstrlKeynames);
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:14 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetReadOnlyMembers // public                        *
 * @return  QList<QString>                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:14 2012----------*/
QList<QString> CwmsWorkflowStepDefinition::GetReadOnlyMembers()
{
   return GetStringList("ReadOnly_Members");
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:10 2012----------*
 * @method  CwmsWorkflowStepDefinition::SetReadOnlyMembers // public                        *
 * @return  void                                             //                                   *
 * @param   QList<QString> p_qstrlKeynames             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:10 2012----------*/
void CwmsWorkflowStepDefinition::SetReadOnlyMembers(QList<QString> p_qstrlKeynames)
{
   SetStringList("ReadOnly_Members", p_qstrlKeynames);
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:05 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetType        // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:05 2012----------*/
int CwmsWorkflowStepDefinition::GetType()
{
   return GetInt("Type");
}

/** +-=---------------------------------------------------------Do 25. Okt 14:15:01 2012----------*
 * @method  CwmsWorkflowStepDefinition::SetType        // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iType                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:15:01 2012----------*/
void CwmsWorkflowStepDefinition::SetType(int p_iType)
{
   SetValue("Type", p_iType);
}

/** +-=---------------------------------------------------------Do 25. Okt 14:14:55 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetChangingValues // public                         *
 * @return  QMap<QString, QString>                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:14:55 2012----------*/
QMap<QString, QString> CwmsWorkflowStepDefinition::GetChangingValues()
{
   return GetStringStringDict("Changing_Values");
}

/** +-=---------------------------------------------------------Do 25. Okt 14:14:51 2012----------*
 * @method  CwmsWorkflowStepDefinition::SetChangingValues // public                         *
 * @return  void                                             //                                   *
 * @param   QMap<QString, QString> p_qmValues                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:14:51 2012----------*/
void CwmsWorkflowStepDefinition::SetChangingValues(QMap<QString, QString> p_qmValues)
{
   SetStringStringDict("Changing_Values", p_qmValues);
}

/** +-=---------------------------------------------------------Do 25. Okt 14:14:44 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetSuccessors  // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:14:44 2012----------*/
CdmObjectContainer* CwmsWorkflowStepDefinition::GetSuccessors()
{
   return GetContainerRefValue("Successor");
}

/** +-=---------------------------------------------------------So 30. Dez 10:05:14 2012----------*
 * @method  CwmsWorkflowStepDefinition::GetSubWorkflow // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 10:05:14 2012----------*/
CdmObject* CwmsWorkflowStepDefinition::GetSubWorkflow()
{
   return GetObjectRefValue("Sub_Workflow");
}

/** +-=---------------------------------------------------------So 30. Dez 10:05:54 2012----------*
 * @method  CwmsWorkflowStepDefinition::SetSubWorkflow // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pObject                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 10:05:54 2012----------*/
void CwmsWorkflowStepDefinition::SetSubWorkflow(CdmObject* p_pObject)
{
   SetObjectRefValue("Sub_Workflow", p_pObject);
}

/** +-=---------------------------------------------------------Do 18. Jul 16:41:07 2013----------*
 * @method  CwmsWorkflowStepDefinition::GetNextSteps         // public                            *
 * @return  QList<CdmObject*>                                //                                   *
 * @param   CdmObject* p_pCdmWorkflowObject                  //                                   *
 * @param   CwmsWorkflowStepExecution p_cExec                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 18. Jul 16:41:07 2013----------*/
QList<CdmObject*> CwmsWorkflowStepDefinition::GetNextSteps(CdmObject* p_pCdmWorkflowObject,
                                                           CwmsWorkflowStepExecution p_cExec)
{
  QList<CdmObject*> qlNextSteps;

   if (CHKPTR(p_pCdmWorkflowObject))
   {
      CdmObjectContainer* pList = GetSuccessors();
      CdmContainerManager* pOLManager = pList->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         pOLManager->ReloadContainerComplete(pList);
         QList<CdmObject*> qlObjects;
         pList->GetObjectList(qlObjects);

         QList<CdmObject*>::iterator qllIt = qlObjects.begin();
         QList<CdmObject*>::iterator qllItEnd = qlObjects.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            CdmObject* pObject = *qllIt;

            if (CHKPTR(pObject))
            {
               QString qstrCondtion = pObject->GetDisplayString("Condition");

               if (qstrCondtion.isEmpty() && p_cExec.IsFinished())
               {
                  CdmValue* pValue = pObject->GetValue("Successor");

                  if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueObjectRef)
                  {
                     CdmObject* pSuccessor = ((CdmValueObjectRef*)pValue)->GetObject();

                     if (pSuccessor)
                     {
                        qlNextSteps.append(pSuccessor);
                     }
                  }
               }
               else
               {
                  CdmObjectContainer* pWorkflowObjectList = p_pCdmWorkflowObject->GetObjectContainer();

                  if (CHKPTR(pWorkflowObjectList))
                  {
                     QString qstrWql = "select from \"" + pWorkflowObjectList->GetKeyname() + "\" where " + qstrCondtion;
                     CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

                     if (pQuery && pQuery->ContainsResultObject(p_pCdmWorkflowObject))
                     {
                        CdmValue* pValue = pObject->GetValue("Successor");

                        if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueObjectRef)
                        {
                           CdmObject* pSuccessor = ((CdmValueObjectRef*)pValue)->GetObject();

                           if (pSuccessor)
                           {
                              qlNextSteps.append(pSuccessor);
                           }
                        }                           
                     }
                  }
               }
            }
         }
      }
   }

   return qlNextSteps;
}

CwmsWorkflowStepDefinition CwmsWorkflowStepDefinition::Create(CdmObjectContainer* p_pContainer)
{
   CwmsWorkflowStepDefinition cCbmsSimpleWorkflowStepDefinition;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCbmsSimpleWorkflowStepDefinition.SetObject(pCdmObject);
   }

   return cCbmsSimpleWorkflowStepDefinition;
}
bool CwmsWorkflowStepDefinition::Delete(CwmsWorkflowStepDefinition cCbmsSimpleWorkflowStepDefinition)
{
   bool bSuccess = false;

   if (cCbmsSimpleWorkflowStepDefinition.IsValid())
   {
      cCbmsSimpleWorkflowStepDefinition.SetDeleted();
      cCbmsSimpleWorkflowStepDefinition.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
