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
#include <qlineedit.h>
#include <qvalidator.h>

// own Includes
#include "CdmLogging.h"
#include "CdmValueInt.h"
#include "CoedtwInteger.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:01:08 2012----------*
 * @method  CoedtwInteger::CoedtwInteger                     // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:01:08 2012----------*/
CoedtwInteger::CoedtwInteger(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pleEdit(nullptr)
{

}

CoedtwInteger::CoedtwInteger(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent)
    : CoeValueWidget(pCdmEventObject, p_pCdmValue, p_pqwParent),
      m_pleEdit(nullptr)
{

}


/** +-=---------------------------------------------------------Mon Dec 8 16:47:23 2003-----------*
 * @method  CoedtwInteger::~CoedtwInteger                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:47:23 2003----------*/
CoedtwInteger::~CoedtwInteger(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:34:04 2012----------*
 * @method  CoedtwInteger::GetEditWidget                     // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:34:04 2012----------*/
QWidget* CoedtwInteger::GetEditWidget(QWidget* p_pqwParent)
{
   m_pleEdit = new QLineEdit(p_pqwParent);
   m_pleEdit->setAlignment(Qt::AlignmentFlag::AlignRight);
   QIntValidator* pqdvValidator = new QIntValidator(m_pleEdit);
   m_pleEdit->setValidator(pqdvValidator);
   
   connect(m_pleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));
   return m_pleEdit;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:47 2003----------*
 * @method  CoedtwInteger::SetValue                          // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:47 2003---------*/
void CoedtwInteger::SetValue(CdmValue* p_pCdmValue)
{
   if (CHKPTR(p_pCdmValue) && CHKPTR(m_pleEdit))
   {
      QString qstrValue = p_pCdmValue->GetDisplayString();//QString::number(((CdmValueInt*)p_pCdmValue)->GetValue());

      if (qstrValue != m_pleEdit->text())
      {
         m_pleEdit->setText(qstrValue);
      }
   }
}

void CoedtwInteger::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && CHKPTR(m_pleEdit))
    {
        QString qstrValue = m_rpCdmValue->GetDisplayString();

        if(qstrValue != m_pleEdit->text())
        {
            m_pleEdit->setText(qstrValue);
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Wed Dec 10 16:52:23 2003----------*
 * @method  CoedtwInteger::ValueChangedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:23 2003---------*/
void CoedtwInteger::ValueChangedSlotByUser(  )
{
    if(m_pleEdit && m_rpCdmValue)
    {
        QLocale loc;
        ((CdmValueInt*)m_rpCdmValue)->SetValue(loc.toInt(m_pleEdit->text()));

        if (m_rpqleCaption)
        {
           m_rpqleCaption->setText(m_pleEdit->text());
        }
    }
}

/** +-=---------------------------------------------------------Fri Dec 12 10:35:46 2003----------*
 * @method  CoedtwInteger::SetReadOnly                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:35:46 2003---------*/
void CoedtwInteger::SetReadOnly(  )
{
   m_pleEdit->setReadOnly(true);
}

void CoedtwInteger::SetEditable()
{
    m_pleEdit->setReadOnly(false);
}

