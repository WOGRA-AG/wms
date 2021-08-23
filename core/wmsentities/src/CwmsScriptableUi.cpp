// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQueryEnhanced.h"

// own Includes
#include "CwmsScriptableUi.h"

CwmsScriptableUi::CwmsScriptableUi()
{
}

CwmsScriptableUi::~CwmsScriptableUi()
{
}

void CwmsScriptableUi::openUi(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

void CwmsScriptableUi::openUi(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::openSearch(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::openImport(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::openExport(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::openHistory(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::openHistory(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

QObject* CwmsScriptableUi::selectObject(CdmObjectContainer* p_pContainer)
{
   QObject* pRet = nullptr;

   Q_UNUSED(p_pContainer);

   return pRet;
}

QObject* CwmsScriptableUi::selectObjectList(CdmClass* p_pCdmClass)
{
   QObject* pRet = nullptr;

   Q_UNUSED(p_pCdmClass);


   return pRet;
}

void CwmsScriptableUi::editPrintingTemplate(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

void CwmsScriptableUi::editPrintingTemplate(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

QObject* CwmsScriptableUi::selectClass()
{
   QObject* pRet = nullptr;

   return pRet;
}
