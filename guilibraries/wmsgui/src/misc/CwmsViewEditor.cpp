/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsViewEditor.cpp
 ** Started Implementation: 2012/08/24
 ** Description:
 **
 ** implements the editor for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

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
#include "CwmsViewEditor.h"

/** +-=---------------------------------------------------------Fr 24. Aug 11:56:17 2012----------*
 * @method  CwmsViewEditor::CwmsViewEditor                   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:56:17 2012----------*/
CwmsViewEditor::CwmsViewEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 24. Aug 11:56:41 2012----------*
 * @method  CwmsViewEditor::~CwmsViewEditor                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsViewEditor                                                *
 *----------------last changed: --------------------------------Fr 24. Aug 11:56:41 2012----------*/
CwmsViewEditor::~CwmsViewEditor()
{
}

/** +-=---------------------------------------------------------Fr 24. Aug 11:57:01 2012----------*
 * @method  CwmsViewEditor::FillDialog                       // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsView p_cCwmsView                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:57:01 2012----------*/
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
   }
}

/** +-=---------------------------------------------------------Fr 24. Aug 11:58:23 2012----------*
 * @method  CwmsViewEditor::CurrentTabChangedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:58:23 2012----------*/
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



/** +-=---------------------------------------------------------Fr 24. Aug 11:57:32 2012----------*
* @method  CwmsViewEditor::ShowResultClickedSlot            // private, slots                    *
* @return  void                                             //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Fr 24. Aug 11:57:32 2012----------*/
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

/** +-=---------------------------------------------------------Fr 24. Aug 11:58:44 2012----------*
 * @method  CwmsViewEditor::Validate                         // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:58:44 2012----------*/
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
               m_pqleState->setText(tr("Fehlerhaft"));
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

/** +-=---------------------------------------------------------Fr 24. Aug 13:19:34 2012----------*
 * @method  CwmsViewEditor::SaveData                         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 13:19:34 2012----------*/
void CwmsViewEditor::SaveData()
{
   if (m_cView.IsValid())
   {
      m_cView.SetName(m_pqleName->text());
      m_cView.SetValid(true);
      m_cView.SetComment(m_pqteComment->toPlainText());
      m_cView.SetViewCommand(m_pqteWql->toPlainText());

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

/** +-=---------------------------------------------------------Fr 24. Aug 12:01:21 2012----------*
 * @method  CwmsViewEditor::CheckClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 12:01:21 2012----------*/
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

/** +-=---------------------------------------------------------Fr 24. Aug 11:57:19 2012----------*
 * @method  CwmsViewEditor::OKClickedSlot                    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 11:57:19 2012----------*/
void CwmsViewEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Fr 24. Aug 13:56:50 2012----------*
 * @method  CwmsViewEditor::Edit                             // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsView p_cView                                 //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 13:56:50 2012----------*/
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
