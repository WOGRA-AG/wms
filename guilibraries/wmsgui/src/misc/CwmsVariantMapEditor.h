#ifndef CWMSVARIANTMAPEDITOR_H
#define CWMSVARIANTMAPEDITOR_H

#include <QDialog>
#include <QVariant>

// forwards
class QFormLayout;
class CwmsVariantMapEditorWidget;

class CwmsVariantMapEditor : public QDialog
{
    Q_OBJECT

private:
    CwmsVariantMapEditorWidget* m_pVariantMapEditor;

public:
    explicit CwmsVariantMapEditor(QWidget *parent = 0);

    void FillDialog(QVariantMap &p_rMap);
    QVariantMap GetVariantMap();

public slots:

    void OkClickedSlot();
    void CancelClickedSlot();

};

#endif // CWMSVARIANTMAPEDITOR_H
