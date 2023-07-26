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
   m_pCwmsContainerWidget->SetContainer(p_pContainer);

   if (p_pContainer)
   {
       setWindowTitle(p_pContainer->GetCaption());
   }
}

CwmsObjectListEditorIf::~CwmsObjectListEditorIf()
{
}

void CwmsObjectListEditorIf::SetQuery(QString p_qstrWql)
{
    m_pCwmsContainerWidget->SetQuery(p_qstrWql);
    //SetCaptionThroughModel(m_pCwmsObjectListListView->GetModel());
}

CwmsObjectListEditorWidgetIf* CwmsObjectListEditorIf::GetWidget()
{
    return m_pCwmsContainerWidget;
}

void CwmsObjectListEditorIf::SetCaptionThroughModel(CdmQueryModel* p_pModel)
{
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

void CwmsObjectListEditorIf::SetModel(CdmQueryModel* p_pModel)
{
    m_pCwmsContainerWidget->SetModel(p_pModel);
    SetCaptionThroughModel(p_pModel);
}

void CwmsObjectListEditorIf::SetContainer(CdmObjectContainer* p_pContainer)
{
   m_pCwmsContainerWidget->SetContainer(p_pContainer);

   if (p_pContainer)
   {
       setWindowTitle(p_pContainer->GetCaption());
   }
}

void CwmsObjectListEditorIf::AddColumn(QString p_qstrColumn)
{
   m_pCwmsContainerWidget->AddColumn(p_qstrColumn);
}

void CwmsObjectListEditorIf::FillDialog()
{
   m_pCwmsContainerWidget->FillDialog();
}

QTreeView* CwmsObjectListEditorIf::GetListView()
{
   return m_pCwmsContainerWidget->GetListView();
}

CwmsObjectListEditorWidgetIf* CwmsObjectListEditorIf::GetContainerEditorWidgetIf()
{
   return m_pCwmsContainerWidget;
}

void CwmsObjectListEditorIf::CloseClickedSlot()
{
   accept();
}

void CwmsObjectListEditorIf::SetDefaultValueForNewObject(QString p_qstrValueName,
                                                         QString p_qstrValue,
                                                         QString p_qstrValue2)
{
   m_pCwmsContainerWidget->SetDefaultValueForNewObject(p_qstrValueName, p_qstrValue, p_qstrValue2);
}

void CwmsObjectListEditorIf::ClearMenu()
{
   m_pCwmsContainerWidget->ClearMenu();
}

void CwmsObjectListEditorIf::AddPopupItem(QString p_qstrItem)
{
   m_pCwmsContainerWidget->AddPopupItem(p_qstrItem);
}

void CwmsObjectListEditorIf::NewClickedSlot()
{
   m_pCwmsContainerWidget->NewClickedSlot();
}

void CwmsObjectListEditorIf::EditClickedSlot()
{
   m_pCwmsContainerWidget->EditClickedSlot();
}

void CwmsObjectListEditorIf::DeleteClickedSlot()
{
   m_pCwmsContainerWidget->DeleteClicekdSlot();
}

CdmObjectContainer* CwmsObjectListEditorIf::GetObjectList()
{
   return m_pCwmsContainerWidget->GetContainer();
}
