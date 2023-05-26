// System and QT Includes
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTreeWidget>

// own Includes
#include "CwmsUserChoiceIf.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmValueUser.h"
#include "CoedtwUser.h"


CoedtwUser::CoedtwUser(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmValue, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
    m_pqleUser = nullptr;
}

CoedtwUser::CoedtwUser(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
    m_pqleUser = nullptr;
}

CoedtwUser::CoedtwUser(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
}

CoedtwUser::~CoedtwUser()
{
    // nothing to do
}

QWidget* CoedtwUser::GetEditWidget(QWidget* p_pqwParent)
{
    QWidget* pqWidget = new QWidget(p_pqwParent);
    QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);
    m_pqleUser = new QLineEdit(pqWidget);
    m_pqleUser->setReadOnly(true);
    pqLayout->addWidget(m_pqleUser);

    m_pqpbClear = new QPushButton(pqWidget);
    m_pqpbClear->setToolTip(tr("Entfernen"));
    QIcon icon9;
    icon9.addFile(QString::fromUtf8(":/icons/cancel24.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_pqpbClear->setIcon(icon9);
    connect(m_pqpbClear, SIGNAL(clicked()), this, SLOT(ClearClickedSlot()));
    pqLayout->addWidget(m_pqpbClear);

    m_pqbButton = new QPushButton(pqWidget);
    m_pqbButton->setToolTip(tr("Auswählen"));
    QIcon icon8;
    icon8.addFile(QString::fromUtf8(":/icons/search24.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_pqbButton->setIcon(icon8);
    pqLayout->addWidget(m_pqbButton);
    connect(m_pqbButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindow()));

    pqLayout->setMargin(0);
    return pqWidget;
}

void CoedtwUser::SetValue(CdmValue* p_pCdmValue)
{
    if (m_pqleUser && p_pCdmValue)
    {
        CumUser* pUser = ((CdmValueUser*)p_pCdmValue)->GetUser();

        if (pUser)
        {
            m_pqleUser->setText(pUser->GetDisplayString());
            m_lCurrentUserId = pUser->GetId();
        }
        else
        {
            m_pqleUser->setText("");
        }
    }
}

void CoedtwUser::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && m_pqleUser)
    {
        CumUser* pUser = ((CdmValueUser*)m_rpCdmValue)->GetUser();

        if (pUser)
        {
            m_pqleUser->setText(pUser->GetDisplayString());
            m_lCurrentUserId = pUser->GetId();
        }
        else
        {
            m_pqleUser->setText("");
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwUser::ValueChangedSlotByUser()
{
}

void CoedtwUser::SetReadOnly()
{
    m_pqbButton->hide();
}

void CoedtwUser::SetEditable()
{
    m_pqbButton->show();
}

QWidget* CoedtwUser::GetSearchWidget(QWidget* p_pqwParent)
{
    return GetEditWidget(p_pqwParent);
}

void CoedtwUser::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
    if (CHKPTR(p_pCdmQueryElementParent) && m_lCurrentUserId > 0)
    {
        EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

        CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                eDmQueryElementTypeCompare,
                                                                eDmQueryCompareType);

        pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lCurrentUserId);
        p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
    }
}

void CoedtwUser::ClearClickedSlot()
{
   if(CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

      if(CHKPTR(pCdmMember))
      {
          ((CdmValueUser*)m_rpCdmValue)->SetUser(nullptr);
          m_pqleUser->setText("");
      }
   }
}

void CoedtwUser::openNewWindow()
{
    m_lCurrentUserId = CwmsUserChoiceIf::GetUserSelection(nullptr);

    if (m_lCurrentUserId > 0)
    {
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pCdmManager))
       {
          CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

          if (CHKPTR(pCumUserManager))
          {
             CumUser* pCumUser = pCumUserManager->FindUserById(m_lCurrentUserId);

             if (pCumUser)
             {
                 if (m_rpCdmValue)
                 {
                    dynamic_cast<CdmValueUser*>(m_rpCdmValue)->SetValue(m_lCurrentUserId);
                 }

                 m_pqleUser->setText(pCumUser->GetDisplayString());
             }
             else
             {
                 m_pqleUser->setText("");
                 m_lCurrentUserId = 0;
             }
          }
       }
    }
}
