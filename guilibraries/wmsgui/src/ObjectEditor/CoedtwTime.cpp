// System and QT Includes
#include <QDateTimeEdit>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QCheckBox>

// own Includes
#include "CdmLogging.h"
#include <CdmValueTime.h>
#include "CoedtwTime.h"



CoedtwTime::CoedtwTime(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqdeTime(nullptr),
  m_pqcbComboBox(nullptr),
  m_pqlLabelFrom(nullptr),
  m_pqlLabelTo(nullptr),
  m_pqdDateEditFrom(nullptr),
  m_pqdDateEditTo(nullptr),
  m_pqchbRelevant(nullptr)
{

}

CoedtwTime::CoedtwTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
   m_pqdeTime(nullptr),
   m_pqcbComboBox(nullptr),
   m_pqlLabelFrom(nullptr),
   m_pqlLabelTo(nullptr),
   m_pqdDateEditFrom(nullptr),
   m_pqdDateEditTo(nullptr),
   m_pqchbRelevant(nullptr)
{

}

CoedtwTime::CoedtwTime(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
: CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
  m_pqdeTime(nullptr),
  m_pqcbComboBox(nullptr),
  m_pqlLabelFrom(nullptr),
  m_pqlLabelTo(nullptr),
  m_pqdDateEditFrom(nullptr),
  m_pqdDateEditTo(nullptr),
  m_pqchbRelevant(nullptr)
{

}


CoedtwTime::~CoedtwTime(  )
{
   // nothing todo qt does it for us :-)
}

QWidget* CoedtwTime::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqdeTime = new QTimeEdit(p_pqwParent);
   connect(m_pqdeTime, SIGNAL(timeChanged(const QTime &)), this, SLOT(ValueChangedSlotByUser()));
   return m_pqdeTime;
}

void CoedtwTime::ValueChangedSlotByUser()
{
   if ( m_pqdeTime && m_rpCdmValue)
   {
      ((CdmValueTime*)m_rpCdmValue)->SetValue(m_pqdeTime->time());

      if (m_rpqleCaption)
      {
         m_rpqleCaption->setText(m_pqdeTime->time().toString());
      }
   }
}

void CoedtwTime::SetValue(CdmValue* p_pCdmValue)
{
   if (m_pqdeTime && p_pCdmValue)
   {
      if (m_pqdeTime->time() != ((CdmValueTime*)p_pCdmValue)->GetValue())
      {
         m_pqdeTime->setTime(((CdmValueTime*)p_pCdmValue)->GetValue());            
      }
   }
}

void CoedtwTime::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && m_pqdeTime)
    {
        if(m_pqdeTime->time() != ((CdmValueTime*)m_rpCdmValue)->GetValue())
        {
           m_pqdeTime->setTime(((CdmValueTime*)m_rpCdmValue)->GetValue());
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwTime::SetReadOnly()
{
   m_pqdeTime->setEnabled(false);
}

void CoedtwTime::SetEditable()
{
    m_pqdeTime->setEnabled(true);
}

QWidget* CoedtwTime::GetSearchWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);

   QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

   m_pqchbRelevant = new QCheckBox(pqwWidget);
   m_pqchbRelevant->setText(tr("Suchrelevant"));
   pqhblLayout->addWidget(m_pqchbRelevant);
   connect(m_pqchbRelevant, SIGNAL(clicked()), this, SLOT(RelevantCheckBoxClickedSlot()));

   m_pqcbComboBox = new QComboBox(pqwWidget);
   m_pqcbComboBox->addItem(tr("gleich"));
   m_pqcbComboBox->addItem(tr("ab"));
   m_pqcbComboBox->addItem(tr("bis"));
   m_pqcbComboBox->addItem(tr("von bis"));
   m_pqcbComboBox->setCurrentIndex(0);
   pqhblLayout->addWidget(m_pqcbComboBox);
   m_pqlLabelFrom = new QLabel(pqwWidget);
   m_pqlLabelFrom->setText(tr("Uhrzeit"));
   pqhblLayout->addWidget(m_pqlLabelFrom);
   m_pqdDateEditFrom = new QTimeEdit(pqwWidget);
   m_pqdDateEditFrom->setTime(QTime::currentTime());
   pqhblLayout->addWidget(m_pqdDateEditFrom);
   m_pqlLabelTo = new QLabel(pqwWidget);
   m_pqlLabelTo->setText(tr("Bis"));
   pqhblLayout->addWidget(m_pqlLabelTo);
   m_pqdDateEditTo = new QTimeEdit(pqwWidget);
   m_pqdDateEditTo->setTime(QTime::currentTime());
   pqhblLayout->addWidget(m_pqdDateEditTo);

   m_pqlLabelTo->hide();
   m_pqdDateEditTo->hide();

   RelevantCheckBoxClickedSlot();

   connect(m_pqcbComboBox, SIGNAL(currentIndexChanged(int)),
      this, SLOT(CompareComboBoxIndexChangedSlot(int)));

   return pqwWidget;
}

void CoedtwTime::RelevantCheckBoxClickedSlot()
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

void CoedtwTime::CompareComboBoxIndexChangedSlot(int p_iIndex)
{
   switch(p_iIndex)      
   {
   case 0:
      m_pqlLabelFrom->setText(tr("Uhrzeit"));
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

void CoedtwTime::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
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

void CoedtwTime::AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeCompare,
         eDmQueryCompareTypeEqual);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->time());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwTime::AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeCompare,
         eDmQueryCompareTypeLargerEqual);
      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->time());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwTime::AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
         eDmQueryElementTypeCompare,
         eDmQueryCompareTypeSmallerEqual);

      if (p_bUseFromEdit)
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->time());
      }
      else
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditTo->time());
      }

      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwTime::AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent)
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

void CoedtwTime::SetSearchDeaultValue(QString p_qstrDefault)
{
   QTime qtTime = QTime::fromString(p_qstrDefault);
   m_pqdDateEditFrom->setTime(qtTime);
}
