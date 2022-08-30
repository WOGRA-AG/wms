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
#include <QTextEdit>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QHBoxLayout>

// own Includes
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
#include "CoeTextEditMainWindow.h"
#include "CoeTextEditIf.h"
#include "CoedtwCharacterDocument.h"

/** +-=---------------------------------------------------------Mi 22. Aug 11:02:02 2012----------*
 * @method  CoedtwCharacterDocument::CoedtwCharacterDocument // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:02:02 2012----------*/
CoedtwCharacterDocument::CoedtwCharacterDocument(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
   m_pqteTextEdit(nullptr),
   m_pTextEdit(nullptr),
   m_pqpbEdit(nullptr)

{
   if (CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pMember = m_rpCdmValue->GetMember();

      if (CHKPTR(pMember))
      {
         SetDisplayType((EdmStringDisplayType)pMember->GetClassReference());
      }
   }
}

CoedtwCharacterDocument::CoedtwCharacterDocument(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
    m_pqteTextEdit(nullptr),
    m_pTextEdit(nullptr),
    m_pqpbEdit(nullptr)

 {
    if (CHKPTR(m_rpCdmValue))
    {
       const CdmMember* pMember = m_rpCdmValue->GetEventMember(pEventObject);

       if (CHKPTR(pMember))
       {
          SetDisplayType((EdmStringDisplayType)pMember->GetClassReference());
       }
    }
 }

/** +-=---------------------------------------------------------Mon Dec 8 16:44:46 2003-----------*
 * @method  CoedtwCharacterDocument::~CoedtwCharacterDocument // public, virtual                  *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:44:46 2003----------*/
CoedtwCharacterDocument::~CoedtwCharacterDocument(  )
{
   // nothing to do QT does it for us
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:55:14 2012-----------*
 * @method  CoedtwCharacterDocument::GetTabEditWidget        // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:55:14 2012-----------*/
QWidget* CoedtwCharacterDocument::GetTabEditWidget(QWidget* p_pqwParent)
{
   QWidget* pWidget = nullptr;

   if (m_eOeDisplayType == edmStringDisplayTypeFormatted)
   {
      if (!m_pTextEdit)
      {
         m_pTextEdit = new CoeTextEditMainWindow(p_pqwParent);
         connect(m_pTextEdit->GetTextEdit(), SIGNAL(textChanged()), this, SLOT(ValueChangedSlotByUser()));
      }

      pWidget = m_pTextEdit;
   }
   else 
   {
      if (!m_pqteTextEdit)
      {
         m_pqteTextEdit = new QTextEdit(p_pqwParent);
         connect(m_pqteTextEdit, SIGNAL(textChanged()), this, SLOT(ValueChangedSlotByUser()));
      }

      pWidget = m_pqteTextEdit;
   }

   return pWidget;
}

/** +-=---------------------------------------------------------Mi 22. Aug 13:58:29 2012----------*
 * @method  CoedtwCharacterDocument::GetEditWidget           // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_qwParent                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 13:58:29 2012----------*/
QWidget* CoedtwCharacterDocument::GetEditWidget(QWidget* p_qwParent)
{

   QWidget* pqwWidget = new QWidget(p_qwParent);
   QVBoxLayout* pqvblLayout = new QVBoxLayout(pqwWidget);

   QHBoxLayout* pqhbButton = new QHBoxLayout(pqwWidget);

   QSpacerItem* pqSeperator = new QSpacerItem(1,1, QSizePolicy::Expanding);
   pqhbButton->addItem(pqSeperator);

   m_pqpbEdit = new QPushButton(pqwWidget);
   m_pqpbEdit->setText(tr("Bearbeiten"));
   m_pqpbEdit->setMaximumWidth(90);
   pqhbButton->addWidget(m_pqpbEdit);
   pqvblLayout->addLayout(pqhbButton);


   m_pqteTextEdit = new QTextEdit(pqwWidget);
   m_pqteTextEdit->setReadOnly(true);
   pqvblLayout->addWidget(m_pqteTextEdit);


   connect(m_pqpbEdit, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
   return pqwWidget;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:57 2003----------*
 * @method  CoedtwCharacterDocument::SetValue                // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:57 2003---------*/
void CoedtwCharacterDocument::SetValue(  CdmValue* p_pCdmValue )
{
   if (CHKPTR(p_pCdmValue))
   {
	   QString qstrValue = ((CdmValueCharacterDocument*)p_pCdmValue)->GetValue();

      if (m_pqteTextEdit)
      {
		  

		  if (m_pqteTextEdit->toPlainText() != qstrValue)
		  {
			m_pqteTextEdit->setPlainText(qstrValue);

			 if (m_rpqleCaption)
			 {
				m_rpqleCaption->setText(m_pqteTextEdit->toPlainText());
			 }
		  }
      }
      else if (m_pTextEdit)
      {
		  if (m_pTextEdit->GetText() != qstrValue)
		  {
			m_pTextEdit->SetText(qstrValue);
		  }
      }
   }
}

void CoedtwCharacterDocument::setEventClassValue()
{

    if(CHKPTR(m_rpCdmValue))
    {
        QString qstrValue = ((CdmValueCharacterDocument*)m_rpCdmValue)->GetValue();
        if(m_pqteTextEdit)
        {
            if(m_pqteTextEdit->toPlainText() != qstrValue)
            {
                m_pqteTextEdit->setPlainText(qstrValue);
                if(m_rpqleCaption)
                {
                    m_rpqleCaption->setText(m_pqteTextEdit->toPlainText());
                }
            }
        }
        else if(m_pTextEdit)
        {
            if(m_pTextEdit->GetText() != qstrValue)
            {
                m_pTextEdit->SetText(qstrValue);
            }
        }
        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Wed Dec 10 16:52:03 2003----------*
 * @method  CoedtwCharacterDocument::ValueChangedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:03 2003---------*/
void CoedtwCharacterDocument::ValueChangedSlotByUser(  )
{
   if (m_pqteTextEdit)
   {
      ((CdmValueCharacterDocument*)m_rpCdmValue)->SetValue(m_pqteTextEdit->toPlainText());
   }
   else if(m_pTextEdit)
   {
      ((CdmValueCharacterDocument*)m_rpCdmValue)->SetValue(m_pTextEdit->GetText());
   }
}

/** +-=---------------------------------------------------------Fri Dec 12 10:35:07 2003----------*
 * @method  CoedtwCharacterDocument::SetReadOnly             // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:35:07 2003---------*/
void CoedtwCharacterDocument::SetReadOnly(  )
{
   if (m_pqpbEdit)
   {
      m_pqpbEdit->hide();
   }

   if (m_pTextEdit)
   {
      m_pTextEdit->GetTextEdit()->setReadOnly(true);
   }
   
}

void CoedtwCharacterDocument::SetEditable()
{
    if(m_pqpbEdit)
    {
        m_pqpbEdit->show();
    }

    if(m_pTextEdit)
    {
        m_pTextEdit->GetTextEdit()->setReadOnly(false);
    }
}

/** +-=---------------------------------------------------------Mi 4. Jun 19:45:44 2008-----------*
 * @method  CoedtwCharacterDocument::EditClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the edit button was clicked. it opens the edit            *
 *          dialog.                                                                               *
 *----------------last changed: --------------------------------Mi 4. Jun 19:45:44 2008-----------*/
void CoedtwCharacterDocument::EditClickedSlot()
{
   CoeTextEditIf* pCoeTextEdit = new CoeTextEditIf(nullptr);
   pCoeTextEdit->SetText(m_pqteTextEdit->toHtml());

   if (pCoeTextEdit->exec() == QDialog::Accepted)
   {
      m_pqteTextEdit->setText(pCoeTextEdit->GetText());
      ValueChangedSlotByUser();
   }
}
