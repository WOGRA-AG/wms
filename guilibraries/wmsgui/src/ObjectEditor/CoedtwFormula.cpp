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
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>

// own Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmValueString.h"
#include "CoedtwFormula.h"


/** +-=---------------------------------------------------------Di 28. Aug 14:24:49 2012----------*
 * @method  CoedtwFormula::CoedtwFormula                   // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constructor for valueediting.                                                     *
 *----------------last changed: --------------------------------Di 28. Aug 14:24:49 2012----------*/
CoedtwFormula::CoedtwFormula(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)   
{
   m_pqleEdit = nullptr;
   const CdmObject* pObject = p_pCdmValue->GetObject();

   if (CHKPTR(pObject))
   {
      connect(pObject, SIGNAL(ObjectModifiedSignal(CdmObject*)), this, SLOT(ValueChangedSlotByUser()));
   }
}

CoedtwFormula::CoedtwFormula(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
 {
    m_pqleEdit = nullptr;

    if (CHKPTR(pEventObject))
    {
       connect(pEventObject, SIGNAL(ObjectModifiedSignal(CdmObject*)), this, SLOT(ValueChangedSlotByUser()));
    }
 }

/** +-=---------------------------------------------------------Di 28. Aug 14:24:54 2012----------*
 * @method  CoedtwFormula::CoedtwFormula                   // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constuctor for searching.                                                         *
 *----------------last changed: --------------------------------Di 28. Aug 14:24:54 2012----------*/
CoedtwFormula::CoedtwFormula(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)   
{
   m_pqleEdit = nullptr;
}

/** +-=---------------------------------------------------------Di 28. Aug 14:24:59 2012----------*
 * @method  CoedtwFormula::~CoedtwFormula                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *----------------last changed: --------------------------------Di 28. Aug 14:24:59 2012----------*/
CoedtwFormula::~CoedtwFormula()
{
   // nothing to do
}

/** +-=---------------------------------------------------------Di 28. Aug 14:25:06 2012----------*
 * @method  CoedtwFormula::GetEditWidget                    // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 14:25:06 2012----------*/
QWidget* CoedtwFormula::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqleEdit = new QLineEdit(p_pqwParent);
   m_pqleEdit->setReadOnly(true);
   return m_pqleEdit;
}

/** +-=---------------------------------------------------------Di 28. Aug 14:25:15 2012----------*
 * @method  CoedtwFormula::SetValue                         // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Di 28. Aug 14:25:15 2012----------*/
void CoedtwFormula::SetValue(CdmValue* p_pCdmValue)
{
   if (m_pqleEdit && p_pCdmValue)
   {
     m_pqleEdit->setText(p_pCdmValue->GetDisplayString());
   }
}

void CoedtwFormula::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue))
    {
        m_pqleEdit->setText(m_rpCdmValue->GetDisplayString());
        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Di 28. Aug 14:25:25 2012----------*
 * @method  CoedtwFormula::ValueChangedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *----------------last changed: --------------------------------Di 28. Aug 14:25:25 2012----------*/
void CoedtwFormula::ValueChangedSlotByUser()
{
   if ( m_pqleEdit && m_rpCdmValue)
   {
      SetValue(m_rpCdmValue);
   }
   setEventClassValue();
}

/** +-=---------------------------------------------------------Di 28. Aug 14:25:42 2012----------*
 * @method  CoedtwFormula::SetReadOnly                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *----------------last changed: --------------------------------Di 28. Aug 14:25:42 2012----------*/
void CoedtwFormula::SetReadOnly()
{
   m_pqleEdit->setReadOnly(true);
}

void CoedtwFormula::SetEditable()
{
    m_pqleEdit->setReadOnly(false);
}
