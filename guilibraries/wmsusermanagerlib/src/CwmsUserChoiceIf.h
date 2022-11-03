// impl started on 27.1.2005

#ifndef CWMSUSERCHOICEIF_H
#define CWMSUSERCHOICEIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>
#include <QList>


// own Includes
#include "wmsusermanagerglobal.h"
#include "ui_CwmsUserChoiceDlg.h"



// forwards
class CumUser;


class WMSUSERMANAGER_API CwmsUserChoiceIf : public QDialog, public Ui::CwmsUserChoiceDlg
{
    Q_OBJECT

public:
    CwmsUserChoiceIf(QWidget* parent = NULL);
    virtual ~CwmsUserChoiceIf();
    int GetSelectedUserId();
    static qint64 GetUserSelection(QWidget* parent);

private slots:
    void OKClickedSlot();
    void CancelClickedSlot();
    void SearchUserClickedSlot();
};

#endif //
