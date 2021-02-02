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
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>


// own Includes
#include "CdmLogging.h"
#include "CdmValueString.h"
#include "CoedtwString.h"


/** +-=---------------------------------------------------------Mi 22. Aug 10:59:39 2012----------*
 * @method  CoedtwString::CoedtwString                       // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constructor for valueediting.                                                     *
 *----------------last changed: --------------------------------Mi 22. Aug 10:59:39 2012----------*/
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

/** +-=---------------------------------------------------------Mo 8. Sep 19:24:58 2008-----------*
 * @method  CoedtwString::CoedtwString                       // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constuctor for searching.                                                         *
 *----------------last changed: --------------------------------Mo 8. Sep 19:24:58 2008-----------*/
CoedtwString::CoedtwString(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent)   
{
   m_pqleEdit = nullptr;
}

/** +-=---------------------------------------------------------Mon Dec 8 16:49:02 2003-----------*
 * @method  CoedtwString::~CoedtwString                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:49:02 2003----------*/
CoedtwString::~CoedtwString(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:44:57 2012----------*
 * @method  CoedtwString::GetEditWidget                      // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:44:57 2012----------*/
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
      pqpbSearch->setText(tr("Suchen"));
      connect(pqpbSearch, SIGNAL(clicked()), this, SLOT(SearchClickedSlot()));
      pqLayout->addWidget(pqpbSearch);
      return pqwParent;
   }
   else
   {
      return m_pqleEdit;
   }
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:34 2003----------*
 * @method  CoedtwString::SetValue                           // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:34 2003---------*/
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

/** +-=---------------------------------------------------------Fr 20. Jan 23:18:54 2006----------*
 * @method  CoedtwString::SearchClickedSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the search button was clicked.                            *
 *----------------last changed: Wolfgang GraÃŸhof----------------Fr 20. Jan 23:18:54 2006----------*/
void CoedtwString::SearchClickedSlot(  )
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

/** +-=---------------------------------------------------------Wed Dec 10 16:52:49 2003----------*
 * @method  CoedtwString::ValueChangedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:49 2003---------*/
void CoedtwString::ValueChangedSlotByUser(  )
{
   if ( m_pqleEdit && m_rpCdmValue)
   {
      ((CdmValueString*)m_rpCdmValue)->SetValue(m_pqleEdit->text());

      if (m_rpqleCaption)
      {
         m_rpqleCaption->setText(m_pqleEdit->text());
      }
   }
   setEventClassValue();
}

/** +-=---------------------------------------------------------Fri Dec 12 10:36:26 2003----------*
 * @method  CoedtwString::SetReadOnly                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:36:26 2003---------*/
void CoedtwString::SetReadOnly(  )
{
   m_pqleEdit->setReadOnly(true);
}

void CoedtwString::SetEditable()
{
    m_pqleEdit->setReadOnly(false);
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:48:15 2012----------*
 * @method  CoedtwString::GetSearchWidget                    // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:48:15 2012----------*/
QWidget* CoedtwString::GetSearchWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);

   QHBoxLayout* pqhblLayout = new QHBoxLayout(pqwWidget);

   m_pqcbComboBox = new QComboBox(pqwWidget);
   m_pqcbComboBox->addItem(tr("beginnt mit"));
   m_pqcbComboBox->addItem(tr("enthält"));
   m_pqcbComboBox->addItem(tr("gleich"));
   m_pqcbComboBox->addItem(tr("endet mit"));
   m_pqcbComboBox->setCurrentIndex(1);
   pqhblLayout->addWidget(m_pqcbComboBox);

   m_pqleEdit = new QLineEdit(pqwWidget); // must be a special lineedit for double values.
   pqhblLayout->addWidget(m_pqleEdit);
   return pqwWidget;
}

/** +-=---------------------------------------------------------Sa 6. Sep 14:00:11 2008-----------*
 * @method  CoedtwString::AddQueryElement                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Sep 14:00:11 2008-----------*/
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

/** +-=---------------------------------------------------------Mi 10. Sep 20:27:16 2008----------*
 * @method  CoedtwString::SetSearchDeaultValue               // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDefault                            //                                   *
 * @comment This method sets the search default value in a searchwidget.                          *
 *----------------last changed: --------------------------------Mi 10. Sep 20:27:16 2008----------*/
void CoedtwString::SetSearchDeaultValue(QString p_qstrDefault)
{
   m_pqleEdit->setText(p_qstrDefault);
}
