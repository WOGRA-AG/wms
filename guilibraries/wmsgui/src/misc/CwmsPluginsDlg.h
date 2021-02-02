#ifndef CWMSPLUGINSDLG_H
#define CWMSPLUGINSDLG_H

// System and Qt Includes
#include <QDialog>

// Basetools Includes
#include "CwmsApplication.h"

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsPluginsDlg.h"


class WMSGUI_API CwmsPluginsDlgIf : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsPluginsDlgIf(QWidget *parent = 0);
    ~CwmsPluginsDlgIf();

    void FillDialog(CwmsApplication p_cApp);
    void FillDialogServer(CdmObjectContainer* p_pContainer);
    void FillDialogAdmin(CdmObjectContainer* p_pContainer);
private:
    Ui::CwmsPluginsDlg *ui;
};

#endif // CWMSPLUGINSDLG_H
