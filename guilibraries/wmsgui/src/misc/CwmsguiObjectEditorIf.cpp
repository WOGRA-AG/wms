/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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

/** +-=---------------------------------------------------------Di 28. Sep 08:14:33 2010----------*
 * @method  CwmsguiObjectEditorIf::CwmsguiObjectEditorIf     // public                            *
 * @return                                                   //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 08:14:33 2010----------*/
CwmsguiObjectEditorIf::CwmsguiObjectEditorIf(CdmObject* p_pCdmObject,
                                             QWidget* parent)
: QDialog(parent),
  m_rpCwmsValidator(nullptr),
  m_qstrObjectEventMode("")
{
   setupUi(this);
   m_rpCdmObject = p_pCdmObject;
}


/** +-=---------------------------------------------------------Tue Dec 16 10:43:15 2003----------*
 * @method  CwmsguiObjectEditorIf::~CwmsguiObjectEditorIf    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsguiObjectEditorIf                                         *
 *                                                                                                *
 *---------------------------------------------------------------Tue Dec 16 10:43:15 2003---------*/
CwmsguiObjectEditorIf::~CwmsguiObjectEditorIf(  )
{
}

/** +-=---------------------------------------------------------Do 23. Feb 13:41:41 2006----------*
 * @method  CwmsguiObjectEditorIf::SetValidator              // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsguiValidator* p_pCwmsguiValidator            //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Do 23. Feb 13:41:41 2006----------*/
void CwmsguiObjectEditorIf::SetValidator(CwmsguiValidator* p_pCwmsguiValidator)
{
   m_rpCwmsValidator = p_pCwmsguiValidator;
}

/** +-=---------------------------------------------------------Di 17. Jan 21:53:23 2006----------*
 * @method  CwmsguiObjectEditorIf::FillDialog                // public                            *
 * @return  void                                             //                                   *
 * @comment Shows the Dialog.                                                                     *
 *----------------last changed: Wolfgang Graßhof----------------Di 17. Jan 21:53:23 2006----------*/
void CwmsguiObjectEditorIf::FillDialog(  )
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

/** +-=---------------------------------------------------------So 25. Jun 14:40:02 2006----------*
 * @method  CwmsguiObjectEditorIf::SetSortedList             // public                            *
 * @return  void                                             //                                   *
 * @param   QStringList p_qstrlSorting                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 25. Jun 14:40:02 2006----------*/
void CwmsguiObjectEditorIf::SetSortedList(QStringList p_qstrlSorting)
{
   m_pCoeObjectEditor->SetSortedList(p_qstrlSorting);
}

/** +-=---------------------------------------------------------Di 16. Mrz 08:24:18 2010----------*
 * @method  CwmsguiObjectEditorIf::OKClickedSlot             // protected, slots                  *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the close button was clicked. it closes the               *
 *          ObjectEditor Dialog.                                                                  *
 *----------------last changed: --------------------------------Di 16. Mrz 08:24:18 2010----------*/
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
           QLinkedList<CdmObject*> qlEventObjects;
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

/** +-=---------------------------------------------------------Do 14. Jul 14:16:39 2011----------*
 * @method  CwmsguiObjectEditorIf::SetReadOnly               // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Jul 14:16:39 2011----------*/
void CwmsguiObjectEditorIf::SetReadOnly()
{
   pushButton1->hide();
}

/** +-=---------------------------------------------------------Do 19. Jan 20:12:02 2006----------*
 * @method  CwmsguiObjectEditorIf::AddHiddenValue            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method adds an hidden value to the objecteditor.                                 *
 *----------------last changed: Wolfgang Graßhof----------------Do 19. Jan 20:12:02 2006----------*/
void CwmsguiObjectEditorIf::AddHiddenValue(  QString p_qstrValue )
{
   m_pCoeObjectEditor->AddHiddenValue(p_qstrValue);
}

/** +-=---------------------------------------------------------Di 8. Mai 21:02:24 2007-----------*
 * @method  CwmsguiObjectEditorIf::SetCaptionValue           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment Over this method you can set, from which value the objectcaption will be              *
 *          autmatically copied.                                                                  *
 *----------------last changed: Wolfgang Graßhof----------------Di 8. Mai 21:02:24 2007-----------*/
void CwmsguiObjectEditorIf::SetCaptionValue(QString p_qstrValue)
{
   m_pCoeObjectEditor->SetCaptionValue(p_qstrValue);
}

/** +-=---------------------------------------------------------Do 19. Jan 20:12:36 2006----------*
 * @method  CwmsguiObjectEditorIf::AddReadOnlyValue          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method adds an readonly value to the obejcteditor.                               *
 *----------------last changed: Wolfgang Graßhof----------------Do 19. Jan 20:12:36 2006----------*/
void CwmsguiObjectEditorIf::AddReadOnlyValue(  QString p_qstrValue )
{
   m_pCoeObjectEditor->AddReadOnlyValue(p_qstrValue);
}

/** +-=---------------------------------------------------------Fr 20. Jan 23:41:48 2006----------*
 * @method  CwmsguiObjectEditorIf::AddObjectRefData          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrObjectList                         //                                   *
 * @param   QString p_qstrDisplayValue                       //                                   *
 * @comment Adds the object reference data.                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Fr 20. Jan 23:41:48 2006----------*/
void CwmsguiObjectEditorIf::AddObjectRefData(  QString p_qstrValue,
                                              QString p_qstrObjectList,
                                              QString p_qstrDisplayValue )
{
   m_pCoeObjectEditor->AddObjectRefData(p_qstrValue, p_qstrObjectList, p_qstrDisplayValue);
}

/** +-=---------------------------------------------------------Mo 3. Sep 16:26:44 2012-----------*
 * @method  CwmsguiObjectEditorIf::SetDisplayType            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   EdmStringDisplayType p_eOeDisplayType            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 16:26:44 2012-----------*/
void CwmsguiObjectEditorIf::SetDisplayType(QString p_qstrValue,
                                           EdmStringDisplayType p_eOeDisplayType)
{
   m_pCoeObjectEditor->SetDisplayType(p_qstrValue, p_eOeDisplayType);
} 

/** +-=---------------------------------------------------------Fr 14. Dez 14:50:43 2012----------*
 * @method  CwmsguiObjectEditorIf::SetFormConfiguration      // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pObject                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 14:50:43 2012----------*/
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

/** +-=---------------------------------------------------------Do 4. Okt 08:40:12 2012-----------*
 * @method  CwmsguiObjectEditorIf::AddProxy                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 4. Okt 08:40:12 2012-----------*/
void CwmsguiObjectEditorIf::AddProxy(QString p_qstrKeyname, CdmEnhancedQueryProxy* p_pCwmsProxy)
{
   m_pCoeObjectEditor->AddProxy(p_qstrKeyname, p_pCwmsProxy);
}
