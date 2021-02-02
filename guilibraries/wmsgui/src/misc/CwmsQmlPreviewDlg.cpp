#include "CwmsQmlPreviewDlg.h"
#include "ui_CwmsQmlPreviewDlg.h"

CwmsQmlPreviewDlg::CwmsQmlPreviewDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsQmlPreviewDlgClass)
{
    ui->setupUi(this);
}

CwmsQmlPreviewDlg::~CwmsQmlPreviewDlg()
{
    delete ui;
}


void CwmsQmlPreviewDlg::AddWindow(QWindow* p_pWindow)
{
    QWidget* pWindowWidget = QWidget::createWindowContainer(p_pWindow, this);
    ui->mainLayout->insertWidget(0, pWindowWidget);
}
