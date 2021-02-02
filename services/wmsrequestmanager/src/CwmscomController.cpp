/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomController.cpp
 ** Started Implementation: 2012/04/01
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

#include "CwmsTimeMeassurement.h"

// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "IwmsWebService.h"
#include "CwmscomData.h"
#include "CwmscomHandler.h"
#include "CwmscomResource.h"
#include "CwmscomController.h"


CwmscomController::CwmscomController(QString p_qstrName, CwmscomHandler* p_pCbmsHandler)
: m_qstrControllerName(p_qstrName),
  m_rpCbmsHandler(p_pCbmsHandler)
{
   if (p_pCbmsHandler)
   {
      p_pCbmsHandler->AddController(m_qstrControllerName, this);
   }
}

CwmscomController::~CwmscomController()
{
   QMap<QString, IwmsWebService*>::iterator qmIt = m_qmResources.begin();
   QMap<QString, IwmsWebService*>::iterator qmItEnd = m_qmResources.end();
   
   for (; qmIt != qmItEnd; ++qmIt)
   {
      IwmsWebService* pResource = qmIt.value();
      delete pResource;
   }

   m_qmResources.clear();
}

QString CwmscomController::GetName()
{
   return m_qstrControllerName;
}

void CwmscomController::AddResource(QString p_qstrResource, IwmsWebService* p_pResource)

{
   m_qmResources.insert(p_qstrResource, p_pResource);
}

QList<QString> CwmscomController::GetResources()
{
   return m_qmResources.keys();
}

void CwmscomController::Execute(CwmscomData* p_pCwmscomData)
{
    CwmsTimeMeassurement cTime(false, "CwmscomController::Execute");
   if (p_pCwmscomData && p_pCwmscomData->IsValid())
   {

      IwmsWebService* pResource = GetResource(p_pCwmscomData->GetResource());
      cTime.finishedTask("Search Ressource");

      if (pResource)
      {
         pResource->execute(p_pCwmscomData);
         cTime.finishedTask("Execute Ressource");
      }
      else
      {
         ERR("Resource not found! Resourcename: " + p_pCwmscomData->GetResource());
      }
   }
   else
   {
      FATAL("Data object invalid for data transfer");
   }
}

IwmsWebService* CwmscomController::GetResource(QString p_qstrName)
{
   IwmsWebService* pResource = nullptr;
   if (m_qmResources.contains(p_qstrName))
   {
      pResource = m_qmResources[p_qstrName];
   }

   return pResource;
}

QString CwmscomController::GetDescription(QString p_qstrResource)
{
   QString qstrDescription;

   IwmsWebService* pCbmsResourceBase = GetResource(p_qstrResource);

   if (pCbmsResourceBase)
   {
      QScopedPointer<CwmscomData> pTemp(new CwmscomData(nullptr, nullptr, m_rpCbmsHandler));
      pCbmsResourceBase->executeDescription(pTemp.data());
      qstrDescription = pTemp->GetResult();
   }
   else
   {
      qstrDescription = "Resource not found!";
   }

   return qstrDescription;
}

IwmsSerializer* CwmscomController::GetSerializer()
{
   return m_rpCbmsHandler->GetSerializer();
}

IwmsParser* CwmscomController::GetParser()
{
   return m_rpCbmsHandler->GetParser();
}
