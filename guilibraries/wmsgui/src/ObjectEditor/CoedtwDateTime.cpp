// System and QT Includes
#include <QDateTimeEdit>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QCheckBox>

// own Includes
#include "CdmValueDateTime.h"
#include "CdmLogging.h"
#include "CoedtwDateTime.h"

CoedtwDateTime::CoedtwDateTime(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqdeDateTime(nullptr),
  m_pqcbComboBox(nullptr),
  m_pqlLabelFrom(nullptr),
  m_pqlLabelTo(nullptr),
  m_pqdDateEditFrom(nullptr),
  m_pqdDateEditTo(nullptr),
  m_pqchbRelevant(nullptr)
{

}

CoedtwDateTime::CoedtwDateTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
   m_pqdeDateTime(nullptr),
   m_pqcbComboBox(nullptr),
   m_pqlLabelFrom(nullptr),
   m_pqlLabelTo(nullptr),
   m_pqdDateEditFrom(nullptr),
   m_pqdDateEditTo(nullptr),
   m_pqchbRelevant(nullptr)
{

}

CoedtwDateTime::CoedtwDateTime(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
  m_pqdeDateTime(nullptr),
  m_pqcbComboBox(nullptr),
  m_pqlLabelFrom(nullptr),
  m_pqlLabelTo(nullptr),
  m_pqdDateEditFrom(nullptr),
  m_pqdDateEditTo(nullptr),
  m_pqchbRelevant(nullptr)
{

}

CoedtwDateTime::~CoedtwDateTime(  )
{
   // nothing todo qt does it for us :-)
}

QWidget* CoedtwDateTime::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqdeDateTime = new QDateTimeEdit(p_pqwParent);
   connect(m_pqdeDateTime, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(ValueChangedSlotByUser()));
   return m_pqdeDateTime;
}

void CoedtwDateTime::ValueChangedSlotByUser(  )
{
   if ( m_pqdeDateTime && m_rpCdmValue)
   {
      ((CdmValueDateTime*)m_rpCdmValue)->SetValue(m_pqdeDateTime->dateTime());

      if (m_rpqleCaption)
      {
         m_rpqleCaption->setText(m_pqdeDateTime->dateTime().toString());
      }
   }
}

void CoedtwDateTime::SetValue(  CdmValue* p_pCdmValue )
{
   QDateTime qdtValue;

   if (p_pCdmValue)
   {
      qdtValue = ((CdmValueDateTime*)p_pCdmValue)->GetValue();
   }
   
   if (!qdtValue.isValid())
   {
      qdtValue = QDateTime::currentDateTime();
   }

   if (m_pqdeDateTime->dateTime() != qdtValue)
   {
      m_pqdeDateTime->setDateTime(qdtValue);
   }
}

void CoedtwDateTime::setEventClassValue()
{
    QDateTime qdtValue;

    if(CHKPTR(m_rpCdmValue))
    {
        qdtValue = ((CdmValueDateTime*)m_rpCdmValue)->GetValue();
    }

    if(!qdtValue.isValid())
    {
        qdtValue = QDateTime::currentDateTime();
    }

    if(m_pqdeDateTime->dateTime() != qdtValue)
    {
        m_pqdeDateTime->setDateTime(qdtValue);
    }

    if(!m_qlEventClassValues.contains(m_rpCdmValue))
    {
        m_qlEventClassValues.append(m_rpCdmValue);
    }
}

void CoedtwDateTime::SetReadOnly(  )
{
   m_pqdeDateTime->setEnabled(false);
}

void CoedtwDateTime::SetEditable()
{
   m_pqdeDateTime->setEnabled(true);
}

QWidget* CoedtwDateTime::GetSearchWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);

   QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

   m_pqchbRelevant = new QCheckBox(pqwWidget);
   m_pqchbRelevant->setText(tr("Suchrelevant"));
   pqhblLayout->addWidget(m_pqchbRelevant);
   connect(m_pqchbRelevant, SIGNAL(clicked()), this, SLOT(RelevantCheckBoxClickedSlot()));

   m_pqcbComboBox = new QComboBox(pqwWidget);
   // m_pqcbComboBox->addItem(tr("gleich")); NOTE StB Not working due mysql/Qt time diff
   m_pqcbComboBox->addItem(tr("ab"));
   m_pqcbComboBox->addItem(tr("bis"));
   m_pqcbComboBox->addItem(tr("von bis"));
   m_pqcbComboBox->setCurrentIndex(0);
   pqhblLayout->addWidget(m_pqcbComboBox);
   m_pqlLabelFrom = new QLabel(pqwWidget);
   m_pqlLabelFrom->setText(tr("Datum"));
   pqhblLayout->addWidget(m_pqlLabelFrom);
   m_pqdDateEditFrom = new QDateTimeEdit(pqwWidget);
   m_pqdDateEditFrom->setDate(QDate::currentDate());
   pqhblLayout->addWidget(m_pqdDateEditFrom);
   m_pqlLabelTo = new QLabel(pqwWidget);
   m_pqlLabelTo->setText(tr("Bis"));
   pqhblLayout->addWidget(m_pqlLabelTo);
   m_pqdDateEditTo = new QDateTimeEdit(pqwWidget);
   m_pqdDateEditTo->setDate(QDate::currentDate());
   pqhblLayout->addWidget(m_pqdDateEditTo);
   m_pqlLabelTo->hide();
   m_pqdDateEditTo->hide();

   connect(m_pqcbComboBox, SIGNAL(currentIndexChanged(int)),
           this, SLOT(CompareComboBoxIndexChangedSlot(int)));

   RelevantCheckBoxClickedSlot();
   return pqwWidget;
}

void CoedtwDateTime::RelevantCheckBoxClickedSlot()
{
   if (m_pqchbRelevant->isChecked())
   {
      m_pqcbComboBox->setEnabled(true);
      m_pqlLabelFrom->setEnabled(true);
      m_pqdDateEditFrom->setEnabled(true);
      m_pqlLabelTo->setEnabled(true);
      m_pqdDateEditTo->setEnabled(true);
   }
   else
   {
      m_pqcbComboBox->setEnabled(false);
      m_pqlLabelFrom->setEnabled(false);
      m_pqdDateEditFrom->setEnabled(false);
      m_pqlLabelTo->setEnabled(false);
      m_pqdDateEditTo->setEnabled(false);
   }
}

void CoedtwDateTime::CompareComboBoxIndexChangedSlot(int p_iIndex)
{
   switch(p_iIndex)      
   {
   case 0:
      m_pqlLabelFrom->setText(tr("Datum"));
      m_pqlLabelTo->hide();
      m_pqdDateEditTo->hide();
      break;
   case 1:
      m_pqlLabelFrom->setText(tr("Ab"));
      m_pqlLabelTo->hide();
      m_pqdDateEditTo->hide();
      break;
   case 2:
      m_pqlLabelFrom->setText(tr("Bis"));
      m_pqlLabelTo->hide();
      m_pqdDateEditTo->hide();
      break;
   case 3:
      m_pqlLabelFrom->setText(tr("Von"));
      m_pqlLabelTo->show();
      m_pqdDateEditTo->show();
      break;
   }
}

void CoedtwDateTime::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent) && m_pqchbRelevant->isChecked())
   {
      switch (m_pqcbComboBox->currentIndex())
      {
      case 0:
         AddQueryElementEqual(p_pCdmQueryElementParent);
         break;
      case 1:
         AddQueryElementFrom(p_pCdmQueryElementParent);
         break;
      case 2:
         AddQueryElementTo(p_pCdmQueryElementParent);
         break;
      case 3:
         AddQueryElementFromTo(p_pCdmQueryElementParent);
         break;
      }
   }
}

void CoedtwDateTime::AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeEqual);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->dateTime());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDateTime::AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent)
{

   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeLargerEqual);
      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->dateTime());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDateTime::AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent,
                                       bool p_bUseFromEdit)
{

   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeSmallerEqual);

      if (p_bUseFromEdit)
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->dateTime());
      }
      else
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditTo->dateTime());
      }
      
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDateTime::AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent)
{

   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeAnd);

      AddQueryElementFrom(pCdmQueryElement);
      AddQueryElementTo(pCdmQueryElement, false);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDateTime::SetSearchDeaultValue(QString p_qstrDefault)
{
   QDateTime qdtDateTime = QDateTime::fromString(p_qstrDefault);
   m_pqdDateEditFrom->setDateTime(qdtDateTime);
}
