// System and QT Includes
#include <QQuickView>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <qtextcodec.h>
#include <QDesktopServices>
#include <QProcess>

// WMS Includes
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CwmsFormUserDefinedExecutor.h"


// Own Includes
#include "CwmsObjectSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"
#include "jshighlighter.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsUIEditor.h"

CwmsUIEditor::CwmsUIEditor(QWidget* p_pParent)
   : QWidget(p_pParent)
{
   setupUi(this);
   connect(&m_FileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(FileChangedSlot(QString)));
}

CwmsUIEditor::~CwmsUIEditor()
{
}

void CwmsUIEditor::closeEvent(QCloseEvent *event)
{
    if (IsModified())
    {
        if (CdmMessageManager::Ask(tr("Änderungen vorhanden"), tr("Sie haben Änderungen an der Funktion vorgenommen.\n Wollen Sie die Speichern?")))
        {
            Save();
        }
    }

    event->accept();
}


void CwmsUIEditor::FillDialog(CwmsFormUserDefined p_Form)
{
   m_Form = p_Form;

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
       QString qstrClassUri = m_Form.GetClassUri();
      CdmClass* pClass = static_cast<CdmClass*>(pManager->GetUriObject(qstrClassUri));

      if (pClass)
      {
         m_pqleClass->setText(pClass->GetKeyname());
      }
   }

   switch(m_Form.GetContext())
   {
      case eWmsFormContextObject:
         m_pqrbObject->setChecked(true);
         break;
      case eWmsFormContextContainer:
         m_pqrbObjectContainer->setChecked(true);
         break;
      case eWmsFormContextWms:
         m_pqrbWmsContext->setChecked(true);
         break;
   }

   switch (m_Form.GetFormType())
   {
      case eWmsFormTypeDialog:
         m_pqrbDialog->setChecked(true);
         break;
      case eWmsFormTypeWidget:
         m_pqrbWidget->setChecked(true);
         break;
      case eWmsFormTypeMainWindow:
         m_pqrbMainWindow->setChecked(true);
         break;
   }

   m_qstrXml = m_Form.GetXml();
   m_pqleName->setText(m_Form.GetName());
   m_pqteCode->setTextWrapEnabled(false);
   m_pqteCode->setCodeFoldingEnabled(true);
   m_pqteCode->setLineNumbersVisible(true);
   m_qstrOriginalCode = m_Form.GetUICode();
   m_pqteCode->setPlainText(m_qstrOriginalCode);
   m_pqteCode->document()->setModified(false);
   m_pqchbDefault->setChecked(m_Form.GetDefault());
   m_pqchbModal->setChecked(m_Form.IsModal());
}

bool CwmsUIEditor::Validate()
{
   bool success = true;

   if (m_pqleName->text().isEmpty())
   {
      MSG_CRIT("Validierung fehlgeschlagen","Name ist Pflichtfeld.");
      success = false;
   }

   if (m_pqleClass->text().isEmpty() && !m_pqrbWmsContext->isChecked())
   {
      MSG_CRIT("Validierung fehlgeschlagen","Wenn Wms Kontext nicht ausgewählt ist, muss eine Klasse selektiert werden.");
      success = false;
   }


   if (m_pqteCode->toPlainText().isEmpty())
   {
      MSG_CRIT("Validierung fehlgeschlagen", "Der Dialogcode muss gefüllt sein.");
      success = false;
   }
   
   return success;
}

void CwmsUIEditor::SaveClickedSlot()
{
    if (Validate())
    {
        Save();
    }
}

bool CwmsUIEditor::Save()
{
    bool success = false;
    if (Validate())
    {
        m_Form.SetName(m_pqleName->text());

        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            CdmClass* pClass = pManager->GetClassManager()->FindClassByKeyname(m_pqleClass->text());

            if (pClass)
            {
                m_Form.SetClassUri(pClass->GetUriInternal());
            }
        }

        m_Form.SetDefault(m_pqchbDefault->isChecked());
        m_Form.SetModal(m_pqchbModal->isChecked());
        m_Form.SetUICode(m_pqteCode->toPlainText());
        m_Form.SetXml(m_qstrXml);

        if (m_pqrbObject->isChecked())
        {
            m_Form.SetContext(eWmsFormContextObject);
        }
        else if (m_pqrbObjectContainer->isChecked())
        {
            m_Form.SetContext(eWmsFormContextContainer);
        }
        else if (m_pqrbWmsContext->isChecked())
        {
            m_Form.SetContext(eWmsFormContextWms);
        }

        if (m_pqrbDialog->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeDialog);
        }
        else if (m_pqrbWidget->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeWidget);
        }
        else if (m_pqrbMainWindow->isChecked())
        {
            m_Form.SetFormType(eWmsFormTypeMainWindow);
        }

        if (m_Form.CommitObject() > 0)
        {
            success = true;
        }
        else
        {
            if (!m_Form.GetObject()->IsModified())
            {
                success = true;
            }
            else
            {
                ERR("Could not save Form!");
            }
        }

        if (success)
        {
            m_pqteCode->document()->setModified(false);

            if (m_rpItem)
            {
                m_rpItem->setText(0,m_Form.GetName());
                m_rpItem->setData(0, Qt::UserRole, m_Form.GetObjectId());
            }
        }
    }
    return success;
}

void CwmsUIEditor::Revert()
{
    if (IsModified())
    {
        FillDialog(m_Form);
    }
}

void CwmsUIEditor::SetItem(QTreeWidgetItem* p_pItem)
{
    m_rpItem = p_pItem;
}

bool CwmsUIEditor::IsModified()
{
    bool bRet = false;

    bRet = (m_pqteCode->document()->isModified());

    if (!bRet)
    {
        bRet = (m_Form.GetName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_pqrbObject->isChecked() && m_Form.GetContext() != eWmsFormContextObject);
    }

    if (!bRet)
    {
        bRet = (m_pqrbObjectContainer->isChecked() && m_Form.GetContext() != eWmsFormContextContainer);
    }

    if (!bRet)
    {
        bRet = (m_pqrbWmsContext->isChecked() && m_Form.GetContext() != eWmsFormContextWms);
    }

    if (!bRet)
    {
        bRet = (m_qstrXml != m_Form.GetXml());
    }

    if (!bRet)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
           CdmClass* pClass = pManager->GetClassManager()->FindClassByKeyname(m_pqleClass->text());

           if (pClass)
           {
              bRet = (m_Form.GetClassUri() != pClass->GetUriInternal());
           }
           else
           {
               bRet = (!m_Form.GetClassUri().isEmpty());
           }
        }
    }

    return bRet;
}

void CwmsUIEditor::Debug()
{
    PreviewClickedSlot();
}

void CwmsUIEditor::Execute()
{
    PreviewClickedSlot();
}

void CwmsUIEditor::SelectClassClickedSlot()
{
   CdmClass* pClass = CwmsClassSelectionIf::GetClass(this);

   if (pClass)
   {
      m_pqleClass->setText(pClass->GetKeyname());
   }
}

void CwmsUIEditor::FileChangedSlot(QString p_qstrFile)
{
  QFile qFile(p_qstrFile);

  if (qFile.open(QIODevice::ReadOnly))
  {
     QString qstrCode = qFile.readAll();
     m_qstrXml = qstrCode;
  }

  qFile.close();
}

void CwmsUIEditor::OpenInExternalEditorSlot()
{
    QString qstrName = m_pqleName->text();
    QString qstrTempPath = QDir::tempPath();
    m_qstrFilename = qstrTempPath + "/" + qstrName + ".ui";

    if (m_qstrXml.isEmpty())
    {
        m_qstrXml = m_Form.GetXml();

        if (m_qstrXml.isEmpty())
        {
            m_qstrXml = GenerateEmptyTemplate(qstrName);
        }
    }

    if (!m_FileWatcher.files().contains(m_qstrFilename))
    {
        QFile qFile(m_qstrFilename);

        if (qFile.open(QIODevice::WriteOnly))
        {
            QTextStream qStream(&qFile);
            qStream.setCodec(QTextCodec::codecForName("UTF-8"));
            qStream << m_qstrXml;

            qFile.close();
            m_FileWatcher.addPath(m_qstrFilename);

            QString qstrApp = qApp->applicationDirPath() + "/designer.exe";
            QStringList qstrlArgs;
            qstrlArgs << m_qstrFilename;

            connect(&m_Process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(ProcessFinishedSlot()));
            m_Process.start(qstrApp, qstrlArgs);
        }
        else
        {
            MSG_CRIT("Temporäre UI Datei konnte nicht angelegt werden","WMS konnte die UI Datei leider nicht speichern.");
        }
    }
    else
    {
        MSG_CRIT("Formular bereits geöffnet","Das Formular ist bereits geöffnet.");
    }
}

QString CwmsUIEditor::GenerateEmptyTemplate(QString qstrName)
{
    QString qstrTemplate = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    qstrTemplate += "<ui version=\"4.0\">\n";
    qstrTemplate += QString("<class>%1</class>\n").arg(qstrName);

    QString qstrWidgetType = "QWidget";

    if (m_pqrbDialog->isChecked())
    {
        qstrWidgetType = "QDialog";
    }
    else if (m_pqrbMainWindow->isChecked())
    {
        qstrWidgetType = "QMainWindow";
    }

    qstrTemplate += QString("<widget class=\"%1\" name=\"%2\">\n").arg(qstrWidgetType).arg(qstrName);
    qstrTemplate += "<property name=\"geometry\">\n";
    qstrTemplate += "<rect>\n";
    qstrTemplate += "<x>0</x>\n";
    qstrTemplate += "<y>0</y>\n";
    qstrTemplate += "<width>640</width>\n";
    qstrTemplate += "<height>480</height>\n";
    qstrTemplate += "</rect>\n";
    qstrTemplate += "</property>\n";
    qstrTemplate += "</widget>\n";
    qstrTemplate += "</ui>\n";
    return qstrTemplate;
}

void CwmsUIEditor::PreviewClickedSlot()
{
    if (IsModified())
    {
        Save();
    }

    CwmsFormUserDefinedExecutor cExecutor;

    if (m_pqrbWmsContext->isChecked())
    {
        cExecutor.ExecuteUserDefinedFormMisc(m_Form, nullptr);
    }
    else if (m_pqrbObject->isChecked())
    {
       CdmObject* pObject = GetFormObject();

       if (pObject)
       {
           cExecutor.ExecuteUserDefinedFormObject(m_Form, pObject, nullptr);
       }
    }
    else if (m_pqrbObjectContainer->isChecked())
    {
        CdmObjectContainer* pContainer = GetFormContainer();

        if (pContainer)
        {
            cExecutor.ExecuteUserDefinedFormContainer(m_Form, pContainer, nullptr);
        }
    }
}

CdmObjectContainer* CwmsUIEditor::GetFormContainer()
{
    CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        auto pClass = pClassManager->FindClassByKeyname(m_pqleClass->text());

        if (CHKPTR(pClass))
        {
            return CwmsContainerSelectionIf::GetObjectContainer(pClass, this);
        }
    }

    return nullptr;
}

CdmObject* CwmsUIEditor::GetFormObject()
{
    CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        auto pClass = pClassManager->FindClassByKeyname(m_pqleClass->text());

        if (CHKPTR(pClass))
        {
            return CwmsObjectSelectionIf::GetObject(pClass, this);
        }
    }

    return nullptr;
}

void CwmsUIEditor::RemoveClassClickedSlot()
{
    m_pqleClass->setText("");
}

void CwmsUIEditor::ProcessFinishedSlot()
{
    m_FileWatcher.removePath(m_qstrFilename);
    QFile::remove(m_qstrFilename);
}
