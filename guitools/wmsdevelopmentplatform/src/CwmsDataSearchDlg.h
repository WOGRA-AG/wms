#ifndef CWMSDATASEARCHDLG_H
#define CWMSDATASEARCHDLG_H

#include <QDialog>

class CdmObjectContainer;
class CdmObject;
class CdmContainerManager;

namespace Ui {
class CwmsDataSearchDlgClass;
}

class CwmsDataSearchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsDataSearchDlg(QWidget *parent = 0);
    ~CwmsDataSearchDlg();

public slots:
    void SearchTypeChangedSlot();
    void SearchModeChangedSlot();
    void SearchClickedSlot();
private:
    Ui::CwmsDataSearchDlgClass *ui;
    void SearchContainer();
    void SearchContainerById();
    void SearchContainerByKeyname();
    void SearchContainerByUri();
    void SearchObject();
    void SearchObjectById();
    void SearchObjectByKeyname();
    void SearchObjectByUri();
    void OpenContainer(CdmObjectContainer *p_pContainer);
    void OpenObject(CdmObject *p_pObject);
    CdmContainerManager *GetContainerManager();
};

#endif // CWMSDATASEARCHDLG_H
