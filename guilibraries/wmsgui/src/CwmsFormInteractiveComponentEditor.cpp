
// WMS Manager Incldues
#include "CdmMessageManager.h"

// own Includes
#include "CwmsFormInteractiveComponentEditor.h"
#include "ui_CwmsFormInteractiveComponentEditor.h"

CwmsFormInteractiveComponentEditorIf::CwmsFormInteractiveComponentEditorIf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsFormInteractiveComponentEditor)
{
    ui->setupUi(this);
}

CwmsFormInteractiveComponentEditorIf::~CwmsFormInteractiveComponentEditorIf()
{
    delete ui;
}

void CwmsFormInteractiveComponentEditorIf::FillDialog(CwmsFormInteractiveComponent p_Form)
{
    ui->m_pqleName->setText(p_Form.GetName());
    ui->m_pqteView->setPlainText(p_Form.GetView());
    ui->m_pqteModelView->setPlainText(p_Form.GetViewModel());
    m_Form = p_Form;
}

bool CwmsFormInteractiveComponentEditorIf::Validate()
{
    bool bRet = true;

    if (ui->m_pqleName->text().isEmpty())
    {
        MSG_CRIT("Pflichtfeld nicht gefüllt", "Name fehlt!");
        bRet = false;
    }

    if (ui->m_pqteView->toPlainText().isEmpty())
    {
        MSG_CRIT("Pflichtfeld nicht gefüllt", "View JSON fehlt!");
        bRet = false;
    }

    if (ui->m_pqteModelView->toPlainText().isEmpty())
    {
        MSG_CRIT("Pflichtfeld nicht gefüllt", "ModelView JSON fehlt!");
        bRet = false;
    }


    return bRet;
}


void CwmsFormInteractiveComponentEditorIf::OKClickedSlot()
{
    if (Validate())
    {
        m_Form.SetName(ui->m_pqleName->text());
        m_Form.SetView(ui->m_pqteView->toPlainText());
        m_Form.SetViewModel(ui->m_pqteModelView->toPlainText());
        m_Form.CommitObject();
        accept();
    }
}


void CwmsFormInteractiveComponentEditorIf::EditInteractiveComponent(QWidget* p_pParent, CwmsFormInteractiveComponent p_Form, bool p_bNew)
{
    CwmsFormInteractiveComponentEditorIf cForm(p_pParent);
    cForm.FillDialog(p_Form);

    if (cForm.exec() != QDialog::Accepted && p_bNew)
    {
        p_Form.SetDeleted();
        p_Form.CommitObject();
    }
}
