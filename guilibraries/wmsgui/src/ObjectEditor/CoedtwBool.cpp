/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qcheckbox.h>

// WMS Includes
#include "CdmValueBool.h"
#include "CdmLogging.h"

// own Includes
#include "CoedtwBool.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:02:22 2012----------*
 * @method  CoedtwBool::CoedtwBool                           // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:02:22 2012----------*/
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

/** +-=---------------------------------------------------------Mo 8. Sep 19:20:39 2008-----------*
 * @method  CoedtwBool::CoedtwBool                           // public                            *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 8. Sep 19:20:39 2008-----------*/
CoedtwBool::CoedtwBool(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)
{

   m_pqchbCheckbox = nullptr;
}


/** +-=---------------------------------------------------------Mon Dec 8 16:31:59 2003-----------*
 * @method  CoedtwBool::~CoedtwBool                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:31:59 2003----------*/
CoedtwBool::~CoedtwBool(  )
{
   // nothing todo qt does it for us :-)
}

/** +-=---------------------------------------------------------Mi 22. Aug 13:57:06 2012----------*
 * @method  CoedtwBool::GetEditWidget                        // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 13:57:06 2012----------*/
QWidget* CoedtwBool::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqchbCheckbox = new QCheckBox(p_pqwParent);
   connect(m_pqchbCheckbox, SIGNAL(clicked()), this, SLOT(ValueChangedSlotByUser()));
   return m_pqchbCheckbox;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:55:48 2003----------*
 * @method  CoedtwBool::ValueChangedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:55:48 2003---------*/
void CoedtwBool::ValueChangedSlotByUser(  )
{
   if ( m_pqchbCheckbox && m_rpCdmValue)
   {
      ((CdmValueBool*)m_rpCdmValue)->SetValue(m_pqchbCheckbox->isChecked());
   }
   setEventClassValue();
}

/** +-=---------------------------------------------------------Wed Dec 10 16:51:12 2003----------*
 * @method  CoedtwBool::SetValue                             // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:51:12 2003---------*/
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

/** +-=---------------------------------------------------------Fri Dec 12 10:34:57 2003----------*
 * @method  CoedtwBool::SetReadOnly                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:34:57 2003---------*/
void CoedtwBool::SetReadOnly(  )
{
   m_pqchbCheckbox->setEnabled(false);
}

void CoedtwBool::SetEditable()
{
    m_pqchbCheckbox->setEnabled(true);
}

/** +-=---------------------------------------------------------Mi 22. Aug 13:57:27 2012----------*
 * @method  CoedtwBool::GetSearchWidget                      // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 13:57:27 2012----------*/
QWidget* CoedtwBool::GetSearchWidget(QWidget* p_pqwParent)
{

   m_pqchbCheckbox = new QCheckBox(p_pqwParent);
   m_pqchbCheckbox->setTristate(true);
   m_pqchbCheckbox->setCheckState(Qt::PartiallyChecked);
   return m_pqchbCheckbox;
}

/** +-=---------------------------------------------------------Sa 6. Sep 14:03:19 2008-----------*
 * @method  CoedtwBool::AddQueryElement                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Sep 14:03:19 2008-----------*/
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

/** +-=---------------------------------------------------------Mi 10. Sep 20:25:14 2008----------*
 * @method  CoedtwBool::SetSearchDeaultValue                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDefault                            //                                   *
 * @comment This method sets the search default value in a searchwidget.                          *
 *----------------last changed: --------------------------------Mi 10. Sep 20:25:14 2008----------*/
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
