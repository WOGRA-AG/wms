/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang GraÃŸhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


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

/** +-=---------------------------------------------------------Mi 22. Aug 10:53:03 2012----------*
 * @method  CoeValueWidget::CoeValueWidget                   // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 10:53:03 2012----------*/
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

/** +-=---------------------------------------------------------Mo 8. Sep 19:35:58 2008-----------*
 * @method  CoeValueWidget::CoeValueWidget                   // public                            *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 8. Sep 19:35:58 2008-----------*/
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

/** +-=---------------------------------------------------------Sa 6. Sep 12:54:44 2008-----------*
 * @method  CoeValueWidget::CreateValueWidget                // public, static                    *
 * @return  CoeValueWidget*                                  //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment Factory method which creates the correct widgets fror the object editor.              *
 *----------------last changed: --------------------------------Sa 6. Sep 12:54:44 2008-----------*/
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

/** +-=---------------------------------------------------------Mo 11. Feb 11:03:39 2013----------*
 * @method  CoeValueWidget::CreateSearchValueWidget          // public, static                    *
 * @return  CoeValueWidget*                                  //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment Factory method which creates the correct widgets fror the object editor.              *
 *----------------last changed: --------------------------------Mo 11. Feb 11:03:39 2013----------*/
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

/** +-=---------------------------------------------------------Fri Dec 5 16:39:01 2003-----------*
 * @method  CoeValueWidget::~CoeValueWidget            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoeValueWidget.                                            *
 *---------------------------------------------------------------Fri Dec 5 16:39:01 2003----------*/
CoeValueWidget::~CoeValueWidget(  )
{
   // this pointers are always widgets, or references so I have nothing to do here :-)
}

/** +-=---------------------------------------------------------Mi 22. Aug 13:51:29 2012----------*
 * @method  CoeValueWidget::CreateWidget                     // public                            *
 * @return  void                                             //                                   *
 * @param   QFormLayout* p_qLayout                           //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 13:51:29 2012----------*/
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
    setEventClassValue();
}

/** +-=---------------------------------------------------------Mo 5. Nov 14:09:19 2012-----------*
 * @method  CoeValueWidget::CreateTabWidget                  // public                            *
 * @return  bool                                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   QVBoxLayout* p_pqlLayout                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 14:09:19 2012-----------*/
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

/** +-=---------------------------------------------------------Mi 22. Aug 15:13:22 2012----------*
 * @method  CoeValueWidget::CreateCaptionLabel               // private                           *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 15:13:22 2012----------*/
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

/** +-=---------------------------------------------------------Mi 22. Aug 13:53:55 2012----------*
 * @method  CoeValueWidget::CreateSearchWidget               // public                            *
 * @return  void                                             //                                   *
 * @param   QFormLayout* p_pqLayout                          //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment creates the searchwidget from this value.                                             *
 *----------------last changed: --------------------------------Mi 22. Aug 13:53:55 2012----------*/
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

/** +-=---------------------------------------------------------Fri Dec 5 16:42:42 2003-----------*
 * @method  CoeValueWidget::ValueChangedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Fri Dec 5 16:42:42 2003----------*/
void CoeValueWidget::ValueChangedSlotByUser(  )
{
}


/** +-=---------------------------------------------------------Mo 5. Nov 11:33:44 2012-----------*
 * @method  CoeValueWidget::GetTabEditWidget                 // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:33:44 2012-----------*/
QWidget* CoeValueWidget::GetTabEditWidget(QWidget* p_pqwParent)
{
   Q_UNUSED(p_pqwParent);
   return nullptr;
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:53:37 2012----------*
 * @method  CoeValueWidget::GetEditWidget                    // public, p virtual                 *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment This method returns the Edit widget for this Value.                                   *
 *----------------last changed: --------------------------------Mi 22. Aug 14:53:37 2012----------*/




/** +-=---------------------------------------------------------Mi 22. Aug 15:23:18 2012----------*
 * @method  CoeValueWidget::GetSearchWidget                  // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget*# p_pqwParent                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 15:23:18 2012----------*/
QWidget* CoeValueWidget::GetSearchWidget(QWidget*)
{
   return nullptr;
}

/** +-=---------------------------------------------------------Di 28. Sep 09:05:06 2010----------*
 * @method  CoeValueWidget::AddQueryElement                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement*# p_pCdmQueryElementParent       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 09:05:06 2010----------*/
void CoeValueWidget::AddQueryElement(CdmQueryElement*)
{
   // here it does nothing. overwrite it in the classes!!!
}

/** +-=---------------------------------------------------------Di 28. Sep 09:05:28 2010----------*
 * @method  CoeValueWidget::SetValue                         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmValue* #p_pCdmValue                           //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Di 28. Sep 09:05:28 2010----------*/
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

/** +-=---------------------------------------------------------Fri Dec 12 10:34:30 2003----------*
 * @method  CoeValueWidget::SetReadOnly                   // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:34:30 2003---------*/
void CoeValueWidget::SetReadOnly(  )
{
}

void CoeValueWidget::SetEditable()
{

}

/** +-=---------------------------------------------------------Mo 3. Sep 16:27:30 2012-----------*
 * @method  CoeValueWidget::SetDisplayType                   // public                            *
 * @return  void                                             //                                   *
 * @param   EdmStringDisplayType p_eOeDisplayType            //                                   *
 * @comment This method sets the displaytype of the widget.                                       *
 *----------------last changed: --------------------------------Mo 3. Sep 16:27:30 2012-----------*/
void CoeValueWidget::SetDisplayType(EdmStringDisplayType p_eOeDisplayType)
{

   m_eOeDisplayType = p_eOeDisplayType;
}

/** +-=---------------------------------------------------------Di 8. Mai 20:53:05 2007-----------*
 * @method  CoeValueWidget::SetCaptionLineEdit               // public                            *
 * @return  void                                             //                                   *
 * @param   QLineEdit* p_pqleCaption                         //                                   *
 * @comment This method sets the caption lineedit with makes it possible that every change        *
 *          of this widget will be set to the caption lineedit.                                   *
 *----------------last changed: Wolfgang GraÃŸhof----------------Di 8. Mai 20:53:05 2007-----------*/
void CoeValueWidget::SetCaptionLineEdit(QLineEdit* p_pqleCaption)
{
   m_rpqleCaption = p_pqleCaption;
}


/** +-=---------------------------------------------------------Mi 10. Sep 19:27:22 2008----------*
 * @method  CoeValueWidget::SetCaption                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment Sets a new caption to the value.                                                      *
 *----------------last changed: --------------------------------Mi 10. Sep 19:27:22 2008----------*/
void CoeValueWidget::SetCaption(QString p_qstrCaption)
{
   m_pqlLabel->setText(p_qstrCaption);
}

/** +-=---------------------------------------------------------Mi 10. Sep 19:28:14 2008----------*
 * @method  CoeValueWidget::SetSearchDeaultValue             // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDefault                            //                                   *
 * @comment This method sets the search default value in a searchwidget.                          *
 *----------------last changed: --------------------------------Mi 10. Sep 19:28:14 2008----------*/
void CoeValueWidget::SetSearchDeaultValue(QString p_qstrDefault)
{
    Q_UNUSED(p_qstrDefault);
   // no implementation here overwrite this method
}
