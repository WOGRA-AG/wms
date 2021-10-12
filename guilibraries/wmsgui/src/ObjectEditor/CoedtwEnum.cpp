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
#include <QComboBox>


// own Includes
#include "CdmLogging.h"
#include "CdmValueEnum.h"
#include "CoedtwEnum.h"


/** +-=---------------------------------------------------------Di 28. Aug 14:37:26 2012----------*
 * @method  CoedtwEnum::CoedtwEnum                           // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constructor for valueediting.                                                     *
 *----------------last changed: --------------------------------Di 28. Aug 14:37:26 2012----------*/
CoedtwEnum::CoedtwEnum(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent)   
{
   m_pqcbComboBox = nullptr;
}

CoedtwEnum::CoedtwEnum(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
 {
    m_pqcbComboBox = nullptr;
 }

/** +-=---------------------------------------------------------Di 28. Aug 14:37:31 2012----------*
 * @method  CoedtwEnum::CoedtwEnum                           // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constuctor for searching.                                                         *
 *----------------last changed: --------------------------------Di 28. Aug 14:37:31 2012----------*/
CoedtwEnum::CoedtwEnum(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)   
{
   m_pqcbComboBox = nullptr;
}

/** +-=---------------------------------------------------------Di 28. Aug 14:37:37 2012----------*
 * @method  CoedtwEnum::~CoedtwEnum                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *----------------last changed: --------------------------------Di 28. Aug 14:37:37 2012----------*/
CoedtwEnum::~CoedtwEnum()
{

   // nothing to do
}

/** +-=---------------------------------------------------------Di 28. Aug 14:37:47 2012----------*
 * @method  CoedtwEnum::GetEditWidget                        // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 14:37:47 2012----------*/
QWidget* CoedtwEnum::GetEditWidget(QWidget* p_pqwParent)
{
   m_pqcbComboBox = new QComboBox(p_pqwParent);
   connect(m_pqcbComboBox, SIGNAL(activated), this, SLOT(ValueChangedSlotByUser()));
   return m_pqcbComboBox;
}

/** +-=---------------------------------------------------------Di 28. Aug 14:37:52 2012----------*
 * @method  CoedtwEnum::SetValue                             // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Di 28. Aug 14:37:52 2012----------*/
void CoedtwEnum::SetValue(CdmValue* p_pCdmValue)
{
   if (m_pqcbComboBox && p_pCdmValue)
   {
      QStringList qstrlSelection = ((CdmValueEnum*)p_pCdmValue)->GetSelectionList();

      m_pqcbComboBox->clear();
      m_pqcbComboBox->addItem("-");

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
      }

      m_pqcbComboBox->setCurrentIndex(((CdmValueEnum*)p_pCdmValue)->GetValue() + 1);
   }
}

void CoedtwEnum::setEventClassValue()
{
    if(m_pqcbComboBox && m_rpCdmValue)
    {
        QStringList qstrlSelection = ((CdmValueEnum*)m_rpCdmValue)->GetSelectionList();

        m_pqcbComboBox->clear();
        m_pqcbComboBox->addItem("-");

        for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
        {
           m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
        }

        m_pqcbComboBox->setCurrentIndex(((CdmValueEnum*)m_rpCdmValue)->GetValue() + 1);

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------So 7. Okt 13:31:14 2012-----------*
 * @method  CoedtwEnum::AddSelectionValuesToComboBox         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 7. Okt 13:31:14 2012-----------*/
void CoedtwEnum::AddSelectionValuesToComboBox()
{
   if (m_pqcbComboBox)
   {
      QStringList qstrlSelection;

      if (m_rpCdmMember)
      {
         qstrlSelection = m_rpCdmMember->GetSelectionList();
      }

      m_pqcbComboBox->clear();
      m_pqcbComboBox->addItem("-");

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqcbComboBox->addItem(qstrlSelection[iCounter]);
      }
   }
}

/** +-=---------------------------------------------------------Di 28. Aug 14:38:08 2012----------*
 * @method  CoedtwEnum::ValueChangedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *----------------last changed: --------------------------------Di 28. Aug 14:38:08 2012----------*/
void CoedtwEnum::ValueChangedSlotByUser()
{
   if (m_pqcbComboBox && m_rpCdmValue)
   {
      ((CdmValueEnum*)m_rpCdmValue)->SetValue(m_pqcbComboBox->currentIndex() - 1);
   }
   setEventClassValue();
}

/** +-=---------------------------------------------------------Di 28. Aug 14:38:21 2012----------*
 * @method  CoedtwEnum::SetReadOnly                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *----------------last changed: --------------------------------Di 28. Aug 14:38:21 2012----------*/
void CoedtwEnum::SetReadOnly()
{
   m_pqcbComboBox->setEnabled(false);
}

void CoedtwEnum::SetEditable()
{
    m_pqcbComboBox->setEnabled(true);
}

/** +-=---------------------------------------------------------Di 28. Aug 14:38:31 2012----------*
 * @method  CoedtwEnum::GetSearchWidget                      // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 14:38:31 2012----------*/
QWidget* CoedtwEnum::GetSearchWidget(QWidget* p_pqwParent)
{
   m_pqcbComboBox = new QComboBox(p_pqwParent);
   AddSelectionValuesToComboBox();
   return m_pqcbComboBox;
}

/** +-=---------------------------------------------------------Di 28. Aug 14:38:43 2012----------*
 * @method  CoedtwEnum::AddQueryElement                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 14:38:43 2012----------*/
void CoedtwEnum::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent) && m_pqcbComboBox->currentIndex() > 0)
   {
      EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareType);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_pqcbComboBox->currentIndex()-1);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}
