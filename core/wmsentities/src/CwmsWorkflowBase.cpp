// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsWorkflowBase.h"

// Forwards

// Enumerations

CwmsWorkflowBase::CwmsWorkflowBase()
 : CdmObjectAdaptor()
{
}

CwmsWorkflowBase::CwmsWorkflowBase(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsWorkflowBase::~CwmsWorkflowBase()
{
}

CdmObject* CwmsWorkflowBase::GetResponsibility()
{
   return GetObjectRefValue("Responsibility");
}

void CwmsWorkflowBase::SetResponsibility(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Responsibility", p_pCdmValue);
}

int CwmsWorkflowBase::GetPosition()
{
   return GetInt("Position");
}

void CwmsWorkflowBase::SetPosition(int p_iValue)
{
   SetValue("Position", p_iValue);
}

QString CwmsWorkflowBase::GetName()
{
   return GetString("Name");
}

void CwmsWorkflowBase::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

QString CwmsWorkflowBase::GetDescription()
{
   return GetString("Description");
}

void CwmsWorkflowBase::SetDescription(QString p_qstrValue)
{
   SetValue("Description", p_qstrValue);
}

int CwmsWorkflowBase::GetState()
{
   return GetInt("State");
}

void CwmsWorkflowBase::SetState(int p_iValue)
{
   SetValue("State", p_iValue);
}

int CwmsWorkflowBase::GetMaxDuration()
{
   return GetInt("Max_Duration");
}

void CwmsWorkflowBase::SetMaxDuration(int p_iValue)
{
   SetValue("Max_Duration", p_iValue);
}

