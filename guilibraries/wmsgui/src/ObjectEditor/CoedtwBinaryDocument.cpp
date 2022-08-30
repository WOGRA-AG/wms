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
#include <QFileDialog>
#include <qpushbutton.h>


// own Includes
#include "CdmLogging.h"
#include "CdmValueBinaryDocument.h"
#include "CoedtwBinaryDocument.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:02:32 2012----------*
 * @method  CoedtwBinaryDocument::CoedtwBinaryDocument       // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:02:32 2012----------*/
CoedtwBinaryDocument::CoedtwBinaryDocument(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqleFilename(nullptr),
  m_pqpbOpen(nullptr),
  m_pqpbSelect(nullptr)
{

}

CoedtwBinaryDocument::CoedtwBinaryDocument(const CdmObject *pEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
   m_pqleFilename(nullptr),
   m_pqpbOpen(nullptr),
   m_pqpbSelect(nullptr)
 {

 }

/** +-=---------------------------------------------------------Mon Dec 8 16:29:15 2003-----------*
 * @method  CoedtwBinaryDocument::~CoedtwBinaryDocument      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *                                                                                                *
 *---------------------------------------------------------------Mon Dec 8 16:29:15 2003----------*/
CoedtwBinaryDocument::~CoedtwBinaryDocument(  )
{
}

/** +-=---------------------------------------------------------Mi 22. Aug 13:54:48 2012----------*
 * @method  CoedtwBinaryDocument::GetEditWidget              // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 13:54:48 2012----------*/
QWidget* CoedtwBinaryDocument::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqwWidget = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqwWidget);

   m_pqleFilename = new QLineEdit(pqwWidget);
   m_pqleFilename->setReadOnly(true);
   pqLayout->addWidget(m_pqleFilename);

   m_pqpbSelect = new QPushButton(pqwWidget);
   m_pqpbSelect->setText(tr("Auswahl"));
   pqLayout->addWidget(m_pqpbSelect);
   connect(m_pqpbSelect, SIGNAL(clicked()), this, SLOT(SelectClickedSlot()));

   m_pqpbOpen = new QPushButton(pqwWidget);
   m_pqpbOpen->setText(tr("Öffnen"));
   pqLayout->addWidget(m_pqpbOpen);
   connect(m_pqpbOpen, SIGNAL(clicked()), this, SLOT(OpenClickedSlot()));

   return pqwWidget;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:51:46 2003----------*
 * @method  CoedtwBinaryDocument::ValueChangedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:51:46 2003---------*/
void CoedtwBinaryDocument::ValueChangedSlotByUser()
{
	if (CHKPTR(m_rpCdmValue))
	{
		CdmValueBinaryDocument* pCdmValueBinDoc = (CdmValueBinaryDocument*)m_rpCdmValue;

		QString qstrFile = m_pqleFilename->text();
		QString qstrExtension;

		int iExtensionPos = qstrFile.lastIndexOf(".");

		if (iExtensionPos > 0)
		{
			qstrExtension = qstrFile.right(qstrFile.length() - iExtensionPos - 1);
		}

        pCdmValueBinDoc->SetValue(qstrFile, qstrExtension);

		if (m_rpqleCaption)
		{
			m_rpqleCaption->setText(m_pqleFilename->text());
		}
	}
}

/** +-=---------------------------------------------------------Wed Dec 10 16:51:25 2003----------*
 * @method  CoedtwBinaryDocument::SetValue                   // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:51:25 2003---------*/
void CoedtwBinaryDocument::SetValue(  CdmValue* p_pCdmValue )
{
   if (CHKPTR(p_pCdmValue) && p_pCdmValue->GetValueType() == eDmValueBinaryDocument)
   {
     m_pqleFilename->setText(((CdmValueBinaryDocument*)p_pCdmValue)->GetFilename());
     //connect(m_pqleFilename, SIGNAL(textChanged(const QString &)), this, SLOT(ValueChangedSlotByUser()));
   }
}

void CoedtwBinaryDocument::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue))
    {
        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
            m_pqleFilename->setText(((CdmValueBinaryDocument*)m_rpCdmValue)->GetFilename());
        }
    }
}

/** +-=---------------------------------------------------------Sa 31. Mai 09:22:29 2008----------*
 * @method  CoedtwBinaryDocument::SelectClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to select a file from                      *
 *          fileselectionbox.                                                                     *
 *----------------last changed: --------------------------------Sa 31. Mai 09:22:29 2008----------*/
void CoedtwBinaryDocument::SelectClickedSlot()
{
   QString qstrFilename = QFileDialog::getOpenFileName(nullptr,
                                                       tr("Bitte wählen Sie das Dokument aus."));


   m_pqleFilename->setText(qstrFilename);
   ValueChangedSlotByUser();
}

/** +-=---------------------------------------------------------Sa 31. Mai 09:23:10 2008----------*
 * @method  CoedtwBinaryDocument::OpenClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to open the stored file.                   *
 *----------------last changed: --------------------------------Sa 31. Mai 09:23:10 2008----------*/
void CoedtwBinaryDocument::OpenClickedSlot()
{
   if (CHKPTR(m_rpCdmValue))
   {
      CdmValueBinaryDocument* pCdmValueBinDoc = (CdmValueBinaryDocument*)m_rpCdmValue;
      pCdmValueBinDoc->ExecuteFile();
   }
}

/** +-=---------------------------------------------------------Fri Dec 12 10:34:46 2003----------*
 * @method  CoedtwBinaryDocument::SetReadOnly                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:34:46 2003---------*/
void CoedtwBinaryDocument::SetReadOnly(  )
{
   m_pqleFilename->setReadOnly(true);
   m_pqpbSelect->hide();
}

void CoedtwBinaryDocument::SetEditable()
{
    m_pqleFilename->setReadOnly(false);
    m_pqpbSelect->show();
}
