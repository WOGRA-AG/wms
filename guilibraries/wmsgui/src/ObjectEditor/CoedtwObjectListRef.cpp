// System and QT Includes
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmap.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmValueContainerRef.h"

// BAsetools Includes
#include "CwmsFormManager.h"

// own Includes
#include "CwmsObjectListSelectionIf.h"
#include "CoedtwObjectListRef.h"
#include "CwmsObjectListEditorIf.h"
#include "CwmsObjectListSelectionIf.h"

CoedtwContainerRef::CoedtwContainerRef(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
: CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqleEdit(nullptr),
  m_pqpbChange(nullptr),
  m_pqpbClear(nullptr),
  m_pqpbView(nullptr),
  m_pObjectListEditor(nullptr),
  m_lContainerId(0)
{
}

CoedtwContainerRef::CoedtwContainerRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_pqleEdit(nullptr),
      m_pqpbChange(nullptr),
      m_pqpbClear(nullptr),
      m_pqpbView(nullptr),
      m_pObjectListEditor(nullptr),
      m_lContainerId(0)
{
}

CoedtwContainerRef::CoedtwContainerRef(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
     m_pqleEdit(nullptr),
     m_pqpbChange(nullptr),
     m_pqpbClear(nullptr),
     m_pqpbView(nullptr),
     m_pObjectListEditor(nullptr),
     m_lContainerId(0)
{
}

CoedtwContainerRef::~CoedtwContainerRef()
{
   // nothing todo qt does it all for us.
}

QWidget* CoedtwContainerRef::GetTabEditWidget(QWidget* p_pqwParent)
{
   if (!m_pObjectListEditor)
   {
      m_pObjectListEditor = new CwmsObjectListEditorWidgetIf(p_pqwParent);
   }
   
   return m_pObjectListEditor;
}

QWidget* CoedtwContainerRef::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqwParent = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqwParent);
   m_pqleEdit = new QLineEdit(pqwParent);
   m_pqleEdit->setReadOnly(true);
   pqLayout->addWidget(m_pqleEdit);
   
   if(m_rpCdmValue && !m_rpCdmValue->IsOwner())
   {
      m_pqpbChange = new QPushButton(pqwParent);
      m_pqpbChange->setText(tr("Auswählen"));
      connect( m_pqpbChange, SIGNAL(clicked()), this, SLOT(ChangeClickedSlot()));
      pqLayout->addWidget(m_pqpbChange);

      m_pqpbClear = new QPushButton(pqwParent);
      m_pqpbClear->setText(tr("Entfernen"));
      connect(m_pqpbClear, SIGNAL(clicked()), this, SLOT(ClearClickedSlot()));
      pqLayout->addWidget(m_pqpbClear);
   }
   else
   {
      m_pqleEdit->hide();
   }

   m_pqpbView = new QPushButton(pqwParent);
   m_pqpbView->setText(tr("Details"));
   connect( m_pqpbView, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
   pqLayout->addWidget(m_pqpbView);
   pqLayout->setMargin(0);

   return pqwParent;
}

void CoedtwContainerRef::SetValue(CdmValue* p_pCdmValue)
{
   if (CHKPTR(p_pCdmValue))
   {
      if (m_pqleEdit)
      {
         m_pqleEdit->setText(p_pCdmValue->GetDisplayString());
      }
      else if (m_pObjectListEditor)
      {
         CdmObjectContainer* pContainer = ((CdmValueContainerRef*)p_pCdmValue)->GetContainer();

         if (CHKPTR(pContainer))
         {

			 CwmsFormManager cManager;
			 CdmObject* pFormConfig = cManager.GeDefaultContainerForm(pContainer);

            // TODO: Check if the complete objectlist will be displayed if not you have to reload it here
            m_pObjectListEditor->SetContainer(pContainer);

			if (pFormConfig)
			{
				m_pObjectListEditor->SetFormConfiguration(pFormConfig);
			}

            m_pObjectListEditor->FillDialog();
         }
      }
   } 
}

void CoedtwContainerRef::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue))
    {

        if(m_pqleEdit)
        {
            m_pqleEdit->setText(m_rpCdmValue->GetDisplayString());
        }
        else if(m_pObjectListEditor)
        {
            CdmObjectContainer *pContainer = ((CdmValueContainerRef*)m_rpCdmValue)->GetContainer();

            if(CHKPTR(pContainer))
            {
                CwmsFormManager cManager;
                CdmObject* pFormConfig = cManager.GeDefaultContainerForm(pContainer);

                if (pFormConfig)
                {
                    m_pObjectListEditor->SetFormConfiguration(pFormConfig);
                }

                m_pObjectListEditor->FillDialog();
            }
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwContainerRef::ValueChangedSlotByUser()
{
   // nothing to do here
}

void CoedtwContainerRef::ChangeClickedSlot()
{
    const CdmMember* pCdmMember = nullptr;

   if(m_rpCdmValue)
   {
      pCdmMember = m_rpCdmValue->GetMember();
   }
   else if (m_rpCdmMember != nullptr)
   {
       pCdmMember = m_rpCdmMember;
   }

  if(CHKPTR(pCdmMember))
  {
     auto pContainer =
             CwmsContainerSelectionIf::GetObjectContainer(pCdmMember->GetSchemeId(),
                                                          pCdmMember->GetClassReference(),
                                                          nullptr);

     if(pContainer)
     {
         m_lContainerId = pContainer->GetId();

         if (m_rpCdmValue)
         {
            ((CdmValueContainerRef*)m_rpCdmValue)->SetValue(pContainer);
            SetValue(m_rpCdmValue);
         }
         else
         {
             m_pqleEdit->setText(pContainer->GetCaption());
         }
     }
  }

}

void CoedtwContainerRef::ClearClickedSlot()
{
    m_lContainerId = 0;

   if(m_rpCdmValue)
   {
      const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

      if(CHKPTR(pCdmMember))
      {
        ((CdmValueContainerRef*)m_rpCdmValue)->CdmValueLong::SetValue(0);
        SetValue(m_rpCdmValue);
      }
   }
   else
   {
       m_lContainerId = 0;
       m_pqleEdit->setText("");
   }
}

void CoedtwContainerRef::EditClickedSlot()
{
   if(CHKPTR(m_rpCdmValue))
   {
      CdmObjectContainer* pContainer = ((CdmValueContainerRef*)m_rpCdmValue)->GetContainer();

      if(pContainer)
      {
         CwmsObjectListEditorIf* pCwmsObjectListEditorIf = new CwmsObjectListEditorIf(pContainer, nullptr);
         const CdmClass* pCdmClass = pContainer->GetClass();

         if(CHKPTR(pCdmClass))
         {
            QMap<qint64, CdmMember*> qmMembers = pCdmClass->GetClassMemberMap();

            QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
            QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

            for(; qmIt != qmItEnd; ++qmIt)
            {
               CdmMember* pCdmMember = qmIt.value();

               if(pCdmMember)
               {
                  pCwmsObjectListEditorIf->AddColumn(pCdmMember->GetKeyname());
               }
            }
         }

         pCwmsObjectListEditorIf->FillDialog();
         pCwmsObjectListEditorIf->setWindowTitle(m_rpCdmValue->GetCaption());
         pCwmsObjectListEditorIf->exec();
         DELPTR(pCwmsObjectListEditorIf);
           
      }
      else
      {
         MSG_CRIT("Error in Editing Container",
                  "No Objectlist choosen");
      }
   }
}

void CoedtwContainerRef::SetReadOnly()
{
   if (m_pqpbChange)
   {
      m_pqpbChange->hide();
   }

   if (m_pObjectListEditor)
   {
      m_pObjectListEditor->SetReadOnly(true);
   }
}

void CoedtwContainerRef::SetEditable()
{
    if(m_pqpbChange)
    {
       m_pqpbChange->show();
    }

    if (m_pObjectListEditor)
    {
       m_pObjectListEditor->SetReadOnly(false);
    }
}

QWidget* CoedtwContainerRef::GetSearchWidget(QWidget* p_pqwParent)
{
   auto pWidget = GetEditWidget(p_pqwParent);
   m_pqpbView->hide();
   return pWidget;
}

void CoedtwContainerRef::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      if (m_lContainerId > 0)
      {
         CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                 eDmQueryElementTypeCompare,
                                                                 eDmQueryCompareTypeEqual);

         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lContainerId);
         p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
      }
   }
}

void CoedtwContainerRef::SetSearchDeaultValue(QString p_qstrDefault)
{
   m_pqleEdit->setText(p_qstrDefault);
}
