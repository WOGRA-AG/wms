// System and QT Includes


// own Includes
#include "CdmObjectContainer.h"
#include "CwmsObjectListEditorIf.h"

CwmsObjectListEditorIf::CwmsObjectListEditorIf(QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
}

CwmsObjectListEditorIf::CwmsObjectListEditorIf(CdmObjectContainer* p_pContainer, QWidget* parent)
: QDialog(parent)
{
   setupUi(this);
   m_pCwmsObjectListListView->SetContainer(p_pContainer);

   if (p_pContainer)
   {
       setWindowTitle(p_pContainer->GetCaption());
   }
}

CwmsObjectListEditorIf::~CwmsObjectListEditorIf()
{
}

void CwmsObjectListEditorIf::SetModel(CdmQueryModel* p_pModel)
{
    m_pCwmsObjectListListView->SetModel(p_pModel);

    if (p_pModel)
    {
        auto pContainer = p_pModel->GetContainer();

        if (pContainer)
        {
            setWindowTitle(pContainer->GetCaption());
        }
        else
        {
            auto pClass = p_pModel->GetClass();

            if (pClass)
            {
                setWindowTitle(pClass->GetCaption());
            }
        }
    }
}

void CwmsObjectListEditorIf::SetContainer(CdmObjectContainer* p_pContainer)
{
   m_pCwmsObjectListListView->SetContainer(p_pContainer);

   if (p_pContainer)
   {
       setWindowTitle(p_pContainer->GetCaption());
   }
}

void CwmsObjectListEditorIf::AddColumn(QString p_qstrColumn)
{
   m_pCwmsObjectListListView->AddColumn(p_qstrColumn);
}

void CwmsObjectListEditorIf::FillDialog()
{
   m_pCwmsObjectListListView->FillDialog();
}

QTreeView* CwmsObjectListEditorIf::GetListView()
{
   return m_pCwmsObjectListListView->GetListView();
}

CwmsObjectListEditorWidgetIf* CwmsObjectListEditorIf::GetContainerEditorWidgetIf()
{
   return m_pCwmsObjectListListView;
}

void CwmsObjectListEditorIf::CloseClickedSlot()
{
   accept();
}

void CwmsObjectListEditorIf::SetDefaultValueForNewObject(QString p_qstrValueName,
                                                         QString p_qstrValue,
                                                         QString p_qstrValue2)
{
   m_pCwmsObjectListListView->SetDefaultValueForNewObject(p_qstrValueName, p_qstrValue, p_qstrValue2);
}

void CwmsObjectListEditorIf::ClearMenu()
{
   m_pCwmsObjectListListView->ClearMenu();
}

void CwmsObjectListEditorIf::AddPopupItem(QString p_qstrItem)
{
   m_pCwmsObjectListListView->AddPopupItem(p_qstrItem);
}

void CwmsObjectListEditorIf::NewClickedSlot()
{
   m_pCwmsObjectListListView->NewClickedSlot();
}

void CwmsObjectListEditorIf::EditClickedSlot()
{
   m_pCwmsObjectListListView->EditClickedSlot();
}

void CwmsObjectListEditorIf::DeleteClickedSlot()
{
   m_pCwmsObjectListListView->DeleteClicekdSlot();
}

CdmObjectContainer* CwmsObjectListEditorIf::GetObjectList()
{
   return m_pCwmsObjectListListView->GetContainer();
}
