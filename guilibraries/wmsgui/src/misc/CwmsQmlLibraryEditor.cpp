
// System and Qt Includes
#include <QFile>
#include <QQuickWindow>
#include <QTreeWidgetItem>
#include <QDir>
#include <QDesktopServices>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// WMSQML Includes
#include "CwqQmlObjectViewer.h"

// own Includes
#include "CwmsQmlLibraryEditor.h"
#include "ui_CwmsQmlLibraryEditor.h"

CwmsQmlLibraryEditor::CwmsQmlLibraryEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CwmsQmlLibraryEditorClass)
{
    ui->setupUi(this);
    connect(&m_FileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(FileChangedSlot(QString)));
}

CwmsQmlLibraryEditor::~CwmsQmlLibraryEditor()
{
    if (IsModified())
    {
        if (CdmMessageManager::Ask(tr("Änderungen vorhanden"), tr("Sie haben Änderungen an der Bibliothek vorgenommen.\n Wollen Sie die Speichern?")))
        {
            Save();
        }
    }

    delete ui;
}

void CwmsQmlLibraryEditor::FillDialog(CwmsFormLibrary p_cForm)
{
    if (p_cForm.IsValid())
    {
        m_cForm = p_cForm;
        ui->m_pqleName->setText(m_cForm.GetName());
        ui->m_pqleVersion->setText(m_cForm.GetVersion());
        ui->m_pqteCode->setPlainText(m_cForm.GetCode());
        ui->m_pqteCode->document()->setModified(false);
    }
}

bool CwmsQmlLibraryEditor::Validate()
{
    bool ret = true;

    if (ui->m_pqleName->text().isEmpty())
    {
        CdmMessageManager::critical(tr("Pflichtfeld nicht gefüllt"),tr("Bibliothek benötigt einen Namen"));
        ret = false;
    }

    if (ui->m_pqleVersion->text().isEmpty())
    {
        CdmMessageManager::critical(tr("Pflichtfeld nicht gefüllt"),tr("Bibliothek benötigt eine Version"));
        ret = false;
    }

    if (ui->m_pqteCode->toPlainText().isEmpty())
    {
        CdmMessageManager::critical(tr("Pflichtfeld nicht gefüllt"),tr("Bibliothek bneötigt Programmcode"));
        ret = false;
    }

    return ret;
}

bool CwmsQmlLibraryEditor::Save()
{
    bool bRet = false;

    if (Validate())
    {
        m_cForm.SetName(ui->m_pqleName->text());
        m_cForm.SetVersion(ui->m_pqleVersion->text());
        m_cForm.SetCode(ui->m_pqteCode->toPlainText());
        m_cForm.CommitObject();
        bRet = true;
        ui->m_pqteCode->document()->setModified(false);

        if (m_rpItem)
        {
            m_rpItem->setText(0, ui->m_pqleName->text());
            m_rpItem->setText(1, ui->m_pqleVersion->text());
            m_rpItem->setData(0, Qt::UserRole, (int)m_cForm.GetObjectId());
        }
    }

    return bRet;
}

void CwmsQmlLibraryEditor::Revert()
{
    if (IsModified())
    {
        ui->m_pqleName->setText(m_cForm.GetName());
        ui->m_pqleVersion->setText(m_cForm.GetVersion());
        ui->m_pqteCode->setPlainText(m_cForm.GetCode());
        ui->m_pqteCode->document()->setModified(false);
    }
}

void CwmsQmlLibraryEditor::SetItem(QTreeWidgetItem* p_pItem)
{
    m_rpItem = p_pItem;
}

bool CwmsQmlLibraryEditor::IsModified()
{
    bool bRet = ui->m_pqteCode->document()->isModified();

    if (!bRet)
    {
        bRet = (ui->m_pqleName->text() != m_cForm.GetName());
    }

    if (!bRet)
    {
        bRet = (ui->m_pqleVersion->text() != m_cForm.GetVersion());
    }

    return bRet;
}


void CwmsQmlLibraryEditor::OKClickedSlot()
{
   if (Validate() && Save())
   {
      //accept();
   }
}


void CwmsQmlLibraryEditor::CancelClickedSlot()
{
//   reject();
}

void CwmsQmlLibraryEditor::FileChangedSlot(QString p_qstrFile)
{
   if (CdmMessageManager::Ask(tr("Datei wurde lokal geändert"),
       tr("Der Code wurde im lokalen Dateisystem geändert. Soll er übernommen werden?")))
   {
      QFile qFile(p_qstrFile);

      if (qFile.open(QIODevice::ReadOnly))
      {
         QString qstrCode = qFile.readAll();
         ui->m_pqteCode->setPlainText(qstrCode);
      }

      qFile.close();
   }
}


void CwmsQmlLibraryEditor::PreviewClickedSlot()
{
   CwqQmlObjectViewer* pViewer = new CwqQmlObjectViewer(this);
   QQuickWindow* pView = pViewer->CreateView(ui->m_pqleName->text(), ui->m_pqteCode->toPlainText());

   if (CHKPTR(pView))
   {
      pView->show();
   }
}

void CwmsQmlLibraryEditor::OpenInExternalEditorClickedSlot()
{
    QString qstrName = ui->m_pqleName->text();
    QString qstrCode = ui->m_pqteCode->toPlainText();

    // ToDo define Working Directory on local disk
    QString qstrTempPath = QDir::tempPath();
    QString qstrFilename = qstrTempPath + "/" + qstrName + ".qml";

    QFile qFile(qstrFilename);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream qStream(&qFile);
        qStream << qstrCode;
    }

    qFile.close();
    m_FileWatcher.addPath(qstrFilename);
    QDesktopServices::openUrl(QUrl(qstrFilename));
}

void CwmsQmlLibraryEditor::Debug()
{
    CdmMessageManager::critical(tr("Nicht unterstützt"), tr("Debugging ist nicht für Benutzeroberflächen unterstützt"));
}

void CwmsQmlLibraryEditor::Execute()
{
    PreviewClickedSlot();
}

