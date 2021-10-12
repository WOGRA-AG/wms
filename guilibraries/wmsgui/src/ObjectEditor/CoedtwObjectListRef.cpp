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
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmap.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmValueContainerRef.h"

// BAsetools Includes
#include "CwmsFormManager.h"

// own Includes
#include "CwmsObjectListSelectionIf.h"
#include "CoedtwObjectListRef.h"
#include "CwmsObjectListEditorIf.h"
#include "CwmsObjectListSelectionIf.h"


/** +-=---------------------------------------------------------Mi 22. Aug 11:00:02 2012----------*
 * @method  CoedtwContainerRef::CoedtwContainerRef         // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 11:00:02 2012----------*/
CoedtwContainerRef::CoedtwContainerRef(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
: CoeValueWidget(p_pCdmValue, p_pqwParent)   
{
   m_pObjectListEditor = nullptr;
   m_pqleEdit          = nullptr;
   m_pqpbChange        = nullptr;
   m_pqpbView          = nullptr;
   m_pqhbLayout        = nullptr;
}

CoedtwContainerRef::CoedtwContainerRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent)
{
    m_pObjectListEditor = nullptr;
    m_pqleEdit          = nullptr;
    m_pqpbChange        = nullptr;
    m_pqpbView          = nullptr;
    m_pqhbLayout        = nullptr;
}

/** +-=---------------------------------------------------------Mon Dec 8 16:47:52 2003-----------*
 * @method  CoedtwContainerRef::~CoedtwContainerRef        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:47:52 2003----------*/
CoedtwContainerRef::~CoedtwContainerRef(  )
{
   // nothing todo qt does it all for us.
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:36:28 2012-----------*
 * @method  CoedtwContainerRef::GetTabEditWidget            // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:36:28 2012-----------*/
QWidget* CoedtwContainerRef::GetTabEditWidget(QWidget* p_pqwParent)
{
   if (!m_pObjectListEditor)
   {
      m_pObjectListEditor = new CwmsObjectListEditorWidgetIf(p_pqwParent);
   }
   
   return m_pObjectListEditor;
}

/** +-=---------------------------------------------------------Mi 22. Aug 14:37:10 2012----------*
 * @method  CoedtwContainerRef::GetEditWidget               // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 14:37:10 2012----------*/
QWidget* CoedtwContainerRef::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqwParent = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqwParent);
   m_pqleEdit = new QLineEdit(pqwParent);
   m_pqleEdit->setReadOnly(true);
   pqLayout->addWidget(m_pqleEdit);
   
   if(!m_rpCdmValue->IsOwner())
   {
      m_pqpbChange = new QPushButton(pqwParent);
      m_pqpbChange->setText(tr("Auswählen"));
      connect( m_pqpbChange, SIGNAL(clicked()), this, SLOT(ChangeClickedSlot()));
      pqLayout->addWidget(m_pqpbChange);

      m_pqpbClear = new QPushButton(pqwParent);
      m_pqpbClear->setText(tr("Entfernen"));
      connect(m_pqpbClear, SIGNAL(clicked()), this, SLOT(ClearClickedSlot()));
      pqLayout->addWidget(m_pqpbClear);
   }
   else
   {
      m_pqleEdit->hide();
   }

   m_pqpbView = new QPushButton(pqwParent);
   m_pqpbView->setText(tr("Details"));
   connect( m_pqpbView, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
   pqLayout->addWidget(m_pqpbView);

   return pqwParent;
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:46:29 2012-----------*
 * @method  CoedtwContainerRef::SetValue                    // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Mo 5. Nov 11:46:29 2012-----------*/
void CoedtwContainerRef::SetValue(CdmValue* p_pCdmValue)
{
   if (CHKPTR(p_pCdmValue))
   {
      if (m_pqleEdit)
      {
         m_pqleEdit->setText(p_pCdmValue->GetDisplayString());
      }
      else if (m_pObjectListEditor)
      {
         CdmObjectContainer* pContainer = ((CdmValueContainerRef*)p_pCdmValue)->GetContainer();

         if (CHKPTR(pContainer))
         {

			 CwmsFormManager cManager;
			 CdmObject* pFormConfig = cManager.GeDefaultContainerForm(pContainer);

            // TODO: Check if the complete objectlist will be displayed if not you have to reload it here
            m_pObjectListEditor->SetContainer(pContainer);

			if (pFormConfig)
			{
				m_pObjectListEditor->SetFormConfiguration(pFormConfig);
			}

            m_pObjectListEditor->FillDialog();
         }
      }
   } 
}

void CoedtwContainerRef::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue))
    {

        if(m_pqleEdit)
        {
            m_pqleEdit->setText(m_rpCdmValue->GetDisplayString());
        }
        else if(m_pObjectListEditor)
        {
            CdmObjectContainer *pContainer = ((CdmValueContainerRef*)m_rpCdmValue)->GetContainer();

            if(CHKPTR(pContainer))
            {
                CwmsFormManager cManager;
                CdmObject* pFormConfig = cManager.GeDefaultContainerForm(pContainer);

                if (pFormConfig)
                {
                    m_pObjectListEditor->SetFormConfiguration(pFormConfig);
                }

                m_pObjectListEditor->FillDialog();
            }
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Wed Dec 10 16:52:30 2003----------*
 * @method  CoedtwContainerRef::ValueChangedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:30 2003---------*/
void CoedtwContainerRef::ValueChangedSlotByUser(  )
{
   // nothing to do here
}

/** +-=---------------------------------------------------------Thu Dec 11 13:14:43 2003----------*
 * @method  CoedtwContainerRef::ChangeClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wan to change the objectlistref.                 *
 *---------------------------------------------------------------Thu Dec 11 13:14:43 2003---------*/
void CoedtwContainerRef::ChangeClickedSlot(  )
{
   if(CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

      if(CHKPTR(pCdmMember))
      {
         CdmObjectContainer* pContainer = CwmsContainerSelectionIf::GetObjectContainer(m_rpCdmValue->GetSchemeId(), 
                                                                                  pCdmMember->GetClassReference(), 
                                                                                  nullptr);

         if(pContainer)
         {
            ((CdmValueContainerRef*)m_rpCdmValue)->SetValue(pContainer);
            SetValue(m_rpCdmValue);
         }
      }
   }
}

void CoedtwContainerRef::ClearClickedSlot()
{
   if(CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

      if(CHKPTR(pCdmMember))
      {
        ((CdmValueContainerRef*)m_rpCdmValue)->CdmValueLong::SetValue(0);
        SetValue(m_rpCdmValue);
      }
   }
}

/** +-=---------------------------------------------------------So 8. Jan 12:36:35 2006-----------*
 * @method  CoedtwContainerRef::EditClickedSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to view the obejctlist.                    *
 *----------------last changed: Wolfgang Graßhof----------------So 8. Jan 12:36:35 2006-----------*/
void CoedtwContainerRef::EditClickedSlot(  )
{
   if(CHKPTR(m_rpCdmValue))
   {
      CdmObjectContainer* pContainer = ((CdmValueContainerRef*)m_rpCdmValue)->GetContainer();

      if(pContainer)
      {
         CwmsObjectListEditorIf* pCwmsObjectListEditorIf = new CwmsObjectListEditorIf(pContainer, nullptr);
         const CdmClass* pCdmClass = pContainer->GetClass();

         if(CHKPTR(pCdmClass))
         {
            QMap<qint64, CdmMember*> qmMembers = pCdmClass->GetClassMemberMap();

            QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
            QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

            for(; qmIt != qmItEnd; ++qmIt)
            {
               CdmMember* pCdmMember = qmIt.value();

               if(pCdmMember)
               {
                  pCwmsObjectListEditorIf->AddColumn(pCdmMember->GetKeyname());
               }
            }
         }

         pCwmsObjectListEditorIf->FillDialog();
         pCwmsObjectListEditorIf->setWindowTitle(m_rpCdmValue->GetCaption());
         pCwmsObjectListEditorIf->exec();
         DELPTR(pCwmsObjectListEditorIf);
           
      }
      else
      {
         CdmMessageManager::critical(tr("Error in Editing Objectlist"), 
                               tr("No Objectlist choosen"));
      }
   }
}

/** +-=---------------------------------------------------------Fri Dec 12 10:35:57 2003----------*
 * @method  CoedtwContainerRef::SetReadOnly                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *---------------------------------------------------------------Fri Dec 12 10:35:57 2003---------*/
void CoedtwContainerRef::SetReadOnly(  )
{
   if (m_pqpbChange)
   {
      m_pqpbChange->hide();
   }

   if (m_pObjectListEditor)
   {
      m_pObjectListEditor->SetReadOnly(true);
   }
}

void CoedtwContainerRef::SetEditable()
{
    if(m_pqpbChange)
    {
       m_pqpbChange->show();
    }

    if (m_pObjectListEditor)
    {
       m_pObjectListEditor->SetReadOnly(false);
    }
}
