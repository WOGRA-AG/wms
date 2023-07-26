// System and QT Includes
#include <qlineedit.h>
#include <qvalidator.h>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

// own Includes
#include "CdmLogging.h"
#include "CdmValueDouble.h"
#include "CdmValueFloat.h"
#include "CoedtwDouble.h"

CoedtwDouble::CoedtwDouble(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmValue, p_pqwParent),
      m_pqlPrefix(nullptr),
      m_pqlSuffix(nullptr),
      m_pqleEdit(nullptr),
      m_pqcbComboBox(nullptr)
{
}

CoedtwDouble::CoedtwDouble(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_pqlPrefix(nullptr),
      m_pqlSuffix(nullptr),
      m_pqleEdit(nullptr),
      m_pqcbComboBox(nullptr)
{
}

CoedtwDouble::CoedtwDouble(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
      m_pqlPrefix(nullptr),
      m_pqlSuffix(nullptr),
      m_pqleEdit(nullptr),
      m_pqcbComboBox(nullptr)
{
}

CoedtwDouble::~CoedtwDouble()
{
    // nothing to do QT does it for us
}

QWidget* CoedtwDouble::GetEditWidget(QWidget* p_pqwParent)
{
    QWidget* pqwWidget = new QWidget(p_pqwParent);
    QHBoxLayout* pqLayout = new QHBoxLayout(pqwWidget);


    if (!m_rpCdmMember->GetPrefix().isEmpty())
    {
        m_pqlPrefix = new QLabel(pqwWidget);
        pqLayout->addWidget(m_pqlPrefix);
    }

    m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
    m_pqleEdit->setAlignment(Qt::AlignmentFlag::AlignRight);
    pqLayout->addWidget(m_pqleEdit);

    if (!m_rpCdmMember->GetSuffix().isEmpty())
    {
        m_pqlSuffix = new QLabel(pqwWidget);
        pqLayout->addWidget(m_pqlSuffix);
    }

    pqLayout->setMargin(0);

    QDoubleValidator* pqdvValidator = new QDoubleValidator(m_pqleEdit);
    m_pqleEdit->setValidator(pqdvValidator);
    connect(m_pqleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));

    return pqwWidget;
}

void CoedtwDouble::SetValue(CdmValue* p_pCdmValue)
{
    if (CHKPTR(m_pqleEdit) && CHKPTR(p_pCdmValue))
    {
        QLocale qLocale;
        QString qstrValue;
        const CdmMember* pMember = p_pCdmValue->GetMember();

        if (!pMember->GetSuffix().isEmpty())
        {
            m_pqlSuffix->setText(pMember->GetSuffix());
        }

        if (!pMember->GetPrefix().isEmpty())
        {
            m_pqlPrefix->setText(pMember->GetPrefix());
        }

        if (p_pCdmValue->GetValueType() == eDmValueDouble)
        {
            double dValue = ((CdmValueDouble*)p_pCdmValue)->GetValue();

            if (pMember->GetDecimalCountInput() > 0)
            {
                qstrValue = qLocale.toString(dValue, 'f', pMember->GetDecimalCountInput());
            }
            else
            {
                qstrValue = qLocale.toString(dValue, 'f', 15);
            }

            double dCurrent = qLocale.toDouble( m_pqleEdit->text());

            if (dValue != dCurrent)
            {
                m_pqleEdit->setText(qstrValue);
            }
        }
        else if (p_pCdmValue->GetValueType() == eDmValueFloat)
        {
            float fValue = ((CdmValueFloat*)p_pCdmValue)->GetValue();

            if (pMember->GetDecimalCountInput() > 0)
            {
                qstrValue = qLocale.toString(fValue, 'f', pMember->GetDecimalCountInput());
            }
            else
            {
                qstrValue = qLocale.toString(fValue, 'f', 7);
            }

            float fCurrent = qLocale.toFloat(m_pqleEdit->text());

            if (fValue != fCurrent)
            {
                m_pqleEdit->setText(qstrValue);
            }
        }
    }
}

void CoedtwDouble::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && CHKPTR(m_pqleEdit))
    {
        QLocale qLocale;
        QString qstrValue;

        const CdmMember* pMember = m_rpCdmValue->GetMember();

        if (!pMember->GetSuffix().isEmpty())
        {
            m_pqlSuffix->setText(pMember->GetSuffix());
        }

        if (!pMember->GetPrefix().isEmpty())
        {
            m_pqlPrefix->setText(pMember->GetPrefix());
        }

        if(m_rpCdmValue->GetValueType() == eDmValueDouble)
        {
            double dValue = ((CdmValueDouble*)m_rpCdmValue)->GetValue();

            if (pMember->GetDecimalCountInput() > 0)
            {
                qstrValue = qLocale.toString(dValue, 'f', pMember->GetDecimalCountInput());
            }
            else
            {
                qstrValue = qLocale.toString(dValue, 'f', 15);
            }

            double dCurrent = qLocale.toDouble( m_pqleEdit->text());

            if (dValue != dCurrent)
            {
                m_pqleEdit->setText(qstrValue);
            }
        }
        else if (m_rpCdmValue->GetValueType() == eDmValueFloat)
        {
            float fValue = ((CdmValueFloat*)m_rpCdmValue)->GetValue();

            if (pMember->GetDecimalCountInput() > 0)
            {
                qstrValue = qLocale.toString(fValue, 'f', pMember->GetDecimalCountInput());
            }
            else
            {
                qstrValue = qLocale.toString(fValue, 'f', 7);
            }

            float fCurrent = qLocale.toFloat(m_pqleEdit->text());

            if (fValue != fCurrent)
            {
                m_pqleEdit->setText(qstrValue);
            }
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwDouble::ValueChangedSlotByUser()
{
    if (CHKPTR(m_pqleEdit))
    {
        QLocale qLocale;
        QString qstrValue = m_pqleEdit->text();
        if (m_rpCdmValue->GetValueType() == eDmValueDouble)
        {
            ((CdmValueDouble*)m_rpCdmValue)->SetValue(qLocale.toDouble(qstrValue));
        }
        else if (m_rpCdmValue->GetValueType() == eDmValueFloat)
        {
            ((CdmValueFloat*)m_rpCdmValue)->SetValue(qLocale.toFloat(qstrValue));
        }

        if (m_rpqleCaption)
        {
            m_rpqleCaption->setText(m_pqleEdit->text());
        }
    }
}

void CoedtwDouble::SetReadOnly()
{
    m_pqleEdit->setReadOnly(true);
}

void CoedtwDouble::SetEditable()
{
    m_pqleEdit->setReadOnly(false);
}

QWidget* CoedtwDouble::GetSearchWidget(QWidget* p_pqwParent)
{
    QWidget* pqwWidget = new QWidget(p_pqwParent);

    QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

    m_pqcbComboBox = new QComboBox(pqwWidget);
    m_pqcbComboBox->addItem(tr("gleich"));
    m_pqcbComboBox->addItem(tr("kleiner"));
    m_pqcbComboBox->addItem(tr("kleiner gleich"));
    m_pqcbComboBox->addItem(tr("größer"));
    m_pqcbComboBox->addItem(tr("größer gleich"));
    m_pqcbComboBox->addItem(tr("von bis"));
    m_pqcbComboBox->setCurrentIndex(0);
    pqhblLayout->addWidget(m_pqcbComboBox);
    m_pqlLabelFrom = new QLabel(pqwWidget);
    m_pqlLabelFrom->setText(tr("Von"));
    pqhblLayout->addWidget(m_pqlLabelFrom);

    m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
    pqhblLayout->addWidget(m_pqleEdit);
    m_pqlLabelTo = new QLabel(pqwWidget);
    m_pqlLabelTo->setText(tr("Bis"));
    pqhblLayout->addWidget(m_pqlLabelTo);
    m_pqleTo = new QLineEdit(pqwWidget);
    pqhblLayout->addWidget(m_pqleTo);

    QDoubleValidator* pqdvValidator = new QDoubleValidator(m_pqleEdit);
    m_pqleEdit->setValidator(pqdvValidator);
    m_pqleTo->setValidator(pqdvValidator);

    m_pqlLabelFrom->hide();
    m_pqlLabelTo->hide();
    m_pqleTo->hide();

    connect(m_pqcbComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(CompareComboBoxIndexChangedSlot(int)));

    return pqwWidget;
}

void CoedtwDouble::CompareComboBoxIndexChangedSlot(int p_iIndex)
{
    if (p_iIndex < 5)
    {
        m_pqlLabelFrom->hide();
        m_pqlLabelTo->hide();
        m_pqleTo->hide();
    }
    else
    {
        m_pqlLabelFrom->show();
        m_pqlLabelTo->show();
        m_pqleTo->show();
    }
}

void CoedtwDouble::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
    if (CHKPTR(p_pCdmQueryElementParent))
    {
        if (!m_pqleEdit->text().isEmpty())
        {
            EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

            if (m_pqcbComboBox->currentIndex() == 5)
            {

            }
            else
            {
                switch(m_pqcbComboBox->currentIndex())
                {
                case 0:
                    eDmQueryCompareType = eDmQueryCompareTypeEqual;
                    break;
                case 1:
                    eDmQueryCompareType = eDmQueryCompareTypeSmaller;
                    break;
                case 2:
                    eDmQueryCompareType = eDmQueryCompareTypeSmallerEqual;
                    break;
                case 3:
                    eDmQueryCompareType = eDmQueryCompareTypeLarger;
                    break;
                case 4:
                    eDmQueryCompareType = eDmQueryCompareTypeLargerEqual;
                    break;
                default:
                    eDmQueryCompareType = eDmQueryCompareTypeEqual;

                }


                CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                        eDmQueryElementTypeCompare,
                                                                        eDmQueryCompareType);

                QString qstrValue = m_pqleEdit->text();
                float fValue = qstrValue.toFloat();

                pCdmQueryElement->SetComparisonValue(m_qstrKeyname, fValue);
                p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
            }
        }
    }
}

void CoedtwDouble::AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeCompare,
         eDmQueryCompareTypeLargerEqual);
      QString qstrValue = m_pqleEdit->text();
      float fValue = qstrValue.toFloat();
      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, fValue);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDouble::AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeCompare,
         eDmQueryCompareTypeSmallerEqual);

      QString qstrValue = m_pqleTo->text();
      float fValue = qstrValue.toFloat();
      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, fValue);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDouble::AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeAnd);

      AddQueryElementFrom(pCdmQueryElement);
      AddQueryElementTo(pCdmQueryElement);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDouble::SetSearchDeaultValue(QString p_qstrDefault)
{
    m_pqleEdit->setText(p_qstrDefault);
}
