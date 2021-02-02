
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

#include "CwmsVariantMapEditorWidget.h"

CwmsVariantMapEditorWidget::CwmsVariantMapEditorWidget(QWidget *parent) :
    QWidget(parent)
{
}



void CwmsVariantMapEditorWidget::FillDialog(QVariantMap& p_rMap)
{
    m_pLayout = new QFormLayout(this);
    setLayout(m_pLayout);
    m_qmValues = p_rMap;

    QVariantMap::iterator qIt = m_qmValues.begin();
    QVariantMap::iterator qItEnd = m_qmValues.end();
    int iCounter = 0;

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qmProperty = qIt.value().toMap();

        QLabel* pLabel = new QLabel(this);
        pLabel->setText(qmProperty[LABEL].toString());
        QWidget* pqEdit = GenerateUIEditElement(qmProperty);
        m_pLayout->setWidget(qmProperty[POSITION].toInt(), QFormLayout::LabelRole, pLabel);
        m_pLayout->setWidget(qmProperty[POSITION].toInt(), QFormLayout::FieldRole, pqEdit);
        ++iCounter;
    }
}

QWidget* CwmsVariantMapEditorWidget::GenerateUIEditElement(QVariantMap& p_rqmProperty)
{
    QWidget* pWidget = nullptr;

    switch (p_rqmProperty[TYPE].toInt())
    {
        case eDmValueString:
            pWidget = new QLineEdit(this);
            static_cast<QLineEdit*>(pWidget)->setText(p_rqmProperty[VALUE].toString());
            if (p_rqmProperty[OPTION].toString() == ENCRYPTED)
            {
                static_cast<QLineEdit*>(pWidget)->setEchoMode(QLineEdit::Password);
            }

            break;
        case eDmValueInt:
            pWidget = new QSpinBox(this);
            static_cast<QSpinBox*>(pWidget)->setMinimum(-999999999);
            static_cast<QSpinBox*>(pWidget)->setMaximum(999999999);
            static_cast<QSpinBox*>(pWidget)->setValue(p_rqmProperty[VALUE].toInt());
            break;
        case eDmValueEnum:
            pWidget = new QComboBox(this);
            static_cast<QComboBox*>(pWidget)->addItems(p_rqmProperty[SELECTION].toStringList());
            static_cast<QComboBox*>(pWidget)->setCurrentIndex(static_cast<QComboBox*>(pWidget)->findText(p_rqmProperty[VALUE].toString()));
            break;
        case eDmValueBool:
            pWidget = new QCheckBox(this);
            static_cast<QCheckBox*>(pWidget)->setChecked(p_rqmProperty[VALUE].toBool());
            break;
        case eDmValueDouble:
            pWidget = new QDoubleSpinBox(this);
            static_cast<QDoubleSpinBox*>(pWidget)->setMinimum(-999999999);
            static_cast<QDoubleSpinBox*>(pWidget)->setMaximum(999999999);
            static_cast<QDoubleSpinBox*>(pWidget)->setValue(p_rqmProperty[VALUE].toDouble());
            break;
        default:
            ERR("Unsupported Type!!");
    }

    return pWidget;
}

QVariantMap CwmsVariantMapEditorWidget::GetVariantMap()
{
    QVariantMap qmNewMap;
    QVariantMap::iterator qIt = m_qmValues.begin();
    QVariantMap::iterator qItEnd = m_qmValues.end();

    for (; qIt != qItEnd; ++qIt)
    {
        QVariantMap qmProperty = qIt.value().toMap();
        QWidget* pWidget = m_pLayout->itemAt(qmProperty[POSITION].toInt(), QFormLayout::FieldRole)->widget();

        if (CHKPTR(pWidget))
        {
            UpdateValue(qmProperty, pWidget);
        }

        qmNewMap.insert(qIt.key(), qmProperty);
    }

    return qmNewMap;
}

void CwmsVariantMapEditorWidget::UpdateValue(QVariantMap& p_rqmProperty, QWidget* pWidget)
{
    switch (p_rqmProperty[TYPE].toInt())
    {
        case eDmValueString:
            p_rqmProperty[VALUE] = static_cast<QLineEdit*>(pWidget)->text();
            break;
        case eDmValueInt:
            p_rqmProperty[VALUE] = static_cast<QSpinBox*>(pWidget)->value();
            break;
        case eDmValueEnum:
            p_rqmProperty[VALUE] = static_cast<QComboBox*>(pWidget)->currentText();
            break;
        case eDmValueBool:
            p_rqmProperty[VALUE] = static_cast<QCheckBox*>(pWidget)->isChecked();
            break;
        case eDmValueDouble:
            p_rqmProperty[VALUE] = static_cast<QDoubleSpinBox*>(pWidget)->value();
            break;
        default:
            ERR("Unsupported Type!!");
    }

}

