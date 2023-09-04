// System and QT Includes
#include <QPushButton>
#include <QCursor>
#include <QModelIndex>
#include <QList>
#include <QMenu>
#include <qtoolbar.h>
#include <QAction>
#include <QMessageBox>
#include <QStandardItemModel>
#include <CwmsQueryModelExportCsv.h>

// WMS Includes
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmQueryEnhanced.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmSession.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"

// own Includes
#include "CwmsExportFileWriter.h"
#include "CwmsImExportManager.h"
#include "CwmsImportDlg.h"
#include "CwmsImport.h"
#include "CwmsExportSettings.h"
#include "CwmsExportSettingsIf.h"
#include "CwmsSearchWindowDlg.h"
#include "CwmsView.h"
#include "CwmsRuntime.h"
#include "CwmsJournalViewer.h"
#include "CwmsHelp.h"
#include "CwmsReportManager.h"
#include "CwmsPrintingTemplate.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsObjectListEditorWidgetIf.h"
#include "CwmsEventClassEditor.h"

CwmsObjectListEditorWidgetIf::CwmsObjectListEditorWidgetIf(QWidget* parent)
    : QWidget(parent),
      m_rpCdmPrintingTemplate(nullptr),
      m_eWmsLvObjectInUseHandling(eWmsLvNone),
      m_rpCdmObjectSelected(nullptr),
      m_pModel(nullptr),
      m_pMenu(nullptr),
      m_pToolBar(nullptr),
      m_qstrObjectEventMode(""),
      m_pEventClassEditor(nullptr)
{
    setupUi(this);

    if (!CdmSessionManager::GetDataProvider()->IsLoggedInUserAdmin())
    {
        m_pqpbMetaData->hide();
    }

    qmlGenerator->hide();
    m_pModel = new CdmQueryModel();
    m_pCwmsObjectListListView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pCwmsObjectListListView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(CustomContextMenuSlot(const QPoint &)));
}

CwmsObjectListEditorWidgetIf::CwmsObjectListEditorWidgetIf(CdmObjectContainer* p_pContainer,
                                                           QWidget* parent)
    : QWidget(parent),
      m_rpCdmPrintingTemplate(nullptr),
      m_eWmsLvObjectInUseHandling(eWmsLvNone),
      m_rpCdmObjectSelected(nullptr),
      m_pModel(nullptr),
      m_pMenu(nullptr),
      m_pToolBar(nullptr),
      m_qstrObjectEventMode(""),
      m_pEventClassEditor(nullptr)
{
    setupUi(this);
    qmlGenerator->hide();
    m_pModel = new CdmQueryModel();
    dynamic_cast<CdmQueryModel*>(m_pModel)->SetContainer(p_pContainer);
    m_pCwmsObjectListListView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_pCwmsObjectListListView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(CustomContextMenuSlot(const QPoint &)));
}

CwmsObjectListEditorWidgetIf::~CwmsObjectListEditorWidgetIf(  )
{
    //DELPTR(m_pModel);
}

void CwmsObjectListEditorWidgetIf::InitContextMenu()
{
    if (!m_pqpbNew->isHidden())
    {
        m_qstrlContextMenuItems.append(tr("Neu"));
    }

    if (!m_pqpbEdit->isHidden())
    {
        m_qstrlContextMenuItems.append(tr("Bearbeiten"));
    }
    else
    {
        m_qstrlContextMenuItems.append(tr("Ansicht"));
    }

    if (!m_pqpbDelete->isHidden())
    {
        m_qstrlContextMenuItems.append(tr("Löschen"));
    }

    if (!m_pqpbPrint->isHidden())
    {
        m_qstrlContextMenuItems.append(tr("Drucken"));
    }
}

void CwmsObjectListEditorWidgetIf::clear()
{
}

void CwmsObjectListEditorWidgetIf::SetContainer(CdmObjectContainer* p_pContainer)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->SetContainer(p_pContainer);
    }
}

void CwmsObjectListEditorWidgetIf::ExecuteQuery(QString p_qstrQuery)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute(p_qstrQuery);
    }
}

void CwmsObjectListEditorWidgetIf::Refresh()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute();
    }
}

void CwmsObjectListEditorWidgetIf::ClearColumns(  )
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute("");
    }
}


void CwmsObjectListEditorWidgetIf::AddColumn(QString p_qstrColumn)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr && CHKPTR(pModel->GetQuery()))
    {
        auto pClass = pModel->GetQuery()->GetClass();

        if (CHKPTR(pClass))
        {
            auto pMember = pClass->FindMember(p_qstrColumn);

            if (CHKPTR(pMember))
            {
                if (pMember->GetValueType() == eDmValueObjectRef)
                {
                    auto pClassRef = pMember->GetClassReferencePtr();

                    if (pClassRef)
                    {
                        auto qstrCaptionMember = pClassRef->GetCaptionMemberKeyname();

                        if (!qstrCaptionMember.isEmpty())
                        {
                            p_qstrColumn += "."+qstrCaptionMember;
                        }
                    }
                }
            }
            else
            {
                ERR("Member not found: "+ p_qstrColumn);
                return;
            }
        }

        pModel->GetQuery()->AddResultElement(p_qstrColumn);
    }
}

void CwmsObjectListEditorWidgetIf::AddDisplayHeader(int p_iColumn, QString p_qstrHeader)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->AddDisplayHeader(p_iColumn, p_qstrHeader);
    }
}

void CwmsObjectListEditorWidgetIf::FillDialog()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        if (!pModel->GetQuery()->HasResultElements())
        {
            pModel->AddAllMembers();
        }

        if (pModel->columnCount() > 0)
        {
            connect(pModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(UpdateTreeViewSlot()));
            m_pCwmsObjectListListView->setModel(pModel);

            if (pModel->GetQuery() && pModel->GetContainer())
            {
                if (m_pqpbJournal->isHidden())
                {
                    CdmDataProvider* pCdmManager = pModel->GetContainer()->GetDataProvider();

                    if (CHKPTR(pCdmManager))
                    {
                        if (pCdmManager->IsLoggedInUserAdmin() && !m_pMenu)
                        {
                            m_pqpbJournal->show();
                        }
                    }
                }

                m_pqpbPrint->hide();
                CwmsReportManager cReportManager;
                CdmQueryEnhanced* pQuery = nullptr;
                const CdmClass* pClass = pModel->GetClass();

                if (CHKPTR(pClass))
                {
                    pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetFullQualifiedName(), eWmsTemplateTypeList);
                }

                if ((pQuery && pQuery->GetResultCount() > 0) || m_rpCdmPrintingTemplate)
                {
                    m_pqpbPrint->show();
                }

                DELPTR(pQuery);
                InitContextMenu();
                m_pCwmsObjectListListView->expandAll();
            }

            AddFunctions();
            pModel->Execute();
            CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pCwmsObjectListListView);
        }
        else
        {
            ERR("No Columns to display!!");
        }

        CdmObjectContainer *pCont = pModel->GetContainer();

        if (pCont)
        {
            const CdmClass *pClass = pCont->GetClass();
            m_pEventClassEditor = new class::CwmsEventClassEditor(pClass, this);
        }
    }
}

QTreeView* CwmsObjectListEditorWidgetIf::GetListView()
{
    return m_pCwmsObjectListListView;
}

void CwmsObjectListEditorWidgetIf::UpdateTreeViewSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute();
        m_pCwmsObjectListListView->expandAll();
        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pCwmsObjectListListView);
    }
}

void CwmsObjectListEditorWidgetIf::NewClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CdmObject* pCdmObject = nullptr;
        CdmObjectContainer* pContainer = pModel->GetContainer();
        m_rpCdmObjectSelected = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());

        if(pContainer)
        {
            CdmObject* pCdmObjectParent = nullptr;

            if (pContainer->IsTree())
            {
                pCdmObjectParent = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());
            }

            const CdmClass *pClass = pContainer->GetClass();
            if(pClass->IsEventSourcingActive())
            {
                m_pEventClassEditor->FillCreateEventEditor();
                int iRet = CdmLogging::eDmFalse;
                iRet = m_pEventClassEditor->exec();
                if(iRet >= 0)
                {
                    CdmClass *pEventClass = m_pEventClassEditor->getSelectedEventClass();

                    CdmContainerManager *pContManager = pContainer->GetContainerManager();
                    QString qstrEventContainerName = "EventClassContainer";
                    pContManager->CreateContainer(pEventClass, qstrEventContainerName);
                    CdmObjectContainer *pEventContainer = pContManager->FindContainerByKeyname(qstrEventContainerName);
                    CdmObject *pEventObject = pEventContainer->CreateNewObject();

                    if(CwmsguiObjectEditorSelector::Create(pEventObject, this))
                    {
                        Refresh();
                    }
                }
            }
            else
            {
                pCdmObject = pContainer->CreateNewObject();

                if (CHKPTR(pCdmObject))
                {
                    // set default values from map
                    QMap<QString, StringPair>::iterator qmIt = m_qmDefaultValuesNewObject.begin();
                    QMap<QString, StringPair>::iterator qmItEnd = m_qmDefaultValuesNewObject.end();

                    for (; qmIt != qmItEnd; ++qmIt)
                    {
                        QString qstrValue = qmIt.key();

                        CdmValue* pCdmValue = pCdmObject->GetValue(qstrValue);

                        if (CHKPTR(pCdmValue))
                        {
                            StringPair strPair = qmIt.value();
                            pCdmValue->SetValue(strPair.first, strPair.second);
                        }
                    }

                    if (pCdmObjectParent)
                    {
                        pCdmObject->SetParentObject(pCdmObjectParent);
                    }

                    CdmObjectAdaptor adaptor(pCdmObject);
                    CdmClass *pCdmClass = pCdmObject->GetClass();
                    if(CHKPTR(pCdmClass))
                    {
                        if (CwmsguiObjectEditorSelector::Create(adaptor, this))
                        {
                            pCdmObject->Commit();
                            Refresh();
                        }
                    }
                }
            }
        }
    }
}

void CwmsObjectListEditorWidgetIf::EditClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        if (m_pqpbEdit->isVisible())
        {
            CdmObject* pCdmObject = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());

            m_rpCdmObjectSelected = pCdmObject;
            CdmContainerManager * pContManager = pCdmObject->GetContainerManager();
            QString qstrEventContName = "EventClassContainer";
            if (pCdmObject)
            {
                CdmClass *pClass = pCdmObject->GetClass();
                if(pClass->IsEventSourcingActive() || pClass->IsEventClass())
                {
                    CdmObjectContainer *pEventCont = pContManager->FindContainerByKeyname(qstrEventContName);
                    if(!pEventCont)
                    {
                        m_pEventClassEditor->FillUpdateEventEditor();
                        int iRet = m_pEventClassEditor->exec();
                        if(iRet >= 0)
                        {
                            CdmClass *pEventClass = m_pEventClassEditor->getSelectedEventClass();
                            if(pEventClass)
                            {
                                pContManager->CreateContainer(pEventClass, qstrEventContName);
                                pEventCont = pContManager->FindContainerByKeyname(qstrEventContName);
                                CdmObject *pEventObject = pEventCont->CreateNewObject();
                                pCdmObject->CopyValuesFromObjectToEventObject(pEventObject);
                                CwmsguiObjectEditorSelector::Edit(pEventObject, this);
                            }
                        }
                    }
                }
                else
                {
                    CwmsguiObjectEditorSelector::Edit(CdmObjectAdaptor(pCdmObject), this);
                }
                CdmObjectContainer *pEventCont = pContManager->FindContainerByKeyname(qstrEventContName);
                if(pEventCont)
                {
                    pContManager->DeleteContainer(pEventCont);
                }

                Refresh();
            }
        }
    }
}

void CwmsObjectListEditorWidgetIf::CopyObjectClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        if (m_pqpbEdit->isVisible())
        {
            CdmObject* pCdmObject = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());
            m_rpCdmObjectSelected = pCdmObject;
            pCdmObject = pCdmObject->GetObjectContainer()->CopyObject(pCdmObject);
            pCdmObject->Commit();
            Refresh();
        }
    }
}

void CwmsObjectListEditorWidgetIf::SetObjectInUseHandling(EwmsLvObjectInUseHandling p_eWmsLvObjectInUseHandling)
{
    m_eWmsLvObjectInUseHandling = p_eWmsLvObjectInUseHandling;
}

void CwmsObjectListEditorWidgetIf::DeleteClicekdSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        QModelIndexList qSelections;
        QItemSelectionModel* pSelection = m_pCwmsObjectListListView->selectionModel();
        QMap<CdmObject*, bool> qlSelectedObjects;
        bool bReferencedObjectFound = false;

        if (pSelection && pSelection->hasSelection())
        {
            qSelections = pSelection->selectedRows();
        }

        CdmClass* pCdmClass = nullptr;
        CdmObject* pCdmObject = nullptr;

        if (pSelection && pSelection->hasSelection())
        {
            pCdmObject = pModel->GetObject(qSelections[0]);
            pCdmClass = pCdmObject->GetClass();

            for (int iPos = 0; iPos < qSelections.count(); ++iPos)
            {
                pCdmObject = pModel->GetObject(qSelections[iPos]);
                if (CHKPTR(pCdmObject))
                {
                    IdmDataAccess* pIdmDataAccess = pCdmObject->GetDataAccess();
                    bool bObjectIsReferenced = (pIdmDataAccess->IsObjectUsed(pCdmObject) == CdmLogging::eDmTrue);
                    qlSelectedObjects.insert(pCdmObject, bObjectIsReferenced);

                    if (bObjectIsReferenced)
                    {
                        bReferencedObjectFound = true;
                    }
                }
            }
        }

        bool bContinue = false;
        bool bDeleteReferencedObjects = true;

        if(pCdmClass)
        {
            if(CdmMessageManager::Ask(tr("Objekte wirklich löschen?"),
                                      tr("Wollen Sie die Objekte wirklich löschen?")))
            {
                bContinue = true;
            }

            if (bReferencedObjectFound && m_eWmsLvObjectInUseHandling == eWmsLvWarning)
            {
                // Ask the user if he really wants to delete the object
                if(CdmMessageManager::Ask(tr("Wollen Sie wirklich löschen?"),
                                          tr("Ein oder mehrere Objekte werden noch refrenziert. Eine Löschung kann zu Inkonsistenzen in der Datenhaltung führen."
                                             "Wollen Sie referenzierte Objekte wirklich löschen?")))
                {
                    bDeleteReferencedObjects = true;
                }
            }
            else if (m_eWmsLvObjectInUseHandling == eWmsLvForbid)
            {
                // Inform the user, that it is not allowed to delete this object
                MSG_INFO(("Löschen von referenzierten Objekten nicht möglich"), ("Ein oder mehrere Objekte werden noch referenziert. Deshalb ist das Löschen dieser Objekte nicht möglich!"));
                bDeleteReferencedObjects = false;
            }

            if (bContinue)
            {
                QMap<CdmObject*, bool>::iterator qmIt = qlSelectedObjects.begin();
                QMap<CdmObject*, bool>::iterator qmItEnd = qlSelectedObjects.end();
                CdmObjectContainer* pContainer = nullptr;
                CdmClass* pClass = nullptr;
                CdmSession *pSession = CdmSessionManager::GetSessionManager()->FindSession();
                IdmEventStoreManager *pEventStoreManager = pSession->getEventStoreManager();
                int iRet = CdmLogging::eDmFalse;

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    bool bIsUsed = qmIt.value();
                    if (!bIsUsed || bDeleteReferencedObjects)
                    {
                        CdmObject* pObject = qmIt.key();

                        if (CHKPTR(pObject))
                        {
                            if (!pContainer)
                            {
                                pContainer = pObject->GetObjectContainer();
                            }

                            pClass = pObject->GetClass();
                            if(pClass->IsEventSourcingActive() || pClass->IsEventClass())
                            {
                                CdmContainerManager *pCdmContainerManager = pClass->GetContainerManager();
                                iRet = IdentificateAndSaveDeleteEvent(pObject, pCdmContainerManager, pEventStoreManager);
                                if(iRet > 0)
                                {
                                    pObject->SetDeleted();
                                }
                            }
                            else
                            {
                                pObject->SetDeleted();
                            }
                        }
                    }
                }

                if (pContainer)
                {
                    pContainer->Commit();
                    Refresh();
                }
            }
        }
    }
}

int CwmsObjectListEditorWidgetIf::IdentificateAndSaveDeleteEvent(CdmObject *pCdmObject, CdmContainerManager *p_pCdmContainerManager, IdmEventStoreManager *p_EventStoreManager)
{
    int iRet = CdmLogging::eDmFalse;

    CdmObjectContainer *pCdmEventObjectContainer = nullptr;
    CdmObject *pCdmEventObject = nullptr;
    QString qstrEventContainerKeyname = "EventClassContainer";
    QVariantList qvlParameters;

    pCdmEventObjectContainer = p_pCdmContainerManager->FindContainerByKeyname(qstrEventContainerKeyname);

    if(pCdmEventObjectContainer)
    {
        pCdmEventObject = pCdmEventObjectContainer->CreateNewObject();
        pCdmObject->CopyValuesFromObjectToEventObject(pCdmEventObject);
        if(CHKPTR(pCdmEventObject))
        {
            qvlParameters = StoreDeleteEvent(p_EventStoreManager, pCdmEventObject);
            IterateOverSubscribersAndExecuteFunction(p_EventStoreManager->getSubscribers(), qvlParameters);
            iRet = CdmLogging::eDmOk;
        }
    }
    else
    {
        INFO("EventContainer does not exist! Creating one.");

        CdmClass *pEventClass = pCdmObject->GetClass()->getSelectedEventClass();
        p_pCdmContainerManager->CreateContainer(pEventClass, qstrEventContainerKeyname);

        pCdmEventObjectContainer = p_pCdmContainerManager->FindContainerByKeyname(qstrEventContainerKeyname);
        pCdmEventObject = pCdmEventObjectContainer->CreateNewObject();
        pCdmObject->CopyValuesFromObjectToEventObject(pCdmEventObject);

        if(pCdmEventObject)
        {
            qvlParameters = StoreDeleteEvent(p_EventStoreManager, pCdmEventObject);
            IterateOverSubscribersAndExecuteFunction(p_EventStoreManager->getSubscribers(), qvlParameters);
            iRet = CdmLogging::eDmOk;
        }
    }
    p_EventStoreManager->DeleteContainersAfterSavingEvent(p_pCdmContainerManager, pCdmEventObjectContainer);
    return iRet;
}

QVariantList CwmsObjectListEditorWidgetIf::StoreDeleteEvent(IdmEventStoreManager *p_pEventStoreManager, CdmObject *pCdmEventObject)
{
    CdmClass *pEventClass = pCdmEventObject->GetClass();
    QString qstrEvent;
    QVariant qvEventObject;
    QVariant qvEventClass;
    QVariantList qvlParameters;

    qvEventClass = pEventClass->GetVariant();
    qvEventObject = pCdmEventObject->GetVariant();

    QVariantList qvlEventContentFormatted;
    qvlEventContentFormatted.append(p_pEventStoreManager->formatEventContent(qvEventClass, qvEventObject));
    qstrEvent = p_pEventStoreManager->getFormattedEventContentAsString(qvlEventContentFormatted);

    QObject *pEventDto = p_pEventStoreManager->createEventDtoObject(qvlEventContentFormatted);
    QVariant qvEventDto = QVariant::fromValue<QObject*>(pEventDto);
    qvlParameters.append(qvEventDto);
    p_pEventStoreManager->startEvent(qstrEvent);
    p_pEventStoreManager->stopEvent(qstrEvent, pEventDto);
    return qvlParameters;
}

void CwmsObjectListEditorWidgetIf::IterateOverSubscribersAndExecuteFunction(QList<CdmClassMethod*> ql_Subscribers, QVariantList qvlParameters)
{
    CdmExecutor *pExecutor = CdmExecutor::GetExecutor();
    QList<CdmClassMethod*>::Iterator qlItStart = ql_Subscribers.begin();
    QList<CdmClassMethod*>::Iterator qlItEnd = ql_Subscribers.end();
    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        QVariant qvFunction = pExecutor->GetFunction()->ExecuteFunctionStatic((*qlItStart), qvlParameters);
    }
}

void CwmsObjectListEditorWidgetIf::PrintClickedSlot()
{
    if (m_rpCdmPrintingTemplate)
    {
        CwmsReportManager::Print(m_rpCdmPrintingTemplate, GetContainer());
    }
    else
    {
        if (m_View.IsValid() && m_View.GetReport() != nullptr)
        {
            CwmsReportManager::Print(m_View.GetReport(), GetContainer());
        }
        else
        {
            CwmsReportManager::PrintDefaultForContainer(GetContainer());
        }
    }
}

void CwmsObjectListEditorWidgetIf::JournalClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsJournalViewer* pViewer = new CwmsJournalViewer(this);
        pViewer->FillDialog(pModel->GetContainer());
        pViewer->exec();
        DELPTR(pViewer);
    }
}

void CwmsObjectListEditorWidgetIf::SearchClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsSearchWindowDlg* pSearch = new CwmsSearchWindowDlg(this);

        QList<QString>::iterator qllIt = m_qllSearchMembers.begin();
        QList<QString>::iterator qllItEnd = m_qllSearchMembers.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            pSearch->AddSearchMember(*qllIt);
        }

        pSearch->FillDialog(pModel->GetContainer());
        pSearch->exec();
        DELPTR(pSearch);
    }
}

void CwmsObjectListEditorWidgetIf::ImportClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsImExportManager cManager;

        QMap<QString, QString> qmConfigurations = cManager.GetImportConfiguration(pModel->GetContainer()->GetClassId());

        if (qmConfigurations.count() == 0)
        {
            OpenImportConfigurator();
        }
        else
        {
            QStringList qstrlKeys = qmConfigurations.keys();
            QMenu qMenu(this);

            for (int iCounter = 0;
                 iCounter < qstrlKeys.count();
                 ++iCounter)
            {
                QAction* pAction = new QAction(qstrlKeys[iCounter], &qMenu);
                qMenu.addAction(pAction);
            }

            qMenu.addSeparator();
            QAction* pAction = new QAction(tr("<Konfiguration...>"), &qMenu);
            qMenu.addAction(pAction);
            pAction = qMenu.exec(QCursor::pos());

            if (pAction)
            {
                if (pAction->text() == tr("<Konfiguration...>"))
                {
                    OpenImportConfigurator();
                }
                else
                {
                    CwmsImportSettings cCwmsImportSettings;
                    cCwmsImportSettings.LoadSettings(pAction->text(), qmConfigurations[pAction->text()]);
                    CwmsImport cImport;
                    cImport.StartImport(pModel->GetContainer(), cCwmsImportSettings);

                    MSG_INFO(("Import beendet"), ("Der Import wurde abgeschlossen."));
                }

                Refresh();
            }
        }
    }
}


void CwmsObjectListEditorWidgetIf::OpenImportConfigurator()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsImportSettings cCwmsImportSettings;
        cCwmsImportSettings.SetContainer(pModel->GetContainer());
        CwmsImport cImport;
        CwmsImportDlg cImportDlg(&cCwmsImportSettings, &cImport, this);

        if (cImportDlg.exec() == QDialog::Accepted)
        {
            cImport.StartImport(pModel->GetContainer(), cCwmsImportSettings);
        }
    }
}


void CwmsObjectListEditorWidgetIf::ExportClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsImExportManager cManager;

        QMap<QString, QString> qmConfigurations = cManager.GetExportConfiguration(pModel->GetContainer()->GetClassId());

        if (qmConfigurations.count() == 0)
        {
            OpenExportConfigurator();
        }
        else
        {
            QStringList qstrlKeys = qmConfigurations.keys();
            QMenu qMenu(this);

            for (int iCounter = 0;
                 iCounter < qstrlKeys.count();
                 ++iCounter)
            {
                QAction* pAction = new QAction(qstrlKeys[iCounter], &qMenu);
                qMenu.addAction(pAction);
            }

            qMenu.addSeparator();
            QAction* pAction = new QAction(tr("<Konfiguration...>"), &qMenu);
            qMenu.addAction(pAction);
            pAction = qMenu.exec(QCursor::pos());

            if (pAction)
            {
                if (pAction->text() == tr("<Konfiguration...>"))
                {
                    OpenExportConfigurator();
                }
                else
                {
                    CwmsExportSettings cCwmsExportSettings;
                    cCwmsExportSettings.Load(pAction->text(), qmConfigurations[pAction->text()]);
                    cCwmsExportSettings.SetContainerId(pModel->GetContainer()->GetId());

                    if (cCwmsExportSettings.GetQuery().isEmpty())
                    {
                        if (!m_qstrWQL.isEmpty())
                        {
                            cCwmsExportSettings.SetQuery(m_qstrWQL);
                        }
                        else
                        {
                            cCwmsExportSettings.SetQuery(pModel->GetQuery());
                        }
                    }

                    CwmsExportWriter cCwmsExportFileWriter(cCwmsExportSettings);
                    cCwmsExportFileWriter.Export();
                    MSG_INFO(("Export beendet"), ("Der Export wurde abgeschlossen."));
                }
            }
        }
    }
}

void CwmsObjectListEditorWidgetIf::OpenExportConfigurator()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CwmsExportSettings cCwmsExportSettings;
        cCwmsExportSettings.SetContainerId(pModel->GetContainer()->GetId());
        cCwmsExportSettings.SetSchemeId(pModel->GetContainer()->GetSchemeId());
        cCwmsExportSettings.SetClassId(pModel->GetContainer()->GetClassId());
        cCwmsExportSettings.SetQuery(pModel->GetQuery());

        CwmsExportSettingsIf* pCwmsExportSettingsIf = new CwmsExportSettingsIf(cCwmsExportSettings, nullptr);
        pCwmsExportSettingsIf->FillDialog();
        pCwmsExportSettingsIf->exec();
        delete pCwmsExportSettingsIf;
    }
}

void CwmsObjectListEditorWidgetIf::SetModel(CdmQueryModel* p_pModel)
{
    if (CHKPTR(p_pModel))
    {
        CdmObjectContainer* pTempContainer = nullptr;
        auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

        if (pModel != nullptr)
        {
            if (p_pModel->GetContainer() == nullptr && m_pModel)
            {
                pTempContainer = p_pModel->GetContainer();
            }
        }

        if (m_pModel)
        {
            DELPTR(m_pModel);
        }

        m_pModel = p_pModel;

        if (pTempContainer)
        {
            p_pModel->SetContainer(pTempContainer);
        }
    }
}

void CwmsObjectListEditorWidgetIf::UnsetProxy()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute("");
    }
}

void CwmsObjectListEditorWidgetIf::SetNewAndDeleteButtonVisibily(bool p_bVisible)
{
    if(!p_bVisible)
    {
        m_pqpbDelete->hide();
        m_pqpbNew->hide();
        m_qstrlContextMenuItems.clear();
    }
    else
    {
        m_pqpbDelete->show();
        m_pqpbNew->show();
    }
}

void CwmsObjectListEditorWidgetIf::SetDefaultValueForNewObject(QString p_qstrValueName,
                                                               QString p_qstrValue,
                                                               QString p_qstrValue2)
{
    m_qmDefaultValuesNewObject.insert(p_qstrValueName, StringPair(p_qstrValue, p_qstrValue2));
}

void CwmsObjectListEditorWidgetIf::ClearMenu()
{
    m_qstrlContextMenuItems.clear();
}

void CwmsObjectListEditorWidgetIf::AddPopupItem(QString p_qstrItem)
{
    m_qstrlContextMenuItems.append(p_qstrItem);
}

void CwmsObjectListEditorWidgetIf::setSelected(CdmObject* pCdmObject)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CdmQuery* pCdmQuery = pModel->GetQuery();

        if (pCdmQuery && pCdmObject)
        {
            CwmsTreeWidgetHelper::SelectObject(m_pCwmsObjectListListView, pCdmObject);
        }
    }
}

CdmObjectContainer* CwmsObjectListEditorWidgetIf::GetContainer()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        return pModel->GetQuery()->GetContainer();
    }

    return nullptr;
}

void CwmsObjectListEditorWidgetIf::SetView(CwmsView p_cCwmsView)
{
    m_View.SetObject(p_cCwmsView.GetObject());
    if (m_View.IsValid())
    {
        if (m_View.IsWql())
        {
            auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

            if (pModel == nullptr)
            {
                DELPTR(m_pModel);
                m_pModel = new CdmQueryModel();
                pModel = dynamic_cast<CdmQueryModel*>(m_pModel);
            }

            if (pModel != nullptr)
            {
                pModel->Execute(p_cCwmsView.GetViewCommand());
            }

            m_pCwmsObjectListListView->setModel(m_pModel);
        }
        else if (m_View.IsModel())
        {
            m_pModel = m_View.GetModel();
            m_pCwmsObjectListListView->setModel(m_pModel);
            HideCopyButton();
            HideExportButton();
            HideImportButton();
            HideJournalButton();

            if (m_View.GetReport() == nullptr)
            {
                HidePrintButton();
            }
            else
            {
                m_pqpbPrint->show();
            }

            //HideRefreshButton();
            HideSearchButton();
            m_pqpbNew->hide();
            m_pqpbEdit->hide();
            m_pqpbDelete->hide();
        }

        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pCwmsObjectListListView);
    }
}

void CwmsObjectListEditorWidgetIf::SetQuery(QString p_qstrWQL)
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        m_qstrWQL = p_qstrWQL;
        pModel->Execute(p_qstrWQL);
        m_pCwmsObjectListListView->setModel(pModel);
        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pCwmsObjectListListView);
    }
}

void CwmsObjectListEditorWidgetIf::CustomContextMenuSlot(const QPoint& p_Pos)
{
    Q_UNUSED(p_Pos);

    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        CdmObject* pCdmObject = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());

        if(CHKPTR(pCdmObject))
        {
            QMenu* pqMenu = new QMenu(this);

            for (int iCounter = 0; iCounter < m_qstrlContextMenuItems.count(); ++iCounter)
            {
                pqMenu->addAction(m_qstrlContextMenuItems[iCounter]);
            }

            QAction* pqaAction = pqMenu->exec(QCursor::pos());

            if (pqaAction)
            {
                QString qstrAction = pqaAction->text();
                ContextMenuAction(qstrAction);
            }

            DELPTR(pqMenu);
        }
    }
}

void CwmsObjectListEditorWidgetIf::ContextMenuAction(QString p_qstrAction)
{
    if (p_qstrAction == tr("Neu"))
    {
        NewClickedSlot();
    }
    else if (p_qstrAction == tr("Bearbeiten") ||
             p_qstrAction == tr("Ansicht"))
    {
        EditClickedSlot();
    }
    else if (p_qstrAction == tr("Löschen"))
    {
        DeleteClicekdSlot();
    }
    else if (p_qstrAction == tr("Drucken"))
    {
        PrintClickedSlot();
    }
    else
    {
        emit ContextMenuActionSignal(p_qstrAction);
    }
}

void CwmsObjectListEditorWidgetIf::ConnectRuntime(CwmsRuntime* p_pCwmsRuntime,
                                                  CwmsApplicationModule p_cModule)
{
    if (p_pCwmsRuntime)
    {
        QMenuBar* pMenuBar = p_pCwmsRuntime->QMainWindow::menuBar();

        if (CHKPTR(pMenuBar))
        {
            m_pMenu = pMenuBar->addMenu(tr(p_cModule.GetName().toUtf8()));
            p_pCwmsRuntime->SetCurrentModuleMenu(m_pMenu);
        }

        m_pToolBar = new QToolBar(tr(p_cModule.GetName().toUtf8()));
        p_pCwmsRuntime->AddToolBar(m_pToolBar);

        QAction* pAction = new QAction(tr("Neu"), this);
        QIcon iconNew;
        iconNew.addFile(QStringLiteral(":/icons/new24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pAction->setIcon(iconNew);
        m_pMenu->addAction(pAction);
        m_pToolBar->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(NewClickedSlot()));
        m_pqpbNew->hide();

        pAction = new QAction(tr("Bearbeiten"), this);
        QIcon iconEdit;
        iconEdit.addFile(QStringLiteral(":/icons/edit24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pAction->setIcon(iconEdit);
        m_pMenu->addAction(pAction);
        m_pToolBar->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(EditClickedSlot()));
        m_pqpbEdit->hide();

        pAction = new QAction(tr("Löschen"), this);
        QIcon iconDelete;
        iconDelete.addFile(QStringLiteral(":/icons/delete24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pAction->setIcon(iconDelete);
        m_pMenu->addAction(pAction);
        m_pToolBar->addAction(pAction);
        connect(pAction, SIGNAL(triggered()), this, SLOT(DeleteClicekdSlot()));
        m_pqpbDelete->hide();

        if (!m_pqpbExport->isHidden())
        {
            pAction = new QAction(tr("Exportieren"), this);
            QIcon iconExport;
            iconExport.addFile(QStringLiteral(":/icons/export24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconExport);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(ExportClickedSlot()));
            m_pqpbExport->hide();
        }

        if (!m_pqpbImport->isHidden())
        {
            pAction = new QAction(tr("Importieren"), this);
            QIcon iconImport;
            iconImport.addFile(QStringLiteral(":/icons/import24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconImport);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(ImportClickedSlot()));
            m_pqpbImport->hide();
        }

        if (!m_pqpbPrint->isHidden())
        {
            pAction = new QAction(tr("Drucken"), this);
            QIcon iconPrint;
            iconPrint.addFile(QStringLiteral(":/icons/print24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconPrint);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(PrintClickedSlot()));
            m_pqpbPrint->hide();
        }

        if (!m_pqpbSearch->isHidden())
        {
            pAction = new QAction(tr("Suchen"), this);
            QIcon iconSearch;
            iconSearch.addFile(QStringLiteral(":/icons/search24.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconSearch);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(SearchClickedSlot()));
            m_pqpbSearch->hide();
        }

        if (!m_pqpbJournal->isHidden())
        {
            pAction = new QAction(tr("Journal"), this);
            QIcon iconJournal;
            iconJournal.addFile(QStringLiteral(":/icons/print-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
            pAction->setIcon(iconJournal);
            m_pMenu->addAction(pAction);
            m_pToolBar->addAction(pAction);
            connect(pAction, SIGNAL(triggered()), this, SLOT(JournalClickedSlot()));
            m_pqpbJournal->hide();
        }
    }
}

void CwmsObjectListEditorWidgetIf::SetFormBase(CwmsFormContainer p_cForm)
{
    if (p_cForm.IsValid())
    {
        if (!p_cForm.GetExportEnabled())
        {
            m_pqpbExport->hide();
        }

        if (!p_cForm.GetImportEnabled())
        {
            m_pqpbImport->hide();
        }

        if (!p_cForm.GetJournalEnabled())
        {
            m_pqpbJournal->hide();
        }

        SetReadOnly(p_cForm.GetReadOnly());

        if (!p_cForm.GetSearchEnabled())
        {
            m_pqpbSearch->hide();
        }

        if (!p_cForm.GetPrintEnabled())
        {
            m_pqpbPrint->hide();
        }

        if (!p_cForm.GetCopyEnabled())
        {
            m_pqpbCopy->hide();
        }

        if (!p_cForm.GetSaveAsCsvEnabled())
        {
            m_pqpbSaveAsCsv->hide();
        }

        setWindowTitle(p_cForm.GetName());
    }
}

void CwmsObjectListEditorWidgetIf::SetModule(CwmsApplicationModule p_cModule)
{
    if (p_cModule.IsValid())
    {
        CdmObject* pCdmObjectUserInterface = p_cModule.GetUserInterface();

        if (!pCdmObjectUserInterface)
        {
            CdmObject* pCdmObjectView = p_cModule.GetView();

            if (pCdmObjectView)
            {
                SetView(CwmsView(pCdmObjectView));
            }
            else
            {
                SetContainer(p_cModule.GetContainerModule());

                auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

                if (pModel != nullptr)
                {
                    if (pModel->columnCount() == 0)
                    {
                        pModel->AddAllMembers();
                    }
                }
            }
        }
        else
        {
            if (pCdmObjectUserInterface->IsTypeOf("Technical_Form_Standard_ObjectList"))
            {
                SetContainer(p_cModule.GetContainerModule());
                SetFormConfiguration(pCdmObjectUserInterface);

            }
            else
            {
                ERR("Wrong Form Defintion for this Widget");
            }
        }
    }
}

void CwmsObjectListEditorWidgetIf::SetFormConfiguration(CdmObject* p_pCdmObejct)
{
    if (p_pCdmObejct->IsTypeOf("Technical_Form_Standard_ObjectList"))
    {
        CwmsFormStandardContainer cForm(p_pCdmObejct);
        SetFormBase(cForm);
        SetFormStandard(cForm);

        QList<QString> qllFucntions = cForm.GetFunctions();

        QList<QString>::iterator qllIt = qllFucntions.begin();
        QList<QString>::iterator qllItEnd = qllFucntions.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            m_qstrlFunctions.append(*qllIt);
        }
    }
    else
    {
        ERR("Wrong Form Defintion for this Widget");
    }
}

void CwmsObjectListEditorWidgetIf::SetFormStandard(CwmsFormStandardContainer p_cForm)
{
    if (p_cForm.IsValid())
    {
        CdmObject* pCdmObjectView = p_cForm.GetView();

        if (pCdmObjectView)
        {
            SetView(CwmsView(pCdmObjectView));
        }
        else
        {
            QList<QString> qllDisplayMembers = p_cForm.GetDisplayMembers();

            QList<QString>::iterator qllIt = qllDisplayMembers.begin();
            QList<QString>::iterator qllItEnd = qllDisplayMembers.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                AddColumn(*qllIt);
            }

            m_qllSearchMembers = p_cForm.GetSearchMembers();
        }
    }
}

void CwmsObjectListEditorWidgetIf::Initialize(CwmsApplicationModule p_cModule,
                                              CwmsRuntime* p_pRuntime)
{
    SetModule(p_cModule);
    ConnectRuntime(p_pRuntime, p_cModule);
    FillDialog();
}

void CwmsObjectListEditorWidgetIf::SetReadOnly(bool p_bReadOnly)
{
    if (p_bReadOnly)
    {
        m_pqpbDelete->hide();
        m_pqpbEdit->hide();
        m_pqpbImport->hide();
        m_pqpbNew->hide();
        disconnect(m_pCwmsObjectListListView, SIGNAL(doubleClicked(QModelIndex)), m_pCwmsObjectListListView, SLOT(EditClickedSlot()));
    }
    else
    {
        m_pqpbDelete->show();
        m_pqpbEdit->show();
        m_pqpbImport->show();
        m_pqpbNew->show();
    }
}

void CwmsObjectListEditorWidgetIf::AddFunctions()
{
    for (int iCounter = 0; iCounter < m_qstrlFunctions.count(); ++iCounter)
    {
        CdmObjectContainer* pList = GetContainer();

        if (CHKPTR(pList))
        {
            const CdmClass* pClass = pList->GetClass();

            if (CHKPTR(pClass))
            {
                QString qstrFunction = m_qstrlFunctions[iCounter];
                CdmClassMethod* pMethod = (const_cast<CdmClass*>(pClass))->GetMethod(qstrFunction);

                if (CHKPTR(pMethod) &&
                        pMethod->GetAccess() == eDmMemberAccessPublic &&
                        pMethod->GetParameterCount() == 0)
                {
                    QPushButton* pButton = new QPushButton(this);
                    QPixmap qPixmap = pMethod->GetIcon();

                    if (!qPixmap.isNull())
                    {
                        pButton->setIcon(QIcon(qPixmap));
                        pButton->setIconSize(QSize(24,24));
                        pButton->setToolTip(pMethod->GetCaption());
                    }
                    else
                    {
                        pButton->setText(pMethod->GetCaption());
                        pButton->setToolTip(pMethod->GetCaption());
                    }

                    if (m_pMenu && m_pToolBar)
                    {
                        QAction* pAction = new QAction(pMethod->GetCaption(), this);
                        pAction->setIcon(QIcon(qPixmap));
                        m_pMenu->addAction(pAction);
                        m_pToolBar->addAction(pAction);
                        connect(pAction, SIGNAL(triggered()), this, SLOT(FunctionClickedSlot()));
                    }

                    int iWidgetCount = m_pqhbFunctions->count() - 1;
                    m_pqhbFunctions->insertWidget(iWidgetCount, pButton);
                    m_qmFunctionMapping.insert(pButton, qstrFunction);
                    connect(pButton, SIGNAL(clicked()), this, SLOT(FunctionClickedSlot()));
                }
            }
        }
    }
}

void CwmsObjectListEditorWidgetIf::FunctionClickedSlot()
{
    QPushButton* pButton = (QPushButton*)sender();

    if (CHKPTR(pButton))
    {
        if (m_qmFunctionMapping.contains(pButton))
        {
            QString qstrFunction = m_qmFunctionMapping[pButton];

            CdmObjectContainer* pList = GetContainer();

            if (CHKPTR(pList))
            {
                const CdmClass* pClass = pList->GetClass();

                if (CHKPTR(pClass))
                {
                    CdmClassMethod* pMethod = (const_cast<CdmClass*>(pClass))->GetMethod(qstrFunction);

                    if (pMethod)
                    {
                        if(!pMethod->IsStatic())
                        {
                            auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

                            if (pModel != nullptr)
                            {
                                CdmObject* pObject = pModel->GetObject(m_pCwmsObjectListListView->currentIndex());

                                if (pObject)
                                {
                                    QVariantList qList;
                                    CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, pObject, qList);
                                }
                                else
                                {
                                    MSG_CRIT("Objekt nicht gewählt",
                                             "Zur Ausführung der Funktion muss ein Objekt in der Liste ausgewählt werden!");
                                }
                            }
                        }
                        else
                        {
                            QVariantList qList;
                            CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, nullptr, qList);
                        }
                    }
                    else
                    {
                        MSG_CRIT("Funktion nicht gefunden", "Die Funktion wurde nicht gefunden.");
                    }

                }
            }
        }
    }

}

void CwmsObjectListEditorWidgetIf::HidePrintButton()
{
    m_pqpbPrint->hide();
}

void CwmsObjectListEditorWidgetIf::HideJournalButton()
{
    m_pqpbJournal->hide();
}

void CwmsObjectListEditorWidgetIf::HideExportButton()
{
    m_pqpbExport->hide();
}

void CwmsObjectListEditorWidgetIf::HideImportButton()
{
    m_pqpbImport->hide();
}

void CwmsObjectListEditorWidgetIf::HideSearchButton()
{
    m_pqpbSearch->hide();
}

void CwmsObjectListEditorWidgetIf::HideRefreshButton()
{
    m_pqpbSearch->hide();
}

void CwmsObjectListEditorWidgetIf::HideCopyButton()
{
    m_pqpbCopy->hide();
}

void CwmsObjectListEditorWidgetIf::HideNewButton()
{
    m_pqpbNew->hide();
}

void CwmsObjectListEditorWidgetIf::HideDeleteButton()
{
    m_pqpbDelete->hide();
}

void CwmsObjectListEditorWidgetIf::HideSaveAsCsvButton()
{
    m_pqpbSaveAsCsv->hide();
}

void CwmsObjectListEditorWidgetIf::SaveAsCsvClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(*m_pModel);
}

void CwmsObjectListEditorWidgetIf::QMLGeneratorClickedSlot()
{
    NOTIMPLEMENTED;
}

void CwmsObjectListEditorWidgetIf::MetaDataClickedSlot()
{
    CdmObjectContainer* pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        QString qstrText = pContainer->GetInfo();
        CwmsHelp::ShowTextHelp(qstrText, this);
    }

}

void CwmsObjectListEditorWidgetIf::RefreshClickedSlot()
{
    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel != nullptr)
    {
        pModel->Execute();
        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pCwmsObjectListListView);
    }
    else if (m_View.IsValid())
    {
        DELPTR(m_pModel);
        m_pModel = m_View.GetModel();
        m_pCwmsObjectListListView->setModel(m_pModel);
    }
}
