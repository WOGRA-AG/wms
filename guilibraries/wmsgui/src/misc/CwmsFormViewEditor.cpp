// System and QT Includes

// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsListWidgetHelper.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsViewManager.h"
#include "CwmsReportManager.h"
#include "CwmsFormViewEditor.h"

CwmsFormViewEditor::CwmsFormViewEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

CwmsFormViewEditor::~CwmsFormViewEditor()
{
}

void CwmsFormViewEditor::FillDialog(CwmsFormView p_cForm, bool p_bNew)
{
   m_cForm.SetObject(p_cForm.GetObject());

   if (m_cForm.IsValid() && !p_bNew)
   {
      m_pqleName->setText(m_cForm.GetName());
      m_pqchbDefault->setChecked(m_cForm.GetDefault());
      m_pqchbSaveAsCsv->setChecked(m_cForm.GetSaveAsCsvEnabled());
      m_pqchbPrint->setChecked(m_cForm.GetPrintEnabled());
      m_pqchbReadOnly->setChecked(m_cForm.GetReadOnly());
      FillViews();
      FillReport(m_cForm.GetPrintingTemplate());
   }
}

void CwmsFormViewEditor::FillReport(CdmObject* p_pCdmObject)
{
   m_cTemplate.SetObject(p_pCdmObject);

   if (m_cTemplate.IsValid())
   {
      m_pqlePrintingTemplate->setText(m_cTemplate.GetName());
   }
   else
   {
      m_pqlePrintingTemplate->setText("");
   }
}

void CwmsFormViewEditor::FillViews()
{
   m_pqlwViews->clear();
   QList<QString> qllFunctions = m_cForm.GetViews();

   QList<QString>::iterator qllIt = qllFunctions.begin();
   QList<QString>::iterator qllItEnd = qllFunctions.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwViews);
      pItem->setText(*qllIt);
   }
}

void CwmsFormViewEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

void CwmsFormViewEditor::AddViewClickedSlot()
{
   CwmsViewManager cManager;
   QList<CdmObject*> qlObject = CwmsObjectSelectionIf::GetListofObjects(cManager.GetContainer(), nullptr, this, "Name");

   if (qlObject.count() > 0)
   {
       for (int counter = 0; counter < qlObject.count(); ++counter)
       {
           auto pObject = qlObject[counter];

           if (CHKPTR(pObject))
           {
              CwmsView cView(pObject);
              QListWidgetItem* pItem = new QListWidgetItem(m_pqlwViews);
              pItem->setText(cView.GetName());
              pItem->setData(Qt::UserRole, cView.GetUri());
           }
       }
   }
}

void CwmsFormViewEditor::RemoveViewClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwViews->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

void CwmsFormViewEditor::ViewUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwViews);
}

void CwmsFormViewEditor::ViewDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwViews);
}

bool CwmsFormViewEditor::Validate()
{
   bool bRet = true;

   if (m_pqlwViews->count() == 0)
   {
      bRet = false;
   }

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
   }

   return bRet;
}

void CwmsFormViewEditor::SaveData()
{
   if (m_cForm.IsValid())
   {
      m_cForm.SetName(m_pqleName->text());
      m_cForm.SetPrintingTemplate(m_cTemplate.GetObject());
      m_cForm.SetDefault(m_pqchbDefault->isChecked());
      m_cForm.SetExportEnabled(false);
      m_cForm.SetImportEnabled(false);
      m_cForm.SetSearchEnabled(false);
      m_cForm.SetCopyEnabled(false);
      m_cForm.SetSaveAsCsvEnabled(m_pqchbSaveAsCsv->isChecked());
      m_cForm.SetJournalEnabled(false);
      m_cForm.SetPrintEnabled(m_pqchbPrint->isChecked());
      m_cForm.SetReadOnly(m_pqchbReadOnly->isChecked());

      QList<QString> qstrlViews;

      for (int iCounter = 0; iCounter < m_pqlwViews->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwViews->item(iCounter);

         if (pItem)
         {
            qstrlViews.append(pItem->text());
         }
      }

      m_cForm.SetViews(qstrlViews);
      m_cForm.CommitObject();
   }
}

void CwmsFormViewEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

void CwmsFormViewEditor::EditForm(CwmsFormView p_cForm, bool p_bNew, QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormViewEditor cEditor(p_pqwParent);
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
