#include "CwmsContainerEditorDlg.h"
#include "ui_CwmsContainerEditorDlg.h"

#include <CdmObjectContainer.h>

CwmsContainerEditorDlg::CwmsContainerEditorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsContainerEditorDlgClass)
{
    ui->setupUi(this);
}

CwmsContainerEditorDlg::~CwmsContainerEditorDlg()
{
    delete ui;
}


void CwmsContainerEditorDlg::SetContainer(CdmObjectContainer* p_pContainer)
{
    ui->m_pContainerEditor->SetContainer(p_pContainer);
    ui->m_pContainerEditor->FillDialog();

    if (p_pContainer)
    {
        setWindowTitle(p_pContainer->GetCaption());
    }
}
