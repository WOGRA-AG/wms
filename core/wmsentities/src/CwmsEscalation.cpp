// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsEscalation.h"

// Forwards

// Enumerations

CwmsEscalation::CwmsEscalation()
 : CdmObjectAdaptor()
{
}

CwmsEscalation::CwmsEscalation(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsEscalation::~CwmsEscalation()
{
}

QList<int> CwmsEscalation::GetEmployees()
{
   return GetIntList("Employees");
}

void CwmsEscalation::AddEmployee(int p_iValue)
{
   AddIntListValue("Employees", p_iValue);
}

int CwmsEscalation::GetViolationOfLimit()
{
   return GetInt("Violation_Of_Limit");
}

void CwmsEscalation::SetViolationOfLimit(int p_iValue)
{
   SetValue("Violation_Of_Limit", p_iValue);
}

int CwmsEscalation::GetEscalationStep()
{
   return GetInt("Escalation_Step");
}

void CwmsEscalation::SetEscalationStep(int p_iValue)
{
   SetValue("Escalation_Step", p_iValue);
}

/** +-=---------------------------------------------------------Mi 17. Okt 16:18:12 2012----------*
 * @method  CwmsEscalation::SendEscalationMail               // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* pCdmWorkflow                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 16:18:12 2012----------*/
void CwmsEscalation::SendEscalationMail(CdmObject* pCdmWorkflow)
{
   QString qstrContent = CreateMailContent(pCdmWorkflow);

   // ToDo
}

/** +-=---------------------------------------------------------Mi 17. Okt 16:14:24 2012----------*
 * @method  CwmsEscalation::CreateMailContent                // private                           *
 * @return  QString                                          //                                   *
 * @param   CdmObject* p_pCdmWorkflow                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 16:14:24 2012----------*/
QString CwmsEscalation::CreateMailContent(CdmObject* p_pCdmWorkflow)
{
   QString qstrText;

   if (CHKPTR(p_pCdmWorkflow))
   {
      qstrText += tr("");
      // ToDO
   }

   return qstrText;
}


CwmsEscalation CwmsEscalation::Create(CdmObjectContainer* p_pContainer)
{
   CwmsEscalation cCbmsEscalation;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCbmsEscalation.SetObject(pCdmObject);
   }

   return cCbmsEscalation;
}
bool CwmsEscalation::Delete(CwmsEscalation cCbmsEscalation)
{
   bool bSuccess = false;
   if (cCbmsEscalation.IsValid())
   {
      cCbmsEscalation.SetDeleted();
      cCbmsEscalation.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
