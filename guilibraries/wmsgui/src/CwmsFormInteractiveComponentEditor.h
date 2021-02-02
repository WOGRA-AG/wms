#ifndef CWMSFORMINTERACTIVECOMPONENTEDITOR_H
#define CWMSFORMINTERACTIVECOMPONENTEDITOR_H

// System and Qt Includes
#include <QDialog>

// Basetools Includes
#include "CwmsFormInteractiveComponent.h"

// Own Includes
#include "wmsgui.h"

namespace Ui {
class CwmsFormInteractiveComponentEditor;
}

class WMSGUI_API CwmsFormInteractiveComponentEditorIf : public QDialog
{
    Q_OBJECT
private:
    CwmsFormInteractiveComponent m_Form;

public:
    explicit CwmsFormInteractiveComponentEditorIf(QWidget *parent = 0);
    ~CwmsFormInteractiveComponentEditorIf();

    static void EditInteractiveComponent(QWidget *p_pParent, CwmsFormInteractiveComponent p_Form, bool p_bNew);
    void FillDialog(CwmsFormInteractiveComponent p_Form);
private slots:
    void OKClickedSlot();
private:
    Ui::CwmsFormInteractiveComponentEditor *ui;
    bool Validate();
};

#endif // CWMSFORMINTERACTIVECOMPONENTEDITOR_H
