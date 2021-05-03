/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormObjectObjectListEditor.cpp
 ** Started Implementation: 2012/09/11
 ** Description:
 **
 ** implements the editor for object objectlist forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsObjectSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsViewManager.h"
#include "CwmsReportManager.h"
#include "CwmsClassMemberSelection.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsFormObjectObjectListEditor.h"

/** +-=---------------------------------------------------------Di 11. Sep 15:47:43 2012----------*
 * @method  CwmsFormObjectObjectListEditor::CwmsFormObjectObjectListEditor // public              *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 15:47:43 2012----------*/
CwmsFormObjectContainerEditor::CwmsFormObjectContainerEditor(QWidget* p_pqwParent)
: CwmsFormStandardContainerEditor(p_pqwParent)
{
   setWindowTitle(tr("Objekt - Container Formular Editor"));
   m_pqlHeader->setText(tr("Objekt - Container Formular Editor"));
   m_pqlView->hide();
   m_pqleView->hide();
   m_pqpbSelectView->hide();
   DELPTR(m_pqwVisibleMembers);
   DELPTR(m_pqwSearchMembers);
   m_pqchbSearch->hide();
}

/** +-=---------------------------------------------------------Di 11. Sep 15:47:51 2012----------*
 * @method  CwmsFormObjectObjectListEditor::~CwmsFormObjectObjectListEditor // public, virtual    *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormObjectObjectListEditor                                *
 *----------------last changed: --------------------------------Di 11. Sep 15:47:51 2012----------*/
CwmsFormObjectContainerEditor::~CwmsFormObjectContainerEditor()
{
}

/** +-=---------------------------------------------------------Di 11. Sep 15:49:27 2012----------*
 * @method  CwmsFormObjectObjectListEditor::FillDialog       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsFormObjectObjectList p_cForm                 //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 15:49:27 2012----------*/
void CwmsFormObjectContainerEditor::FillDialog(CwmsFormObjectContainer p_cForm, bool p_bNew)
{
   CwmsFormStandardContainerEditor::FillDialog(p_cForm, p_bNew);
   m_cForm = p_cForm;

   if (m_cForm.IsValid() && !p_bNew)
   {
      m_pqleJoinKeyname->setText(m_cForm.GetEditorKeyname());
      
      m_pqchbSelectionReadOnly->setChecked(m_cForm.GetSelectionListReadOnly());
      m_pqteEditorWql->setPlainText( m_cForm.GetEditorWql());

      CdmObjectContainer* pContainer = m_cForm.GetSelectionObjectList();

      if (pContainer)
      {
         m_pqleSelectionObjectList->setText(pContainer->GetKeyname());
		 m_rpCdmSelectionList = pContainer;
      }
      else
      {
         m_pqleSelectionObjectList->setText("");
      }

      CdmObject* pCdmObject = m_cForm.GetSelectionView();

      if (pCdmObject)
      {
         CwmsView cView(pCdmObject);
         m_pqleSelectionView->setText(cView.GetName());
      }
      
      m_pqleSelectionView->setText("");
      FillSelectionMembers();
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 16:53:39 2012----------*
 * @method  CwmsFormObjectObjectListEditor::FillSelectionMembers // private                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 16:53:39 2012----------*/
void CwmsFormObjectContainerEditor::FillSelectionMembers()
{
	m_pqlwSelectionMembers->clear();
	QList<QString> qllSelectionMembers = m_cForm.GetSelectionDisplayMembers();
	QList<QString>::iterator qllIt = qllSelectionMembers.begin();
	QList<QString>::iterator qllItEnd = qllSelectionMembers.end();

	for (; qllIt != qllItEnd; ++qllIt)
	{
		QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSelectionMembers);
		pItem->setText(*qllIt);
	}
}

/** +-=---------------------------------------------------------Di 11. Sep 16:01:09 2012----------*
 * @method  CwmsFormObjectObjectListEditor::Validate         // protected                         *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 16:01:09 2012----------*/
bool CwmsFormObjectContainerEditor::Validate()
{
   return CwmsFormStandardContainerEditor::Validate();
}

/** +-=---------------------------------------------------------Di 11. Sep 16:01:26 2012----------*
 * @method  CwmsFormObjectObjectListEditor::SaveData         // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 16:01:26 2012----------*/
void CwmsFormObjectContainerEditor::SaveData()
{
   if (m_cForm.IsValid())
   {
      m_cForm.SetEditorKeyname(m_pqleJoinKeyname->text());
      m_cForm.SetSelectionListReadOnly(m_pqchbSelectionReadOnly->isChecked());
      m_cForm.SetSelectionObjectList(m_rpCdmSelectionList);
      m_cForm.SetSelectionView(m_cSelectionView.GetObject());
	  m_cForm.SetEditorWql(m_pqteEditorWql->toPlainText());

	  QList<QString> qllSelectionMembers;

	  for (int iPos = 0; iPos < m_pqlwSelectionMembers->count(); ++iPos)
	  {
			QListWidgetItem* pItem = m_pqlwSelectionMembers->item(iPos);

			if (pItem)
			{
				qllSelectionMembers.append(pItem->text());
			}
	  }
	  
	  m_cForm.SetSelectionDisplayMembers(qllSelectionMembers);

	  CwmsFormStandardContainerEditor::SaveData();
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 16:03:53 2012----------*
 * @method  CwmsFormObjectObjectListEditor::EditForm         // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsFormObjectObjectList p_cForm                 //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 16:03:53 2012----------*/
void CwmsFormObjectContainerEditor::EditForm(CwmsFormObjectContainer p_cForm,
                                              bool p_bNew,
                                              QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormObjectContainerEditor cEditor(p_pqwParent);
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
