// System and QT Includes
#include <QMenu>
#include <QAction>
#include <qtoolbar.h>
#include <CwmsQueryModelExportCsv.h>

// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmObject.h"
#include "CdmRights.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsReportManager.h"
#include "CwmsImExportManager.h"
#include "CwmsExportSettings.h"
#include "CwmsExportFileWriter.h"
#include "CwmsPrintingTemplate.h"
#include "IwmsPrinting.h"
#include "CwmsExportSettingsIf.h"
#include "CwmsImport.h"
#include "CwmsImportDlg.h"
#include "CwmsFormSearch.h"
#include "CwmsRuntime.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsSearchWindow.h"


CwmsSearchWindow::CwmsSearchWindow(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_pCdmQuery(nullptr),
  m_rpCdmPrintingTemplate(nullptr),
  m_pMenu(nullptr),
  m_pToolBar(nullptr)
{
   setupUi(this);
   m_pqtvResult->setModel(&m_CdmModel);
}

CwmsSearchWindow::~CwmsSearchWindow()
{
   // change of ownership of m_pCdmQuery
   // m_pCdmQuery will be deleted by Model
}

void CwmsSearchWindow::AddSearchMember(QString p_qstrSearchMember)
{
   m_pCwmsSearchWidget->AddSearchMember(p_qstrSearchMember);
}

void CwmsSearchWindow::FillDialog(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))     
   {
      connect(m_pCwmsSearchWidget, SIGNAL(SearchSignal()), this, SLOT(SearchSlot()));
      m_pCwmsSearchWidget->SetObjectList(p_pContainer);
      m_pCwmsSearchWidget->FillWidget();
   }
}

void CwmsSearchWindow::FillDialog(CdmClass* p_pClass)
{
   if (CHKPTR(p_pClass))
   {
      connect(m_pCwmsSearchWidget, SIGNAL(SearchSignal()), this, SLOT(SearchSlot()));
      m_pCwmsSearchWidget->SetClass(p_pClass);
      m_pCwmsSearchWidget->FillWidget();
   }
}

void CwmsSearchWindow::SetEditVisibility(bool p_bVisible)
{
    if (!p_bVisible)
    {
        m_pqpbEdit->hide();
    }
    else
    {
        m_pqpbEdit->show();
    }
}

void CwmsSearchWindow::SetDeleteVisibility(bool p_bVisible)
{
    if (!p_bVisible)
    {
        m_pqpbDelete->hide();
    }
    else
    {
        m_pqpbDelete->show();
    }
}

void CwmsSearchWindow::SetImportVisibility(bool p_bVisible)
{
    if (!p_bVisible)
    {
        m_pqpbImport->hide();
    }
    else
    {
        m_pqpbImport->show();
    }
}

void CwmsSearchWindow::SetExportVisibility(bool p_bVisible)
{
    if (!p_bVisible)
    {
        m_pqpbExport->hide();
    }
    else
    {
        m_pqpbExport->show();
    }
}

void CwmsSearchWindow::SetPrintVisibility(bool p_bVisible)
{
    if (!p_bVisible)
    {
        m_pqpbPrint->hide();
    }
    else
    {
        m_pqpbPrint->show();
    }
}

void CwmsSearchWindow::EditClickedSlot()
{
   CdmObject* pCdmObject = m_CdmModel.GetObject(m_pqtvResult->currentIndex());

   if (pCdmObject)
   {
      CwmsguiObjectEditorSelector::Edit(CdmObjectAdaptor(pCdmObject), this);
   }
}

CdmObject* CwmsSearchWindow::GetSelectedObject()
{
    return m_CdmModel.GetObject(m_pqtvResult->currentIndex());
}

QList<CdmObject*> CwmsSearchWindow::GetSelectedObjects()
{
    return m_CdmModel.GetObjects(m_pqtvResult);
}

void CwmsSearchWindow::DeleteClickedSlot()
{
    QModelIndexList qSelections;
    QItemSelectionModel* pSelection = m_pqtvResult->selectionModel();
    QMap<CdmObject*, bool> qlSelectedObjects;
    bool bReferencedObjectFound = false;

    if (pSelection && pSelection->hasSelection())
    {
        qSelections = pSelection->selectedRows();
    }

    for (int iPos = 0; iPos < qSelections.count(); ++iPos)
    {
        CdmObject* pCdmObject = m_CdmModel.GetObject(qSelections[iPos]);
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

    bool bContinue = false;
    bool bDeleteReferencedObjects = false;

    if(CdmMessageManager::Ask(QStringLiteral("Objekte wirklich löschen?"),
                              QStringLiteral("Wollen Sie die Objekte wirklich löschen?")))
    {
       bContinue = true;
    }

    if (bReferencedObjectFound)
    {
       // Ask the user if he really wants to delete the object
       if(CdmMessageManager::Ask(QStringLiteral("Wollen Sie wirklich löschen?"),
          QStringLiteral("Ein oder mehrere Objekte werden noch refrenziert. Eine Löschung kann zu Inkonsistenzen in der Datenhaltung führen."
          "Wollen Sie referenzierte Objekte wirklich löschen?")))
       {
          bDeleteReferencedObjects = true;
       }
    }

  if (bContinue)
  {
        QMap<CdmObject*, bool>::iterator qmIt = qlSelectedObjects.begin();
        QMap<CdmObject*, bool>::iterator qmItEnd = qlSelectedObjects.end();
        CdmObjectContainer* pContainer = nullptr;

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

                    pObject->SetDeleted();
                }
            }
        }

        if (pContainer)
        {
            pContainer->Commit();
            SearchSlot();
        }
  }

}

void CwmsSearchWindow::SearchSlot()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QTime qStart = QTime::currentTime();
   m_pCdmQuery = new CdmQuery();
   m_pCwmsSearchWidget->CreateQuery(*m_pCdmQuery);
   AddResultMembers();
   // change of ownership of m_pCdmQuery
   m_CdmModel.Execute(m_pCdmQuery);
   QTime qEnd = QTime::currentTime();
   m_pqleDuration->setText(QString::number(qStart.msecsTo(qEnd)) + " msecs");
   m_pqleResultCount->setText(QString::number(m_pCdmQuery->GetResultCount()) + " Objekte");
   m_pqtvResult->setModel(&m_CdmModel);
   QApplication::restoreOverrideCursor();
}

void CwmsSearchWindow::AddResultMember(QString p_qstrMember)
{
    m_qllResultMembers.append(p_qstrMember);
}

void CwmsSearchWindow::AddResultMembers()
{
   if (m_qllResultMembers.count() > 0)
   {
      QList<QString>::iterator qllIt = m_qllResultMembers.begin();
      QList<QString>::iterator qllItEnd = m_qllResultMembers.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         m_pCdmQuery->AddResultElement(*qllIt);
      }
   }
   else
   {
       m_pCdmQuery->AddAllMembers();
   }
}

void CwmsSearchWindow::NewClickedSlot()
{
    CdmObject* pCdmObject = nullptr;
    CdmObjectContainer* pContainer = m_CdmModel.GetContainer();

    if(pContainer)
    {
       CdmObject* pCdmObjectParent = nullptr;

       if (pContainer->IsTree())
       {
          pCdmObjectParent = m_CdmModel.GetObject(m_pqtvResult->currentIndex());
       }

       pCdmObject = pContainer->CreateNewObject();

       if (CHKPTR(pCdmObject))
       {
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
                  SearchSlot();
              }
          }
       }
   }
}

void CwmsSearchWindow::CopyClickedSlot()
{
    if (m_pqpbEdit->isVisible())
    {
        CdmObject* pCdmObject = m_CdmModel.GetObject(m_pqtvResult->currentIndex());
        pCdmObject = pCdmObject->GetObjectContainer()->CopyObject(pCdmObject);
        pCdmObject->Commit();
        SearchSlot();
    }
}

void CwmsSearchWindow::SaveAsCsvClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(m_CdmModel);
}

void CwmsSearchWindow::PrintClickedSlot()
{
   if (m_rpCdmPrintingTemplate)
   {
      Print(m_rpCdmPrintingTemplate);
   }
   else
   {
      Print();
   }
}

void CwmsSearchWindow::Print(CdmObject* p_pCdmObject)
{
   CwmsPrintingTemplate cTemplate(p_pCdmObject);

   if (cTemplate.IsValid())
   {
       IwmsPrinting* pPrinting = CwmsReportManager::GetPrintingObject();

       if (CHKPTR(pPrinting))
       {
           pPrinting->AddObjectContainer("ObjectContainer", m_pCdmQuery->GetContainer());
           pPrinting->SetTemplate(cTemplate);
           pPrinting->Print();
           DELPTR(pPrinting);
       }
   }
}

void CwmsSearchWindow::Print()
{
   CwmsReportManager cReportManager;  
   QString qstrTemplate;
   CdmObjectContainer* pList = m_pCdmQuery->GetContainer();
   CdmQuery* pQuery = nullptr;

   if (CHKPTR(pList))
   {
      const CdmClass* pClass = pList->GetClass();

      if (CHKPTR(pClass))
      {
         pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(), 
                                                          eWmsTemplateTypeList);
      }
   }

   if (pQuery)
   {
      int iResultCount = pQuery->GetResultCount();

      if (iResultCount > 0)
      {
         for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
         {
            QString qstrName = pQuery->GetResultAt(0, iCounter).toString();
            bool bDefault = pQuery->GetResultAt(1, iCounter).toBool();

            if (iCounter == 0)
            {
               qstrTemplate = qstrName;
            }

            if (bDefault)
            {
               qstrTemplate = qstrName;
               break;
            }
         }
      }

      DELPTR(pQuery);
   }

   if (!qstrTemplate.isEmpty())
   {
      CwmsPrintingTemplate cTemplate = cReportManager.GetReport(qstrTemplate);
      Print(cTemplate.GetObject());
   }
}

void CwmsSearchWindow::ImportClickedSlot()
{

   CwmsImExportManager cManager;
   CdmObjectContainer* pContainer = m_CdmModel.GetContainer();

   if (pContainer)
   {
       QMap<QString, QString> qmConfigurations = cManager.GetImportConfiguration(pContainer->GetClassId());

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
                cImport.StartImport(m_CdmModel.GetContainer(), cCwmsImportSettings);

                MSG_INFO(("Import beendet"),
                                               ("Der Import wurde abgeschlossen."));
             }
          }
       }
   }
   else
   {
       MSG_INFO("Import nicht möglich",
                "Import kann nicht gestartet werden, das Suche noch nicht ausgeführt wurde oder ungültig ist.");
   }
}

void CwmsSearchWindow::OpenImportConfigurator()
{

   CwmsImportSettings cCwmsImportSettings;
   cCwmsImportSettings.SetContainer(m_CdmModel.GetContainer());
   CwmsImport cImport;
   CwmsImportDlg cImportDlg(&cCwmsImportSettings, &cImport, this);

   if (cImportDlg.exec() == QDialog::Accepted)
   {

      cImport.StartImport(m_CdmModel.GetContainer(), cCwmsImportSettings);
   }
}

void CwmsSearchWindow::ExportClickedSlot()
{
   CwmsImExportManager cManager;

   CdmObjectContainer* pContainer = m_CdmModel.GetContainer();

   if (pContainer)
   {
       QMap<QString, QString> qmConfigurations = cManager.GetExportConfiguration(pContainer->GetClassId());

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
                cCwmsExportSettings.SetContainerId(m_CdmModel.GetContainer()->GetId());
                cCwmsExportSettings.SetQuery(m_pCdmQuery);
                CwmsExportWriter cCwmsExportFileWriter(cCwmsExportSettings);
                cCwmsExportFileWriter.Export();
                MSG_INFO(("Export beendet"),
                                               ("Der Export wurde abgeschlossen."));
             }
          }

       }
   }
   else
   {
       MSG_INFO(("Export nicht möglich"), ("Export kann nicht gestartet werden, das Suche noch nicht ausgeführt wurde oder ungültig ist."));
   }
}

void CwmsSearchWindow::OpenExportConfigurator()
{
   CwmsExportSettings cCwmsExportSettings;
   cCwmsExportSettings.SetContainerId(m_CdmModel.GetContainer()->GetId());
   cCwmsExportSettings.SetSchemeId(m_CdmModel.GetContainer()->GetSchemeId());
   cCwmsExportSettings.SetClassId(m_CdmModel.GetContainer()->GetClassId());
   cCwmsExportSettings.SetQuery(m_pCdmQuery);

   CwmsExportSettingsIf* pCwmsExportSettingsIf = new CwmsExportSettingsIf(cCwmsExportSettings, nullptr);
   pCwmsExportSettingsIf->FillDialog();
   pCwmsExportSettingsIf->exec();
   delete pCwmsExportSettingsIf;
}

void CwmsSearchWindow::ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule p_cModule)
{
   if (p_pRuntime)
   {
      m_pToolBar = p_pRuntime->addToolBar(tr(p_cModule.GetName().toUtf8()));
      p_pRuntime->AddToolBar(m_pToolBar);
      QMenuBar* pMenuBar = p_pRuntime->QMainWindow::menuBar();

      if (CHKPTR(pMenuBar))
      {
         m_pMenu = pMenuBar->addMenu(tr(p_cModule.GetName().toUtf8()));
         p_pRuntime->SetCurrentModuleMenu(m_pMenu);
      }

      QAction* pAction = new QAction(tr("Bearbeiten"), this);
      QIcon iconEdit;
      iconEdit.addFile(QStringLiteral(":/icons/edit24.png"), QSize(), QIcon::Normal, QIcon::Off);
      pAction->setIcon(iconEdit);
      m_pMenu->addAction(pAction);
      m_pToolBar->addAction(pAction);
      connect(pAction, SIGNAL(triggered()), this, SLOT(EditClickedSlot()));
      m_pqpbEdit->hide();

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
   }
}

void CwmsSearchWindow::SetModule(CwmsApplicationModule p_cModule)
{
   if (p_cModule.IsValid())
   {
      CwmsFormSearch cForm(p_cModule.GetUserInterface());

      QList<QString> qllDisplayMembers = cForm.GetDisplayMembers();
      m_qllResultMembers = qllDisplayMembers;
      QList<QString> qllSearchMembers = cForm.GetSearchMembers();

      QList<QString>::iterator qllIt = qllSearchMembers.begin();
      QList<QString>::iterator qllItEnd = qllSearchMembers.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         AddSearchMember(*qllIt);
      }

      if (cForm.GetPrintEnabled())
      {
         m_pqpbPrint->show();
      }
      else
      {
         m_pqpbPrint->hide();
      }

      if (cForm.GetExportEnabled())
      {
         m_pqpbExport->show();
      }
      else
      {
         m_pqpbExport->hide();
      }
      
      if (cForm.GetImportEnabled())
      {
         m_pqpbImport->show();
      }
      else
      {
         m_pqpbImport->hide();
      }

      m_rpCdmPrintingTemplate = cForm.GetPrintingTemplate();
      FillDialog(cForm.GetSearchList());
   }
}

void CwmsSearchWindow::Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime)
{
   SetModule(p_cModule);
   ConnectRuntime(p_pRuntime, p_cModule);
}
