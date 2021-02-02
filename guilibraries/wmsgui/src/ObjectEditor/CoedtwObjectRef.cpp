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
#include <qlayout.h>
#include <qpushbutton.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmMember.h"
#include "CdmEnhancedQueryProxy.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmValueObjectRef.h"
#include "CdmClass.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsguiObjectEditorIf.h"
#include "CoedtwObjectRef.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "cwmsobjectchoicecombobox.h"


/** +-=---------------------------------------------------------Mi 22. Aug 10:59:51 2012----------*
 * @method  CoedtwObjectRef::CoedtwObjectRef                 // public                            *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Destructor of Class CoedtwObjectRef                                               *
 *----------------last changed: --------------------------------Mi 22. Aug 10:59:51 2012----------*/
CoedtwObjectRef::CoedtwObjectRef(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
  m_pqcbObjectChoice(nullptr),
  m_pqpbSelect(nullptr),
  m_pqpbEdit(nullptr),
  m_pqpbClear(nullptr),
  m_bProxyCreatedByThis(false),
  m_pqleObject(nullptr),
  m_bShowEditButton(true),
  m_pCwmsProxy(nullptr),
  m_pObjectEditor(nullptr)
{
   // nothing todo
}

CoedtwObjectRef::CoedtwObjectRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
   m_pqcbObjectChoice(nullptr),
   m_pqpbSelect(nullptr),
   m_pqpbEdit(nullptr),
   m_pqpbClear(nullptr),
   m_bProxyCreatedByThis(false),
   m_pqleObject(nullptr),
   m_bShowEditButton(true),
   m_pCwmsProxy(nullptr),
   m_pObjectEditor(nullptr)
{

}


/** +-=---------------------------------------------------------Mon Dec 8 16:48:21 2003-----------*
 * @method  CoedtwObjectRef::~CoedtwObjectRef                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *---------------------------------------------------------------Mon Dec 8 16:48:21 2003----------*/
CoedtwObjectRef::~CoedtwObjectRef(  )
{
   if (m_bProxyCreatedByThis)
   {
      DELPTR(m_pCwmsProxy);
   }
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:58:15 2012-----------*
 * @method  CoedtwObjectRef::SetProxy                        // public                            *
 * @return  void                                             //                                   *
 * @param   CdmEnhancedQueryProxy* p_pCwmsProxy              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 3. Okt 11:58:15 2012-----------*/
void CoedtwObjectRef::SetProxy(CdmEnhancedQueryProxy* p_pCwmsProxy)
{
   m_pCwmsProxy = p_pCwmsProxy;
}

void CoedtwObjectRef::SetProxy(QString p_qstrWql)
{
   m_pCwmsProxy = new CdmEnhancedQueryProxy();
   m_pCwmsProxy->CdmQueryModel::Execute(p_qstrWql);
   m_bProxyCreatedByThis = true;
}

/** +-=---------------------------------------------------------Mo 5. Nov 11:46:54 2012-----------*
 * @method  CoedtwObjectRef::GetTabEditWidget                // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Nov 11:46:54 2012-----------*/
QWidget* CoedtwObjectRef::GetTabEditWidget(QWidget* p_pqwParent)
{
   if (!m_pObjectEditor)
   {
      m_pObjectEditor = new CwmsObjectEditor(p_pqwParent);
      //m_pObjectEditor->DeactivateOwnerMode();
   }

   return m_pObjectEditor;
}

void CoedtwObjectRef::GetComboBoxEdit(QWidget* pqWidget, QHBoxLayout* pqLayout)
{
    m_pqcbObjectChoice = new CwmsObjectChoiceComboBox(pqWidget);

    if (m_pCwmsProxy)
    {
       m_pqcbObjectChoice->SetProxy(m_pCwmsProxy);
       m_pqcbObjectChoice->FillProxyData();
    }

    pqLayout->addWidget(m_pqcbObjectChoice);

    connect(m_pqcbObjectChoice,
            SIGNAL(activated(int)),
            this,
            SLOT(ValueChangedSlotByUser()));
}


void CoedtwObjectRef::GetComboBoxEdit(CdmObjectContainer* pContainer, QWidget* pqWidget, QHBoxLayout* pqLayout)
{
    if (m_qstrVisibleKeyname.isEmpty())
    {
       const CdmClass* pClass = pContainer->GetClass();

       if (CHKPTR(pClass))
       {
          const CdmMember* pMember = pClass->GetCaptionMember();

          if (pMember)
          {
             m_qstrVisibleKeyname = pMember->GetKeyname();
          }
       }
    }

    m_pqcbObjectChoice = new CwmsObjectChoiceComboBox(pqWidget);
    m_pqcbObjectChoice->SetContainerAndDisplayValue(pContainer,
                                                     m_qstrVisibleKeyname);

    if (m_pCwmsProxy)
    {
       m_pqcbObjectChoice->SetProxy(m_pCwmsProxy);
    }

    pqLayout->addWidget(m_pqcbObjectChoice);

    connect(m_pqcbObjectChoice,
            SIGNAL(activated(int)),
            this,
            SLOT(ValueChangedSlotByUser()));
}

void CoedtwObjectRef::GetSelectionEdit(QHBoxLayout* pqLayout, QWidget* pqWidget)
{
    m_pqleObject = new QLineEdit(pqWidget);
    m_pqleObject->setReadOnly(true);
    pqLayout->addWidget(m_pqleObject);

    m_pqpbSelect = new QPushButton(pqWidget);
    m_pqpbSelect->setText(tr("Auswählen"));
    connect(m_pqpbSelect, SIGNAL(clicked()),
            this, SLOT(ChooseClickedSlot()));
    pqLayout->addWidget(m_pqpbSelect);

    m_pqpbClear = new QPushButton(pqWidget);
    m_pqpbClear->setText(tr("Entfernen"));
    connect(m_pqpbClear, SIGNAL(clicked()), this, SLOT(ClearClickedSlot()));
    pqLayout->addWidget(m_pqpbClear);
}

QWidget* CoedtwObjectRef::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqWidget = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);

   if(CHKPTR(m_rpCdmValue))
   {
      CdmContainerManager* pCdmOLManager = m_rpCdmValue->GetContainerManager();

      if(CHKPTR(pCdmOLManager))
      {
         CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(m_qstrObjectList);

         if(pContainer && pContainer->CountObjectsOnDb() < 30)
         {
             GetComboBoxEdit(pContainer, pqWidget, pqLayout);
         }
         else if (m_pCwmsProxy)
         {
             GetComboBoxEdit(pqWidget, pqLayout);
         }
         else
         {
            pContainer = GetSingleObjectList();

            if(pContainer && pContainer->CountObjectsOnDb() < 30)
            {
                GetComboBoxEdit(pContainer, pqWidget, pqLayout);
            }
            else
            {
               GetSelectionEdit(pqLayout, pqWidget);
            }
         }
      }
   }
   
   if (m_bShowEditButton)
   {
      m_pqpbEdit = new QPushButton(pqWidget);
      m_pqpbEdit->setText(tr("Details"));

      connect(m_pqpbEdit, SIGNAL(clicked()), this, SLOT(EditClickedSlot()));
      pqLayout->addWidget(m_pqpbEdit);
   }

   return pqWidget;
}

/** +-=---------------------------------------------------------Wed Dec 10 16:50:38 2003----------*
 * @method  CoedtwObjectRef::SetValue                        // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                      //                                   *
 * @comment This method sets the value in the widget.                                             *
 *---------------------------------------------------------------Wed Dec 10 16:50:38 2003---------*/
void CoedtwObjectRef::SetValue(CdmValue* p_pCdmValue)
{
   if(p_pCdmValue)
   {
      if(m_pqleObject)
      {
         m_pqleObject->setText(p_pCdmValue->GetDisplayString());
      }
      else if (m_pqcbObjectChoice)
      {
         ((CdmValueObjectRef*)p_pCdmValue)->GetObject();
         m_pqcbObjectChoice->SetCurrentObjectId(((CdmValueObjectRef*)p_pCdmValue)->GetValue());
      }
      else if (m_pObjectEditor)
      {
         CdmObject* pCdmObject = ((CdmValueObjectRef*)p_pCdmValue)->GetObject();

         if (CHKPTR(pCdmObject))
         {
            m_pObjectEditor->SetObject(pCdmObject);
            m_pObjectEditor->FillObjectEditor();
         }
      }
   }
}

void CoedtwObjectRef::SetEventValueInTab(CdmValue *pCdmValue, CdmObject *pEventObject)
{
    if(pCdmValue)
    {
        if(m_pqleObject)
        {
            m_pqleObject->setText(pCdmValue->GetDisplayString());
        }
        else if (m_pqcbObjectChoice)
        {
            ((CdmValueObjectRef*)pCdmValue)->GetReferenceObjectFromEvent(pEventObject);
            m_pqcbObjectChoice->SetCurrentObjectId(((CdmValueObjectRef*)pCdmValue)->GetValue());
        }
        else if (m_pObjectEditor)
        {
            CdmObject *pCdmObject = ((CdmValueObjectRef*)pCdmValue)->GetReferenceObjectFromEvent(pEventObject);

            if (CHKPTR(pCdmObject))
            {
                m_pObjectEditor->SetObject(pCdmObject);
                m_pObjectEditor->FillObjectEditor();
            }
        }
    }
}

void CoedtwObjectRef::setEventClassValue()
{
    //not needed here
}

/** +-=---------------------------------------------------------Wed Dec 10 16:52:40 2003----------*
 * @method  CoedtwObjectRef::ValueChangedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *---------------------------------------------------------------Wed Dec 10 16:52:40 2003---------*/
void CoedtwObjectRef::ValueChangedSlotByUser()
{
   if(CHKPTR(m_rpCdmValue))
   {
      CdmObject* pCdmObject = m_pqcbObjectChoice->GetSelectedObject();
      ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(pCdmObject);
   }
   setEventClassValue();
}

/** +-=---------------------------------------------------------Do 19. Jan 20:19:21 2006----------*
 * @method  CoedtwObjectRef::EditClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to view the obejctlist.                    *
 *----------------last changed: Wolfgang Graßhof----------------Do 19. Jan 20:19:21 2006----------*/
void CoedtwObjectRef::EditClickedSlot()
{
   if(CHKPTR(m_rpCdmValue))
   {
      CdmObject* pCdmObject = ((CdmValueObjectRef*)m_rpCdmValue)->GetObject();

      if(pCdmObject)
      {
         CwmsguiObjectEditorIf* pCwmsObjectEditorIf = new CwmsguiObjectEditorIf(pCdmObject, nullptr);
         pCwmsObjectEditorIf->FillDialog();
         pCwmsObjectEditorIf->setWindowTitle(m_rpCdmValue->GetCaption());
         pCwmsObjectEditorIf->exec();
         delete pCwmsObjectEditorIf;
      }
      else
      {
         CdmMessageManager::information(tr("Kein Object ausgewählt"), 
                                  tr("Sie können kein Feld bearbeiten in dem kein Wert ausgewählt ist."));
      }
   }
}

/** +-=---------------------------------------------------------Mo 23. Jan 22:10:22 2006----------*
 * @method  CoedtwObjectRef::ChooseClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the choose button was clicked.                            *
 *----------------last changed: Wolfgang Graßhof----------------Mo 23. Jan 22:10:22 2006----------*/
void CoedtwObjectRef::ChooseClickedSlot()
{
   const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

   if (CHKPTR(pCdmMember))
   {
      long lClassId = pCdmMember->GetClassReference();
      CdmObjectContainer* pContainer = CwmsContainerSelectionIf::GetObjectContainer(pCdmMember->GetSchemeId(),
                                                                                    lClassId,
                                                                                    nullptr);

      if (pContainer) // can be nullptr if the user cancels the process
      {

          CdmObject* pCdmObject = nullptr;

            pCdmObject = CwmsObjectSelectionIf::GetObject(pContainer, nullptr, nullptr);

         if(pCdmObject)
         {
            ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(pCdmObject);
            m_pqleObject->setText(pCdmObject->GetCaption());
         }
      }
   }
}

void CoedtwObjectRef::ClearClickedSlot()
{
   if(CHKPTR(m_rpCdmValue))
   {
      const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

      if(CHKPTR(pCdmMember))
      {
          ((CdmValueObjectRef*)m_rpCdmValue)->SetValue(nullptr);
          m_pqleObject->setText("");
      }
   }
}

/** +-=---------------------------------------------------------Di 24. Jan 21:18:25 2006----------*
 * @method  CoedtwObjectRef::GetSingleObjectList             // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Di 24. Jan 21:18:25 2006----------*/
CdmObjectContainer* CoedtwObjectRef::GetSingleObjectList(  )
{
   CdmObjectContainer* pContainer = nullptr;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

      if(CHKPTR(pIdmDataAccess))
      {
         QMap<long, QString> qmObjectLists;
         const CdmMember* pCdmMember = m_rpCdmValue->GetMember();

         if (CHKPTR(pCdmMember))
         {
            long lClassId = pCdmMember->GetClassReference();

            if (lClassId > 0)
            {

                pIdmDataAccess->GetContainerList(pCdmMember->GetSchemeId(),
                                                 lClassId,
                                                 qmObjectLists);


                if(qmObjectLists.count() == 1)
                {
                   QMap<long, QString>::iterator qmIt = qmObjectLists.begin();
                   CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(pCdmMember->GetSchemeId());

                   if(CHKPTR(pContainerManager))
                   {
                      pContainer = pContainerManager->FindEmptyContainerById(qmIt.key());
                   }
                }
            }
         }
      }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Fri Dec 12 10:36:10 2003----------*
 * @method  CoedtwObjectRef::SetReadOnly                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                         *
 *---------------------------------------------------------------Fri Dec 12 10:36:10 2003---------*/
void CoedtwObjectRef::SetReadOnly(  )
{
   if (m_pqleObject)
   {
      m_pqleObject->show();
   }
   
   if (m_pqcbObjectChoice)
   {
      m_pqcbObjectChoice->setEnabled(false);
   }

   if (m_pObjectEditor)
   {
      m_pObjectEditor->SetReadOnly(true);
   }

   if(m_pqpbSelect)
   {
        m_pqpbSelect->hide();
   }

   if (m_pqpbEdit)
   {
        m_pqpbEdit->hide();
   }

   if (m_pqpbClear)
   {
        m_pqpbClear->hide();
   }
}

void CoedtwObjectRef::SetEditable()
{
   if (m_pqleObject)
   {
      m_pqleObject->hide();
   }

   if (m_pqcbObjectChoice)
   {
      m_pqcbObjectChoice->setEnabled(true);
   }

   if (m_pObjectEditor)
   {
      m_pObjectEditor->SetReadOnly(false);
   }

   if(m_pqpbSelect)
   {
        m_pqpbSelect->show();
   }

   if (m_pqpbEdit)
   {
        m_pqpbEdit->show();
   }

   if (m_pqpbClear)
   {
        m_pqpbClear->show();
   }
}

/** +-=---------------------------------------------------------Di 10. Jun 12:40:30 2008----------*
 * @method  CoedtwObjectRef::HideEditButton                  // public                            *
 * @return  void                                             //                                   *
 * @comment This method hides the edit button of the objectref.                                   *
 *----------------last changed: --------------------------------Di 10. Jun 12:40:30 2008----------*/
void CoedtwObjectRef::HideEditButton()
{
   m_bShowEditButton = false;
}

/** +-=---------------------------------------------------------Do 19. Jan 20:43:13 2006----------*
 * @method  CoedtwObjectRef::SetObjectList                   // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrObjectList                         //                                   *
 * @param   QString p_qstrVisibleKeyname                     //                                   *
 * @comment This method sets the objectlist source, in which the user can choose the object for the objectreferenece.*
 *----------------last changed: Wolfgang Graßhof----------------Do 19. Jan 20:43:13 2006----------*/
void CoedtwObjectRef::SetObjectList(  QString p_qstrObjectList, QString p_qstrVisibleKeyname )
{
   m_qstrObjectList = p_qstrObjectList;
   m_qstrVisibleKeyname = p_qstrVisibleKeyname;
}
