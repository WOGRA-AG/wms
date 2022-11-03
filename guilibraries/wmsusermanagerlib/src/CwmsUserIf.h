#ifndef CWMSUSERIF_H
#define CWMSUSERIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT includes
#include <QWidget>
#include <QList>


// own Inlcudes
#include "ui_CwmsUserWidget.h"


// forwards
class CumUser;
class CumUserGroup;

class CwmsUserIf : public QWidget, public Ui::CwmsUserWidget
{
    Q_OBJECT

private:
    CumUser* m_rpCumUser;
    QList<CumUserGroup*> m_qvlUserGroups;


public:
    CwmsUserIf(CumUser* p_pCumUser, QWidget* p_pqwParent = NULL);
    virtual ~CwmsUserIf();

public slots:
    void AddScheme();
    void RemoveScheme();
    void AddGroup();
    void RemoveGroup();

private:
    void FillDialog();
    void FillGroups();
    void FillSchemes();

private slots:
    void ChangePasswordClickedSlot();
    void UpdateCLickedSlot();
};


#endif
