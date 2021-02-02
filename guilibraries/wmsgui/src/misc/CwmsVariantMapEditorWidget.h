#ifndef CwmsVariantMapEditorWidget_H
#define CwmsVariantMapEditorWidget_H

#include <QDialog>
#include <QVariant>

// forwards
class QFormLayout;

class CwmsVariantMapEditorWidget : public QWidget
{
    Q_OBJECT

private:
    QFormLayout* m_pLayout;
    QVariantMap m_qmValues;

    QWidget *GenerateUIEditElement(QVariantMap &p_rqmProperty);

    void UpdateValue(QVariantMap &p_rqmProperty, QWidget *pWidget);
public:
    explicit CwmsVariantMapEditorWidget(QWidget *parent = 0);

    void FillDialog(QVariantMap &p_rMap);
    QVariantMap GetVariantMap();

};

#endif // CwmsVariantMapEditorWidget_H
