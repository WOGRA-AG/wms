// System and QT Includes
#include <QComboBox>


// own Includes
#include "CdmLogging.h"
#include "CdmValueEnum.h"
#include "CoedtwEnum.h"


CoedtwEnum::CoedtwEnum(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)   
{
   m_pqcbComboBox = nullptr;
}

CoedtwEnum::CoedtwEnum(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
 {
    m_pqcbComboBox = nullptr;
 }

CoedtwEnum::CoedtwEnum(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)   
{
   m_pqcbComboBox = nullptr;
}

CoedtwEnum::~CoedtwEnum()
{
   // nothing to do
}

QWidget* CoedtwEnum::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqcbComboBox = new QComboBox(p_pqwParent);
   connect(m_pqcbComboBox, SIGNAL(activated(int)), this, SLOT(ValueChangedSlotByUser()));
   return m_pqcbComboBox;
}

void CoedtwEnum::SetValue(CdmValue* p_pCdmValue)
{
   if (m_pqcbComboBox && p_pCdmValue)
   {
      QStringList qstrlSelection = ((CdmValueEnum*)p_pCdmValue)->GetSelectionList();

      m_pqcbComboBox->clear();
      m_pqcbComboBox->addItem("-");

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
      }

      m_pqcbComboBox->setCurrentIndex(((CdmValueEnum*)p_pCdmValue)->GetValue() + 1);
   }
}

void CoedtwEnum::setEventClassValue()
{
    if(m_pqcbComboBox && m_rpCdmValue)
    {
        QStringList qstrlSelection = ((CdmValueEnum*)m_rpCdmValue)->GetSelectionList();

        m_pqcbComboBox->clear();
        m_pqcbComboBox->addItem("-");

        for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
        {
           m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
        }

        m_pqcbComboBox->setCurrentIndex(((CdmValueEnum*)m_rpCdmValue)->GetValue() + 1);

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwEnum::AddSelectionValuesToComboBox()
{
   if (m_pqcbComboBox)
   {
      QStringList qstrlSelection;

      if (m_rpCdmMember)
      {
         qstrlSelection = m_rpCdmMember->GetSelectionList();
      }

      m_pqcbComboBox->clear();
      m_pqcbComboBox->addItem("-");

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
      }
   }
}

void CoedtwEnum::ValueChangedSlotByUser()
{
   if (m_pqcbComboBox && m_rpCdmValue)
   {
      ((CdmValueEnum*)m_rpCdmValue)->SetValue(m_pqcbComboBox->currentIndex() - 1);
   }
}

void CoedtwEnum::SetReadOnly()
{
   m_pqcbComboBox->setEnabled(false);
}

void CoedtwEnum::SetEditable()
{
    m_pqcbComboBox->setEnabled(true);
}

QWidget* CoedtwEnum::GetSearchWidget(QWidget* p_pqwParent)
{
   m_pqcbComboBox = new QComboBox(p_pqwParent);
   AddSelectionValuesToComboBox();
   return m_pqcbComboBox;
}

void CoedtwEnum::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent) && m_pqcbComboBox->currentIndex() > 0)
   {
      EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareType);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqcbComboBox->currentIndex()-1);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}
