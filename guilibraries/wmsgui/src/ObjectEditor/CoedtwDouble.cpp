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
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

// own Includes
#include "CdmLogging.h"
#include "CdmValueDouble.h"
#include "CdmValueFloat.h"
#include "CoedtwDouble.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:01:27 2012----------*
 * @method  CoedtwDouble::CoedtwDouble                       // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:01:27 2012----------*/
CoedtwDouble::CoedtwDouble(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqcbComboBox(nullptr)
{

   m_pqleEdit = nullptr;
}

CoedtwDouble::CoedtwDouble(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_pqcbComboBox(nullptr)
{
    m_pqleEdit = nullptr;
}

/** +-=---------------------------------------------------------Mo 8. Sep 19:24:32 2008-----------*
 * @method  CoedtwDouble::CoedtwDouble                       // public                            *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 8. Sep 19:24:32 2008-----------*/
CoedtwDouble::CoedtwDouble(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
  m_pqcbComboBox(nullptr)   
{

   m_pqleEdit = nullptr;
}

/** +-=---------------------------------------------------------Mon Dec 8 16:45:24 2003-----------*
 * @method  CoedtwDouble::~CoedtwDouble                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:45:24 2003----------*/
CoedtwDouble::~CoedtwDouble(  )
{
   // nothing to do QT does it for us
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:54:40 2012----------*
 * @method  CoedtwDouble::GetEditWidget                      // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:54:40 2012----------*/
QWidget* CoedtwDouble::GetEditWidget(QWidget* p_pqwParent)
{
    QWidget* pqwWidget = new QWidget(p_pqwParent);
    QHBoxLayout* pqLayout = new QHBoxLayout(pqwWidget);


    if (!m_rpCdmMember->GetPrefix().isEmpty())
    {
        m_pqlPrefix = new QLabel(pqwWidget);
        pqLayout->addWidget(m_pqlPrefix);
    }

   m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
   m_pqleEdit->setAlignment(Qt::AlignmentFlag::AlignRight);
   pqLayout->addWidget(m_pqleEdit);

   if (!m_rpCdmMember->GetSuffix().isEmpty())
   {
       m_pqlSuffix = new QLabel(pqwWidget);
       pqLayout->addWidget(m_pqlSuffix);
   }

   pqLayout->setMargin(0);

   QDoubleValidator* pqdvValidator = new QDoubleValidator(m_pqleEdit);
   m_pqleEdit->setValidator(pqdvValidator);
   connect(m_pqleEdit, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));

   return pqwWidget;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:52 2003----------*
 * @method  CoedtwDouble::SetValue                           // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:52 2003---------*/
void CoedtwDouble::SetValue(  CdmValue* p_pCdmValue )
{
   if (CHKPTR(m_pqleEdit) && CHKPTR(p_pCdmValue))
   {
       QLocale qLocale;
	   QString qstrValue;
       const CdmMember* pMember = p_pCdmValue->GetMember();

       if (!pMember->GetSuffix().isEmpty())
       {
           m_pqlSuffix->setText(pMember->GetSuffix());
       }

       if (!pMember->GetPrefix().isEmpty())
       {
           m_pqlPrefix->setText(pMember->GetPrefix());
       }

      if (p_pCdmValue->GetValueType() == eDmValueDouble)
      {
         double dValue = ((CdmValueDouble*)p_pCdmValue)->GetValue();

         if (pMember->GetDecimalCountInput() > 0)
         {
             qstrValue = qLocale.toString(dValue, 'f', pMember->GetDecimalCountInput());
         }
         else
         {
            qstrValue = qLocale.toString(dValue, 'f', 15);
         }

         double dCurrent = qLocale.toDouble( m_pqleEdit->text()); 

         if (dValue != dCurrent)
         {
		 	   m_pqleEdit->setText(qstrValue);
		   }
      }
      else if (p_pCdmValue->GetValueType() == eDmValueFloat)
      {
         float fValue = ((CdmValueFloat*)p_pCdmValue)->GetValue();

         if (pMember->GetDecimalCountInput() > 0)
         {
             qstrValue = qLocale.toString(fValue, 'f', pMember->GetDecimalCountInput());
         }
         else
         {
            qstrValue = qLocale.toString(fValue, 'f', 7);
         }

         float fCurrent = qLocale.toFloat(m_pqleEdit->text()); 

         if (fValue != fCurrent)
         {
            m_pqleEdit->setText(qstrValue);
		   }
      }
   }
}

void CoedtwDouble::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && CHKPTR(m_pqleEdit))
    {
        QLocale qLocale;
        QString qstrValue;

        const CdmMember* pMember = m_rpCdmValue->GetMember();

        if (!pMember->GetSuffix().isEmpty())
        {
            m_pqlSuffix->setText(pMember->GetSuffix());
        }

        if (!pMember->GetPrefix().isEmpty())
        {
            m_pqlPrefix->setText(pMember->GetPrefix());
        }

        if(m_rpCdmValue->GetValueType() == eDmValueDouble)
        {
            double dValue = ((CdmValueDouble*)m_rpCdmValue)->GetValue();

            if (pMember->GetDecimalCountInput() > 0)
            {
                qstrValue = qLocale.toString(dValue, 'f', pMember->GetDecimalCountInput());
            }
            else
            {
               qstrValue = qLocale.toString(dValue, 'f', 15);
            }

            double dCurrent = qLocale.toDouble( m_pqleEdit->text());

            if (dValue != dCurrent)
            {
                  m_pqleEdit->setText(qstrValue);
            }
        }
        else if (m_rpCdmValue->GetValueType() == eDmValueFloat)
        {
           float fValue = ((CdmValueFloat*)m_rpCdmValue)->GetValue();

           if (pMember->GetDecimalCountInput() > 0)
           {
               qstrValue = qLocale.toString(fValue, 'f', pMember->GetDecimalCountInput());
           }
           else
           {
              qstrValue = qLocale.toString(fValue, 'f', 7);
           }

           float fCurrent = qLocale.toFloat(m_pqleEdit->text());

           if (fValue != fCurrent)
           {
              m_pqleEdit->setText(qstrValue);
             }
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Wed Dec 10 16:52:13 2003----------*
 * @method  CoedtwDouble::ValueChangedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:13 2003---------*/
void CoedtwDouble::ValueChangedSlotByUser(  )
{
   if (CHKPTR(m_pqleEdit))
   {
	   QLocale qLocale;
	   QString qstrValue = m_pqleEdit->text();
      if (m_rpCdmValue->GetValueType() == eDmValueDouble)
      {
		((CdmValueDouble*)m_rpCdmValue)->SetValue(qLocale.toDouble(qstrValue));
      }
      else if (m_rpCdmValue->GetValueType() == eDmValueFloat)
      {
         ((CdmValueFloat*)m_rpCdmValue)->SetValue(qLocale.toFloat(qstrValue));
      }

      if (m_rpqleCaption)
      {
         m_rpqleCaption->setText(m_pqleEdit->text());
      }
   }
}

/** +-=---------------------------------------------------------Fri Dec 12 10:35:37 2003----------*
 * @method  CoedtwDouble::SetReadOnly                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:35:37 2003---------*/
void CoedtwDouble::SetReadOnly(  )
{
   m_pqleEdit->setReadOnly(true);
}

void CoedtwDouble::SetEditable()
{
    m_pqleEdit->setReadOnly(false);
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:33:35 2012----------*
 * @method  CoedtwDouble::GetSearchWidget                    // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:33:35 2012----------*/
QWidget* CoedtwDouble::GetSearchWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);

   QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

   m_pqcbComboBox = new QComboBox(pqwWidget);
   m_pqcbComboBox->addItem(tr("gleich"));
   m_pqcbComboBox->addItem(tr("kleiner"));
   m_pqcbComboBox->addItem(tr("kleiner gleich"));
   m_pqcbComboBox->addItem(tr("größer"));
   m_pqcbComboBox->addItem(tr("größer gleich"));
   m_pqcbComboBox->setCurrentIndex(0);
   pqhblLayout->addWidget(m_pqcbComboBox);

   m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
   pqhblLayout->addWidget(m_pqleEdit);

   QDoubleValidator* pqdvValidator = new QDoubleValidator(m_pqleEdit);
   m_pqleEdit->setValidator(pqdvValidator);
   return pqwWidget;
}

/** +-=---------------------------------------------------------Sa 6. Sep 14:00:31 2008-----------*
 * @method  CoedtwDouble::AddQueryElement                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Sep 14:00:31 2008-----------*/
void CoedtwDouble::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent))
   {
      if (!m_pqleEdit->text().isEmpty())
      {
         EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;
         switch(m_pqcbComboBox->currentIndex())
         {
         case 0:
            eDmQueryCompareType = eDmQueryCompareTypeEqual;
            break;
         case 1:
            eDmQueryCompareType = eDmQueryCompareTypeSmaller;
            break;
         case 2:
            eDmQueryCompareType = eDmQueryCompareTypeSmallerEqual;
            break;
         case 3:
            eDmQueryCompareType = eDmQueryCompareTypeLarger;
            break;
         case 4:
            eDmQueryCompareType = eDmQueryCompareTypeLargerEqual;
            break;
         default:
            eDmQueryCompareType = eDmQueryCompareTypeEqual;

         }


         CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                 eDmQueryElementTypeCompare,
                                                                 eDmQueryCompareType);

         QString qstrValue = m_pqleEdit->text();
         float fValue = qstrValue.toFloat();

         pCdmQueryElement->SetComparisonValue(m_qstrKeyname, fValue);
         p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
      }
   }
}

/** +-=---------------------------------------------------------Mi 10. Sep 20:26:59 2008----------*
 * @method  CoedtwDouble::SetSearchDeaultValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDefault                            //                                   *
 * @comment This method sets the search default value in a searchwidget.                          *
 *----------------last changed: --------------------------------Mi 10. Sep 20:26:59 2008----------*/
void CoedtwDouble::SetSearchDeaultValue(QString p_qstrDefault)
{
   m_pqleEdit->setText(p_qstrDefault);
}
