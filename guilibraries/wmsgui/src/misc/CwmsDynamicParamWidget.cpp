// System and Qt Includes
#include <QDateTimeEdit>

// WMS Coommons Includes
#include "CdmLogging.h"

// own Includes
#include "CwmsUserSelectionBox.h"
#include "CwmsDynamicParamWidget.h"


CwmsDynamicParamWidget::CwmsDynamicParamWidget(QString p_qstrName, EdmValueType p_eType, QWidget *parent)
    : QWidget(parent),
      m_qstrName(p_qstrName),
      m_eType(p_eType),
      m_pInput(nullptr)

{
    CreateWidget();
}


CwmsDynamicParamWidget::~CwmsDynamicParamWidget()
{

}

void CwmsDynamicParamWidget::CreateWidget()
{
    auto layout = CreateLayoutAndLabel();
       switch(m_eType)
       {
       case eDmValueBool:
          CreateBoolWidget();
          break;
       case eDmValueInt:
       case eDmValueEnum:
       case eDmValueCounter:
       case eDmValueLong:
       case eDmValueFloat:
       case eDmValueDouble:
          CreateNumberWidget();
          break;
       case eDmValueString:
       case eDmValueCharacterDocument:
          CreateTextWidget();
          break;
       case eDmValueDate:
          CreateDateWidget();
          break;
       case eDmValueTime:
          CreateTimeWidget();
          break;
       case eDmValueDateTime:
          CreateDateTimeWidget();
          break;
       case eDmValueUser:
          CreateUserWidget();
          break;
       case eDmValueUserGroup:
          CreateUserGroupWidget();
          break;
       default:
          ERR("Value for " + m_qstrName + " not implemented for Dynamic Param Widget");
          break;

       }
}

QVariant CwmsDynamicParamWidget::GetInput()
{
    QVariant qvValue;

    switch(m_eType)
    {
    case eDmValueBool:
        qvValue = GetBoolValue();
       break;
    case eDmValueInt:
    case eDmValueEnum:
    case eDmValueCounter:
    case eDmValueLong:
    case eDmValueFloat:
    case eDmValueDouble:
        qvValue = GetNumberValue();
       break;
    case eDmValueString:
    case eDmValueCharacterDocument:
        qvValue = GetTextValue();
       break;
    case eDmValueDate:
        qvValue = GetDateValue();
       break;
    case eDmValueTime:
        qvValue = GetTimeValue();
       break;
    case eDmValueDateTime:
        qvValue = GetDateTimeValue();
       break;
    case eDmValueUser:
        qvValue = GetUserValue();
       break;
    case eDmValueUserGroup:
       break;
    default:
       ERR("Value for " + m_qstrName + " not implemented for Dynamic Param Widget");
       break;

    }

    return qvValue;
}

QHBoxLayout *CwmsDynamicParamWidget::CreateLayoutAndLabel()
{
 auto layout = new QHBoxLayout;
 setLayout(layout);
 auto pLabel = new QLabel(this);
 pLabel->setText(m_qstrName);
 layout->addWidget(pLabel);
 return layout;
}

void CwmsDynamicParamWidget::CreateBoolWidget()
{
    auto pCheckBox = new QCheckBox(this);
    pCheckBox->setText("");
    pCheckBox->setChecked(false);
    layout()->addWidget(pCheckBox);
    m_pInput = pCheckBox;
}

QVariant CwmsDynamicParamWidget::GetBoolValue()
{
    QVariant qvValue;
    auto pCheckBox = dynamic_cast<QCheckBox*>(m_pInput);

    if (CHKPTR(pCheckBox))
    {
        qvValue = pCheckBox->isChecked();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateNumberWidget()
{
    CreateTextWidget();
}

QVariant CwmsDynamicParamWidget::GetNumberValue()
{
    QVariant qvValue;
    auto pLineEdit = dynamic_cast<QLineEdit*>(m_pInput);

    if (CHKPTR(pLineEdit))
    {
        QString qstrText = pLineEdit->text();
        QLocale loc;
        qvValue = loc.toDouble(qstrText);
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateTextWidget()
{
    auto pLineEdit = new QLineEdit(this);
    pLineEdit->setText("");
    layout()->addWidget(pLineEdit);
    m_pInput = pLineEdit;
}

QVariant CwmsDynamicParamWidget::GetTextValue()
{
    QVariant qvValue;
    auto pLineEdit = dynamic_cast<QLineEdit*>(m_pInput);

    if (CHKPTR(pLineEdit))
    {
        qvValue = pLineEdit->text();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateDateWidget()
{
    auto pDateEdit = new QDateEdit(this);
    pDateEdit->setDate(QDate::currentDate());
    pDateEdit->setCalendarPopup(true);
    layout()->addWidget(pDateEdit);
    m_pInput = pDateEdit;
}

QVariant CwmsDynamicParamWidget::GetDateValue()
{
    QVariant qvValue;
    auto pDateEdit = dynamic_cast<QDateEdit*>(m_pInput);

    if (CHKPTR(pDateEdit))
    {
        qvValue = pDateEdit->date();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateDateTimeWidget()
{
    auto pDateEdit = new QDateTimeEdit(this);
    pDateEdit->setDateTime(QDateTime::currentDateTime());
    layout()->addWidget(pDateEdit);
    m_pInput = pDateEdit;
}

QVariant CwmsDynamicParamWidget::GetDateTimeValue()
{
    QVariant qvValue;
    auto pDateEdit = dynamic_cast<QDateTimeEdit*>(m_pInput);

    if (CHKPTR(pDateEdit))
    {
        qvValue = pDateEdit->dateTime();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateTimeWidget()
{
    auto pDateEdit = new QTimeEdit(this);
    pDateEdit->setTime(QTime::currentTime());
    layout()->addWidget(pDateEdit);
    m_pInput = pDateEdit;
}

QVariant CwmsDynamicParamWidget::GetTimeValue()
{
    QVariant qvValue;
    auto pDateEdit = dynamic_cast<QTimeEdit*>(m_pInput);

    if (CHKPTR(pDateEdit))
    {
        qvValue = pDateEdit->time();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateUserWidget()
{
    auto pUserSelection = new CwmsUserSelectionBox(this);
    layout()->addWidget(pUserSelection);
    m_pInput = pUserSelection;
}

QVariant CwmsDynamicParamWidget::GetUserValue()
{
    QVariant qvValue;
    auto pUserSelection = dynamic_cast<CwmsUserSelectionBox*>(m_pInput);

    if (CHKPTR(pUserSelection))
    {
        qvValue = pUserSelection->GetSelectedUserId();
    }

    return qvValue;
}

void CwmsDynamicParamWidget::CreateUserGroupWidget()
{
    ERR("Value for " + m_qstrName + " not implemented for Dynamic Param Widget");
    // todo
}
