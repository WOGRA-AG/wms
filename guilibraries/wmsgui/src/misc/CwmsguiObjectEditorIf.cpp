// System and QT Includes
#include <QLayout>
#include <QObject>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmQueryEnhanced.h"
#include "CdmDataProvider.h"
#include "CdmValue.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmSession.h"
#include "CwmsJson.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"

// WMSBASETOOLS Includes
#include "CwmsbtSessionManager.h"

// own Includes
#include "CwmsJournalViewer.h"
#include "CwmsguiValidator.h"
#include "CwmsguiObjectEditorIf.h"

CwmsguiObjectEditorIf::CwmsguiObjectEditorIf(CdmObject* p_pCdmObject,
                                             QWidget* parent)
: QDialog(parent),
  m_rpCwmsValidator(nullptr),
  m_qstrObjectEventMode("")
{
   setupUi(this);
   m_rpCdmObject = p_pCdmObject;
}

CwmsguiObjectEditorIf::~CwmsguiObjectEditorIf()
{
}

void CwmsguiObjectEditorIf::SetValidator(CwmsguiValidator* p_pCwmsguiValidator)
{
   m_rpCwmsValidator = p_pCwmsguiValidator;
}

void CwmsguiObjectEditorIf::FillDialog()
{
   CdmClass* pCdmClass = m_rpCdmObject->GetClass();

   if (CHKPTR(m_rpCdmObject))
   {
      m_pCoeObjectEditor->SetObject(m_rpCdmObject);
      m_pCoeObjectEditor->FillObjectEditor();

      if (CHKPTR(pCdmClass))
      {
         setWindowTitle(m_rpCdmObject->GetCaption() + QStringLiteral(" - ") + m_rpCdmObject->GetKeyname());
         m_pqlArticleType->setText(pCdmClass->GetCaption() + QStringLiteral(" ") + tr("bearbeiten"));
      }
   }
}

void CwmsguiObjectEditorIf::FillEventDialog()
{
    CdmClass *pEventClass = m_rpCdmObject->GetClass();

    m_pCoeObjectEditor->SetObject(m_rpCdmObject);
    m_pCoeObjectEditor->FillObjectEventEditor(pEventClass, GetObjectEventMode());

    if (CHKPTR(pEventClass))
    {
       setWindowTitle(m_rpCdmObject->GetCaption() + " - " + m_rpCdmObject->GetKeyname());
       m_pqlArticleType->setText(pEventClass->GetCaption() + " " + tr("ansehen"));
    }
}

void CwmsguiObjectEditorIf::SetSortedList(QStringList p_qstrlSorting)
{
   m_pCoeObjectEditor->SetSortedList(p_qstrlSorting);
}

void CwmsguiObjectEditorIf::OKClickedSlot()
{
    const CdmClass *pClass = nullptr;
    bool bContinue = true;

    if(m_rpCwmsValidator)
    {
        bContinue = m_rpCwmsValidator->Validate();
    }

    if (bContinue)
    {
        pClass = m_rpCdmObject->GetClass();
        if (CHKPTR(pClass))
        {
            if(pClass->IsEventClass())
            {
                if(SUCCESSFULL(workOffEvents()))
                {
                    accept();
                }
            }
            else
            {
                CdmObjectContainer *container = m_rpCdmObject->GetObjectContainer();
                if (CdmExecutor::ExecuteValidation(container))
                {
                    accept();
                }
            }
        }
    }
}

int CwmsguiObjectEditorIf::workOffEvents()
{
    int iRet = CdmLogging::eDmFalse;

    CdmObject *pEventObject = nullptr;
    CdmClass *pEventClass = nullptr;
    CdmClass *pCdmObjectClass = m_rpCdmObject->GetClass();

    QString qstrEventContainerKeyname = "EventClassContainer";
    QVariantList qvlParameters;

    CdmSessionManager *pSessionManager = CdmSessionManager::GetSessionManager();
    CdmSession *pSession = pSessionManager->FindSession();
    IdmEventStoreManager *pEventStoreManager = pSession->getEventStoreManager();

    if (pEventStoreManager)
    {
       CdmContainerManager *pContainerManager = m_rpCdmObject->GetContainerManager();
       CdmObjectContainer *pEventContainer = m_rpCdmObject->GetObjectContainer();

       if(pEventContainer)
       {
           QList<CdmObject*> qlEventObjects;
           pEventContainer->GetObjectList(qlEventObjects);
           //there will allways just one object in this list.
           if(!qlEventObjects.isEmpty())
           {
               pEventObject = qlEventObjects.first();
               if(pEventObject)
               {
                   qvlParameters = saveEventAndReturnJSFunctionParameters(pEventStoreManager, pEventObject);
                   IterateOverSubscribersAndExecuteFunction(pEventStoreManager->getSubscribers(), qvlParameters);
                   iRet = CdmLogging::eDmOk;
               }
           }
       }
       else
       {
           INFO("EventClassContainer does not exist. Creating one.");

           pEventClass = pCdmObjectClass->getSelectedEventClass();
           pContainerManager->CreateContainer(pEventClass, qstrEventContainerKeyname);

           pEventContainer = pContainerManager->FindContainerByKeyname(qstrEventContainerKeyname);
           pEventObject = pEventContainer->CreateNewObject();

           if(pEventObject)
           {
               qvlParameters = saveEventAndReturnJSFunctionParameters(pEventStoreManager, pEventObject);
               IterateOverSubscribersAndExecuteFunction(pEventStoreManager->getSubscribers(), qvlParameters);
               iRet = CdmLogging::eDmOk;
           }
       }
       pEventStoreManager->DeleteContainersAfterSavingEvent(pContainerManager, pEventContainer);
    }
    else
    {
       CdmObject* pObject = m_pCoeObjectEditor->GetObject();
       if (CHKPTR(pObject))
       {
         iRet = pObject->Commit();
       }
    }

    return iRet;
}

QVariantList CwmsguiObjectEditorIf::saveEventAndReturnJSFunctionParameters(IdmEventStoreManager *p_EventStoreManager, CdmObject *p_EventObject)
{
    QVariantList qvlParameters;

    if (p_EventStoreManager)
    {
       QString qstrEvent;
       QVariant qvEventObject;
       QVariant qvEventClass;
       CdmClass *pEventClass = p_EventObject->GetClass();

       qvEventClass = pEventClass->GetVariant();
       qvEventObject = p_EventObject->GetVariant();

       QVariantList qvlEventContentFormatted;
       qvlEventContentFormatted.append(p_EventStoreManager->formatEventContent(qvEventClass, qvEventObject));
       qstrEvent = p_EventStoreManager->getFormattedEventContentAsString(qvlEventContentFormatted);

       QObject* pEventDto = p_EventStoreManager->createEventDtoObject(qvlEventContentFormatted);
       QVariant qvEventDto = QVariant::fromValue<QObject*>(pEventDto);
       qvlParameters.append(qvEventDto);
       p_EventStoreManager->startEvent(qstrEvent);
       p_EventStoreManager->stopEvent(qstrEvent, pEventDto);
    }

    return qvlParameters;
}

void CwmsguiObjectEditorIf::IterateOverSubscribersAndExecuteFunction(QList<CdmClassMethod*> ql_Subscribers, QVariantList qvlParameters)
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();
    QList<CdmClassMethod*>::iterator ql_ItStart = ql_Subscribers.begin();
    QList<CdmClassMethod*>::iterator ql_ItEnd = ql_Subscribers.end();
    for(; ql_ItStart != ql_ItEnd; ql_ItStart++)
    {
        CdmClassMethod *pClassMethod = (*ql_ItStart);
        if(CHKPTR(pClassMethod))
        {
            QVariant qvFunction = pExecutor->GetFunction()->ExecuteFunctionStatic(pClassMethod, qvlParameters);
        }
    }
}

void CwmsguiObjectEditorIf::SetReadOnly()
{
   pushButton1->hide();
}

void CwmsguiObjectEditorIf::AddHiddenValue(QString p_qstrValue)
{
   m_pCoeObjectEditor->AddHiddenValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::SetCaptionValue(QString p_qstrValue)
{
   m_pCoeObjectEditor->SetCaptionValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::AddReadOnlyValue(QString p_qstrValue)
{
   m_pCoeObjectEditor->AddReadOnlyValue(p_qstrValue);
}

void CwmsguiObjectEditorIf::AddObjectRefData(QString p_qstrValue,
                                             QString p_qstrObjectList,
                                             QString p_qstrDisplayValue)
{
   m_pCoeObjectEditor->AddObjectRefData(p_qstrValue, p_qstrObjectList, p_qstrDisplayValue);
}

void CwmsguiObjectEditorIf::AddObjectRefData(QString p_qstrValue,
                                             QString p_qstrWql)
{
   m_pCoeObjectEditor->AddObjectRefData(p_qstrValue, p_qstrWql);
}

void CwmsguiObjectEditorIf::SetDisplayType(QString p_qstrValue,
                                           EdmStringDisplayType p_eOeDisplayType)
{
   m_pCoeObjectEditor->SetDisplayType(p_qstrValue, p_eOeDisplayType);
} 

void CwmsguiObjectEditorIf::SetFormConfiguration(CdmObject* p_pObject)
{
    m_pCoeObjectEditor->SetFormConfiguration(p_pObject);
}

void CwmsguiObjectEditorIf::SetObjectEventMode(QString qstr_EventMode)
{
    m_qstrObjectEventMode = qstr_EventMode;
}

QString CwmsguiObjectEditorIf::GetObjectEventMode() const
{
    return m_qstrObjectEventMode;
}

void CwmsguiObjectEditorIf::AddProxy(QString p_qstrKeyname, CdmQueryModel *p_pCwmsProxy)
{
   m_pCoeObjectEditor->AddProxy(p_qstrKeyname, p_pCwmsProxy);
}
