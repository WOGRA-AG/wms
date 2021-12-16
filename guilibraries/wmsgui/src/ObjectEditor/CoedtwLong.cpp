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
#include "CdmValueLong.h"
#include "CoedtwLong.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:00:17 2012----------*
 * @method  CoedtwLong::CoedtwLong                           // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:00:17 2012----------*/
CoedtwLong::CoedtwLong(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)   
{

   m_pleEdit = nullptr;
}

CoedtwLong::CoedtwLong(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
{
    m_pleEdit = nullptr;
}

/** +-=---------------------------------------------------------Mon Dec 8 16:47:23 2003-----------*
 * @method  CoedtwLong::~CoedtwLong                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:47:23 2003----------*/
CoedtwLong::~CoedtwLong(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:36:34 2012----------*
 * @method  CoedtwLong::GetEditWidget                        // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:36:34 2012----------*/
QWidget* CoedtwLong::GetEditWidget(QWidget* p_pqwParent)
{
   m_pleEdit = new QLineEdit(p_pqwParent);
   m_pleEdit->setAlignment(Qt::AlignmentFlag::AlignRight);
   QIntValidator* pqdvValidator = new QIntValidator(m_pleEdit); // rethink this, this is wrong
   m_pleEdit->setValidator(pqdvValidator);
   
   connect(m_pleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));
   return m_pleEdit;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:47 2003----------*
 * @method  CoedtwLong::SetValue                          // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:47 2003---------*/
void CoedtwLong::SetValue(  CdmValue* p_pCdmValue )
{
   if (CHKPTR(p_pCdmValue) && CHKPTR(m_pleEdit))
   {
      QString qstrValue = p_pCdmValue->GetDisplayString();//QString::number(((CdmValueLong*)p_pCdmValue)->GetValue());

      if (qstrValue != m_pleEdit->text())
      {
         m_pleEdit->setText(qstrValue);
      }
   }
}

void CoedtwLong::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && CHKPTR(m_pleEdit))
    {
        QString qstrValue = m_rpCdmValue->GetDisplayString();

        if (qstrValue != m_pleEdit->text())
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
 * @method  CoedtwLong::ValueChangedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:23 2003---------*/
void CoedtwLong::ValueChangedSlotByUser(  )
{
   ((CdmValueLong*)m_rpCdmValue)->SetValue(m_pleEdit->text().toLong());

   if (m_rpqleCaption)
   {
      m_rpqleCaption->setText(m_pleEdit->text());
   }
   setEventClassValue();
}
