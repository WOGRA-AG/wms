// System and QT Includes
#include <qcheckbox.h>

// WMS Includes
#include "CdmValueBool.h"
#include "CdmLogging.h"

// own Includes
#include "CoedtwBool.h"


CoedtwBool::CoedtwBool(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)
{

   m_pqchbCheckbox = nullptr;
}

CoedtwBool::CoedtwBool(const CdmObject *pEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
{
    m_pqchbCheckbox = nullptr;
}

CoedtwBool::CoedtwBool(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)
{

   m_pqchbCheckbox = nullptr;
}

CoedtwBool::~CoedtwBool(  )
{
   // nothing todo qt does it for us :-)
}

QWidget* CoedtwBool::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqchbCheckbox = new QCheckBox(p_pqwParent);
   connect(m_pqchbCheckbox, SIGNAL(clicked()), this, SLOT(ValueChangedSlotByUser()));
   return m_pqchbCheckbox;
}

void CoedtwBool::ValueChangedSlotByUser(  )
{
   if ( m_pqchbCheckbox && m_rpCdmValue)
   {
      ((CdmValueBool*)m_rpCdmValue)->SetValue(m_pqchbCheckbox->isChecked());
   }
}

void CoedtwBool::SetValue(  CdmValue* p_pCdmValue )
{
    m_pqchbCheckbox->setChecked(((CdmValueBool*)p_pCdmValue)->GetValue());
}

void CoedtwBool::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue))
    {
        m_pqchbCheckbox->setChecked(((CdmValueBool*)m_rpCdmValue)->GetValue());
        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwBool::SetReadOnly(  )
{
   m_pqchbCheckbox->setEnabled(false);
}

void CoedtwBool::SetEditable()
{
    m_pqchbCheckbox->setEnabled(true);
}

QWidget* CoedtwBool::GetSearchWidget(QWidget* p_pqwParent)
{
   m_pqchbCheckbox = new QCheckBox(p_pqwParent);
   m_pqchbCheckbox->setTristate(true);
   m_pqchbCheckbox->setCheckState(Qt::PartiallyChecked);
   return m_pqchbCheckbox;
}

void CoedtwBool::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      if (m_pqchbCheckbox->checkState() != Qt::PartiallyChecked)
      {
         CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                 eDmQueryElementTypeCompare,
                                                                 eDmQueryCompareTypeEqual);

         if (m_pqchbCheckbox->checkState() == Qt::Checked)
         {
            pCdmQueryElement->SetComparisonValue(m_qstrKeyname, true);
         }
         else
         {
            pCdmQueryElement->SetComparisonValue(m_qstrKeyname, false);
         }

         p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
      }
   }
}

void CoedtwBool::SetSearchDeaultValue(QString p_qstrDefault)
{
    if (p_qstrDefault.toLower() == "true")
    {
        m_pqchbCheckbox->setCheckState(Qt::Checked);
    }
    else if (p_qstrDefault.toLower() == "false")
    {
        m_pqchbCheckbox->setCheckState(Qt::Unchecked);
    }
}
