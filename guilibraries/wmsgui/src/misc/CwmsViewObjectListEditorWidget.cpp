/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsViewObjectListEditorWidget.cpp
 ** Started Implementation: 2012/09/09
 ** Description:
 **
 ** implements an objectlisteditor with different views for user selection
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CwmsApplicationModule.h"
#include "CwmsView.h"
#include "CwmsFormView.h"
#include "CwmsViewManager.h"
#include "CwmsViewObjectListEditorWidget.h"


/** +-=---------------------------------------------------------So 9. Sep 12:30:27 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::CwmsViewObjectListEditorWidget // public              *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 12:30:27 2012-----------*/
CwmsViewObjectListEditorWidget::CwmsViewObjectListEditorWidget(QWidget* p_pqwParent)
: QWidget(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------So 9. Sep 12:31:03 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::~CwmsViewObjectListEditorWidget // public, virtual    *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsViewObjectListEditorWidget                                *
 *----------------last changed: --------------------------------So 9. Sep 12:31:03 2012-----------*/
CwmsViewObjectListEditorWidget::~CwmsViewObjectListEditorWidget()
{
}

/** +-=---------------------------------------------------------So 9. Sep 12:31:11 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::FillDialog       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 12:31:11 2012-----------*/
void CwmsViewObjectListEditorWidget::FillDialog()
{
   m_pCwmsEditor->FillDialog();
   ViewSelectionChangedSlot();
}

/** +-=---------------------------------------------------------Fr 14. Sep 10:39:14 2012----------*
 * @method  CwmsViewObjectListEditorWidget::AddView          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrViewName                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Sep 10:39:14 2012----------*/
void CwmsViewObjectListEditorWidget::AddView(QString p_qstrViewName)
{
   QListWidgetItem* pItem = new QListWidgetItem(m_pqlwFilters);
   pItem->setText(p_qstrViewName);
   
   if (m_pqlwFilters->count() == 1)
   {
      pItem->setSelected(true);
   }
}

/** +-=---------------------------------------------------------So 9. Sep 12:32:19 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::LoadView         // private                           *
 * @return  CwmsView                                         //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 12:32:19 2012-----------*/
CwmsView CwmsViewObjectListEditorWidget::LoadView(QString p_qstrName)
{
   CwmsViewManager cManager;
   CwmsView cView = cManager.GetViewByName(p_qstrName);
   return cView;
}

/** +-=---------------------------------------------------------So 9. Sep 12:36:30 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::ViewSelectionChangedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 12:36:30 2012-----------*/
void CwmsViewObjectListEditorWidget::ViewSelectionChangedSlot()
{
   QListWidgetItem* pItem = GetSelectedView();

   if (pItem)
   {
      QString qstrViewName = pItem->text();
      CwmsView cView = LoadView(qstrViewName);
      m_pCwmsEditor->SetView(cView);
      m_pCwmsEditor->Refresh();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 12:40:34 2012-----------*
 * @method  CwmsViewObjectListEditorWidget::GetSelectedView  // public                            *
 * @return  QListWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 12:40:34 2012-----------*/
QListWidgetItem* CwmsViewObjectListEditorWidget::GetSelectedView()
{
   QListWidgetItem* pItem = nullptr;
   QList<QListWidgetItem*> qlItems = m_pqlwFilters->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Di 23. Jul 13:21:01 2013----------*
 * @method  CwmsViewObjectListEditorWidget::ConnectRuntime   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsRuntime* p_pRuntime                          //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 23. Jul 13:21:01 2013----------*/
void CwmsViewObjectListEditorWidget::ConnectRuntime(CwmsRuntime* p_pRuntime,
                                                    CwmsApplicationModule p_cModule)
{
  m_pCwmsEditor->ConnectRuntime(p_pRuntime, p_cModule);
}

/** +-=---------------------------------------------------------Mo 17. Sep 10:36:56 2012----------*
 * @method  CwmsViewObjectListEditorWidget::SetModule        // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:36:56 2012----------*/
void CwmsViewObjectListEditorWidget::SetModule(CwmsApplicationModule p_cModule)
{
   if (p_cModule.IsValid())
   {
      CdmObject* pCdmObject = p_cModule.GetUserInterface();
      CwmsFormView cForm(pCdmObject);
      m_pCwmsEditor->SetFormBase(cForm);
      QList<QString> qllViews = cForm.GetViews();

      QList<QString>::iterator qllIt = qllViews.begin();
      QList<QString>::iterator qllItEnd = qllViews.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         AddView(*qllIt);
      }

      if (qllViews.count() == 1)
      {
         m_pqlwFilters->hide();         
      }

      ViewSelectionChangedSlot();
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 10:36:40 2012----------*
 * @method  CwmsViewObjectListEditorWidget::Initialize       // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @param   CwmsRuntime* p_pRuntime                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:36:40 2012----------*/
void CwmsViewObjectListEditorWidget::Initialize(CwmsApplicationModule p_cModule,
                                                CwmsRuntime* p_pRuntime)
{
   SetModule(p_cModule);
   ConnectRuntime(p_pRuntime, p_cModule);
   FillDialog();
}
