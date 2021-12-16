// System and QT Includes
#include <qlabel.h>
#include <qlayout.h>
#include <QHBoxLayout>

// own Includes
#include "CdmLogging.h"
#include "CdmValue.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmClass.h"

#include "CoedtwBinaryDocument.h"
#include "CoedtwBool.h"
#include "CoedtwCharacterDocument.h"
#include "CoedtwDate.h"
#include "CoedtwDateTime.h"
#include "CoedtwDouble.h"
#include "CoedtwInteger.h"
#include "CoedtwLong.h"
#include "CoedtwObjectListRef.h"
#include "CoedtwObjectRef.h"
#include "CoedtwString.h"
#include "CoedtwTime.h"
#include "CoedtwList.h"
#include "CoedtwEnum.h"
#include "CoedtwFormula.h"
#include "CoedtwUser.h"
#include "CoedtwUserGroup.h"
#include "CoeDataTypeWidget.h"

QList<CdmValue*> CoeValueWidget::m_qlEventClassValues;

CoeValueWidget::CoeValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : QObject(p_pqwParent),
  m_eOeDisplayType(edmStringDisplayTypeFormatted),
  m_rpCdmValue(p_pCdmValue),
  m_rpCdmMember(nullptr),
  m_rpqleCaption(nullptr),
  m_pqhbLayout(nullptr),
  m_pqlLabel(nullptr)
{
   if (m_rpCdmValue)
   {
      m_rpCdmMember = m_rpCdmValue->GetMember();
      connect(m_rpCdmValue, SIGNAL(ValueChanged(CdmValue*)), this, SLOT(SetValue(CdmValue*)));
   }
}

CoeValueWidget::CoeValueWidget(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent)
    : QObject(p_pqwParent),
      m_eOeDisplayType(edmStringDisplayTypeFormatted),
      m_rpCdmValue(p_pCdmValue),
      m_rpCdmMember(nullptr),
      m_rpqleCaption(nullptr),
      m_pqhbLayout(nullptr),
      m_pqlLabel(nullptr)
{
    if(m_rpCdmValue)
    {
        m_rpCdmMember = m_rpCdmValue->GetEventMember(pCdmEventObject);
        connect(m_rpCdmValue, SIGNAL(ValueChanged(CdmValue*)), this, SLOT(SetValue(CdmValue*)));
    }
}

CoeValueWidget::CoeValueWidget(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
: QObject(p_pqwParent),
  m_eOeDisplayType(edmStringDisplayTypeFormatted),
  m_rpCdmValue(nullptr),
  m_rpCdmMember(p_pCdmMember),
  m_qstrKeyname(p_qstrKeyname),
  m_rpqleCaption(nullptr),
  m_pqhbLayout(nullptr),
  m_pqlLabel(nullptr)
{
}

CoeValueWidget* CoeValueWidget::CreateValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
{
   CoeValueWidget* pCoeValueWidget = nullptr;

      switch(p_pCdmValue->GetValueType())
      {
      case eDmValueBool:
         pCoeValueWidget = new CoedtwBool(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueInt:
      case eDmValueCounter:    
         pCoeValueWidget = new CoedtwInteger(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueLong:        
         pCoeValueWidget = new CoedtwLong(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueFloat:             
      case eDmValueDouble:            
         pCoeValueWidget = new CoedtwDouble(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueString:        
         {
            pCoeValueWidget = new CoedtwString(p_pCdmValue, p_pqwParent);
            const CdmMember* pCdmMember = p_pCdmValue->GetMember();
            if (CHKPTR(pCdmMember))
            {
               pCoeValueWidget->SetDisplayType((EdmStringDisplayType)pCdmMember->GetClassReference());
            }
         }
         break;
      case eDmValueDate:              
         pCoeValueWidget = new CoedtwDate(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueTime:              
         pCoeValueWidget = new CoedtwTime(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDateTime:          
         pCoeValueWidget = new CoedtwDateTime(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueObjectRef:         
         pCoeValueWidget = new CoedtwObjectRef(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueContainerRef:    
         pCoeValueWidget = new CoedtwContainerRef(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueBinaryDocument:    
         pCoeValueWidget = new CoedtwBinaryDocument(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueCharacterDocument:
         pCoeValueWidget = new CoedtwCharacterDocument(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictIntDouble:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictIntString:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictIntInt:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictStringDouble:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictStringInt:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueDictStringString:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueListDouble:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueListInt:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueListString:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueListObjects:
         pCoeValueWidget = new CoedtwList(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueFormula:
         pCoeValueWidget = new CoedtwFormula(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueEnum:
         pCoeValueWidget = new CoedtwEnum(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueUser:
         pCoeValueWidget = new CoedtwUser(p_pCdmValue, p_pqwParent);
         break;
      case eDmValueUserGroup:
         pCoeValueWidget = new CoedtwUserGroup(p_pCdmValue, p_pqwParent);
         break;
      default:
         ERR( "Value not implemented" );
         break;
         
      }

   return pCoeValueWidget;
}

CoeValueWidget*CoeValueWidget::CreateEventValueWidget(CdmValue* p_pCdmEventValue, QWidget* p_pqwParent, const CdmObject *p_EventObject)
{
    CoeValueWidget* pCoeValueWidget = nullptr;
    CdmClass *pEventClass = nullptr;
    EdmValueType eValue = eDmValueNone;

    if (CHKPTR(p_pCdmEventValue))
    {
        pEventClass = p_EventObject->GetClass();
        if(pEventClass->IsEventClass())
        {
            eValue = p_pCdmEventValue->GetEvenValueType(p_EventObject);
        }
        else
        {
            eValue = p_pCdmEventValue->GetValueType();
        }
       switch(eValue)
       {
       case eDmValueBool:
          pCoeValueWidget = new CoedtwBool(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueInt:
       case eDmValueCounter:
          pCoeValueWidget = new CoedtwInteger(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueLong:
          pCoeValueWidget = new CoedtwLong(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueFloat:
       case eDmValueDouble:
          pCoeValueWidget = new CoedtwDouble(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueString:
          {
             pCoeValueWidget = new CoedtwString(p_EventObject, p_pCdmEventValue, p_pqwParent);
             const CdmMember* pCdmMember = nullptr;
             if(pEventClass->IsEventClass())
             {
                 pCdmMember = p_pCdmEventValue->GetEventMember(p_EventObject);
             }
             else
             {
                 pCdmMember = p_pCdmEventValue->GetMember();
             }

             if (CHKPTR(pCdmMember))
             {
                pCoeValueWidget->SetDisplayType((EdmStringDisplayType)pCdmMember->GetClassReference());
             }
          }
          break;
       case eDmValueDate:
          pCoeValueWidget = new CoedtwDate(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueTime:
          pCoeValueWidget = new CoedtwTime(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDateTime:
          pCoeValueWidget = new CoedtwDateTime(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueObjectRef:
          pCoeValueWidget = new CoedtwObjectRef(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueContainerRef:
          pCoeValueWidget = new CoedtwContainerRef(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueBinaryDocument:
          pCoeValueWidget = new CoedtwBinaryDocument(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueCharacterDocument:
          pCoeValueWidget = new CoedtwCharacterDocument(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictIntDouble:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictIntString:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictIntInt:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictStringDouble:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictStringInt:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueDictStringString:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueListDouble:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueListInt:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueListString:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueListObjects:
          pCoeValueWidget = new CoedtwList(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueFormula:
          pCoeValueWidget = new CoedtwFormula(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueEnum:
          pCoeValueWidget = new CoedtwEnum(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueUser:
          pCoeValueWidget = new CoedtwUser(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       case eDmValueUserGroup:
          pCoeValueWidget = new CoedtwUserGroup(p_EventObject, p_pCdmEventValue, p_pqwParent);
          break;
       default:
          ERR( "Value not implemented" );
          break;

       }
    }

    return pCoeValueWidget;
}

CoeValueWidget* CoeValueWidget::CreateSearchValueWidget(const CdmMember* p_pCdmMember,
                                                        QString p_qstrKeyname,
                                                        QWidget* p_pqwParent)
{
   CoeValueWidget* pCoeValueWidget = nullptr;

   if (CHKPTR(p_pCdmMember))
   {
      switch(p_pCdmMember->GetValueType())
      {
      case eDmValueBool:
         pCoeValueWidget = new CoedtwBool((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueInt:
      case eDmValueCounter:    
      case eDmValueLong:        
      case eDmValueFloat:             
      case eDmValueDouble:            
         pCoeValueWidget = new CoedtwDouble((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueString:      
      case eDmValueCharacterDocument:
         pCoeValueWidget = new CoedtwString((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueDate:              
         pCoeValueWidget = new CoedtwDate((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueTime:              
         pCoeValueWidget = new CoedtwTime((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueDateTime:          
         pCoeValueWidget = new CoedtwDateTime((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueUser:          
         pCoeValueWidget = new CoedtwUser((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueEnum:          
         pCoeValueWidget = new CoedtwEnum((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      case eDmValueUserGroup:
         pCoeValueWidget = new CoedtwUserGroup((const_cast<CdmMember*>(p_pCdmMember)), p_qstrKeyname, p_pqwParent);
         break;
      default:
         WARNING("Value not implemented for search");
         break;

      }
   }

   return pCoeValueWidget;
}

CoeValueWidget::~CoeValueWidget()
{
   // this pointers are always widgets, or references so I have nothing to do here :-)
}

void CoeValueWidget::CreateWidget(QFormLayout* p_qLayout, QWidget* p_pqwParent)
{
   QWidget* pqLabel = CreateCaptionLabel(p_pqwParent);
   QWidget* pqEdit = GetEditWidget(p_pqwParent);
  
   if (pqLabel && pqEdit)
   {
      p_qLayout->addRow(pqLabel, pqEdit); 
      
      if (CHKPTR(m_rpCdmMember))
      {
         pqLabel->setToolTip(m_rpCdmMember->GetComment());
         pqEdit->setToolTip(m_rpCdmMember->GetComment());
      }
   }

   SetValue(m_rpCdmValue);
}

void CoeValueWidget::CreateEventWidget(QFormLayout* p_qLayout, QWidget* p_pqwParent)
{
    QWidget* pqLabel = CreateCaptionLabel(p_pqwParent);
    QWidget* pqEdit = GetEditWidget(p_pqwParent);

    if (pqLabel && pqEdit)
    {
       p_qLayout->addRow(pqLabel, pqEdit);

       if (CHKPTR(m_rpCdmMember))
       {
          pqLabel->setToolTip(m_rpCdmMember->GetComment());
          pqEdit->setToolTip(m_rpCdmMember->GetComment());
       }
    }

    p_qLayout->setMargin(6);
    setEventClassValue();
}

bool CoeValueWidget::CreateTabWidget(QWidget* p_pqwParent, QVBoxLayout* p_pqlLayout)
{

   bool bRet = false;
   QWidget* pqEdit = GetTabEditWidget(p_pqwParent);

   if(pqEdit)
   {
      pqEdit->show();
      p_pqlLayout->addWidget(pqEdit); 
      bRet = true;
   }

   return bRet;
}

QWidget* CoeValueWidget::CreateCaptionLabel(QWidget* p_pqwParent)
{
   m_pqlLabel = new QLabel(p_pqwParent);

   if (m_rpCdmMember)
   {
      m_pqlLabel->setText(" " + m_rpCdmMember->GetCaption());
   }
   else if (m_rpCdmValue)
   {
      m_pqlLabel->setText(" " + m_rpCdmValue->GetCaption());
   }
   
   m_pqlLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
   return m_pqlLabel;
}

void CoeValueWidget::CreateSearchWidget(QFormLayout* p_pqLayout, QWidget* p_pqwParent)
{
   QWidget* pqLabel = CreateCaptionLabel(p_pqwParent);
   QWidget* pqSearch = GetSearchWidget(p_pqwParent);

   if (pqLabel && pqSearch)
   {
      p_pqLayout->addRow(pqLabel, pqSearch);   
      if (CHKPTR(m_rpCdmMember))
      {
         pqLabel->setToolTip(m_rpCdmMember->GetComment());
         pqSearch->setToolTip(m_rpCdmMember->GetComment());
      }
   }
}

void CoeValueWidget::ValueChangedSlotByUser()
{
}

QWidget* CoeValueWidget::GetTabEditWidget(QWidget* p_pqwParent)
{
   Q_UNUSED(p_pqwParent);
   return nullptr;
}

QWidget* CoeValueWidget::GetSearchWidget(QWidget*)
{
   return nullptr;
}

void CoeValueWidget::AddQueryElement(CdmQueryElement*)
{
   // here it does nothing. overwrite it in the classes!!!
}

void CoeValueWidget::SetValue(CdmValue* )
{
   // here it does nothing. overwrite it in the classes!!!
}

void CoeValueWidget::setEventClassValue()
{
    //overwritten in classes!
}

void CoeValueWidget::SetEventValueInTab(CdmValue *pCdmValue, CdmObject *pEventObject)
{
    //overwritten in CoedtwObjectRef
}

QList<CdmValue *> CoeValueWidget::getEventClassValues() const
{
    return m_qlEventClassValues;
}

void CoeValueWidget::SetReadOnly()
{
}

void CoeValueWidget::SetEditable()
{

}

void CoeValueWidget::SetDisplayType(EdmStringDisplayType p_eOeDisplayType)
{

   m_eOeDisplayType = p_eOeDisplayType;
}

void CoeValueWidget::SetCaptionLineEdit(QLineEdit* p_pqleCaption)
{
   m_rpqleCaption = p_pqleCaption;
}

void CoeValueWidget::SetCaption(QString p_qstrCaption)
{
   m_pqlLabel->setText(p_qstrCaption);
}

void CoeValueWidget::SetSearchDeaultValue(QString p_qstrDefault)
{
    Q_UNUSED(p_qstrDefault);
   // no implementation here overwrite this method
}
