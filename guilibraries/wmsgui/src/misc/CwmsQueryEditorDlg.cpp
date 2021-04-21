#include "CwmsQueryEditorDlg.h"
#include "ui_CwmsQueryEditorDlg.h"

CwmsQueryEditorDlg::CwmsQueryEditorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsQueryEditorDlg)
{
    ui->setupUi(this);
}

CwmsQueryEditorDlg::~CwmsQueryEditorDlg()
{
    delete ui;
}
