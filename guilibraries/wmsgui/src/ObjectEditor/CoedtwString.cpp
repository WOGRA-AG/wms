// System and QT Includes
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>


// own Includes
#include "CdmLogging.h"
#include "CdmValueString.h"
#include "CoedtwString.h"


CoedtwString::CoedtwString(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)   
{
   m_pqleEdit = nullptr;

   if (CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pMember = m_rpCdmValue->GetMember();

      if (CHKPTR(pMember))
      {
         SetDisplayType((EdmStringDisplayType)pMember->GetClassReference());
      }
   }
}

CoedtwString::CoedtwString(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent)
    :CoeValueWidget(pCdmEventObject, p_pCdmValue, p_pqwParent)
{
         m_pqleEdit = nullptr;

         if(CHKPTR(m_rpCdmValue))
         {
             const CdmMember* pMember = m_rpCdmValue->GetEventMember(pCdmEventObject);

             if(CHKPTR(pMember))
             {
                 SetDisplayType((EdmStringDisplayType)pMember->GetClassReference());
             }
         }
}

CoedtwString::CoedtwString(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)   
{
   m_pqleEdit = nullptr;
}

CoedtwString::~CoedtwString(  )
{
   // nothing to do
}

QWidget* CoedtwString::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqwParent = p_pqwParent;
   QHBoxLayout* pqLayout = nullptr;

   if(m_eOeDisplayType == edmStringDisplayTypeDirectory || 
      m_eOeDisplayType == edmStringDisplayTypeFile)
   {
      pqwParent = new QWidget(p_pqwParent);
      pqLayout = new QHBoxLayout(pqwParent);
   }

   m_pqleEdit = new QLineEdit(pqwParent);
   if (m_eOeDisplayType == edmStringDisplayTypeEncrypted)
   {
      m_pqleEdit->setEchoMode(QLineEdit::Password);
   }

   if (m_eOeDisplayType == edmStringDisplayTypeDirectory || 
       m_eOeDisplayType == edmStringDisplayTypeFile)
   {
       pqLayout->addWidget(m_pqleEdit);
      QPushButton* pqpbSearch = new QPushButton(pqwParent);
      pqpbSearch->setToolTip(tr("Suchen"));
      QIcon icon8;
      icon8.addFile(QString::fromUtf8(":/icons/search24.png"), QSize(), QIcon::Normal, QIcon::Off);
      pqpbSearch->setIcon(icon8);
      connect(pqpbSearch, SIGNAL(clicked()), this, SLOT(SearchClickedSlot()));
      pqLayout->addWidget(pqpbSearch);
      return pqwParent;
   }
   else
   {
      return m_pqleEdit;
   }
}

void CoedtwString::SetValue(  CdmValue* p_pCdmValue )
{
   if (CHKPTR(m_pqleEdit) && CHKPTR(p_pCdmValue))
   {
       QString qstrValueDisplayString = p_pCdmValue->GetDisplayString();
      if (qstrValueDisplayString != m_pqleEdit->text())
      {
         m_pqleEdit->setText(p_pCdmValue->GetDisplayString());
      }

      connect(m_pqleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));
   }
}

void CoedtwString::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && CHKPTR(m_pqleEdit))
    {
        QString qstrValueDisplayString = m_rpCdmValue->GetDisplayString();
        if(qstrValueDisplayString != m_pqleEdit->text())
        {
            m_pqleEdit->setText(m_rpCdmValue->GetDisplayString());
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

void CoedtwString::SearchClickedSlot()
{
   QString qstrSearch;

   if(m_eOeDisplayType == edmStringDisplayTypeDirectory)
   {
      qstrSearch = QFileDialog::getExistingDirectory(nullptr, 
                                                     tr("Bitte wählen Sie das Verzeichnis aus"),
                                                     m_pqleEdit->text());
   }
   else if(m_eOeDisplayType == edmStringDisplayTypeFile)
   {
      qstrSearch = QFileDialog::getOpenFileName(nullptr,
                                                tr("Bitte wählen Sie die Datei aus"),
                                                m_pqleEdit->text());
   }

   if(!qstrSearch.isEmpty())
   {
      m_pqleEdit->setText(qstrSearch);
      ValueChangedSlotByUser();
   }
}

void CoedtwString::ValueChangedSlotByUser()
{
   if ( m_pqleEdit && m_rpCdmValue)
   {
      ((CdmValueString*)m_rpCdmValue)->SetValue(m_pqleEdit->text());

      if (m_rpqleCaption)
      {
         m_rpqleCaption->setText(m_pqleEdit->text());
      }
   }
}

void CoedtwString::SetReadOnly()
{
   m_pqleEdit->setReadOnly(true);
}

void CoedtwString::SetEditable()
{
    m_pqleEdit->setReadOnly(false);
}

QWidget* CoedtwString::GetSearchWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);

   QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

   m_pqcbComboBox = new QComboBox(pqwWidget);
   m_pqcbComboBox->addItem(tr("beginnt mit"));
   m_pqcbComboBox->addItem(QStringLiteral("enthält"));
   m_pqcbComboBox->addItem(tr("gleich"));
   m_pqcbComboBox->addItem(tr("endet mit"));
   m_pqcbComboBox->setCurrentIndex(1);
   pqhblLayout->addWidget(m_pqcbComboBox);

   m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
   pqhblLayout->addWidget(m_pqleEdit);
   return pqwWidget;
}

void CoedtwString::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      if (!m_pqleEdit->text().isEmpty())
      {
         QString qstrValue = m_pqleEdit->text();
         EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;
         switch(m_pqcbComboBox->currentIndex())
         {
         case 0:
            eDmQueryCompareType = eDmQueryCompareTypeLike;
            qstrValue += "%";

            break;
         case 1:
            qstrValue = "%" + qstrValue + "%";
            eDmQueryCompareType = eDmQueryCompareTypeLike;
            break;
         case 2:
            eDmQueryCompareType = eDmQueryCompareTypeEqual;
            break;
         case 3:
            qstrValue = "%" + qstrValue;
            eDmQueryCompareType = eDmQueryCompareTypeLike;
            break;
         default:
            eDmQueryCompareType = eDmQueryCompareTypeEqual;

         }


         CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                 eDmQueryElementTypeCompare,
                                                                 eDmQueryCompareType);

         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, qstrValue);
         p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
      }
   }
}

void CoedtwString::SetSearchDeaultValue(QString p_qstrDefault)
{
   m_pqleEdit->setText(p_qstrDefault);
}
