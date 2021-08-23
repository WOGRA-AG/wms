// System and QT Includes


// WMS Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmObjectContainer.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"

// own Includes
#include "CwmsQueryEditor.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsViewEditor.h"

#include <CwmsReportManager.h>

CwmsViewEditor::CwmsViewEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

CwmsViewEditor::~CwmsViewEditor()
{
}

void CwmsViewEditor::FillDialog(CwmsView p_cCwmsView)
{
   m_cView = p_cCwmsView;

   if (m_cView.IsValid())
   {
      m_pqleName->setText(m_cView.GetName());
      m_pqteComment->setPlainText(m_cView.GetComment());
      m_pqteWql->setPlainText(m_cView.GetViewCommand());

      if (m_cView.GetValid())
      {
         m_pqleState->setText(tr("OK"));
      }
      else
      {
         m_pqleState->setText(tr("Fehlerhaft"));
      }

      FillReport(m_cView.GetReport());
   }
}

void CwmsViewEditor::CurrentTabChangedSlot()
{
   if (m_pqTabWidget->currentIndex() == 1)
   {
      QString qstrWql = m_pqteWql->toPlainText().simplified();

      if (qstrWql.toUpper().startsWith("SELECT"))
      {
         CdmQueryEnhanced* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::BuildQuery(qstrWql);

         if (pCdmQuery)
         {
            CwmsQueryEditor::FillQueryAnalyzer(m_pqtwValidator, pCdmQuery);
            DELPTR(pCdmQuery);
         }
      }
      else
      {
         // todo check if it is a function
      }
   }
}

void CwmsViewEditor::ShowResultClickedSlot()
{
   if (Validate())
   {
      // ToDo
   }
   else
   {
      CheckClickedSlot();
   }
}

bool CwmsViewEditor::Validate()
{
   bool bRet = false;

   if (m_cView.IsValid())
   {
       QString qstrWql = m_pqteWql->toPlainText().simplified();

       if (!qstrWql.isEmpty())
       {
           if (CdmQuery::IsWql(qstrWql))
           {
               CdmQueryEnhanced* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::BuildQuery(qstrWql);

               if (pCdmQuery)
               {
                   m_pqleState->setText(tr("OK"));
                   DELPTR(pCdmQuery);
                   bRet = true;
               }
               else
               {
                   ERR(tr("Sie haben ungültiges WQL Kommando eingegeben. Validierung ist fehlgeschlagen"));
                   m_pqleState->setText(tr("Fehlerhaft"));
               }
           }
           else if (CwmsView::FindModelMethod(qstrWql))
           {
               m_pqleState->setText(tr("OK - Model Funktion"));
               bRet = true;
           }
           else
           {
               m_pqleState->setText(tr("Fehlerhaft - Funktion nicht gefunden"));
           }
       }
       else
       {
           ERR(tr("Sie haben kein WQL Kommando eingegeben. Validierung ist fehlgeschlagen"));
           m_pqleState->setText(tr("Fehlerhaft"));
       }
   }
   else
   {
      ERR(tr("View Object ist ungültig"));
   }

   return bRet;
}

void CwmsViewEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

void CwmsViewEditor::FillReport(CdmObject* p_pCdmObject)
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

void CwmsViewEditor::SaveData()
{
   if (m_cView.IsValid())
   {
      m_cView.SetName(m_pqleName->text());
      m_cView.SetValid(true);
      m_cView.SetComment(m_pqteComment->toPlainText());
      m_cView.SetViewCommand(m_pqteWql->toPlainText());
      m_cView.SetReport(m_cTemplate.GetObject());

      if (m_cView.IsWql())
      {
          CdmQueryEnhanced* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::BuildQuery(m_cView.GetViewCommand());

          if (pCdmQuery)
          {
             m_cView.SetReference(pCdmQuery->GetContainerId());
             DELPTR(pCdmQuery);
          }
      }

      m_cView.CommitObject();
   }
}

void CwmsViewEditor::CheckClickedSlot()
{
   if (Validate())
   {
      CdmMessageManager::information(tr("Sicht ist in Ordnung"), tr("Keine Fehler gefunden."));
   }
   else
   {
      CdmMessageManager::critical(tr("Sicht ist fehlerhaft"), tr("In der Sicht sind Fehler enthalten!"));
   }
}

void CwmsViewEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

void CwmsViewEditor::Edit(CwmsView p_cView, bool p_bNew, QWidget* p_pqwParent)
{
   if (p_cView.IsValid())
   {  
      CwmsViewEditor* pEditor = new CwmsViewEditor(p_pqwParent);
      pEditor->FillDialog(p_cView);

      if (pEditor->exec() != QDialog::Accepted && p_bNew)
      {
         p_cView.SetDeleted();
         p_cView.CommitObject();
      }

      DELPTR(pEditor);
   }
}
