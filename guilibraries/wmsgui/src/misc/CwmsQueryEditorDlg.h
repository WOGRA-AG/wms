#ifndef CWMSQUERYEDITORDLG_H
#define CWMSQUERYEDITORDLG_H

#include <QDialog>


#include "wmsgui.h"

namespace Ui {
class CwmsQueryEditorDlg;
}

class WMSGUI_API CwmsQueryEditorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsQueryEditorDlg(QWidget *parent = nullptr);
    ~CwmsQueryEditorDlg();

private:
    Ui::CwmsQueryEditorDlg *ui;
};

#endif // CWMSQUERYEDITORDLG_H
