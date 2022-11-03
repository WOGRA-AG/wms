#ifndef CWMSPASSWORDIF_H
#define CWMSPASSWORDIF_H


// System and QT Includes
#include <QDialog>


// own Includes
#include "wmsusermanagerglobal.h"
#include "ui_CwmsPasswordDlg.h"



// forwards
class CumUser;



class WMSUSERMANAGER_API CwmsPasswordIf : public QDialog, public Ui::CwmsNewPasswordDlg
{
    Q_OBJECT

private:
    CumUser* m_rpUser;

public:
    CwmsPasswordIf(CumUser* p_pUser,
                   QWidget* parent = NULL);
    virtual ~CwmsPasswordIf();
    static bool ChangePassword(CumUser* p_pCumUser, QWidget* parent);

private slots:
    void CancelClickedSlot();
    void OKClickedSlot();
};

#endif
