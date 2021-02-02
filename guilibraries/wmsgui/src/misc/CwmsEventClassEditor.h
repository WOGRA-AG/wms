#ifndef CWMSEVENTCLASSEDITOR_H
#define CWMSEVENTCLASSEDITOR_H

#include <QDialog>
#include <CdmClass.h>
#include <CdmClassManager.h>

namespace Ui {
class CwmsEventClassEditor;
}

class CwmsEventClassEditor : public QDialog
{
    Q_OBJECT

public:
    CwmsEventClassEditor(const CdmClass *pObjectClass, QWidget *parent = NULL);
    virtual ~CwmsEventClassEditor();

    void FillCreateEventEditor();
    void FillDeleteEventEditor();
    void FillUpdateEventEditor();
    CdmClass *getSelectedEventClass() const;
protected slots:
    void OKClickedSlot();
    void CancelClickedSlot();
private:
    Ui::CwmsEventClassEditor *ui;
    CdmClass *m_pObjectClass;
    CdmClass *m_pSelectedEventClass;

    void setSelectedEventClass(CdmClass *pSelEventClass);
};

#endif // CWMSEVENTCLASSEDITOR_H
