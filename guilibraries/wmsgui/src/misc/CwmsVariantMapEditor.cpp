
// System and Qt Includes
#include <QVariant>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

// WMS Commons Includes
#include "wmsdefines.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmValue.h"

// Own Includes
#include "CwmsVariantMapEditorWidget.h"
#include "CwmsVariantMapEditor.h"

CwmsVariantMapEditor::CwmsVariantMapEditor(QWidget *parent) :
    QDialog(parent),
    m_pVariantMapEditor(nullptr)
{
}

void CwmsVariantMapEditor::FillDialog(QVariantMap& p_rMap)
{
    QVBoxLayout* pMainLayout = new QVBoxLayout(this);
    setLayout(pMainLayout);

    m_pVariantMapEditor = new CwmsVariantMapEditorWidget(this);
    m_pVariantMapEditor->FillDialog(p_rMap);
    pMainLayout->addWidget(m_pVariantMapEditor);

    QHBoxLayout* pButtonLayout = new QHBoxLayout(this);
    pMainLayout->addItem(pButtonLayout);

    pButtonLayout->addStretch();

    QPushButton* pCancel = new QPushButton(this);
    pCancel->setText(tr("Abbrechen"));
    pButtonLayout->addWidget(pCancel);
    QPushButton* pOk = new QPushButton(this);
    pOk->setText(tr("OK"));
    pButtonLayout->addWidget(pOk);

    connect(pOk, SIGNAL(clicked()), this, SLOT(OkClickedSlot()));
    connect(pCancel, SIGNAL(clicked()), this, SLOT(CancelClickedSlot()));
}

QVariantMap CwmsVariantMapEditor::GetVariantMap()
{
    if (CHKPTR(m_pVariantMapEditor))
    {
        return m_pVariantMapEditor->GetVariantMap();
    }
    else
    {
        return QVariantMap();
    }
}


void CwmsVariantMapEditor::OkClickedSlot()
{
    accept();
}

void CwmsVariantMapEditor::CancelClickedSlot()
{
    reject();
}
