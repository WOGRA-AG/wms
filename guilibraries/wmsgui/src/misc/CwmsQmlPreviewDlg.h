#ifndef CWMSQMLPREVIEWDLG_H
#define CWMSQMLPREVIEWDLG_H

#include <QDialog>

namespace Ui {
class CwmsQmlPreviewDlgClass;
}

class CwmsQmlPreviewDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsQmlPreviewDlg(QWidget *parent = 0);
    ~CwmsQmlPreviewDlg();

    void AddWindow(QWindow *p_pWindow);
private:
    Ui::CwmsQmlPreviewDlgClass *ui;
};

#endif // CWMSQMLPREVIEWDLG_H
