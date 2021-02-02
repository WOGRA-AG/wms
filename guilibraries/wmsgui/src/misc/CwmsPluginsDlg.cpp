

// System and Qt Includes

// WMS Basetools Includes


// Own Includes
#include "CwmsPluginsDlg.h"

CwmsPluginsDlgIf::CwmsPluginsDlgIf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsPluginsDlg)
{
    ui->setupUi(this);
}

CwmsPluginsDlgIf::~CwmsPluginsDlgIf()
{
    delete ui;
}


void CwmsPluginsDlgIf::FillDialog(CwmsApplication p_cApp)
{
    ui->m_pCwmsPlugins->FillWidgetApplication(p_cApp);
}

void CwmsPluginsDlgIf::FillDialogServer(CdmObjectContainer* p_pContainer)
{
    ui->m_pCwmsPlugins->FillWidgetServer(p_pContainer);
}

void CwmsPluginsDlgIf::FillDialogAdmin(CdmObjectContainer* p_pContainer)
{
   ui->m_pCwmsPlugins->FillWidgetAdmin(p_pContainer);
}
