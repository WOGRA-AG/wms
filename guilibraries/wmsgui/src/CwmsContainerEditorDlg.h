#ifndef CWMSCONTAINEREDITORDLG_H
#define CWMSCONTAINEREDITORDLG_H

#include <QDialog>

#include "wmsgui.h"

class CdmObjectContainer;

namespace Ui {
class CwmsContainerEditorDlgClass;
}

class WMSGUI_API CwmsContainerEditorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsContainerEditorDlg(QWidget *parent = 0);
    ~CwmsContainerEditorDlg();

    void SetContainer(CdmObjectContainer *p_pContainer);
private:
    Ui::CwmsContainerEditorDlgClass *ui;
};

#endif // CWMSCONTAINEREDITORDLG_H
