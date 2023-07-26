// System and QT Includes
#include <QDateEdit>
#include <QComboBox>
#include <QLabel>
#include <qlineedit.h>
#include <QHBoxLayout>
#include <QCheckBox>
// own Includes
#include "CdmValueDate.h"
#include "CdmLogging.h"
#include "CoedtwDate.h"


CoedtwDate::CoedtwDate(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
   m_pqdeDate(nullptr),
   m_pqcbComboBox(nullptr),
   m_pqlLabelFrom(nullptr),
   m_pqlLabelTo(nullptr),
   m_pqdDateEditFrom(nullptr),
   m_pqdDateEditTo(nullptr),
   m_pqchbRelevant(nullptr)
{


}

CoedtwDate::CoedtwDate(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
    m_pqdeDate(nullptr),
    m_pqcbComboBox(nullptr),
    m_pqlLabelFrom(nullptr),
    m_pqlLabelTo(nullptr),
    m_pqdDateEditFrom(nullptr),
    m_pqdDateEditTo(nullptr),
    m_pqchbRelevant(nullptr)
{

}

CoedtwDate::CoedtwDate(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
  m_pqdeDate(nullptr),
  m_pqcbComboBox(nullptr),
  m_pqlLabelFrom(nullptr),
  m_pqlLabelTo(nullptr),
  m_pqdDateEditFrom(nullptr),
  m_pqdDateEditTo(nullptr),
  m_pqchbRelevant(nullptr)
{
}

CoedtwDate::~CoedtwDate()
{
   // nothing todo qt does it for us :-)
}

QWidget* CoedtwDate::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqdeDate = new QDateEdit(p_pqwParent);
   m_pqdeDate->setMinimumDate(QDate(1800,1,1));
   m_pqdeDate->setSpecialValueText("--.--.----");
   m_pqdeDate->setCalendarPopup(true);
   connect(m_pqdeDate, SIGNAL(dateChanged(const QDate &)), this, SLOT(ValueChangedSlotByUser()));
   return m_pqdeDate;
}

void CoedtwDate::ValueChangedSlotByUser()
{
   if ( m_pqdeDate && m_rpCdmValue)
   {
      QDate qdNewDate = m_pqdeDate->date();

      if (qdNewDate < QDate(1800,1,1))
      {
         QDate qdInvalid;
         ((CdmValueDate*)m_rpCdmValue)->SetValue(qdInvalid);

         if (m_rpqleCaption)
         {
            m_rpqleCaption->setText(tr("kein Datum gewählt"));
         }
      }
      else
      {
         ((CdmValueDate*)m_rpCdmValue)->SetValue(m_pqdeDate->date());

         if (m_rpqleCaption)
         {
            m_rpqleCaption->setText(m_pqdeDate->date().toString());
         }
      }
   }
}

void CoedtwDate::SetValue(CdmValue* p_pCdmValue)
{
   QDate qdDate;

   if (p_pCdmValue)
   {
      qdDate = ((CdmValueDate*)p_pCdmValue)->GetValue();
   }
   
   if (m_pqdeDate->date() != qdDate)
   {
      if (qdDate.isValid())
      {
         m_pqdeDate->setDate(qdDate);
      }
      else
      {
         m_pqdeDate->setDate(QDate(1799,1,1));
      }
   }
}

void CoedtwDate::setEventClassValue()
{
    QDate qdDate;

    if(CHKPTR(m_rpCdmValue))
    {
        qdDate = ((CdmValueDate*)m_rpCdmValue)->GetValue();
    }

    if(!qdDate.isValid())
    {
        qdDate = QDate::currentDate();
    }

    if(m_pqdeDate->date() != qdDate)
    {
        m_pqdeDate->setDate(qdDate);
    }

    if(!m_qlEventClassValues.contains(m_rpCdmValue))
    {
        m_qlEventClassValues.append(m_rpCdmValue);
    }
}

void CoedtwDate::SetReadOnly()
{
   m_pqdeDate->setEnabled(false);
}

void CoedtwDate::SetEditable()
{
    m_pqdeDate->setEnabled(true);
}

QWidget* CoedtwDate::GetSearchWidget(QWidget* p_pqwParent)
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
   m_pqlLabelFrom->setText(tr("Datum"));
   pqhblLayout->addWidget(m_pqlLabelFrom);
   m_pqdDateEditFrom = new QDateEdit(pqwWidget);
   m_pqdDateEditFrom->setCalendarPopup(true);
   m_pqdDateEditFrom->setDate(QDate::currentDate());
   pqhblLayout->addWidget(m_pqdDateEditFrom);
   m_pqlLabelTo = new QLabel(pqwWidget);
   m_pqlLabelTo->setText(tr("Bis"));
   pqhblLayout->addWidget(m_pqlLabelTo);
   m_pqdDateEditTo = new QDateEdit(pqwWidget);
   m_pqdDateEditTo->setCalendarPopup(true);
   m_pqdDateEditTo->setDate(QDate::currentDate());
   pqhblLayout->addWidget(m_pqdDateEditTo);

   m_pqlLabelTo->hide();
   m_pqdDateEditTo->hide();
   RelevantCheckBoxClickedSlot();

   connect(m_pqcbComboBox, SIGNAL(currentIndexChanged(int)),
           this, SLOT(CompareComboBoxIndexChangedSlot(int)));

   return pqwWidget;
}

void CoedtwDate::RelevantCheckBoxClickedSlot()
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

void CoedtwDate::CompareComboBoxIndexChangedSlot(int p_iIndex)
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

void CoedtwDate::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
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

void CoedtwDate::AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeEqual);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->date());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDate::AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeLargerEqual);
      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->date());
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDate::AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareTypeSmallerEqual);
      if (p_bUseFromEdit)
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditFrom->date());
      }
      else
      {
         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqdDateEditTo->date());
      }

      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwDate::AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent)
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

void CoedtwDate::SetSearchDeaultValue(QString p_qstrDefault)
{
   QDate qdDate = QDate::fromString(p_qstrDefault);
   m_pqdDateEditFrom->setDate(qdDate);
}
