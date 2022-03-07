// System and QT Includes


// own Includes
#include "CwmsApplicationModule.h"
#include "CwmsView.h"
#include "CwmsFormView.h"
#include "CwmsViewManager.h"
#include "CwmsViewObjectListEditorWidget.h"


CwmsViewObjectListEditorWidget::CwmsViewObjectListEditorWidget(QWidget* p_pqwParent)
: QWidget(p_pqwParent)
{
   setupUi(this);
}

CwmsViewObjectListEditorWidget::~CwmsViewObjectListEditorWidget()
{
}

void CwmsViewObjectListEditorWidget::FillDialog()
{
   m_pCwmsEditor->FillDialog();
   ViewSelectionChangedSlot();
}

void CwmsViewObjectListEditorWidget::AddView(QString p_qstrViewName)
{
   QListWidgetItem* pItem = new QListWidgetItem(m_pqlwFilters);
   pItem->setText(p_qstrViewName);
   
   if (m_pqlwFilters->count() == 1)
   {
      pItem->setSelected(true);
   }
}

CwmsView CwmsViewObjectListEditorWidget::LoadView(QString p_qstrName)
{
   CwmsViewManager cManager;
   CwmsView cView = cManager.GetViewByName(p_qstrName);
   return cView;
}

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

void CwmsViewObjectListEditorWidget::ConnectRuntime(CwmsRuntime* p_pRuntime,
                                                    CwmsApplicationModule p_cModule)
{
  m_pCwmsEditor->ConnectRuntime(p_pRuntime, p_cModule);
}

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

void CwmsViewObjectListEditorWidget::Initialize(CwmsApplicationModule p_cModule,
                                                CwmsRuntime* p_pRuntime)
{
   SetModule(p_cModule);
   ConnectRuntime(p_pRuntime, p_cModule);
   FillDialog();
}
