// System and QT Includes
#include <QComboBox>
#include <QLineEdit>

// own Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmValueUserGroup.h"
#include "CoedtwUserGroup.h"
#include "CwmsUserGroupChoiceIf.h"

CoedtwUserGroup::CoedtwUserGroup(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
     m_lCurrentGroupId(0)
{
    m_pqbButton = nullptr;
    m_qleGroup = nullptr;
}

CoedtwUserGroup::CoedtwUserGroup(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_lCurrentGroupId(0)
 {
     m_pqbButton = nullptr;
     m_qleGroup = nullptr;
 }

CoedtwUserGroup::CoedtwUserGroup(const CdmMember *p_pCdmMember,
                                 QString p_qstrKeyname,
                                 QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent) ,
     m_lCurrentGroupId(0)
{
   m_pqbButton = nullptr;
   m_qleGroup = nullptr;
}

CoedtwUserGroup::~CoedtwUserGroup()
{
   // nothing to do
}

QWidget* CoedtwUserGroup::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqWidget = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);
   m_qleGroup = new QLineEdit(pqWidget);
   m_qleGroup->setReadOnly(true);
   pqLayout->addWidget(m_qleGroup);
   m_pqbButton = new QPushButton(QStringLiteral("Auswählen"), pqWidget);
   pqLayout->addWidget(m_pqbButton);
   connect(m_pqbButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindow()));
   return pqWidget;
}

void CoedtwUserGroup::SetValue(CdmValue* p_pCdmValue)
{
   if (m_qleGroup && p_pCdmValue)
   {
      CumUserGroup* pCumGroup = ((CdmValueUserGroup*)p_pCdmValue)->GetUserGroup();

      if(pCumGroup)
      {
          m_qleGroup->setText(pCumGroup->GetGroupName());
          m_lCurrentGroupId = pCumGroup->GetId();
      }
      else
      {
          m_qleGroup->setText("");
      }
   }
}

void CoedtwUserGroup::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && m_qleGroup)
    {
        CumUserGroup* pCumGroup = ((CdmValueUserGroup*)m_rpCdmValue)->GetUserGroup();

        if(pCumGroup)
        {
            m_qleGroup->setText(pCumGroup->GetGroupName());
            m_lCurrentGroupId = pCumGroup->GetId();
        }
        else
        {
            m_qleGroup->setText("");
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwUserGroup::ValueChangedSlotByUser()
{
}

void CoedtwUserGroup::SetReadOnly()
{
   m_pqbButton->hide();
}

void CoedtwUserGroup::SetEditable()
{
    m_pqbButton->show();
}

QWidget* CoedtwUserGroup::GetSearchWidget(QWidget* p_pqwParent)
{
   return GetEditWidget(p_pqwParent);
}

void CoedtwUserGroup::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent) && m_lCurrentGroupId > 0)
   {
      EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareType);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lCurrentGroupId);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwUserGroup::openNewWindow()
{
    m_lCurrentGroupId = CwmsUserGroupChoiceIf::GetGroupSelection(nullptr);

    if(m_lCurrentGroupId > 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if(CHKPTR(pCdmManager))
        {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if(CHKPTR(pCumUserManager))
            {
                CumUserGroup* pCumGroup = pCumUserManager->FindUserGroupById(m_lCurrentGroupId);

                if(pCumGroup)
                {
                    dynamic_cast<CdmValueUserGroup*>(m_rpCdmValue)->SetValue(m_lCurrentGroupId);
                    m_qleGroup->setText(pCumGroup->GetGroupName());
                }
                else
                {
                    m_qleGroup->setText("");
                    m_lCurrentGroupId = 0;
                }
            }
        }
    }
}
