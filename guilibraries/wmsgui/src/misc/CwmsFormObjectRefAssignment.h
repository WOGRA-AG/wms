#ifndef CWMSFORMOBJECTREFASSIGNMENT_H
#define CWMSFORMOBJECTREFASSIGNMENT_H

#include <QDialog>

namespace Ui {
class CwmsFormObjectRefAssignment;
}


// Forwards
class CdmClass;

class CwmsFormObjectRefAssignment : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsFormObjectRefAssignment(QWidget *parent = 0);
    ~CwmsFormObjectRefAssignment();

    void FillDialog(CdmClass *p_pClass);
    static QString GetObjectReferenceSelection(QWidget *p_pParent, CdmClass *p_pClass);
    QString GetReference();
private slots:
    void ContainerClickedSlot();
    void WQLClickedSlot();
    void OKClickedSlot();
private:
    Ui::CwmsFormObjectRefAssignment *ui;
    QString GetSelectedObjectContainer();
    bool Validate();
};

#endif // CWMSFORMOBJECTREFASSIGNMENT_H
